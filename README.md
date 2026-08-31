# Automated-HRV-on-esp8266
Project which containt file to assambly your HRV, based on an esp8266 as controller



In order to run FW on ESP8266:
1. Install Arduino Ide;
2. Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
3. Install required libraries;
4. Create ./my_main.cpp/credentials.hpp file with content above(replace with you credentials):


#ifndef MY_CRED_HPP
#define MY_CRED_HPP

#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_SSID "My_Wifi_SSID"
#define WIFI_PSW "ThisIsStrongPassword"
#define MQTT_USER "My_MQTT_Broker"
#define MQTT_PSW "test12345"

//You can use generic free mqtt broker for testing purpose
//#defin MQTT_URL "broker.mqtt-dashboard.com"

#ifndef MQTT_URL
#define MQTT_IP_1 192
#define MQTT_IP_2 168
#define MQTT_IP_3 0
#define MQTT_IP_4 1
#endif /*MQTT_URL*/

#define MQTT_PORT 1883



#ifdef __cplusplus
}
#endif


#endif /*MY_CRED_HPP*/


