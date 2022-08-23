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



/**
 * @brief	ham de khoi tao ket noi mqtt
 * @param	_topic - topic cua server tra ve
 * @param	_espID - ID cua esp
 * @param	_mqttClient - bien luu tru ket noi
 * @return None
 */
void initMqttClient(char* _topic, char* _espID, PubSubClient& _mqttClient)
{
  uint8_t espMacAddress[6];
  WiFi.macAddress(espMacAddress);
  uint32_t macAddressDecimal = (espMacAddress[3] << 16) + (espMacAddress[4] << 8) + espMacAddress[5];
  sprintf(_topic, "/AirSENSE v3_luxury/ESP32_%08d/", macAddressDecimal);
  sprintf(_espID, "%08d", macAddressDecimal);
  _mqttClient.setServer(mqttServerAddress, mqttServerPort);
  _mqttClient.connect(_espID);
  Serial.println(_topic);
  Serial.println(_espID);
  mqttClient.connect(espID);
}

/**
 * @brief	ham de khoi tao ket noi mqtt
 * @param	hum - do am
 * @param	tem -  nhiet do
 * @param	pm1 - pm1.0
 * @param	pm25 - pm2.5
 * @param	pm10 - pm10
 * @param	03 - 03
 * @return  None
 */
void senddatatoMQTT(float hum,float tem,int pm1,int pm25,int pm10,float O3)
{
    if (WiFi.status() == WL_CONNECTED)
    {
       if (mqttClient.connected())
       {
         timeClient.update();
         uint32_t epochTime = timeClient.getEpochTime();   
         char mes[256] = {0};
         sprintf(mes, "{\"DATA\":{\"O3\":\%.1f\,\"Hum\":\%.1f\,\"Pm1\":\%d\,\"Pm10\":\%d\,\"Pm2p5\":\%d\,\"Time\":\%d\,\"Tem\":\%.1f\},\"NodeID\":\"%s\"}",O3,hum,pm1,pm10,pm25,epochTime,tem,nameDevice1);
         if (mqttClient.publish(topic, mes, true))
         {
#ifdef	DEBUG_SERIAL
           Serial.println(mes); 
#endif
         }
         mqttClient.loop();
       }
       else 
       {
		    mqttClient.connect(espID);
#ifdef	DEBUG_SERIAL
        Serial.println(" - mqtt reconnect ");
        mqttClient.subscribe("huuhuong");
#endif
       }
     }
}
