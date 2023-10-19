#ifndef MQTT_H
#define MQTT_H
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>

class MQTT
{
private:

public:
    void mqtt_begin();
    bool mqtt_public(const char *payload);
    void mqtt_loop();
};
#endif