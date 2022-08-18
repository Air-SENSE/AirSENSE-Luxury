WiFiClient espClient;
PubSubClient mqttClient(espClient);

//const char mqttServerAddress[15] = "23.89.159.119";
const char mqttServerAddress[15] = "188.68.48.86";
const uint16_t mqttServerPort = 1883;

char topic[32];
char espID[10];

char nameDevice[12];
uint8_t MacAddress[6];
uint32_t lastSenddatatoMQTT = millis();


void initMqttClient(char* _topic, char* _espID, PubSubClient& _mqttClient)
{
  uint8_t espMacAddress[6];
  WiFi.macAddress(espMacAddress);
  uint32_t macAddressDecimal = (espMacAddress[3] << 16) + (espMacAddress[4] << 8) + espMacAddress[5];
  sprintf(_topic, "/AirSENSE v3_luxury/ESP32_%08d/", macAddressDecimal);
  sprintf(_espID, "%08d", macAddressDecimal);
  _mqttClient.setServer(mqttServerAddress, mqttServerPort);
  _mqttClient.connect(_espID);
  //_mqttClient.subscribe("huuhuong");
  Serial.println(_topic);
  Serial.println(_espID);
  mqttClient.connect(espID);
  //mqttClient.setCallback(callback);
}
void senddatatoMQTT(float hum,float tem,int pm1,int pm25,int pm10,float O3)
{
    if (WiFi.status() == WL_CONNECTED)
    {
       if (mqttClient.connected())
       {
         timeClient.update();
         uint32_t epochTime = timeClient.getEpochTime();      
//         uint8_t hum = int(TFT_humi);         
//         uint8_t tem = int(TFT_temp);        
//         uint16_t pm1 = TFT_pm1;        
//         uint16_t pm25 = TFT_pm25;      
//         uint16_t pm10 = TFT_pm10;        
//         float O3 = TFT_o3_ppb;
                
         char mes[256] = {0};
         sprintf(mes, "{\"DATA\":{\"O3\":\%.1f\,\"Hum\":\%.1f\,\"Pm1\":\%d\,\"Pm10\":\%d\,\"Pm2p5\":\%d\,\"Time\":\%d\,\"Tem\":\%.1f\},\"NodeID\":\"%s\"}",O3,hum,pm1,pm10,pm25,epochTime,tem,nameDevice1);
         if (mqttClient.publish(topic, mes, true))
         {
           //Serial.println(mes); 
         }
         mqttClient.loop();
       }
       else 
       {
        //Serial.println(" - mqtt reconnect ");
        mqttClient.connect(espID);
        //mqttClient.subscribe("huuhuong");
       }
     }
}
