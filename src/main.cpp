#include "main.h"

const char *soft_ssid = "Termoplast";
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

void stmConfigToJSON(StaticJsonDocument<256> &data);

StatusMsgTypeDef statusMsg;
JobMsgTypeDef jobMsg;
StmConfigTypeDef stmConfig;

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

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

void getSTMConfig()
{
  commMsg.msg_id = WIFI_GET_STM_CONFIG;
  commMsg.comm = 0;
  commMsg.CS = calculateCS((uint8_t *)&commMsg, sizeof(commMsg) - 1);
  dataSend((uint8_t *)&commMsg, sizeof(commMsg));
}

void setHeating()
{
  commMsg.msg_id = WIFI_SET_HEATING;
  commMsg.comm = 0;
  commMsg.CS = calculateCS((uint8_t *)&commMsg, sizeof(commMsg) - 1);
  dataSend((uint8_t *)&commMsg, sizeof(commMsg));
}

void setStmConfig()
{
  stmConfig.start_msg0 = START_MSG0,
  stmConfig.start_msg1 = START_MSG1,
  stmConfig.control_id = WIFI_CONTROL_ID;
  stmConfig.msg_id = WIFI_SET_STM_CONFIG;
  stmConfig.CS = calculateCS((uint8_t *)&stmConfig, sizeof(stmConfig)-1);
  dataSend((uint8_t *)&stmConfig, sizeof(stmConfig));
}

void startJob(float _volume, uint32_t _cycles, uint32_t _time_hold)
{
  jobMsg.start_msg0 = START_MSG0,
  jobMsg.start_msg1 = START_MSG1,
  jobMsg.control_id = WIFI_CONTROL_ID;
  jobMsg.msg_id = WIFI_SET_JOB;
  jobMsg.comm = JOB_START;
  jobMsg.volume = _volume;
  jobMsg.cycles = _cycles;
  jobMsg.time_hold = _time_hold;
  jobMsg.CS = calculateCS((uint8_t *)&jobMsg, sizeof(jobMsg)-1);
  dataSend((uint8_t *)&jobMsg, sizeof(jobMsg));
}

void setJob(JOB_STATUS _comm)
{
  jobMsg.start_msg0 = START_MSG0,
  jobMsg.start_msg1 = START_MSG1,
  jobMsg.control_id = WIFI_CONTROL_ID;
  jobMsg.msg_id = WIFI_SET_JOB;
  jobMsg.comm = _comm;
  jobMsg.CS = calculateCS((uint8_t *)&jobMsg, sizeof(jobMsg)-1);
  dataSend((uint8_t *)&jobMsg, sizeof(jobMsg));
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
      else if (settDataIn[3] == WIFI_GET_STM_CONFIG && count_inbyte >= sizeof(StmConfigTypeDef))
      {
        memcpy(&stmConfig, settDataIn, sizeof(StmConfigTypeDef));
        count_inbyte = 0;
        StaticJsonDocument<256> data;
        stmConfigToJSON(data);
        String response;
        serializeJson(data, response);
        if (g_request != NULL) {
          g_request->send(http_200, "application/json", response);
        }
      }
    }
    else count_inbyte = 0;
  }
  else count_inbyte = 0;
  serial_busy = 0;  
}

void statusToJSON(StaticJsonDocument<512> &data)
{
  data["t1"] = statusMsg.temp1;
  data["t2"] = statusMsg.temp2;
  data["t3"] = statusMsg.temp3;
  data["c_cou"] = statusMsg.cycles_count;
  data["c_set"] = statusMsg.cycles_set;
  //data["sens"] = (uint16_t *)&statusMsg.sens;
  //data["err"] = (uint16_t *)&statusMsg.error;
}
void stmConfigToJSON(StaticJsonDocument<256> &data)
{
  data["u0"] = stmConfig.termConfig.volume_per_rev;
  data["u1"] = stmConfig.termConfig.motor1_speed;
  data["u2"] = stmConfig.termConfig.motor1_acc;
  data["u3"] = stmConfig.termConfig.motor2_speed;
  data["u4"] = stmConfig.termConfig.motor2_acc;
  data["u5"] = stmConfig.termConfig.temp1;
  data["u6"] = stmConfig.termConfig.temp2;
  data["u7"] = stmConfig.termConfig.temp3;
  data["u8"] = stmConfig.termConfig.Kp;
  data["u9"] = stmConfig.termConfig.Kp;
  data["u10"] = stmConfig.termConfig.Kp;
  data["u11"] = stmConfig.termConfig.bitParams.ind;
}

