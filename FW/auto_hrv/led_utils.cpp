
#include "led_utils.hpp"
#include <Arduino.h>



#define TASK_PERIOD 1000 // Task period in milliseconds
int ledState = LOW;


void Led_Init(void){
    pinMode(2, OUTPUT);

}
void Led_MainFunction(void){

    if (ledState == LOW) {
      ledState = HIGH;  // Note that this switches the LED *off*
    } else {
      ledState = LOW;  // Note that this switches the LED *on*
    }
    digitalWrite(2, ledState);


}