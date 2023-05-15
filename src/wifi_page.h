#ifndef INC_WIFI_PAGE_H_
#define INC_WIFI_PAGE_H_

const char wifi_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <meta charset="utf-8">
  <title>WiFi Config</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
  * {font-family: "Lucida Console"}
  body
  {
    display: grid;
    grid-template-columns: 1fr;
    background-color: #4a4a4a;
		color: white;
  }
	input
  {
    background-color: #666666;
    color: white;
    text-align: center;
    line-height: 1.5em;         
  }      
  input::placeholder
  {
    color: #A7A7A7;
  }
  h3
  {
    text-align: center;
  }
  .wifi-form {
    display: grid;
    grid-template-columns: [labels] auto [controls] 1fr;
    grid-auto-flow: row;
    grid-gap: .8em;
    padding: 1.2em;
  }
  .wifi-form > label  {
    grid-column: labels;
    grid-row: auto;
  }
  .wifi-form > input,
  .wifi-form > textarea {
    grid-column: controls;
    grid-row: auto;
    grid-auto-columns: minmax(100px, auto);
  }
  .send-b {
    margin-top: 20px;
    text-align: center;
  }
  </style>
  </head><body>
  <h3>Настройка сети</h3>
  <form class = "wifi-form" action="/wifi" method="post">
    <label for="ssid">SSID:</label>
    <input type="text" name="ssid" placeholder="WiFi_FREE">
    <label for="password">Password:</label>
    <input type="password" name="password" placeholder="*****">
    <label for="client">IP:</label>
    <input type="text" name="client" pattern="\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}" placeholder="192.168.1.100" value="%IP%">
    <label for="gateway">Gateway:</label>
    <input type="text" name="gateway" pattern="\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}" placeholder="192.168.1.1" value="%GATEWAY%">
    <label for="subnet">Subnet:</label>
    <input type="text" name="subnet" pattern="\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}" placeholder="255.255.255.0" value="%SUBNET%">
    <label for="dns">DNS:</label>
    <input type="text" name="dns" pattern="\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}" placeholder="192.168.1.1" value="%DNS%">
    <input class="send-b" type="submit" value="Сохранить">
  </form>
  <br><br><br><br>
  <form action="/wifi" method="post">
    <input type="hidden" name="reset" value="1">
    <input type="submit" value="Сброс настроек">
  </form>
  <br>
  Настройки по умолчанию:
  <br>
  Точка доступа: Termoplast
  <br>
  IP: 192.168.1.1
  <br>
</body></html>
)rawliteral";

#endif /* INC_WIFI_PAGE_H_ */