#ifndef INC_UPDATE_STM_H_
#define INC_UPDATE_STM_H_

const char update_stm[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="utf-8"><meta http-equiv="X-UA-Compatible" content="IE=edge"><meta name="viewport" content="width=device-width,initial-scale=1.0"><title>Shuttle control</title><style>
  body{background-color:#4a4a4a;}
  h1{color:white;border-radius:0.5em;margin:3px;font-size:1em;padding:0.2em 0.2em;background:#05149c;text-align:center}
  h3{color:#e2d7d7;font-size:0.8em;text-align:center;}
  footer{background-color:#050e8a;color:white;margin:3px;text-align:center;padding:0.3em 0.3em;border-radius:0.375em;font-size:60%;text-align:center;position:absolute;bottom:10px;left:10px;right:10px;}
  input{width:70%;margin:3px auto 35px auto;padding:10px 0px 10px 0px;background-color:#666666;color:white;border-radius:10px;text-align:center;font-size:medium;}
  button{width:100%;height:50px;background-color:#7A7A7A;margin:3px auto 5px auto;padding:10px;color:white;border-radius:10px;text-align:center;font-size:medium;box-shadow:04px#3C3C3C;}
  button:hover{background-color:#6A6A6A}
  button:active{background-color:#0b1494;box-shadow:02px#3C3C3C;transform:translateY(2px);}
  .grid-container{grid-template-columns:410px;display:grid;grid-gap:0px;height:100%;align-items:center;justify-content:center;}
  *{font-family:"LucidaConsole";}
  .form-upload{width:100%;display:flex;flex-direction:column;align-items:center;}
  progress{width:80%;height:15px;margin-top:10px;border:none;background-color:#001797;display: none;}
  progress::-webkit-progress-bar{border:none;background-color:#7086ff;}
  progress::-webkit-progress-value{background-color:#0a0097;}
  progress::-moz-progress-bar{border:none;background-color:#7086ff;}
  .prog_flash{margin-top: 40px;background-color:#970000;}
  .prog_flash::-webkit-progress-bar{background-color:#ff7070;}
  .prog_flash::-webkit-progress-value{background-color:#970000;}
  .form-upload__container{margin-top:10px;margin-right:20px;color:#d4d4d4;font-size:16px;}
  .form-upload__status:empty::before{content:"";}
  .form-upload__status:empty+span{display:none;}
  .loader{position:absolute;margin-top:30px;left:calc(50% - 64px);width:128px;height:128px;border-radius:50%;perspective:800px;display:none;}
  .inner{position:absolute;box-sizing:border-box;width:100%;height:100%;border-radius:50%;}
  .inner.one{left:0%;top:0%;animation:rotate-one 1s linear infinite;border-bottom:4px solid #0031d4;}
  .inner.two{right:0%;top:0%;animation:rotate-two 1s linear infinite;border-right:4px solid #0031d4;}
  .inner.three{right:0%;bottom:0%;animation:rotate-three 1s linear infinite;border-top:4px solid #0031d4;}
  @keyframes rotate-one{0%{transform:rotateX(35deg)rotateY(-45deg)rotateZ(0deg);}100%{transform:rotateX(35deg)rotateY(-45deg)rotateZ(360deg);}}
  @keyframes rotate-two{0%{transform:rotateX(50deg)rotateY(10deg)rotateZ(0deg);}100%{transform:rotateX(50deg)rotateY(10deg)rotateZ(360deg);}}
  @keyframes rotate-three{0%{transform:rotateX(35deg)rotateY(55deg)rotateZ(0deg);}100%{transform:rotateX(35deg)rotateY(55deg)rotateZ(360deg);}}</style></head><body>
<h1>Обновление прошивки шаттла</h1>
<h3>Выберите файл прошивки</h3>
<div class="grid-container">
<form class="form-upload" action="/updatestm" method="post" id="uploadForm" enctype="multipart/form-data">
  <input accept=".bin" style="width:80%" id="uploadForm_File" type="file" name="fupload" value="" onchange="(event)=>uploadFile(event)">
  <button style="width:80%" id="uploadForm_Submit" type="submit">Прошить</button>
  <progress id="progressBar" value="0" max="100"></progress>
  <div class="form-upload__container">
    <span class="form-upload__status" id="uploadForm_Status"></span>
    <span id="uploadForm_Size"></span>
  </div>
  <progress class="prog_flash" id="progressFlash" value="0" max="100"></progress>
  <div class="form-upload__container">
    <span class="form-upload__status" id="FlashForm_Status"></span>
    <span id="FlashForm_Size"></span>
  </div>
</form>
</div><div class="loader" id="loader"><div class="inner one"></div><div class="inner two"></div><div class="inner three"></div></div>
<footer>&copy;skynet</footer>
<script>    
const form = document.getElementById('uploadForm')
const fileInput = document.getElementById('uploadForm_File')
const sizeText = document.getElementById('uploadForm_Size')
const statusText = document.getElementById('uploadForm_Status')
const progressBar = document.getElementById('progressBar')  
fileInput.addEventListener('change',()=>{
  //const file = this.files[0]
  const file=event.target.files[0];
  if (file.size > 1 * 1048576) {
    alert('Прошивка до 1 МБ')
    this.value = null
  }});  
form.addEventListener('submit',(event)=>{
  event.preventDefault()
  const fileToUpload = fileInput.files[0]
  const formSent = new FormData()
  const xhr = new XMLHttpRequest()  
  if (fileInput.files.length > 0) {
    document.getElementById("loader").style.display='block';
    document.getElementById("progressBar").style.display='block';
    formSent.append('uploadForm_File', fileToUpload)
    xhr.upload.addEventListener('progress', progressHandler, false)
    xhr.addEventListener('load', loadHandler, false)
    xhr.open('POST', '/updatestm')
    xhr.send(formSent)
  } else {
    alert('Выберите файл')
  }
  return false
});  
function progressHandler(event) {
  const BYTES_IN_KB = 1024
  const loadedKb = (event.loaded/BYTES_IN_KB).toFixed(1)
  const totalSizeKb = (event.total/BYTES_IN_KB).toFixed(1)
  const percentLoaded = Math.round((event.loaded / event.total) * 100)  
  progressBar.value = percentLoaded
  sizeText.textContent = `${loadedKb} из ${totalSizeKb} KБ`
  statusText.textContent = `Загрузка файла ${percentLoaded}% | `  
}  
function loadHandler(event) {
  const obj = JSON.parse(event.target.responseText);
  statusText.textContent = obj.message;
}
if (!!window.EventSource) {
      let size = 1;
      let bytes = 0;
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
      source.addEventListener('flash', function (e) {
        const sizeFlash = document.getElementById('FlashForm_Size')
        const statusFlash = document.getElementById('FlashForm_Status')
        const progressFlash = document.getElementById('progressFlash')
        progressFlash.style.display='block';
        //console.log(e)
        //console.log(e.data)
        const obj = JSON.parse(e.data);
        //console.log("status_parse ", obj.message);
        statusFlash.textContent = obj.message;
        
        if (obj.size != undefined) size = obj.size;
        if (obj.bytes != undefined) {
          bytes = obj.bytes;
          sizeFlash.textContent = bytes+"Б";
        }
        const percentLoaded = Math.round((bytes / size) * 100)
        progressFlash.value = percentLoaded
        //console.log(size, " ", bytes, " ", percentLoaded)
        if (percentLoaded == 100)
        {
          sizeFlash.textContent = "";
            document.getElementById("loader").style.display = 'none';
            setTimeout(function(){
              window.location.href = '/';
            }, 7000)
        }

      }, false);
    }
</script></body></html>
)rawliteral";

#define WRITE_ADDR 0x08000000
#define SIZE_WRITE 256
#if defined(CONFIG_IDF_TARGET_ESP32S3)
	#define RX_GPIO 10
  #define TX_GPIO 11
#else
	#define RX_GPIO 16
  #define TX_GPIO 17
#endif

#define BOOT_GPIO 12
#define RESET_GPIO 3

void flashStm(AsyncEventSource &events, bool &stm_fl);

#endif /* INC_UPDATE_STM_H_ */