void tftDisplayUpdate()
{
  //if (loaded)
  //{
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
    /*tft.setFreeFont(&GlametrixBold12pt8b_rus);
    tft.drawString("Датчик 1", 5, 60, 1);
    tft.drawString("Датчик 2", 105, 60, 1);
    tft.drawString("Датчик 3", 195, 60, 1);*/
    
    tft.drawString((String)WiFi.RSSI(), 270, 2, 4);

    tft.setTextColor(TFT_GREENYELLOW, TFT_BLACK);
    static uint32_t cycles_count = 0;
    static uint32_t cycles_set = 0;
    if (statusMsg.cycles_count != cycles_count || statusMsg.cycles_set != cycles_set)
    {
      tft.fillRect(5, 35, 315, 28, TFT_BLACK);
      String str = "/korpus1.stl " + (String)statusMsg.cycles_count + "/" +(String)statusMsg.cycles_set;
      tft.drawString(str, 5, 35, 4);
      tft.fillRect(5, 65, 310, 20, TFT_GOLD);
      tft.fillRect(7, 67, 306, 16, TFT_BLACK);
      int32_t bar_size = map(statusMsg.cycles_count, 0, statusMsg.cycles_set, 0, 306);
      tft.fillRect(7, 67, bar_size, 16, TFT_ORANGE);
    }
    cycles_count = statusMsg.cycles_count;
    cycles_set = statusMsg.cycles_set;
    

    static float temp1 = 0;
    static float temp2 = 0;
    static float temp3 = 0;
    if (statusMsg.temp1 != temp1 || statusMsg.temp2 != temp2 || statusMsg.temp3 != temp3)
    tft.fillRect(5, 124, 312, 43, TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString(String(statusMsg.temp1, 0), 15, 124, 6);
    tft.drawString(String(statusMsg.temp2, 0), 120, 124, 6);
    tft.drawString(String(statusMsg.temp3, 0), 228, 124, 6);
    temp1 = statusMsg.temp1;
    temp2 = statusMsg.temp2;
    temp3 = statusMsg.temp3;

    ///table

    tft.drawRect(2, 95, 316, 75, TFT_DARKGREY);

    tft.drawLine(2, 120, 316, 120, TFT_DARKGREY);

    tft.drawLine(105, 95, 105, 169, TFT_DARKGREY);
    tft.drawLine(215, 95, 215, 169, TFT_DARKGREY);

    ////end table

    /*if (statusMsg.temp1 < 10)
      tft.drawString((String)statusMsg.temp1, 128, 55, 8);
    else if (statusMsg.temp1 >= 100)
      tft.drawString((String)statusMsg.temp1, 72, 55, 8);
    else
      tft.drawString((String)statusMsg.temp1, 100, 55, 8);*/
  //}
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
    tft.drawString((String)WiFi.localIP().toString(), 100, 2, 4);
  }
  else
  {
    WiFi.mode(WIFI_AP);

    WiFi.softAP(soft_ssid, soft_pass);
    delay(100);
    WiFi.softAPConfig(IP, Gateway, Subnet);
    String scr_ip = (String)IP[0] + "." + (String)IP[1] + "." + (String)IP[2] + "." + (String)IP[3];
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_SILVER, TFT_BLACK);
    tft.drawString(scr_ip, 100, 2, 4);
  }

  tft.setTextColor(TFT_GREENYELLOW, TFT_BLACK);
  tft.drawString("Sensor 1", 25, 98, 2);
  tft.drawString("Sensor 2", 135, 98, 2);
  tft.drawString("Sensor 3", 240, 98, 2);

  ///table

  tft.drawRect(2, 95, 316, 75, TFT_DARKGREY);

  tft.drawLine(2, 120, 316, 120, TFT_DARKGREY);

  tft.drawLine(105, 95, 105, 169, TFT_DARKGREY);
  tft.drawLine(215, 95, 215, 169, TFT_DARKGREY);

  ////end table

  //tft.drawString("/korpus1.stl 128/200", 5, 35, 4);
  tft.fillRect(5, 65, 310, 20, TFT_GOLD);
  tft.fillRect(7, 67, 306, 16, TFT_BLACK);
  //tft.fillRect(7, 67, 180, 16, TFT_ORANGE);

  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
  for (int i = 0; i < 100; i++)
  {
    statusMsg.temp1 = i;
    statusMsg.temp2 = i;
    statusMsg.temp3 = i;
    tftDisplayUpdate();
    delay(10);
  }
  statusMsg.temp1 = 0;
  statusMsg.temp2 = 0;
  statusMsg.temp3 = 0;
  tftDisplayUpdate();
  loaded = true;

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(http_200, cont_txt, main_html); });
  server.on("/wifi.html", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(http_200, cont_txt, wifi_html, processor); });
  server.on("/help.html", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(http_200, cont_txt, help_html); });
  server.on("/params.html", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(http_200, cont_txt, params_html); });
  server.on("/stats.html", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              // request->send_P(http_200, cont_txt, stats_html);
            });
  server.on("/update_e.html", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (request->authenticate(http_username, http_password))
              {
                request->send_P(http_200, cont_txt, update_esp);
                authenticated = true;
              }
              else
              {
                // Serial.println( "Unauthorized access." );
                return request->requestAuthentication();
              }
              // request->send_P(http_200, cont_txt, update_esp);
            });
  server.on("/update_stm.html", HTTP_GET, [](AsyncWebServerRequest *request)
            {
      if ( request->authenticate(http_username, http_password) )
      {
        request->send_P(http_200, cont_txt, update_stm);
        authenticated = true;
      }
      else
      {
        //Serial.println( "Unauthorized access." );
        return request->requestAuthentication();
      } });
  server.on("/manual.html", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(http_200, cont_txt, manual_html); });
  server.on("/wifi", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String inputMessage;

        if (request->hasParam("ssid", true)) {
            inputMessage = request->getParam("ssid", true)->value();
            p_ssid = inputMessage;

            inputMessage = request->getParam("password", true)->value();
            p_password = inputMessage;

            inputMessage = request->getParam("client", true)->value();
            s_client = inputMessage;

            inputMessage = request->getParam("gateway", true)->value();
            s_gateway = inputMessage;

            inputMessage = request->getParam("subnet", true)->value();
            s_subnet = inputMessage;

            inputMessage = request->getParam("dns", true)->value();
            s_dns = inputMessage;
        }
        request->send(http_200, cont_txt, reboot_html);
        config_saved = true;
        //Serial.println("");  Serial.print("WiFi connected to: "); Serial.println(p_ssid); Serial.println(p_password);
        //Serial.print("IP address: ");  Serial.println(WiFi.localIP());
        preferences.begin("my-pref", false);
        preferences.putBool("config_saved", config_saved);
        preferences.putString("ssid", p_ssid);
        preferences.putString("password", p_password);
        preferences.putString("client", s_client);
        preferences.putString("gateway", s_gateway);
        preferences.putString("subnet", s_subnet);
        preferences.putString("dns", s_dns);
        preferences.end();
        ESP.restart(); });
    server.on("/params.html", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send_P(http_200, cont_txt, params_html);
    });
  server.on(
      "/update", HTTP_POST, [](AsyncWebServerRequest *request)
      {
      if (authenticated) {
        request->send(http_200, "application/json", "{\"message\":\"Успешно\"}");
        delay(3000);
        ESP.restart();
      }
      else {
        request->send(401);
      } },
      [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
      {
        if (authenticated)
        {
          esp_flashing = 1;
          if (!index)
          {
            // Serial.printf( "UPLOAD: Started to receive '%s'.\n", filename.c_str() );
            String fname = "/" + filename;
            if ((String)esp_firmware != fname)
            {
              return request->send(http_200, "application/json", "{\"message\":\"Ошибка идентификатора\"}");
            }
            if (!Update.begin(UPDATE_SIZE_UNKNOWN))
            {
              Update.printError(Serial);
            }
          }
          // Serial.printf( "%i bytes received.\n", index );
          if (Update.write(data, len) != len)
          {
            Update.printError(Serial);
          }
          if (final)
          {
            if (Update.end(true))
            { // true to set the size to the current progress
              Serial.printf("Update Success: %u\nRebooting...\n", index);
            }
            else
            {
              Update.printError(Serial);
            }
          }
        }
        else
        {
          request->send(401);
        }
      });
  server.on("/updatestm", HTTP_POST, [](AsyncWebServerRequest *request)
    {
      if (authenticated) {
        request->send(http_200, "application/json", "{\"message\":\"Файл загружен\"}");
      }
      else {
        request->send(401);
      }
    },
      [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
      {
        if (authenticated)
        {
          if (!index)
          {
            SPIFFS.remove(stm_firmware);
            Serial.printf("UPLOAD: Started to receive '%s'.\n", filename.c_str());
            String fname = "/" + filename;
            if ((String)stm_firmware == fname)
            {
              fsUploadFile = SPIFFS.open(stm_firmware, "w");
            }
            else
              return request->send(http_200, "application/json", "{\"message\":\"Ошибка идентификатора\"}");
          }
          // Serial.printf( "%i bytes received.\n", index );
          if (fsUploadFile)
          {
            // Serial.printf( "%i bytes received.\n", index );
            fsUploadFile.write(data, len);
          }
          if (final)
          {
            if (fsUploadFile)
            {
              fsUploadFile.close();
              Serial.print(F("firmware size: "));
              Serial.println(index);
              stm_flashing = 1;
            }
          }
        }
        else
        {
          request->send(401);
          events.send("{\"message\":\"Не авторизован\"}", "flash", millis());
        }
      });
  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request)
            {
        //StaticJsonDocument<100> data;
        serial_busy = 1;
        if (request->hasParam("123"))
        {
            if(request->getParam("888")->value())
            {
                //beepCommSend();    
            }
        }
        else if (request->hasParam("234"))
        {
          //autoCommSend(STATUS_UPLOAD);
        }
        else
        {
          request->send(http_200, "application/json", "{\"message\":\"error\"}");
          //data["message"] = "No message parameter";
        }
        //g_request = request;
        request->send(http_200, "application/json", "{\"message\":\"ok\"}");
  });
  server.on("/manual", HTTP_GET, [](AsyncWebServerRequest *request)
            {        
        if (request->hasParam("comm"))
        {
          int val = request->getParam("comm")->value().toInt();
          if (val >= 0 && val < 5)
          {
            serial_busy = 1;
            //manualCommSend(static_cast<MOVE_COM>(val));
          }
        }
        else
        {
          request->send(http_200, "application/json", "{\"message\":\"error\"}");
        }
        request->send(http_200, "application/json", "{\"message\":\"ok\"}"); });
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
            {
      StaticJsonDocument<512> data;
      statusToJSON(data);
      String response;
      serializeJson(data, response);
      request->send(http_200, "application/json", response); });
  server.on("/sens", HTTP_GET, [](AsyncWebServerRequest *request)
            {
      StaticJsonDocument<64> data;
      //sensorsToJSON(data);
      String response;
      serializeJson(data, response);
      request->send(http_200, "application/json", response); });
  server.on("/stats", HTTP_GET, [](AsyncWebServerRequest *request)
            {
      StaticJsonDocument<128> data;
      //statsToJSON(data);
      String response;
      serializeJson(data, response);
      request->send(http_200, "application/json", response); });
  server.on("/param", HTTP_GET, [](AsyncWebServerRequest *request)
            {           
      if (request->hasParam("user_read"))
      {
        g_request = request;
        serial_busy = 1;
        getSTMConfig();
      }
      else request->send(http_200, "application/json", "{\"message\":\"Ошибка\"}"); });
  server.on("/param", HTTP_POST, [](AsyncWebServerRequest *request)
            {
      String inputMessage;
      int err = 0;
      if (request->hasParam("u0", true))
      {
        inputMessage = request->getParam("u0", true)->value();
        stmConfig.termConfig.volume_per_rev = inputMessage.toFloat();
        inputMessage = request->getParam("u1", true)->value();
        stmConfig.termConfig.motor1_speed = inputMessage.toInt();
        inputMessage = request->getParam("u2", true)->value();
        stmConfig.termConfig.motor1_acc = inputMessage.toInt();
        inputMessage = request->getParam("u3", true)->value();
        stmConfig.termConfig.motor2_speed = inputMessage.toInt();
        inputMessage = request->getParam("u4", true)->value();
        stmConfig.termConfig.motor2_acc = inputMessage.toInt();
        inputMessage = request->getParam("u5", true)->value();
        stmConfig.termConfig.temp1 = inputMessage.toInt();
        inputMessage = request->getParam("u6", true)->value();
        stmConfig.termConfig.temp2 = inputMessage.toInt();
        inputMessage = request->getParam("u7", true)->value();
        stmConfig.termConfig.temp3 = inputMessage.toInt();
        inputMessage = request->getParam("u8", true)->value();
        stmConfig.termConfig.Kp = inputMessage.toFloat();
        inputMessage = request->getParam("u9", true)->value();
        stmConfig.termConfig.Ki = inputMessage.toFloat();
        inputMessage = request->getParam("u10", true)->value();
        stmConfig.termConfig.Kd = inputMessage.toFloat();
        if (request->hasParam("u11", true))
        {
          inputMessage = request->getParam("u11", true)->value();
          stmConfig.termConfig.bitParams.ind = inputMessage.toInt();
        }
        else stmConfig.termConfig.bitParams.ind = 0;
        if (err == 0)
        {
          setStmConfig();
          request->send(http_200, "application/json", "{\"message\":\"Успешно\"}");
        }
        else request->send(http_200, "application/json", "{\"message\":\"Ошибка\"}");
      }
      else request->send(http_200, "application/json", "{\"message\":\"Ошибка\"}"); });
  server.on("/sett", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        StaticJsonDocument<100> data;
        if (request->hasParam("message", true))
        {
            data["message"] = request->getParam("message", true)->value();
        }
        else// if (request->hasParam("myFile"))
        {
            //data["message"] = "No message parameter";

            String response;
            //serializeJson(data, response);
            int params = request->params();
            for(int i=0;i<params;i++){
                AsyncWebParameter* p = request->getParam(i);
                response += p->name().c_str();
                response += "=\n=";
                response += p->value().c_str();
                response += "=\n=";
            }
            request->send(http_200, "application/json", response);
            return;
        }
        //else
        //{
        //    data["message"] = "No message parameter";
        //}
        String response;
        serializeJson(data, response);
        request->send(http_200, "application/json", response); });
  events.onConnect([](AsyncEventSourceClient *client)
                   {
      if(client->lastId()){
        Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
      }
      // send event with message "", id current millis
      // and set reconnect delay to 10 second
      client->send("sse start", NULL, millis(), 10000); });
  server.addHandler(&events);

  server.onNotFound(notFound);
  server.begin();

  SPIFFS.begin(true);

  esp_task_wdt_init(WDT_TIMEOUT, true);
  esp_task_wdt_add(NULL);

}




unsigned long lastTime = 0;  
unsigned long timerDelay = 1000;

void loop()
{
  esp_task_wdt_reset();
  if (!esp_flashing) {
    if (!stm_flashing) getSerialData();

    if (((millis() - lastTime) > timerDelay) && !stm_flashing)
    {      
      tftDisplayUpdate();
      // status update
      if (!serial_busy) {
        getStatusCommSend();
      }
      else {
        serial_busy = 0;
      }
      lastTime = millis();
    }
    if (stm_flashing)
    {
      if (!_alite_ )
      {
        esp_task_wdt_init(WDT_TIMEOUT, false);
        _alite_ = 1;
        alite_update();
      }
      flashStm(events, stm_flashing);
    }
  }
  else
  {
    if (!_alite_ )
    {
      esp_task_wdt_init(WDT_TIMEOUT, false);
      _alite_ = 1;
      alite_update();
    }
  }
  yield();
}
