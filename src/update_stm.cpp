#include "main.h"
#include "update_stm.h"

void stmSerialSet();
void stmSerialUnset();
uint8_t enter_bootloader();
void exit_bootloader();
uint8_t erase_memory();
uint8_t write_memory(AsyncEventSource &events);
uint8_t send_cmd(uint8_t* cmd_array, uint8_t _size);
uint8_t send_adress(uint32_t addr);
uint8_t ack_byte();

void flashStm(AsyncEventSource &events, bool &stm_fl)
{
  // Serial.println(F("init1")); 
  events.send("{\"message\":\"Инициализация\"}","flash",millis());
  // Serial.println(F("init2")); 
  uint8_t res;
  stmSerialSet();
  // Serial.println(F("init3"));
  delay(3000);
  res = enter_bootloader();
  // Serial.println(F("bootloader"));  
  // Serial.println(res);
  events.send("{\"message\":\"Очистка памяти\"}","flash",millis());
  res = erase_memory();
  // Serial.println(F("erase"));  
  // Serial.println(res);
  // Serial.println(F("open file"));  
  // Serial.println(res);
  res = write_memory(events);
  // Serial.println(F("write"));
  // Serial.println(res);
  events.send("{\"message\":\"Перезагрузка контроллера\"}","flash",millis());
  stmSerialUnset();
  exit_bootloader();
  // Serial.println(F("completed"));
  stm_fl = 0;
  delay(3000);
  ESP.restart();
}

void stmSerialSet()
{
    Serial1.end();
    delay(10);
    Serial1.begin(57600, SERIAL_8E1, RX_GPIO, TX_GPIO);
}
void stmSerialUnset()
{
    Serial1.end();
    delay(10);
    Serial1.begin(9600, SERIAL_8N1, RX_GPIO, TX_GPIO);
}
uint8_t enter_bootloader()
{
  digitalWrite(BOOT_GPIO, HIGH);
  delay(500);
  digitalWrite(RESET_GPIO, LOW);
  delay(50);
  digitalWrite(RESET_GPIO, HIGH);
  delay(200);
  while (Serial1.available())
  {
    Serial1.read();
  }
  Serial1.write(0x7F);
  return ack_byte();
}

void exit_bootloader()
{
  digitalWrite(BOOT_GPIO, LOW);
  delay(500);
  digitalWrite(RESET_GPIO, LOW);
  delay(50);
  digitalWrite(RESET_GPIO, HIGH);
  delay(200);
}

uint8_t erase_memory()
{
  uint8_t cmd_array[3] = { 0x44, 0xBB };
  uint8_t res = send_cmd(cmd_array, 2);
  if (res == 1)
    return 1;
  cmd_array[0] = 0xFF;
  cmd_array[1] = 0xFF;
  cmd_array[2] = 0x00;
  res = send_cmd(cmd_array, 3);
  if (res == 1)
    return 1;
  return 0;
}

uint8_t write_memory(AsyncEventSource &events)
{
  File df = SPIFFS.open(stm_firmware, "r");

  if (df)
  {
    uint32_t size_file = df.size();
    //  Serial.print(F("Size: "));
    //  Serial.println(size_file);
    String f_size = "{\"message\":\"Прошивка\", \"size\":" + (String)size_file + "}";
    events.send(f_size.c_str(), "flash", millis());

    uint8_t cmd_array[2] = {0x31, 0xCE};
    uint32_t count_addr = 0;
    uint16_t len = 0;
    uint32_t seek_len = 0;

    String fpos = "";
    String fmsg = "{\"message\":\"Прошивка\", \"bytes\":";

    while (true)
    {
      if (send_cmd(cmd_array, 2) == 0)
      {
        uint8_t ret_adr = send_adress(WRITE_ADDR + count_addr);
        count_addr = count_addr + SIZE_WRITE;

        if (ret_adr == 0)
        {
          uint8_t write_buff[SIZE_WRITE] = {
              0,
          };
          len = df.read(write_buff, SIZE_WRITE);
          seek_len++;
          df.seek(SIZE_WRITE * seek_len);

          uint8_t cs, buf[SIZE_WRITE + 2];
          uint16_t i, aligned_len;

          aligned_len = (len + 3) & ~3;
          cs = aligned_len - 1;
          buf[0] = aligned_len - 1;

          for (i = 0; i < len; i++)
          {
            cs ^= write_buff[i];
            buf[i + 1] = write_buff[i];
          }

          for (i = len; i < aligned_len; i++)
          {
            cs ^= 0xFF;
            buf[i + 1] = 0xFF;
          }

          buf[aligned_len + 1] = cs;
          Serial1.write(buf, aligned_len + 2);
          uint8_t ab = ack_byte();

          if (ab != 0)
          {
            events.send("{\"message\":\"ERR - block not write\"}", "flash", millis());
            return 0;
          }
          fpos = fmsg + String(df.position()) + "}";
          events.send(fpos.c_str(), "flash", millis());

          if (size_file == df.position())
          {
            events.send("{\"message\":\"Успешно 100%\"}", "flash", millis());
            while (Serial1.available())
            {
              Serial1.read();
              delay(1);
            }

            String reciv = "";

            for (uint16_t i = 0; i < 2000; i++)
            {
              if (Serial1.available())
              {
                while (Serial1.available())
                {
                  char c = Serial1.read();
                  reciv += c;
                  delay(1);
                }
                break;
              }
              delay(1);
            }
            //  Serial.println(F("Write- OK"));
            break;
          }
        }
        else
        {
          events.send("{\"message\":\"ERR - adress write\"}", "flash", millis());
          return 0;
        }
      }
      else
      {
        events.send("{\"message\":\"ERR - cmd code\"}", "flash", millis());
        return 0;
      }
    }
    df.close();
  }
  else
  {
    events.send("{\"message\":\"ERR - file\"}", "flash", millis());
    return 0;
  }
  return 1;
}

uint8_t send_cmd(uint8_t* cmd_array, uint8_t _size)
{
  Serial1.write(cmd_array, _size);
  return ack_byte();
}

uint8_t send_adress(uint32_t addr)
{
  uint8_t buf[5] = {0,};
  buf[0] = addr >> 24;
  buf[1] = (addr >> 16) & 0xFF;
  buf[2] = (addr >> 8) & 0xFF;
  buf[3] = addr & 0xFF;
  buf[4] = buf[0] ^ buf[1] ^ buf[2] ^ buf[3];
  Serial1.write(buf, 5);
  return ack_byte();
}

uint8_t ack_byte()
{ 
  for(uint16_t i = 0; i < 500000; i++)
  {
    if(Serial1.available())
    {
      uint8_t res = Serial1.read();
      if(res == 0x79) return 0;   
    }
    yield();
    delay(1);  
  }
  return 1;
}
