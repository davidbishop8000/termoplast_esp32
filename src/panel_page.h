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
  <title>Сontrol</title>
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
    .item {
      border: 2px solid black;
      border-radius: 10px;
      grid-template-columns: auto 1fr;
      margin-top: -2px;
      margin-left: 15px;
      margin-right: 15px;
      display: grid;
      grid-template-rows: 1fr;
      padding: 1px;
      border: 2px solid black;
      border-radius: 10px;
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
    .item-temp {
      margin-top: -2px;
      margin-left: 15px;
      margin-right: 15px;
      display: grid;
      grid-template-columns: 1fr 1fr 1fr;
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
	
	
	.black-frame {
  padding: 3px;
  margin: 1px;
  border-radius: 5px;
  border: 1px solid silver;
}

.centered {
  text-align: center;
}

.analogdisplay-day {
  --bg-color: rgba(0, 0, 0, 0);
  --digit-color: black;
  --with-gradient: true;
  --display-background-gradient-from: LightGrey;
  --display-background-gradient-to: white; /* used if --withGradient: false */
  --display-line-color: rgba(255, 255, 255, 0.5);
  --label-fill-color: rgba(255, 255, 255, 0.5);
  --with-display-shadow: true;
  --shadow-color: rgba(0, 0, 0, 0.75);
  --outline-color: DarkGrey;
  --major-tick-color: black;
  --minor-tick-color: black;
  --value-color: grey;
  --value-outline-color: black;
  --value-nb-decimal: 1;
  --hand-color: red;
  --hand-outline-color: black;
  --with-hand-shadow: true;
  --knob-color: DarkGrey;
  --knob-outline-color: black;
  --font: Arial;
  --value-font-size-factor: 1;
}

direction-display .analogdisplay-day {
  --value-nb-decimal: 0;
}

.analogdisplay-night {
  --bg-color: rgba(0, 0, 0, 0);
  --digit-color: cyan;
  --with-gradient: true;
  --display-background-gradient-from: DarkGrey; /* used if --withGradient: true */
  --display-background-gradient-to: black;
  --display-line-color: rgba(255, 255, 255, 0.5);
  --label-fill-color: red;
  --with-display-shadow: true;
  --shadow-color: black;
  --outline-color: DarkGrey;
  --major-tick-color: red;
  --minor-tick-color: red;
  --value-color: rgb(255, 255, 255);
  --value-outline-color: black;
  --value-nb-decimal: 1;
  --hand-color: rgba(204, 255, 0, 0.4);
  --hand-outline-color: red;
  --with-hand-shadow: true;
  --knob-color: #dd1010;
  --knob-outline-color: rgb(66, 8, 8);
  --font: Arial;
  --value-font-size-factor: 1;
}

direction-display .analogdisplay-night {
  --value-nb-decimal: 0;
}

/* Monochrome, cyan */
.analogdisplay-monochrome-cyan {
  --bg-color: rgba(0, 0, 0, 0);
  --digit-color: cyan;
  --with-gradient: false;
  --display-background-gradient-from: LightGrey; /* used if --withGradient: true */
  --display-background-gradient-to: rgba(0, 0, 0, 0);
  --display-line-color: rgba(0, 255, 255, 0.5);
  --label-fill-color: rgba(0, 0, 0, 0);
  --with-display-shadow: false;
  --shadow-color: rgba(0, 0, 0, 0.75);
  --outline-color: cyan;
  --major-tick-color: cyan;
  --minor-tick-color: cyan;
  --value-color: cyan;
  --value-outline-color: cyan;
  --value-nb-decimal: 1;
  --hand-color: rgba(0, 0, 0, 0);
  --hand-outline-color: cyan;
  --with-hand-shadow: false;
  --knob-color: cyan;
  --knob-outline-color: cyan;
  --font: Arial;
  --value-font-size-factor: 1;
}

.analogdisplay-monochrome-orange {
  --bg-color: rgba(0, 0, 0, 0);
  --digit-color: orange;
  --with-gradient: false;
  --display-background-gradient-from: undefined; /* used if --withGradient: true */
  --display-background-gradient-to: black;
  --display-line-color: rgba(255, 165, 0, 0.5); /* orange */
  --label-fill-color: rgba(255, 255, 255, 0);
  --with-display-shadow: false;
  --shadow-color: black;
  --outline-color: orange;
  --major-tick-color: orange;
  --minor-tick-color: orange;
  --value-color: orange;
  --value-outline-color: orange;
  --value-nb-decimal: 1;
  --hand-color: rgba(0, 0, 0, 0);
  --hand-outline-color: orange;
  --with-hand-shadow: false;
  --knob-color: orange;
  --knob-outline-color: orange;
  --index-color: orange; /* Compass rose index */
  --outlined-port-starboard: true;
  --font: Arial;
  --value-font-size-factor: 1;
}

/* Day, flat gray */
.analogdisplay-flat-gray {
  --bg-color: rgba(255, 255, 255, 0);
  --digit-color: grey;
  --with-gradient: true;
  --display-background-gradient-from: LightGrey;
  --display-background-gradient-to: white; /* used if --withGradient: false */
  --display-line-color: rgba(0, 0, 0, 0.5);
  --label-fill-color: rgba(255, 255, 255, 0.5);
  --with-display-shadow: false;
  --shadow-color: rgba(0, 0, 0, 0.75);
  --outline-color: DarkGrey;
  --major-tick-color: grey;
  --minor-tick-color: grey;
  --value-color: grey;
  --value-outline-color: black;
  --value-nb-decimal: 1;
  --hand-color: red;
  --hand-outline-color: grey;
  --with-hand-shadow: true;
  --knob-color: DarkGrey;
  --knob-outline-color: black;
  --font: Arial;
  --value-font-size-factor: 1;
}

direction-display
  .analogdisplay-monochrome-cyan
  .analogdisplay-monochrome-orange
  .analogdisplay-flat-gray {
  --value-nb-decimal: 0;
}

analog-display .analog-for-prmsl {
  /* Default is 1 */
  --value-font-size-factor: 0.75;
}
	
	
	
  </style>
</head>
<body>
  <h1 id="conn">offline</h1>
  <div class="grid-container">
    <div class="item-status">
      <div>
        <p>Сигнал: <span id="signal">--</span></p>
      </div>
      <div>
        <p>Статус: <span id="status">--</span></p>
      </div>
    </div>

    <div class="item-errors" id="block_errors" style="display: none">
      <div>
        <p class="errors"><span id="errors"></span></p>
      </div>
    </div>
    <div class="item-temp">
        <analog-display id="temp1" class="analogdisplay-night" title="Hum" id="hum-01" min-value="0" max-value="290" value="0" major-ticks="40" minor-ticks="10" with-border="true" overlap="50" digital-data-len="3" digital-data-val="0" width="120" height="120"></analog-display>
        <analog-display id="temp2" class="analogdisplay-night" title="Hum" id="hum-02" min-value="0" max-value="290" value="0" major-ticks="40" minor-ticks="10" with-border="true" overlap="50" digital-data-len="3" digital-data-val="0" width="120" height="120"></analog-display>
        <analog-display id="temp3" class="analogdisplay-night" title="Hum" id="hum-03" min-value="0" max-value="290" value="0" major-ticks="40" minor-ticks="10" with-border="true" overlap="50" digital-data-len="3" digital-data-val="0" width="120" height="120"></analog-display>
	</div>
  <div class="item">
    <p>Объем:</p>
    <input type="text" name="u0" id="u0" pattern="[0-9]{1}\.\d{0,1}" placeholder="1.0">

    <p>Время форм.:</p>
    <input type="text" name="u1" id="u1" pattern="[0-9]{1,3}" placeholder="100">
  </div>
    <div class="item-uplquant">
      
      <p>Кол-во деталей:</p>
      <input type="number" name="" id="input" min="1" placeholder="--">
      <button class="grey-d" id="btn">&#9654;</button>
    </div>
    <br><br><br>
    <div class="item-1">
      <button class="red" id="manual" onclick="window.location.href = 'manual.html';" color="red">Ручное управление</button>
    </div>
    <div class="item-help">
      <a href="sensors.html">Датчики</a>
      <a href="diag.html">Диагностика</a>
      <a href="job.html">Задание</a>
      <a href="params.html">Параметры</a>
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
    const volume =  document.getElementById(`u0`);
    const press_time =  document.getElementById(`u1`);
    btn.addEventListener('click', sendGet);
    async function sendGet() {
      if (input.value) {
        try {
          input.classList.remove('error');
          const response = await fetch(`control?quant=${input.value}&vol=${volume.value}&time=${press_time.value}`);
          if (response.ok) {
            const result = await response.json();
            console.log(`control?quant=${input.value}`);
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
        console.log("status_parse ", obj.status, obj.signal, obj.t1, obj.t2, obj.t3, obj.err, obj.warn);

        const temp1 = document.getElementById("temp1");
        const temp2 = document.getElementById("temp2");
        const temp3 = document.getElementById("temp3");

        temp1.value = obj.t1;
				temp1.digitalDataVal = obj.t1;
				temp2.value = obj.t2;
        temp2.digitalDataVal = obj.t2;
        temp3.value = obj.t3;
        temp3.digitalDataVal = obj.t3;

        document.getElementById("signal").innerHTML = obj.signal;
        document.getElementById("status").innerHTML = obj.status;
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



    const analogVerbose = false;
const ANALOG_TAG_NAME = "analog-display";

const defaultAnalogDisplayColorConfig = {
  bgColor: "rgba(0, 0, 0, 0)" /* transparent, 'white', */,
  digitColor: "black",
  withGradient: true,
  displayBackgroundGradient: {
    from: "LightGrey",
    to: "white"
  },
  displayLineColor: "rgba(0, 0, 0, 0.5)",
  labelFillColor: "rgba(255, 255, 255, 0.5)",
  withDisplayShadow: true,
  shadowColor: "rgba(0, 0, 0, 0.75)",
  outlineColor: "DarkGrey",
  majorTickColor: "black",
  minorTickColor: "black",
  valueColor: "grey",
  valueOutlineColor: "black",
  valueNbDecimal: 1,
  handColor: "red", // 'rgba(0, 0, 100, 0.25)',
  handOutlineColor: "black",
  withHandShadow: true,
  knobColor: "DarkGrey",
  knobOutlineColor: "black",
  font: "Arial" /* 'Source Code Pro' */,
  valueFontSizeFactor: 1
};

/* global HTMLElement */
class AnalogDisplay extends HTMLElement {
  // WIP

  static get observedAttributes() {
    return [
      "width", // Integer. Canvas width
      "height", // Integer. Canvas height
      "major-ticks", // Float. value between major ticks (those with labels)
      "minor-ticks", // Float. value between minor ticks
      "min-value", // Float. Min value. Default 0
      "max-value", // Float. Max value.
      "overlap", // Integer. Display overlap in degrees. Default 0.
      "with-min-max", // Boolean, default false
      "with-digits", // Boolean, default true. Index Values for major-ticks
      "with-border", // Boolean, default true
      "label", // String. Ignored if digital-data-* are provided.
      "digital-data-len", // Integer, optional, to display instead of label, like log value along with BSP. Number of characters to display
      "digital-data-val", // Float, optional. Must be present idf the above exists.
      "value" // Float. Value to display
    ];
  }

  constructor() {
    super();
    this._shadowRoot = this.attachShadow({ mode: "open" }); // 'open' means it is accessible from external JavaScript.
    // create and append a <canvas>
    this.canvas = document.createElement("canvas");
    this.shadowRoot.appendChild(this.canvas);

    // Default values
    this._value = 0;
    this._width = 150;
    this._height = 150;
    this._major_ticks = 10;
    this._minor_ticks = 1;
    this._min_value = 0.0;
    this._max_value = 1.0;
    this._overlap = 0;
    this._with_min_max = false;
    this._with_digits = true;
    this._with_border = true;
    this._label = undefined;
    this._digital_data_len = undefined;
    this._digital_data_val = undefined;

    this.miniVal = 10000000;
    this.maxiVal = -10000000;

    this._previousClassName = "";
    this.analogDisplayColorConfig = defaultAnalogDisplayColorConfig; // Init

    if (analogVerbose) {
      console.log("Data in Constructor:", this._value);
    }
  }

  // Called whenever the custom element is inserted into the DOM.
  connectedCallback() {
    if (analogVerbose) {
      console.log("connectedCallback invoked, 'value' is [", this.value, "]");
    }
  }

  // Called whenever the custom element is removed from the DOM.
  disconnectedCallback() {
    if (analogVerbose) {
      console.log("disconnectedCallback invoked");
    }
  }

  // Called whenever an attribute is added, removed or updated.
  // Only attributes listed in the observedAttributes property are affected.
  attributeChangedCallback(attrName, oldVal, newVal) {
    if (analogVerbose) {
      console.log(
        "attributeChangedCallback invoked on " +
        attrName +
        " from " +
        oldVal +
        " to " +
        newVal
      );
    }
    switch (attrName) {
      case "value":
        this._value = parseFloat(newVal);
        this.miniVal = Math.min(
          Math.max(this._min_value, this._value),
          this.miniVal
        );
        this.maxiVal = Math.max(
          Math.min(this._max_value, this._value),
          this.maxiVal
        );
        break;
      case "width":
        this._width = parseInt(newVal);
        break;
      case "height":
        this._height = parseInt(newVal);
        break;
      case "major-ticks":
        this._major_ticks = parseFloat(newVal);
        break;
      case "minor-ticks":
        this._minor_ticks = parseFloat(newVal);
        break;
      case "min-value":
        this._min_value = parseFloat(newVal);
        break;
      case "max-value":
        this._max_value = parseFloat(newVal);
        break;
      case "overlap":
        this._overlap = parseInt(newVal);
        break;
      case "with-digits":
        this._with_digits = "true" === newVal;
        break;
      case "with-border":
        this._with_border = "true" === newVal;
        break;
      case "with-min-max":
        this._with_min_max = "true" === newVal;
        break;
      case "label":
        this._label = newVal;
        break;
      case "digital-data-len":
        this._digital_data_len = parseInt(newVal);
        break;
      case "digital-data-val":
        this._digital_data_val = parseFloat(newVal);
        break;
      default:
        break;
    }
    this.repaint();
  }

  // Called whenever the custom element has been moved into a new document.
  adoptedCallback() {
    if (analogVerbose) {
      console.log("adoptedCallback invoked");
    }
  }

  set value(option) {
    this.setAttribute("value", option);
    if (analogVerbose) {
      console.log(">> Value option:", option);
    }
    //	this.repaint();
  }
  set width(val) {
    this.setAttribute("width", val);
  }
  set height(val) {
    this.setAttribute("height", val);
  }
  set majorTicks(val) {
    this.setAttribute("major-ticks", val);
  }
  set minorTicks(val) {
    this.setAttribute("minor-ticks", val);
  }
  set withMinMax(val) {
    this.setAttribute("with-min-max", val);
  }
  set withDigits(val) {
    this.setAttribute("with-digits", val);
  }
  set withBorder(val) {
    this.setAttribute("with-border", val);
  }
  set overlap(val) {
    this.setAttribute("overlap", val);
  }
  set minValue(val) {
    this.setAttribute("min-value", val);
  }
  set maxValue(val) {
    this.setAttribute("max-value", val);
  }
  set label(val) {
    this.setAttribute("label", val);
  }
  set digitalDataLen(val) {
    this.setAttribute("digital-data-len", val);
  }
  set digitalDataVal(val) {
    this.setAttribute("digital-data-val", val);
  }
  set shadowRoot(val) {
    this._shadowRoot = val;
  }

  get value() {
    return this._value;
  }
  get width() {
    return this._width;
  }
  get height() {
    return this._height;
  }
  get minorTicks() {
    return this._minor_ticks;
  }
  get majorTicks() {
    return this._major_ticks;
  }
  get withMinMax() {
    return this._with_min_max;
  }
  get withDigits() {
    return this._with_digits;
  }
  get withBorder() {
    return this._with_border;
  }
  get minValue() {
    return this._min_value;
  }
  get maxValue() {
    return this._max_value;
  }
  get overlap() {
    return this._overlap;
  }
  get label() {
    return this._label;
  }
  get digitalDataLen() {
    return this._digital_data_len;
  }
  get digitalDataVal() {
    return this._digital_data_val;
  }
  get shadowRoot() {
    return this._shadowRoot;
  }

  // Component methods
  repaint() {
    this.drawDisplay(this._value);
  }

  getColorConfig(classNames) {
    let colorConfig = defaultAnalogDisplayColorConfig;
    let classes = classNames.split(" ");
    for (let cls = 0; cls < classes.length; cls++) {
      let className = classes[cls];
      for (let s = 0; s < document.styleSheets.length; s++) {
        //		console.log("Walking though ", document.styleSheets[s]);
        for (
          let r = 0;
          document.styleSheets[s].cssRules !== null &&
          r < document.styleSheets[s].cssRules.length;
          r++
        ) {
          let selector = document.styleSheets[s].cssRules[r].selectorText;
          //			console.log(">>> ", selector);
          if (
            selector !== undefined &&
            (selector === "." + className ||
             (selector.indexOf("." + className) > -1 &&
              selector.indexOf(ANALOG_TAG_NAME) > -1))
          ) {
            // Cases like "tag-name .className"
            //				console.log("  >>> Found it! [%s]", selector);
            let cssText = document.styleSheets[s].cssRules[r].style.cssText;
            let cssTextElems = cssText.split(";");
            cssTextElems.forEach(function(elem) {
              if (elem.trim().length > 0) {
                let keyValPair = elem.split(":");
                let key = keyValPair[0].trim();
                let value = keyValPair[1].trim();
                switch (key) {
                  case "--bg-color":
                    colorConfig.bgColor = value;
                    break;
                  case "--digit-color":
                    colorConfig.digitColor = value;
                    break;
                  case "--with-gradient":
                    colorConfig.withGradient = value === "true";
                    break;
                  case "--display-background-gradient-from":
                    colorConfig.displayBackgroundGradient.from = value;
                    break;
                  case "--display-background-gradient-to":
                    colorConfig.displayBackgroundGradient.to = value;
                    break;
                  case "--display-line-color":
                    colorConfig.displayLineColor = value;
                    break;
                  case "--label-fill-color":
                    colorConfig.labelFillColor = value;
                    break;
                  case "--with-display-shadow":
                    colorConfig.withDisplayShadow = value === "true";
                    break;
                  case "--shadow-color":
                    colorConfig.shadowColor = value;
                    break;
                  case "--outline-color":
                    colorConfig.outlineColor = value;
                    break;
                  case "--major-tick-color":
                    colorConfig.majorTickColor = value;
                    break;
                  case "--minor-tick-color":
                    colorConfig.minorTickColor = value;
                    break;
                  case "--value-color":
                    colorConfig.valueColor = value;
                    break;
                  case "--value-outline-color":
                    colorConfig.valueOutlineColor = value;
                    break;
                  case "--value-nb-decimal":
                    colorConfig.valueNbDecimal = value;
                    break;
                  case "--hand-color":
                    colorConfig.handColor = value;
                    break;
                  case "--hand-outline-color":
                    colorConfig.handOutlineColor = value;
                    break;
                  case "--with-hand-shadow":
                    colorConfig.withHandShadow = value === "true";
                    break;
                  case "--knob-color":
                    colorConfig.knobColor = value;
                    break;
                  case "--knob-outline-color":
                    colorConfig.knobOutlineColor = value;
                    break;
                  case "--font":
                    colorConfig.font = value;
                    break;
                  case "--value-font-size-factor":
                    colorConfig.valueFontSizeFactor = parseFloat(value);
                    break;
                  default:
                    break;
                }
              }
            });
          }
        }
      }
    }
    return colorConfig;
  }

  drawDisplay(analogValue) {
    let currentStyle = this.className;
    if (this._previousClassName !== currentStyle || true) {
      // Reload
      //	console.log("Reloading CSS");
      try {
        this.analogDisplayColorConfig = this.getColorConfig(currentStyle);
      } catch (err) {
        // Absorb?
        console.log(err);
      }
      this._previousClassName = currentStyle;
    }

    let digitColor = this.analogDisplayColorConfig.digitColor;

    let context = this.canvas.getContext("2d");
    context.clearRect(0, 0, this.width, this.height);

    let radius =
        Math.min(this.width, this.height) / (this.overlap > 0 ? 2 : 1) * 0.9;

    // Set the canvas size from its container.
    this.canvas.width = this.width;
    this.canvas.height = this.height;

    let totalAngle = Math.PI + 2 * this.toRadians(this.overlap);

    context.beginPath();

    if (this.withBorder === true) {
      //  context.arc(x, y, radius, startAngle, startAngle + Math.PI, antiClockwise);
      //    context.arc(canvas.width / 2, radius + 10, radius, Math.PI - toRadians(overlapOver180InDegree), (2 * Math.PI) + toRadians(overlapOver180InDegree), false);
      context.arc(
        this.canvas.width / 2,
        radius + 10,
        radius,
        Math.PI - this.toRadians(this.overlap > 0 ? 90 : 0),
        2 * Math.PI + this.toRadians(this.overlap > 0 ? 90 : 0),
        false
      );
      context.lineWidth = 5;
    }

    if (this.analogDisplayColorConfig.withGradient) {
      let grd = context.createLinearGradient(0, 5, 0, radius);
      grd.addColorStop(
        0,
        this.analogDisplayColorConfig.displayBackgroundGradient.from
      ); // 0  Beginning
      grd.addColorStop(
        1,
        this.analogDisplayColorConfig.displayBackgroundGradient.to
      ); // 1  End
      context.fillStyle = grd;
    } else {
      context.fillStyle = this.analogDisplayColorConfig.displayBackgroundGradientTo;
    }
    if (this.analogDisplayColorConfig.withDisplayShadow) {
      context.shadowOffsetX = 3;
      context.shadowOffsetY = 3;
      context.shadowBlur = 3;
      context.shadowColor = this.analogDisplayColorConfig.shadowColor;
    } else {
      context.shadowOffsetX = 0;
      context.shadowOffsetY = 0;
      context.shadowBlur = 0;
      context.shadowColor = undefined;
    }
    context.lineJoin = "round";
    context.fill();
    context.strokeStyle = this.analogDisplayColorConfig.outlineColor;
    context.stroke();
    context.closePath();

    // Min-max?
    if (this.withMinMax && this.miniVal < this.maxiVal) {
      context.beginPath();

      let ___minAngle =
          totalAngle *
          ((this.miniVal - this.minValue) / (this.maxValue - this.minValue)) -
          this.toRadians(this.overlap) -
          Math.PI;
      let ___maxAngle =
          totalAngle *
          ((this.maxiVal - this.minValue) / (this.maxValue - this.minValue)) -
          this.toRadians(this.overlap) -
          Math.PI;

      //Center
      context.moveTo(this.canvas.width / 2, radius + 10);
      context.arc(
        this.canvas.width / 2,
        radius + 10,
        radius * 0.75,
        ___minAngle,
        ___maxAngle,
        false
      );

      //    context.arc(288, 75, 70, 0, Math.PI, false);
      context.closePath();
      context.lineWidth = 1;
      context.fillStyle = "gray";
      context.fill();
      //    context.strokeStyle = '#550000';
      //    context.stroke();
    }

    // Major Ticks
    context.beginPath();
    for (let i = 0; i <= this.maxValue - this.minValue; i += this.majorTicks) {
      let currentAngle =
          totalAngle * (i / (this.maxValue - this.minValue)) -
          this.toRadians(this.overlap);
      let xFrom =
          this.canvas.width / 2 - radius * 0.95 * Math.cos(currentAngle);
      let yFrom = radius + 10 - radius * 0.95 * Math.sin(currentAngle);
      let xTo = this.canvas.width / 2 - radius * 0.85 * Math.cos(currentAngle);
      let yTo = radius + 10 - radius * 0.85 * Math.sin(currentAngle);
      context.moveTo(xFrom, yFrom);
      context.lineTo(xTo, yTo);
    }
    context.lineWidth = 3;
    context.strokeStyle = this.analogDisplayColorConfig.majorTickColor;
    context.stroke();
    context.closePath();

    // Minor Ticks
    if (this.minorTicks > 0) {
      context.beginPath();
      for (
        let i = 0;
        i <= this.maxValue - this.minValue;
        i += this.minorTicks
      ) {
        let _currentAngle =
            totalAngle * (i / (this.maxValue - this.minValue)) -
            this.toRadians(this.overlap);

        let xFrom =
            this.canvas.width / 2 - radius * 0.95 * Math.cos(_currentAngle);
        let yFrom = radius + 10 - radius * 0.95 * Math.sin(_currentAngle);
        let xTo =
            this.canvas.width / 2 - radius * 0.9 * Math.cos(_currentAngle);
        let yTo = radius + 10 - radius * 0.9 * Math.sin(_currentAngle);
        context.moveTo(xFrom, yFrom);
        context.lineTo(xTo, yTo);
      }
      context.lineWidth = 1;
      context.strokeStyle = this.analogDisplayColorConfig.minorTickColor;
      context.stroke();
      context.closePath();
    }

    let scale = radius / 100;
    // Numbers (indexes) on major ticks
    if (this.withDigits) {
      context.beginPath();
      for (
        let i = 0;
        i <= this.maxValue - this.minValue;
        i += this.majorTicks
      ) {
        context.save();
        context.translate(this.canvas.width / 2, radius + 10); // canvas.height);
        let __currentAngle =
            totalAngle * (i / (this.maxValue - this.minValue)) -
            this.toRadians(this.overlap);
        //      context.rotate((Math.PI * (i / maxValue)) - (Math.PI / 2));
        context.rotate(__currentAngle - Math.PI / 2);
        context.font =
          "bold " +
          Math.round(scale * 15) +
          "px " +
          this.analogDisplayColorConfig.font; // Like "bold 15px Arial"
        context.fillStyle = digitColor;
        let str = (i + this.minValue).toString();
        let len = context.measureText(str).width;
        context.fillText(str, -len / 2, -(radius * 0.8) + 10);
        context.lineWidth = 1;
        context.strokeStyle = this.analogDisplayColorConfig.valueOutlineColor;
        context.strokeText(str, -len / 2, -(radius * 0.8) + 10); // Outlined
        context.restore();
      }
      context.closePath();
    }

    // Value
    let text = analogValue.toFixed(
      this.analogDisplayColorConfig.valueNbDecimal
    );
    //  text = displayValue.toFixed(nbDecimal); // analogDisplayColorConfig.valueNbDecimal);
    let len = 0;
    context.font =
      "bold " +
      Math.round(
      scale * 40 * this.analogDisplayColorConfig.valueFontSizeFactor
    ) +
      "px " +
      this.analogDisplayColorConfig.font; // "bold 40px Arial"
    let metrics = context.measureText(text);
    len = metrics.width;

    context.beginPath();
    context.fillStyle = this.analogDisplayColorConfig.valueColor;
    context.fillText(text, this.canvas.width / 2 - len / 2, radius * 0.75 + 10);
    context.lineWidth = 1;
    context.strokeStyle = this.analogDisplayColorConfig.valueOutlineColor;
    context.strokeText(
      text,
      this.canvas.width / 2 - len / 2,
      radius * 0.75 + 10
    ); // Outlined
    context.closePath();

    // Label ?
    if (this.label !== undefined) {
      var fontSize = 20;
      text = this.label;
      len = 0;
      context.font =
        "bold " +
        Math.round(scale * fontSize) +
        "px " +
        this.analogDisplayColorConfig.font; // "bold 40px Arial"
      metrics = context.measureText(text);
      len = metrics.width;

      context.beginPath();
      context.fillStyle = this.analogDisplayColorConfig.labelFillColor;
      context.fillText(
        text,
        this.canvas.width / 2 - len / 2,
        2 * radius - fontSize * scale * 2.1
      );
      context.lineWidth = 1;
      context.strokeStyle = this.analogDisplayColorConfig.valueOutlineColor;
      context.strokeText(
        text,
        this.canvas.width / 2 - len / 2,
        2 * radius - fontSize * scale * 2.1
      ); // Outlined
      context.closePath();
    }

    // Digits? Note: not compatible with label (above), would hide it. Example: Log Value // TODO Look into this
    if (this.digitalDataLen !== undefined) {
      let oneDigitWidth = this.canvas.width / 3 / this.digitalDataLen;
      let oneDigitHeight = oneDigitWidth * 1.4;

      if (this.analogDisplayColorConfig.withGradient) {
        let start = 1.1025 * (this.canvas.height / 2);
        let grd = context.createLinearGradient(
          0,
          start,
          0,
          start + oneDigitHeight
        );
        grd.addColorStop(
          0,
          this.analogDisplayColorConfig.displayBackgroundGradient.to
        ); // 0  Beginning
        grd.addColorStop(
          1,
          this.analogDisplayColorConfig.displayBackgroundGradient.from
        ); // 1  End
        context.fillStyle = grd;
      } else {
        context.fillStyle = this.analogDisplayColorConfig.displayBackgroundGradient.to;
      }

      // The rectangles around each digit
      let digitOrigin =
          this.canvas.width / 2 - this.digitalDataLen * oneDigitWidth / 2;
      for (let i = 0; i < this.digitalDataLen; i++) {
        context.beginPath();

        let x = digitOrigin + i * oneDigitWidth;
        let y = 1.1025 * (this.canvas.height / 2);
        context.fillRect(x, y, oneDigitWidth, oneDigitHeight);
        context.lineWidth = 1;
        context.strokeStyle = this.analogDisplayColorConfig.displayLineColor;
        context.rect(x, y, oneDigitWidth, oneDigitHeight);
        context.stroke();
        context.closePath();
      }

      context.shadowOffsetX = 0;
      context.shadowOffsetY = 0;
      context.shadowBlur = 0;

      // Value
      if (this.digitalDataVal !== undefined) {
        let text = this.digitalDataVal.toFixed(0);
        while (text.length < this.digitalDataLen) {
          text = "0" + text;
        }
        let fontSize = Math.round(scale * 14);
        for (let i = 0; i < this.digitalDataLen; i++) {
          len = 0;
          context.font = "bold " + fontSize + "px Arial"; // "bold 40px Arial"
          let txt = text.substring(i, i + 1);
          let metrics = context.measureText(txt);
          len = metrics.width;
          let x = digitOrigin + i * oneDigitWidth;
          let y = 1.1025 * (this.canvas.height / 2);
          context.beginPath();
          context.fillStyle = this.analogDisplayColorConfig.valueColor;
          context.fillText(
            txt,
            x + oneDigitWidth / 2 - len / 2,
            y + oneDigitHeight / 2 + fontSize / 2
          );
          context.lineWidth = 1;
          context.strokeStyle = this.analogDisplayColorConfig.valueOutlineColor;
          context.strokeText(
            txt,
            x + oneDigitWidth / 2 - len / 2,
            y + oneDigitHeight / 2 + fontSize / 2
          ); // Outlined
          context.closePath();
        }
      }
    }

    // Hand
    context.beginPath();
    if (this.analogDisplayColorConfig.withHandShadow) {
      context.shadowColor = this.analogDisplayColorConfig.shadowColor;
      context.shadowOffsetX = 3;
      context.shadowOffsetY = 3;
      context.shadowBlur = 3;
    }
    // Center
    context.moveTo(this.canvas.width / 2, radius + 10);
    let valInBoundaries = Math.min(analogValue, this._max_value);
    valInBoundaries = Math.max(valInBoundaries, this._min_value);

    let ___currentAngle =
        totalAngle *
        ((valInBoundaries - this.minValue) / (this.maxValue - this.minValue)) -
        this.toRadians(this.overlap);
    // Left
    let x =
        this.canvas.width / 2 -
        radius * 0.05 * Math.cos(___currentAngle - Math.PI / 2);
    let y =
        radius + 10 - radius * 0.05 * Math.sin(___currentAngle - Math.PI / 2);
    context.lineTo(x, y);
    // Tip
    x = this.canvas.width / 2 - radius * 0.9 * Math.cos(___currentAngle);
    y = radius + 10 - radius * 0.9 * Math.sin(___currentAngle);
    context.lineTo(x, y);
    // Right
    x =
      this.canvas.width / 2 -
      radius * 0.05 * Math.cos(___currentAngle + Math.PI / 2);
    y = radius + 10 - radius * 0.05 * Math.sin(___currentAngle + Math.PI / 2);
    context.lineTo(x, y);

    context.closePath();
    context.fillStyle = this.analogDisplayColorConfig.handColor;
    context.fill();
    context.lineWidth = 1;
    context.strokeStyle = this.analogDisplayColorConfig.handOutlineColor;
    context.stroke();
    // Knob
    context.beginPath();
    context.arc(this.canvas.width / 2, radius + 10, 7, 0, 2 * Math.PI, false);
    context.closePath();
    context.fillStyle = this.analogDisplayColorConfig.knobColor;
    context.fill();
    context.strokeStyle = this.analogDisplayColorConfig.knobOutlineColor;
    context.stroke();
  }

  toDegrees(rad) {
    return rad * (180 / Math.PI);
  }

  toRadians(deg) {
    return deg * (Math.PI / 180);
  }
}

// Associate the tag and the class
window.customElements.define(ANALOG_TAG_NAME, AnalogDisplay);

// Demo utilities
function setData(from, to) {
  let elem = document.getElementById(to);
  let value = document.getElementById(from).value; // Field to read to get the value
  if (value.length !== 0) {
    elem.value = value; // value corresponds to the 'set value(val) { ...', invokes the setter in the HTMLElement class
  }
}

let animation = false; // Not more than one animation at a given time, for this demo.
let currentValue;
let incr;
let intervalId;

function smoothlySet(webComp, from, to) {
  webComp.value = currentValue;
  //		console.log("From %f to %f, currently %f", from, to, currentValue);
  currentValue += incr;
  if ((incr > 0 && currentValue > to) || (incr < 0 && currentValue < to)) {
    webComp.value = to;
    window.clearInterval(intervalId);
    animation = false;
  }
}

function doAnimate(fromField, toComp, increment, on360) {
  if (animation) {
    alert("Already animating, please wait...");
  } else {
    if (on360 === undefined) {
      on360 = false;
    }
    let webComp = document.getElementById(toComp);
    let startFrom = webComp.value;
    if (document.getElementById(fromField).value.length !== 0) {
      let goTo = parseFloat(document.getElementById(fromField).value);
      if (goTo !== NaN && startFrom !== goTo) {
        if (on360 === true) {
          if (Math.abs(goTo - startFrom) > 180) {
            if (startFrom < 180) {
              goTo -= 360;
            } else {
              goTo += 360;
            }
          }
        }
        animation = true;
        currentValue = startFrom;
        incr =
          (startFrom < goTo ? 1 : -1) *
          (increment !== undefined ? increment : 0.1);
        intervalId = window.setInterval(function() {
          smoothlySet(webComp, startFrom, goTo);
        }, 50);
      }
    }
  }
}

function setBorder(cb, id) {
  document.getElementById(id).withBorder = cb.checked;
}

function setRose(cb, id) {
  document.getElementById(id).withRose = cb.checked;
}

function setMinMax(cb, id) {
  document.getElementById(id).withMinMax = cb.checked;
}

function setDigitVal(field, id) {
  document.getElementById(id).digitalDataVal = field.value;
}
</script>
<footer>&copy;skynet</footer>
</body>
</html>
)rawliteral";

#endif /* INC_PANEL_PAGE_H_ */