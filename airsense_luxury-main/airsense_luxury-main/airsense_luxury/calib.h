#include "EasyNextionLibrary.h"  // Include EasyNextionLibrary 
#include <EEPROM.h>
#include "ozone.h"
#include "SHT85"
#include "TFLP01.h"
EasyNex myNex(Serial2); // Create an object of EasyNex class with the name < myNex >
// Set as parameter the Serial you are going to use
int number0 = 0;
int lastnumber0 = 0;
int number1 = 0;
int lastnumber1 = 0;
int number2 = 0;
int lastnumber2 = 0;
int number3 = 0;
int lastnumber3 = 0;
int number4 = 0;
int lastnumber4 = 0;
int number5 = 0;
int lastnumber5 = 0;
int number6 = 0;
int lastnumber6 = 0;
int number7 = 0;
int lastnumber7 = 0;
char  TFT_string[10];
unsigned long timer ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  myNex.begin(9600);
  EEPROM.begin(512);
  delay(500);
  Serial.println("OK");
  timer = millis();
}

//void loop()
//{
//  save_ozone();
//  save_temp();
//  save_humi();
//  save_pm25();
//}

void save_ozone() {
  float ozoneConcentration = (float)Ozone.readOzoneData(COLLECT_NUMBER) / 1000.0;
  number0 = myNex.readNumber("calib.n2.val");   // We read the value of n5 and store it to number variable
  number1 = myNex.readNumber("calib.n7.val");   // We read the value of n5 and store it to number variable
  if (number0 != 777777) {                   // 777777 is the return value if the code fails to read the new value
    lastnumber0 = number0;   // The chances of getting a wrong value is one in a million.
    if (lastnumber0 != 0)
    {
      int x = lastnumber0;
      EEPROM.write(0, x); // save in addresss 0 eeprom esp32
      EEPROM.commit();     // push
    }
  }
  if (number1 != 777777) {                   // 777777 is the return value if the code fails to read the new value
    lastnumber1 = number1;   // The chances of getting a wrong value is one in a million.
    if (lastnumber1 != 0)
    {
      int y = lastnumber1;
      EEPROM.write(10, y); // save in addresss 0 eeprom esp32
      EEPROM.commit();     // push
    }
  }
  if (number0 == 777777 && number1 == 777777) {
    number0 = lastnumber0;
    number1 = lastnumber1;
  }
  timer = millis();
  float a_ozone_in_flash = EEPROM.read(0); // read in adddresss 20 eeprom esp32
  float b_ozone_in_flash = EEPROM.read(10);
  if (lastnumber0 == 0 && lastnumber1 == 0)
  {
//    float ozone_in_flash = a_ozone_in_flash * ozoneConcentration + b_ozone_in_flash; // calculate calib ozone
  
    myNex.writeNum("calib.n2.val", a_ozone_in_flash);
    myNex.writeNum("calib.n7.val", b_ozone_in_flash);
  }
}
void save_temp()
{
  get_SHTdata_temp();
  number2 = myNex.readNumber("calib.n0.val");   // We read the value of n0 and store it to number variable
  number3 = myNex.readNumber("calib.n5.val");
  if (number2 != 777777) {                   // 777777 is the return value if the code fails to read the new value
    lastnumber2 = number2;   // The chances of getting a wrong value is one in a million.
    if (lastnumber2 != 0)
    {
      int x = lastnumber2;
      EEPROM.write(20, x); // save in adddresss 0 eeprom esp32
      EEPROM.commit();     // push
    }
  }
  if (number3 != 777777) {                   // 777777 is the return value if the code fails to read the new value
    lastnumber3 = number3;   // The chances of getting a wrong value is one in a million.
    if (lastnumber3 != 0)
    {
      int y = lastnumber3;
      EEPROM.write(30, y); // save in adddresss 0 eeprom esp32
      EEPROM.commit();     // push
    }
  }

  if (number2 == 777777 && number3 == 777777) {
    number2 = lastnumber2;
    number3 = lastnumber3;
  }
  timer = millis();
  int a_temp_in_flash = EEPROM.read(20); // read in adddresss 20 eeprom esp32
  int b_temp_in_flash = EEPROM.read(30); // read in adddresss 30 eeprom esp32
  if (lastnumber2 == 0 && lastnumber3 == 0)
  {
//    temp_in_flash = a_temp_in_flash * TFT_temp + b_temp_in_flash;
    myNex.writeNum("calib.n0.val", a_temp_in_flash);
    myNex.writeNum("calib.n5.val", b_temp_in_flash);
  }
}

void save_humi()
{
  get_SHTdata_humi();
  number4 = myNex.readNumber("calib.n1.val");
  number5 = myNex.readNumber("calib.n6.val");
  if (number4 != 777777) {
    lastnumber4 = number5;
    Serial.println("1.  in stack");
    Serial.println(lastnumber4);
    if (lastnumber4 != 0)
    {
      int x = lastnumber4;
      EEPROM.write(40, x); // save in adddresss 40 eeprom esp32
      EEPROM.commit();     // push
    }
  }
  
  if (number != 777777) {
    lastnumber4 = number5;
    Serial.println("1.  in stack");
    Serial.println(lastnumber4);
    if (lastnumber4 != 0)
    {
      int x = lastnumber4;
      EEPROM.write(40, x); // save in adddresss 40 eeprom esp32
      EEPROM.commit();     // push
    }
  }

  else if (number1 == 777777) {
    number1 = lastnumber1;
  }
  timer = millis();
  int a_humi_in_flash = EEPROM.read(40); // read in adddresss 40 eeprom esp32
  int b_humi_in_flash = EEPROM.read(50); // read in adddresss 50 eeprom esp32
  //  Serial.println("1. in flash: ");
  //  Serial.println(humi_in_flash);

  if (lastnumber1 == 0)
  {
//    int humi_in_flash = a_humi_in_flash * TFT_humi + b_humi_in_flash;
    myNex.writeNum("calib.n1.val", a_humi_in_flash);
    myNex.writeNum("calib.n6.val", b_humi_in_flash);
  }
}

void save_pm25()
{
  getTFLP01data();
  number6 = myNex.readNumber("calib.n3.val");
  number7 = myNex.readNumber("calib.n4.val");
  if (number4 != 777777) {
    lastnumber4 = number4;
    Serial.println("1.  in stack");
    Serial.println(lastnumber4);
    if (lastnumber4 != 0)
    {
      int j = lastnumber4;
      EEPROM.write(60, j); // save in adddresss 60 eeprom esp32
      EEPROM.write(70, j); // save in adddresss 70 eeprom esp32
      EEPROM.commit();     // push
    }
  }

  else if (number4 == 777777) {
    number4 = lastnumber4;
  }
  timer = millis();
  int a_pm25_in_flash = EEPROM.read(60); // read in adddresss 50 eeprom esp32
  int b_pm25_in_flash = EEPROM.read(70);
  //     Serial.println("1. in flash: ");
  //     Serial.println(pm25_in_flash);

  if (lastnumber4 == 0)
  {
//    int pm25_in_flash = a_pm25_in_flash * TFT_pm25 + b_pm25_in_flash;
    myNex.writeNum("calib.n3.val", a_pm25_in_flash);
    myNex.writeNum("calib.n4.val", b_pm25_in_flash);
  }
}
