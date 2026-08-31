#include "common.h"
#include "scheduler.hpp"
#include "led_utils.hpp"
#include "wifi_utils.hpp"
#include "mqtt_utils.hpp"
#include <Arduino.h>


#define SCHM_1MS_TASK_PERIOD 1
#define SCHM_10MS_TASK_PERIOD 10
#define SCHM_100MS_TASK_PERIOD 100
#define SCHM_1S_TASK_PERIOD 1000
#define SCHM_10S_TASK_PERIOD 10000


static void SchM_IdleTask(void);
static void SchM_1msTask(void);
static void SchM_10msTask(void);
static void SchM_100msTask(void);
static void SchM_1sTask(void);
static void SchM_10sTask(void);

static unsigned long last_1ms_task_time = 0;
static unsigned long last_10ms_task_time = 0;
static unsigned long last_100ms_task_time = 0;
static unsigned long last_1s_task_time = 0;
static unsigned long last_10s_task_time = 0;



void SchM_IdleTask(void) {
    // This function is called after every loop

}


void SchM_1msTask(void) {
    // This function is called every 1 millisecond.
    // Place your 1ms periodic tasks here.
    Mqtt_MainFunction();
}

void SchM_1sTask(void) {
    // This function is called every 1 second.
    // Place your 1s periodic tasks here.
    Led_MainFunction(); // Call the LED main function every 1 second
}

void SchM_10sTask(void) {
    // This function is called every 10 seconds.
    // Place your 10s periodic tasks here.
    
    WiFi_MainFunction();
}

void SchM_10msTask(void) {
    // This function is called every 10 milliseconds.
    // Place your 10ms periodic tasks here.
    
}

void SchM_100msTask(void) {
    // This function is called every 100 milliseconds.
    // Place your 100ms periodic tasks here.
}


void SchM_Init(void){
    last_1ms_task_time = 0;
    last_10ms_task_time = 0;
    last_100ms_task_time = 0;
    last_1s_task_time = 0;
    last_10s_task_time = 0;
#ifdef USE_DEBUG
    Serial.begin(115200);

    Serial.printf("Chip ID: %08X\n", ESP.getChipId());
    Serial.printf("CPU: %u MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Flash: %u bytes\n", ESP.getFlashChipRealSize());
#endif
    Led_Init();
    WiFi_Init();
    Mqtt_Init();
}


void SchM_MainFunction(unsigned long now){

    if (now - last_10s_task_time >= SCHM_10S_TASK_PERIOD) {
        last_10s_task_time = now;
        SchM_10sTask();
#ifdef USE_DEBUG
        Serial.print("Now: ");
        Serial.println(now);
#endif
    } else if (now - last_1s_task_time >= SCHM_1S_TASK_PERIOD) {
        last_1s_task_time = now;
        SchM_1sTask();
    } else if (now - last_1ms_task_time >= SCHM_1MS_TASK_PERIOD) {
        last_1ms_task_time = now;
        SchM_1msTask();
    }
    SchM_IdleTask();


}