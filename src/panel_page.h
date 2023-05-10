#ifndef INC_PANEL_PAGE_H_
#define INC_PANEL_PAGE_H_

const char main_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <link rel="shortcut icon"
    href="data:image/x-icon;base64, AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAAAAAAAAAAAAABAGFAAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQEBAgACACAQEBACACACAAEBAQICAAAgEBAQAiAAAgAAAAACAAAAICIiIAIAAAIAAAACAgAAICAAAAICIAAgAgAAAgICACACAAAgAgAgIAIAIgAAAAAAAAIAAAEAERAQIAAAAQAQABAgAAABAREAECAAAAEQEAAQAiIgAQARERGq7QAAVtsAAKq9AABWewAA/v0AAAb7AAD69QAA+nYAAPq2AAD21gAAz/8AAL7FAAB+3QAAfo0AAH5dAACGwAAA"
    type="image/x-icon" />
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width,initial-scale=1.0">
  <title>Shuttle control</title>
  <style>
    h1 {
      color: white;
      border-radius: 0.5em;
      margin: 3px;
      font-size: 1em;
      padding: 0.2em 0.2em;
      background: #810000;
      text-align: center
    }
    footer {
      background-color: #810000;
      color: white;
      margin: 3px;
      text-align: center;
      padding: 0.3em 0.3em;
      border-radius: 0.375em;
      font-size: 60%;
      text-align: center
    }
    body {
      /*display: grid;
        grid-template-columns: 1fr;*/
      background-color: #4a4a4a;
    }
    a {
      width: 80%;
      margin: 3px auto;
      padding: 10px;
      background-color: #666666;
      color: white;
      border-radius: 10px;
      text-align: center;
    }
    p {
      margin: 2px auto auto 2px;
      padding: 1px;
      padding-bottom: 4px;
      color: white;
    }
    .errors {
      color: rgb(223, 14, 14);
      font-size: small;
    }
    .warnings {
      color: rgb(219, 216, 9);
      font-size: small;
    }
    .stat {
      margin-right: 20px;
    }
    input {
      width: 70%;
      margin: 3px auto;
      padding: 10px;
      background-color: #666666;
      color: white;
      border-radius: 10px;
      text-align: center;
      font-size: medium;
    }
    input::placeholder {
      color: #A7A7A7;
    }
    button {
      width: 100%;
      height: 50px;
      margin: 3px auto;
      padding: 10px;
      color: white;
      border-radius: 10px;
      text-align: center;
      font-size: medium;
      box-shadow: 0 4px #3C3C3C;
    }
    button:hover {
      background-color: #6A6A6A
    }
    button:active {
      background-color: #761F1F;
      box-shadow: 0 2px #3C3C3C;
      transform: translateY(2px);
    }
    button.grey-u {
      background-color: #5c6169;
    }
    button:hover.grey-u {
      background-color: #4c4f55;
    }
    .grey {
      background-color: #7A7A7A;
    }
    button.red {
      background-color: #761F1F;
    }
    button:hover.red {
      background-color: #4e0a0a;
    }
    .grey-d {
      background-color: #7A7A7A;
      font-size: xx-large;
      padding: 0px;
    }
    .grid-container {
      grid-template-columns: 410px;
      display: grid;
      grid-gap: 0px;
      height: 100%;
      align-items: center;
      justify-content: center;
    }
    .item-status {
      margin-left: 15px;
      margin-right: 15px;
      display: grid;
      grid-template-columns: 1fr;
      grid-template-rows: 1fr 1fr;
      padding: 1px;
      border: 2px solid black;
      border-radius: 10px;
    }
    .item-errors {
      margin-top: -2px;
      margin-left: 15px;
      margin-right: 15px;
      display: grid;
      grid-template-columns: 1fr;
      grid-template-rows: 1fr 1fr;
      padding: 1px;
      border: 2px solid black;
      border-radius: 10px;
    }
    .item-help {
      margin-top: 2px;
      margin-left: 15px;
      margin-right: 15px;
      margin-bottom: 2px;
      display: grid;
      grid-template-columns: 1fr 1fr;
      grid-template-rows: 1fr;
      padding: 1px;
      border: 2px solid black;
      border-radius: 10px;
    }
    .item-uplquant {
      margin-top: -2px;
      margin-left: 15px;
      margin-right: 15px;
      display: grid;
      grid-template-columns: 2fr 1fr 1fr;
      grid-template-rows: 1fr;
      padding: 1px;
      border: 2px solid black;
      border-radius: 10px;
    }
    .item-0 {
      margin-left: 15px;
      margin-right: 15px;
      padding: 1px;
      border: 3px solid black;
      border-radius: 10px;
    }
    .item-1 {
      margin-left: 15px;
      margin-right: 15px;
      padding: 1px;
      border: 0px solid black;
      border-radius: 10px;
    }
    .item-2 {
      margin-left: 15px;
      margin-right: 15px;
      display: flex;
      padding: 4px;
      border: 2px solid black;
      border-radius: 10px;
    }
    .item-3 {
      display: flex;
      padding: 10px;
      border: 1px solid black;
      border-radius: 10px;
    }
    .item-4 {
      margin-top: -2px;
      margin-left: 15px;
      margin-right: 15px;
      display: grid;
      grid-template-columns: 1fr 1fr;
      grid-template-rows: 1fr 2fr;
      padding-left: 4px;
      padding-right: 4px;
      padding-bottom: 2px;
      border: 2px solid black;
      border-radius: 10px;
      justify-items: center;
    }
    .u_item-0 {
      grid-column: 1/3;
      grid-row: 1/1;
      padding: 0px;
    }
    .u_item-1 {
      width: 100%;
      grid-column: 1/2;
      grid-row: 2/2;
      margin-right: 5px;
    }
    .u_item-2 {
      width: 100%;
      grid-column: 2/3;
      grid-row: 2/2;
      margin-left: 5px;
    }
    .upl_item {
      margin-right: 5px;
    }
    .down_item {
      margin-left: 5px;
    }
    .error {
      border-color: red;
    }
    .error::placeholder {
      color: red;
    }
    *{
      font-family: "Lucida Console";
    }
  </style>
