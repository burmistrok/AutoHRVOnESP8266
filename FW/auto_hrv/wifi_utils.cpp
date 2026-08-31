#include "wifi_utils.hpp"
#include "common.h"
#include "credentials.hpp"
#include <Arduino.h>
#include <ESP8266WiFi.h>

#define TASK_PERIOD (10000u) 
#define CHECK_PERIOD (30000u/TASK_PERIOD) /*every 30 seconds*/

void setup_wifi(void);


const char* ssid = WIFI_SSID;
const char* password = WIFI_PSW;
uint8_t u8_retry_cnt = 0u;


void WiFi_Init(void){
  u8_retry_cnt = 0u;
  setup_wifi();
}


void WiFi_MainFunction(void){
  if (u8_retry_cnt < CHECK_PERIOD){
    u8_retry_cnt++;
  }else{
    if (WiFi.status() != WL_CONNECTED) {
#ifdef USE_DEBUG
    Serial.println("Wi-Fi down! Manually triggering reconnect...");
#endif
    // Re-issue begin to force the hardware to scan and reconnect
    WiFi.begin(ssid, password); 
    }
  }

}


void setup_wifi(void) {

  delay(10);
  // We start by connecting to a WiFi network
#ifdef USE_DEBUG
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
#endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef USE_DEBUG
    Serial.print(".");
#endif
  }

  randomSeed(micros());
#ifdef USE_DEBUG
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
#endif
}