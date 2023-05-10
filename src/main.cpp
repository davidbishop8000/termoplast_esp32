#include "main.h"

// const char *soft_ssid = "Shuttle";
const char *soft_pass = "atomic2023";

const uint8_t IP[4] = {192, 168, 1, 1};
const uint8_t Gateway[4] = {192, 168, 1, 1};
const uint8_t Subnet[4] = {255, 255, 255, 0};
const uint8_t DNS[4] = {192, 168, 1, 1};

const uint8_t IP_Client[4] = {192, 168, 1, 77};

String s_client;
String s_gateway;
String s_subnet;
String s_dns;

const char *http_username = "admin";
const char *http_password = "12345";
bool authenticated = true;

const String cont_txt = F("text/html");
const int http_200 = 200;

bool serial_busy = 0;

bool esp_flashing = 0;
bool stm_flashing = 0;
bool _alite_ = 0;

String p_ssid;
String p_password;
bool config_saved = false;
bool loaded = false;

TFT_eSPI tft = TFT_eSPI();

Preferences preferences;
DNSServer dnsServer;

AsyncWebServer server(80);

AsyncEventSource events("/events");

File fsUploadFile;

uint8_t settDataIn[100];

StatusMsgTypeDef statusMsg;

String processor(const String &var)
{
  if (var == "IP")
  {
    return (WiFi.localIP()).toString();
  }
  else if (var == "GATEWAY")
  {
    return (WiFi.gatewayIP()).toString();
  }
  else if (var == "SUBNET")
  {
    return (WiFi.subnetMask()).toString();
  }
  else if (var == "DNS")
  {
    return (WiFi.dnsIP()).toString();
  }
  return String();
}

CommMsgTypeDef commMsg = {
    .start_msg0 = START_MSG0,
    .start_msg1 = START_MSG1,
    .control_id = WIFI_CONTROL_ID,
    .msg_id = WIFI_NONE,
    .comm = 0,
    .r0 = 0,
    .r1 = 0,
    .CS = 0,
};

uint8_t calculateCS(uint8_t *msg, size_t msg_size)
{
  uint8_t cs = 0;
  for (int i = 0; i < msg_size; i++)
  {
    cs += msg[i];
  }
  return cs;
}

void alite_update()
{
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_RED);
  tft.drawString("Firmware", 5, 60, 4);
  tft.drawString("update", 5, 100, 4);
  tft.pushImage(150, 0, 170, 170, (uint16_t *)alite);
}

void dataSend(uint8_t *sdata, size_t size)
{
  Serial1.write(sdata, size);
}

void getStatusCommSend()
{
  commMsg.msg_id = WIFI_GET_STATUS;
  commMsg.comm = 0;
  commMsg.CS = calculateCS((uint8_t *)&commMsg, sizeof(commMsg) - 1);
  dataSend((uint8_t *)&commMsg, sizeof(commMsg));
}

AsyncWebServerRequest *g_request;

void getSerialData()
{
  static uint8_t count_inbyte = 0;
  while (Serial1.available() > 0)
  {
    settDataIn[count_inbyte] = Serial1.read();
    count_inbyte++;
    if (count_inbyte >= 100)
    {
      count_inbyte = 0;
      break;
    }
  }
  if (settDataIn[0] == START_MSG0)
  {
    if (settDataIn[1] == START_MSG1)
    {
      if (settDataIn[3] == WIFI_GET_STATUS && count_inbyte >= sizeof(StatusMsgTypeDef))
      {
        memcpy(&statusMsg, settDataIn, sizeof(StatusMsgTypeDef));
        count_inbyte = 0;
      }
    }
    else
    {
      // if (g_request != NULL) {
      //  g_request->send(http_200, "application/json", "{message: \"ok\"}");
      //}
    }
  }
  else
    count_inbyte = 0;
  serial_busy = 0;
}

void statusToJSON(StaticJsonDocument<512> &data)
{
  data["temp1"] = statusMsg.temp1;
  data["temp2"] = statusMsg.temp2;
  data["temp3"] = statusMsg.temp3;
}