</head>
<body>
  <h1 id="conn">offline</h1>
  <div class="grid-container">
    <div class="item-status">
      <div>
        <p>Заряд: <span class="stat" id="charge">--</span>
          Режим: <span class="stat" id="mode">--</span>
          Сигнал: <span id="signal">--</span></p>
      </div>
      <div>
        <p>Статус: <span id="status">--</span></p>
      </div>
    </div>

    <div class="item-errors" id="block_errors" style="display: none">
      <div>
        <p class="errors"><span id="errors"></span></p>
      </div>
      <div>
        <p class="warnings"><span id="warnings"></span></p>
      </div>
    </div>    
    <div class="item-1">
      <button class="grey b100" value="beep=1">Поиск шаттла</button>
    </div>
    <div class="item-2">
      <div class="upl_item">
        <button class="grey-u" value="upload=1">Загрузка &#8593;</button>
        <button class="grey-u" value="long_upload=1">Прод.загрузка &#8657;</button>
      </div>
      <div class="down_item">
        <button class="grey-u" value="download=1">Выгрузка &#8595;</button>
        <button class="grey-u" value="long_download=1">Прод.выгрузка &#8659;</button>
      </div>
    </div>
    <div class="item-4">
      <div class="u_item-0">
        <p>&#9484;&#9472;&#9472;&#9472;&#9472;Уплотнение&#9472;&#9472;&#9472;&#9472;&#9488;</p>
      </div>
      <div class="u_item-1">
        <button class="grey" value="compact_b=1">&#9660; назад</button>
      </div>
      <div class="u_item-2">
        <button class="grey" value="compact_f=1">вперед &#9650;</button>
      </div>
    </div>
    <div class="item-uplquant">
      <p>Выгрузить заданное кол-во:</p>
      <input type="number" name="" id="input" min="1" placeholder="--">
      <button class="grey-d" id="btn">&#9654;</button>
    </div>
    <div class="item-1">
      <button class="grey" value="go_home=1">Вернуться назад &#9660;</button>
    </div>
    <div class="item-1">
      <button class="grey" value="go_away=1">Отъехать от края &#9650;</button>
    </div>
    <div class="item-1">
      <button class="grey" value="get_pallets=1">Подсчет паллет &#8593;</button>
    </div>
    <div class="item-1">
      <button class="red" id="manual" onclick="window.location.href = 'manual.html';" color="red">Ручной режим</button>
    </div>
    <div class="item-1">
      <button class="grey" value="reset=1">Сброс ошибок &#8855;</button>
    </div>
    <div class="item-help">
      <a href="battery.html">Батарея</a>
      <a href="sensors.html">Датчики</a>
      <a href="diagnostic.html">Диагностика</a>
      <a href="params.html">Параметры</a>
    </div>
    <div class="item-help">
      <a href="help.html">Помощь</a>
      <a href="wifi.html">Настройка сети</a>
    </div>
  </div>
  <script>
    var button = document.querySelectorAll(('button'));
    let timer_conn = setTimeout(offline, 5000);
    function offline() {
      document.getElementById("conn").style.backgroundColor="#810000";
      document.getElementById("conn").innerHTML = "offline";
    }
    for (var i = 0; i < button.length; i++) {
      if (button[i].id != 'btn' && button[i].id != 'manual') {
        button[i].addEventListener('click', send_m, false);
      }
    }
    async function send_m() {
      try {
        const response = await fetch(`control?${this.value}`)
        if (response.ok) {
          const result = await response.json();
          console.log(`control?${this.value}`);
        }
      } catch (e) {
        console.log(e);
      }
    }
    const btn = document.querySelector('#btn');
    const input = document.querySelector('#input');
    btn.addEventListener('click', sendGet);
    async function sendGet() {
      if (input.value) {
        try {
          input.classList.remove('error');
          const response = await fetch(`control?pallet_quant=${input.value}`);
          if (response.ok) {
            const result = await response.json();
            console.log(`control?pallet_quant=${input.value}`);
          }
        } catch (e) {
          console.log(e);
        }
      } else {
        input.classList.add('error');
      }
    }
    if (!!window.EventSource) {
      var source = new EventSource('/events');
      source.addEventListener('open', function (e) {
        console.log("Events Connected");
      }, false);
      source.addEventListener('error', function (e) {
        if (e.target.readyState != EventSource.OPEN) {
          console.log("Events Disconnected");
        }
      }, false);
      source.addEventListener('message', function (e) {
        console.log("message", e.data);
      }, false);
      source.addEventListener('status', function (e) {
        clearTimeout(timer_conn);
        timer_conn = setTimeout(offline, 5000);
        document.getElementById("conn").style.backgroundColor = "blue";
        document.getElementById("conn").innerHTML = "online";
        console.log("status_data ", e.data);
        //const json = e.data.json();
        const obj = JSON.parse(e.data);
        console.log("status_parse ", obj.charge, obj.status, obj.signal, obj.mode, obj.quant, obj.downl, obj.size, obj.err, obj.warn);
        //document.getElementById("charge").innerHTML = e.data;
        document.getElementById("charge").innerHTML = obj.charge+"%";
        let str_mode;
        if (obj.mode == 1) str_mode = "FIFO";
        else str_mode = "LIFO";
        document.getElementById("mode").innerHTML = str_mode;
        document.getElementById("signal").innerHTML = obj.signal;
        document.getElementById("status").innerHTML = obj.status;
        if (obj.status == "Выгрузка" && obj.downl > 0) document.getElementById("input").value = obj.downl;
        if (obj.err[0] == "Нет" && obj.warn[0] == "Нет") document.getElementById("block_errors").style.display = 'none';
        else {
          document.getElementById("block_errors").style.display = 'block';
          if (obj.err[0] != "Нет") {
            let er = "";
            for (let i=0; i < obj.err.length; i++) {
              er += String(obj.err[i]);
              if (i<obj.err.length-1) er += ", ";
            }
            document.getElementById("errors").innerHTML =er;
          }
          else document.getElementById("errors").innerHTML = "";
          if (obj.warn[0] != "Нет") {
            let wr = "";
            for (let i=0; i < obj.warn.length; i++) {
              wr += String(obj.warn[i]);
              if (i<obj.warn.length-1) wr += ", ";
            }
            document.getElementById("warnings").innerHTML = wr;
          }
          else document.getElementById("warnings").innerHTML = "";
        }
      }, false);
    }
  </script>
  <footer>&copy;skynet</footer>
</body>
</html>
)rawliteral";

#endif /* INC_PANEL_PAGE_H_ */