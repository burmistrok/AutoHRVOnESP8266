
#include "scheduler.hpp"


void setup() {
  // put your setup code here, to run once:
  SchM_Init();

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  SchM_MainFunction(now);
}
