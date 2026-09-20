#ifndef MQTT_UTILS_HPP
#define MQTT_UTILS_HPP

#ifdef __cplusplus
extern "C" {
#endif


void Mqtt_Init(void);
void Mqtt_MainFunction(void);
void Mqtt_PublishData(const char* topic, float payload);

#ifdef __cplusplus
}
#endif


#endif /*MQTT_UTILS_HPP*/