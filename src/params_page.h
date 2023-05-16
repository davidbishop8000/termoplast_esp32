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
</style></head><body><h3>Параметры</h3>
    <div class="item">
        <button id="user_read">Считать</button>
        <form class="param-form" action="/param" id="user_f" method="post">
            <label for="u0">Объем на об.:</label>
            <input type="text" name="u0" id="u0" pattern="[0-9]{1}\.\d{0,1}" placeholder="1.0">
            <label for="u1">Скорость экстр.:</label>
            <input type="text" name="u1" id="u1" pattern="[0-9]{1,3}" placeholder="10">
            <label for="u2">Ускорение экстр.:</label>
            <input type="text" name="u2" id="u2" pattern="[0-9]{1,3}" placeholder="10">

            <label for="u3">Скорость пресс.:</label>
            <input type="text" name="u3" id="u3" pattern="[0-9]{1,3}" placeholder="10">
            <label for="u4">Ускорение пресс.:</label>
            <input type="text" name="u4" id="u4" pattern="[0-9]{1,3}" placeholder="10">

            <label for="u5">Темп.1:</label>
            <input type="text" name="u5" id="u5" pattern="[0-9]{1,3}" placeholder="100">
            <label for="u6">Темп.2:</label>
            <input type="text" name="u6" id="u6" pattern="[0-9]{1,3}" placeholder="100">
            <label for="u7">Темп.3:</label>
            <input type="text" name="u7" id="u7" pattern="[0-9]{1,3}" placeholder="100">

            <label for="u8">Kp:</label>
            <input type="text" name="u8" id="u8" pattern="[0-9]{1}\.\d{0,1}" placeholder="1.0">
            <label for="u9">Ki:</label>
            <input type="text" name="u9" id="u9" pattern="[0-9]{1}\.\d{0,1}" placeholder="1.0">
            <label for="u10">Kd:</label>
            <input type="text" name="u10" id="u10" pattern="[0-9]{1}\.\d{0,1}" placeholder="1.0">

            <label for="u11">Индикация</label>
            <input type="checkbox" value="1" name="u11" id="u11">
        </form><p><span id="u_stat" style="display: none"></span></p>
        <button id="user_save">Сохранить</button>
    </div><script>      
      let user_d = [];
      for (let i = 0; i<=12; i++)
      {
        user_d[i] = document.getElementById(`u${i}`);
      }
      async function getUser() {
      document.getElementById("u_stat").style.display = "none";
        try {
          const response = await fetch(`param?user_read=1`);
          if (response.ok) {
            const data = await response.json();
            user_d[0].value = parseFloat(data.u0).toFixed(2);
            for (let i = 1; i<=7; i++)
            {
              user_d[i].value = data['u${i}'];
            }
            user_d[8].value = parseFloat(data.u9).toFixed(2);
            user_d[9].value = parseFloat(data.u10).toFixed(2);
            user_d[10].value = parseFloat(data.u11).toFixed(2);
            user_d[11].checked = data.u12;
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
      const btn_user_read = document.getElementById("user_read");
      const btn_user_save = document.getElementById("user_save");
      btn_user_read.addEventListener('click', getUser);      
      btn_user_save.addEventListener('click', setUser);      
    </script></body></html>
)rawliteral";

#endif /* INC_PARAMS_PAGE_H_ */