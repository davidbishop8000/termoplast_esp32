#ifndef INC_PARAMS_PAGE_H_
#define INC_PARAMS_PAGE_H_

const char params_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <meta charset="utf-8">
  <title>Parameters</title>
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
  input::placeholder{color:#A7A7A7;}
  h3{text-align:center;}
  h4{text-align:center;}
  button {
      width: 50%;
      height: 30px;
      margin: 5px auto;
        display:block;
      padding: 0px;
      color: white;
      border-radius: 10px;
      text-align: center;
      font-size: medium;
      box-shadow: 0 4px #3C3C3C;
      background-color: #666666;
    }
    button:hover {
      background-color: #6A6A6A
    }
    button:active {
      background-color: #761F1F;
      box-shadow: 0 2px #3C3C3C;
      transform: translateY(2px);
    }
    p{
      text-align: center;
    }
  .param-form {
    display: grid;
    grid-template-columns: [labels] auto [controls] 1fr;
    grid-auto-flow: row;
    grid-gap: .8em;
    padding: 1.2em;
  }
  .param-form > label  {
    grid-column: labels;
    grid-row: auto;
  }
  .param-form > input,
  .param-form > textarea {
    grid-column: controls;
    grid-row: auto;
    grid-auto-columns: minmax(100px, auto);
  }
  .send-b {
    margin-top: 20px;
    text-align: center;
  }
  .item {
      border: 2px solid black;
      border-radius: 10px;
      grid-template-columns: auto 1fr;
    }
</style></head><body><h3>Параметры шаттла</h3><h4>Пользовательские</h4>
    <div class="item">
        <button id="user_read">Считать</button>
        <form class="param-form" action="/param" id="user_f" method="post">
            <label for="u0">МПР:</label>
            <input type="text" name="u0" id="u0" pattern="[0-9]{1,3}" placeholder="100">
            <label for="u1">Макс. скорость:</label>
            <input type="text" name="u1" id="u1" pattern="[0-9]{1}\.\d{0,1}" placeholder="0.8">
            <label for="u2">FIFO:</label>
            <input type="checkbox" value="1" name="u2" id="u2">
            <label for="u3">Инверсия:</label>
            <input type="checkbox" value="1" name="u3" id="u3">
        </form><p><span id="u_stat" style="display: none"></span></p>
        <button id="user_save">Сохранить</button>
    </div><br><br><h4>Инженерные</h4>
<div class="item">
    <button id = "eng_read">Считать</button>
    <form class="param-form" action="param" id="eng_f" method="post">
        <label for="e0">Номер шаттла:</label>
        <input type="text" name="e0" id="e0" pattern="[0-9]{1,2}" placeholder="0">
        <label for="e1">Мин. заряд:</label>
        <input type="text" name="e1" id="e1" pattern="[0-9]{1,2}" placeholder="10">
        <label for="e2">Время ож. загр:</label>
        <input type="text" name="e2" id="e2" pattern="[0-9]{1,3}" placeholder="8">
        <label for="e3">Число досок:</label>
        <input type="text" name="e3" id="e3" pattern="[1-9]{1}" placeholder="3">
        <label for="e4">Торм. от доски:</label>
        <input type="text" name="e4" id="e4" pattern="[0-9]{1,3}" placeholder="30">
        <label for="e5">Таймер демо:</label>
        <input type="text" name="e5" id="e5" pattern="[0-9]{1,3}" placeholder="60">
        <label for="e6">Нач. отсч. МПР:</label>
        <input type="text" name="e6" id="e6" pattern="[0-9]{1,3}" placeholder="500">
        <label for="e7" id="le6">Пер. число:</label>
        <input type="text" name="e7" id="e7" pattern="[0-9]{1}\.\d{0,9}" placeholder="0.03833">
        <label for="e8">Макс. темп:</label>
        <input type="text" name="e8" id="e8" pattern="[0-9]{1,3}" placeholder="250 - для отключения">
        <label for="e9">Отступ от нач:</label>
        <input type="checkbox" value="1" name="e9" id="e9">
        <label for="e10">Инверт. энк:</label>
        <input type="checkbox" value="1" name="e10" id="e10">
        <label for="e11">Защита акб:</label>
        <input type="checkbox" value="1" name="e11" id="e11">
        <label for="e12">Датч. канала:</label>
        <input type="checkbox" value="1" name="e12" id="e12">
        <label for="e13">Разреш. демо:</label>
        <input type="checkbox" value="1" name="e13" id="e13">
        <label for="e14">Перехват:</label>
        <input type="checkbox" value="1" name="e14" id="e14">
        <label for="e15">Бампер безоп:</label>
        <input type="checkbox" value="1" name="e15" id="e15">
    </form><p><span id="e_stat" style="display: none"></span></p><button id = "eng_save">Сохранить</button></div><script>      
      let user_d = [];
      for (let i = 0; i<=3; i++)
      {
        user_d[i] = document.getElementById(`u${i}`);
      }
      let eng_d = [];
      for (let i = 0; i<=15; i++)
      {
        eng_d[i] = document.getElementById(`e${i}`);
      }
      async function getUser() {
        document.getElementById("u_stat").style.display = "none";
        try {
          const response = await fetch(`param?user_read=1`);
          if (response.ok) {
            const data = await response.json();
            user_d[0].value = data.u0;
            user_d[1].value = parseFloat(data.u1).toFixed(2);
            user_d[2].checked = data.u2;
            user_d[3].checked = data.u3;
					  //console.log(data);
          }
        } catch (e) {
          //console.log(e);
        }
      }
      async function setUser() {
        try {           
          const response = await fetch(`param`, {
            method: 'POST',
            body: new FormData(user_f)
          });
          if (response.ok) {
            const data = await response.json();
            if ('message' in data){
              const u_stat = document.getElementById("u_stat");
              u_stat.innerHTML = data.message;
              if (data.message == "Успешно") u_stat.style.color = "green";
              else u_stat.style.color = "red";}
            u_stat.style.display = "block";
          }
        } catch (e) {
          //console.log(e);
        }
      }
      async function getEng() {
        document.getElementById("e_stat").style.display = "none";
        try {
          const response = await fetch(`param?eng_read=1`);
          if (response.ok) {
            const data = await response.json();
            for (let i = 0; i<=8; i++)
            {
              eng_d[i].value = data[`e${i}`];
            }
            eng_d[8].value = data.e8;
            for (let i = 9; i<=15; i++)
            {
              eng_d[i].checked = data[`e${i}`];
            }
					  //console.log(data);
          }
        } catch (e) {
          //console.log(e);
        }
      }
      async function setEng() {
        try {           
          const response = await fetch(`param`, {
            method: 'POST',
            body: new FormData(eng_f)
          });
          if (response.ok) {
            const data = await response.json();
            if ('message' in data){
              const e_stat = document.getElementById("e_stat");
              e_stat.innerHTML = data.message;
              if (data.message == "Успешно") e_stat.style.color = "green";
              else e_stat.style.color = "red";}
            e_stat.style.display = "block";
          }
        } catch (e) {
          //console.log(e);
        }
      }
      const btn_user_read = document.getElementById("user_read");
      const btn_eng_read = document.getElementById("eng_read");
      const btn_user_save = document.getElementById("user_save");
      const btn_eng_save = document.getElementById("eng_save");
      btn_user_read.addEventListener('click', getUser);      
      btn_eng_read.addEventListener('click', getEng);
      btn_user_save.addEventListener('click', setUser);      
      btn_eng_save.addEventListener('click', setEng);
    </script></body></html>
)rawliteral";

#endif /* INC_PARAMS_PAGE_H_ */