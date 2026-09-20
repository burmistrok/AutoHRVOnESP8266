#include "ota.hpp"
#include "common.h"
#include "credentials.hpp"
#include <Arduino.h>

#include <ArduinoOTA.h>

void Ota_CallbackStart(void) {
  Serial.println("OTA Start");
}

void Ota_Init(void){
  ArduinoOTA.setHostname(DEVICE_NAME);
  ArduinoOTA.onStart([]() { Ota_CallbackStart(); });
  // Optional password
  ArduinoOTA.setPassword(OTA_PASS);
  ArduinoOTA.begin();
}



void Ota_MainFunction(void){
    
  ArduinoOTA.handle();
}