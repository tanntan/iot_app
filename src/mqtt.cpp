#include "mqtt.h"
#include "esp_wifi.h"

const char * server = "mqtt-dev.ltlabs.co";
int port = 1883;
const char * username = "emqx";
const char * password = "public";

WiFiClient wificlient;
PubSubClient mqttClient(wificlient);
void callback(char* topic, byte* payload, unsigned int length) {
    // Handle incoming MQTT messages here
}
void retryConnection()
{
    while (!mqttClient.connected())
    {
        if(mqttClient.connect("esp32Mqtt", username, password))
        {
            char service_name[100];
            sprintf(service_name,"%012llx", ESP.getEfuseMac());
            mqttClient.publish("M5Stack/connect", service_name);
            return;
        } else {
            Serial.println("Connnection unsuccess");
        }
        vTaskDelay(500);
    }
    
}
void MQTT::mqtt_begin()
{
    unsigned long currentMilli;
    while (WiFi.status() != WL_CONNECTED)
    {
        if(millis() - currentMilli > 3000)
        {
            currentMilli = millis();
            break;
        }
        vTaskDelay(500);
    }
    Serial.println("WiFi Connected");
    // wificlient.setInsecure();
    mqttClient.setServer(server, port);
    if(WiFi.status() == WL_CONNECTED)
    {
        retryConnection();
    }
    
    mqttClient.setCallback(callback);
}

bool MQTT::mqtt_public(const char * payload)
{
    return mqttClient.publish("M5Stack/count", payload);
}
void MQTT::mqtt_loop()
{
    if(!mqttClient.connected() && WiFi.status() == WL_CONNECTED)
    {
        retryConnection();
        vTaskDelay(1000);
    }
    mqttClient.loop();
}
