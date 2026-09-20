
#include "mqtt_utils.hpp"
#include "common.h"
#include "credentials.hpp"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define TASK_PERIOD   (1u)
#define RETRY_PERIOD  (5000u/TASK_PERIOD)


const char *HA_USER = MQTT_USER;
const char *HA_PASS = MQTT_PSW;
#ifdef MQTT_URL 
const char* broker = MQTT_URL;
#else
IPAddress broker(MQTT_IP_1,MQTT_IP_2,MQTT_IP_3,MQTT_IP_4); // IP address of your MQTT broker
#endif

String Topic_main = DEVICE_NAME;
void callback(char* topic, byte* payload, unsigned int length);
bool connect(void);

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
unsigned long retry_cnt = 0;




void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();


}



bool connect(void) {
  bool ret_val = false;
#ifdef USE_DEBUG
    Serial.print("Attempting MQTT connection...");
#endif
    if (client.connect(DEVICE_NAME,HA_USER,HA_PASS)) {
#ifdef USE_DEBUG
      Serial.println("connected");
#endif
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("ForceOutFan");
      ret_val = true;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
    }
  return ret_val;
}

void Mqtt_Init(void){
  retry_cnt=0;
  client.setServer(broker, MQTT_PORT);
  Serial.println(broker);
  client.setCallback(callback);
  connect();

}


void Mqtt_MainFunction(void){
  if(!client.connected()){
    if (retry_cnt < RETRY_PERIOD){
      retry_cnt++;
    }else{
      connect();
      retry_cnt=0u;
    }

  }else{
    client.loop();
    retry_cnt=0u;
  }

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }

void Mqtt_PublishData(const char* topic, float payload){
  Topic_main += topic
  client.publish(topic, msg);
}

}