void tftDisplayUpdate()
{
  if (loaded)
  {
    //tft.fillScreen(TFT_BLACK);
    int64_t sec = (esp_timer_get_time() / 1000ULL) / 1000ULL;
    int Hours = (sec / 3600UL);
    int Minutes = (sec % 3600UL) / 60UL;
    int Seconds = (sec % 3600UL) % 60UL;
    String sSec;
    String sMin;
    if (Seconds < 10)
      sSec = "0" + (String)Seconds;
    else
      sSec = (String)Seconds;
    if (Minutes < 10)
      sMin = "0" + (String)Minutes;
    else
      sMin = (String)Minutes;
    String times = (String)Hours + ":" + sMin + ":" + sSec;
    // tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
    tft.drawString(times, 0, 2, 4);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    // tft.setFreeFont(FFrus);
    // tft.drawString("Заряд"), 150, 2, GFXFF);
    tft.drawString((String)WiFi.RSSI(), 260, 2, 4);
    if (statusMsg.temp1 < 10)
      tft.drawString((String)statusMsg.temp1, 128, 55, 8);
    else if (statusMsg.temp1 >= 100)
      tft.drawString((String)statusMsg.temp1, 72, 55, 8);
    else
      tft.drawString((String)statusMsg.temp1, 100, 55, 8);
  }
}

void setup()
{

  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RX_GPIO, TX_GPIO);
  pinMode(BOOT_GPIO, OUTPUT); // boot_0
  digitalWrite(BOOT_GPIO, LOW);
  digitalWrite(RESET_GPIO, HIGH);
  pinMode(RESET_GPIO, OUTPUT); // reset

  pinMode(PIN_POWER_ON, OUTPUT);
  digitalWrite(PIN_POWER_ON, HIGH);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  // tft.pushImage(150, 0, 170, 170, (uint16_t *)alite);
  // delay(2000);

  ledcSetup(0, 2000, 8);
  ledcAttachPin(TFT_BL, 0);
  ledcWrite(0, 255);

  tft.setTextSize(1);
  tft.setTextColor(TFT_DARKGREY);
  tft.drawString("Loading...", 5, 100, 4);

  preferences.begin("my-pref", false);

  IPAddress _client;
  IPAddress _gateway;
  IPAddress _subnet;
  IPAddress _dns;

  if (preferences.isKey("config_saved"))
  {
    config_saved = preferences.getBool("config_saved", false);
    p_ssid = preferences.getString("ssid", "Sample_SSID");
    p_password = preferences.getString("password", "abcdefgh");
    _client.fromString(preferences.getString("client", "192.168.1.100"));
    _gateway.fromString(preferences.getString("gateway", "192.168.1.1"));
    _subnet.fromString(preferences.getString("subnet", "255.255.255.0"));
    _dns.fromString(preferences.getString("dns", "192.168.1.1"));
  }
  preferences.end();

  uint16_t tryCount = 0;
  WiFi.config(_client, _gateway, _subnet, _dns);
  WiFi.mode(WIFI_STA);
  char ssid_arr[20];
  char password_arr[20];
  p_ssid.toCharArray(ssid_arr, p_ssid.length() + 1);
  p_password.toCharArray(password_arr, p_password.length() + 1);
  // Serial.print("Received SSID: "); Serial.println(ssid_arr); Serial.print("And password: "); Serial.println(password_arr);
  Serial.println(_client);
  Serial.println(_gateway);
  Serial.println(_subnet);
  Serial.println(_dns);
  if (config_saved)
  {
    WiFi.begin(ssid_arr, password_arr);
    // WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED && tryCount < 10) // WiFi.waitForConnectResult()
    {
      tryCount++;
      Serial.print(".");
      delay(1000);
    }
    Serial.println();
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    WiFi.setAutoConnect(true);
    WiFi.persistent(true);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_SILVER, TFT_BLACK);
    tft.drawString((String)WiFi.localIP().toString(), 140, 6, 2);
  }
  else
  {
    WiFi.mode(WIFI_AP);
    // CapHandler = new CaptiveRequestHandler;
    // captiva = true;

    char soft_ssid[20];
    String st_ssid = "Termoplast";
    st_ssid.toCharArray(soft_ssid, st_ssid.length() + 1);
    WiFi.softAP(soft_ssid, soft_pass);
    delay(100);
    WiFi.softAPConfig(IP, Gateway, Subnet);
    String scr_ip = (String)IP[0] + "." + (String)IP[1] + "." + (String)IP[2] + "." + (String)IP[3];
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_SILVER, TFT_BLACK);
    tft.drawString(scr_ip, 140, 6, 2);
  }
  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  for (int i = 0; i < 100; i++)
  {
    statusMsg.temp1 = i;
    tftDisplayUpdate();
    delay(10);
  }
  statusMsg.temp1 = 0;
  tftDisplayUpdate();
  loaded = true;


}

void loop()
{
  //getStatusCommSend();
  getSerialData();
  delay(10);
  tftDisplayUpdate();
}
