//
//#include "EasyNextionLibrary.h"  // Include EasyNextionLibrary 
//#include <EEPROM.h>
//
//EasyNex myNex(Serial2); // Create an object of EasyNex class with the name < myNex >
//                       // Set as parameter the Serial you are going to use
//int number = 0;
//int lastnumber = 0;
//int number1 = 0;
//int lastnumber1 = 0;
//int number2 = 0;
//int lastnumber2 = 0;
//int number3 = 0;
//int lastnumber3 = 0;
//int number4 = 0;
//int lastnumber4 = 0;
//char  TFT_string[10];
//unsigned long timer ;
//void setup() {
//  // put your setup code here, to run once:
// Serial.begin(115200);
// myNex.begin(9600); 
//  EEPROM.begin(512);      
//  delay(500);    
//   Serial.println("OK"); 
//  timer = millis();
//}
//
//void loop() 
//{
//  save_temp();
//  save_humi();
//  save_pm1(); 
//  save_pm10();
//  save_pm25();
//}
//void save_temp()
//{
//    number = myNex.readNumber("calib.n0.val");   // We read the value of n0 and store it to number variable
//    if(number != 777777){                     // 777777 is the return value if the code fails to read the new value
//      lastnumber = number;   // The chances of getting a wrong value is one in a million.
//      if(lastnumber !=0)                                     
//      {
//             int x = lastnumber;
//             EEPROM.write(0, x); // save in adddresss 0 eeprom esp32
//             EEPROM.commit();     // push
//      }
//    }
//                                           
//    else if(number == 777777){
//      number = lastnumber;
//    }
//     timer = millis();
//     int temp_in_flash = EEPROM.read(0); // read in adddresss 0 eeprom esp32
//     
//  if(lastnumber==0)
//  {
//  myNex.writeNum("calib.n0.val",temp_in_flash);
//  }
//}
//void save_humi()
//{
//    number1 = myNex.readNumber("calib.n1.val");   
//    if(number1 != 777777){                     
//      lastnumber1 = number1;   
//      Serial.println("1.  in stack");
//      Serial.println(lastnumber1);                                      
//      if(lastnumber1 !=0)                                     
//      {
//             int y = lastnumber1;
//             EEPROM.write(10, y); // save in adddresss 10 eeprom esp32
//             EEPROM.commit();     // push
//      }
//    }
//                                           
//    else if(number1 == 777777){
//      number1 = lastnumber1;
//    }
//     timer = millis();
//     int humi_in_flash = EEPROM.read(10); // read in adddresss 10 eeprom esp32
//     Serial.println("1. in flash: ");
//     Serial.println(humi_in_flash);
//     
//  if(lastnumber1==0)
//  {
//  myNex.writeNum("calib.n1.val",humi_in_flash);
//  }
//}
//void save_pm1()
//{
//    number2 = myNex.readNumber("calib.n2.val");   
//    if(number2 != 777777){                     
//      lastnumber2 = number2;  
//      Serial.println("1.  in stack");
//      Serial.println(lastnumber2);         
//      if(lastnumber2 !=0)                                     
//      {
//             int z = lastnumber2;
//             EEPROM.write(30, z); // save in adddresss 30 eeprom esp32
//             EEPROM.commit();     // push
//      }
//    }
//                                           
//    else if(number2 == 777777){
//      number2 = lastnumber2;
//    }
//     timer = millis();
//     int pm1_in_flash = EEPROM.read(30); // read in adddresss 30 eeprom esp32
//     Serial.println("1. in flash: ");
//     Serial.println(pm1_in_flash);   
//  if(lastnumber2==0)
//  {
//  myNex.writeNum("calib.n2.val",pm1_in_flash);
//  }
//}
//void save_pm10()
//{
//    number3 = myNex.readNumber("calib.n3.val");   
//    if(number3 != 777777){             
//      lastnumber3 = number3; 
//      Serial.println("1.  in stack");
//      Serial.println(lastnumber3);                                  
//      if(lastnumber3 !=0)                                     
//      {
//             int i = lastnumber3;
//             EEPROM.write(40, i); // save in adddresss 40 eeprom esp32
//             EEPROM.commit();     // push
//      }
//    }
//                                           
//    else if(number3 == 777777){
//      number3 = lastnumber3;
//    }
//     timer = millis();
//     int pm10_in_flash = EEPROM.read(40); // read in adddresss 40 eeprom esp32
//     Serial.println("1. in flash: ");
//     Serial.println(pm10_in_flash);
//     
//  if(lastnumber3==0)
//  {
//  myNex.writeNum("calib.n3.val",pm10_in_flash);
//  }
//}
//void save_pm25()
//{
//    number4 = myNex.readNumber("calib.n4.val");   
//    if(number4 != 777777){                  
//      lastnumber4 = number4;  
//      Serial.println("1.  in stack");
//      Serial.println(lastnumber4);                                 
//      if(lastnumber4 !=0)                                     
//      {
//             int j = lastnumber4;
//             EEPROM.write(50, j); // save in adddresss 50 eeprom esp32
//             EEPROM.commit();     // push
//      }
//    }
//                                           
//    else if(number4 == 777777){
//      number4 = lastnumber4;
//    }
//     timer = millis();
//     int pm25_in_flash = EEPROM.read(50); // read in adddresss 50 eeprom esp32
////     Serial.println("1. in flash: ");
////     Serial.println(pm25_in_flash);
//     
//  if(lastnumber4==0)
//  {
//  myNex.writeNum("calib.n4.val",pm25_in_flash);
//  }
//}
