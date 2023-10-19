#include "pref.h"
#include <ArduinoJson.h>

Preferences prefer;
String buffer;

void PREF::pref_init(data_t &deviceData)
{
    prefer.begin("ltie-sensor", false);
    pref_getInt(deviceData.count, "count");
    pref_getInt(deviceData.mode, "mode");
    pref_getBool(deviceData.learned, "learned");
    pref_getInt(deviceData.diff, "diff");
    pref_getString(buffer, "ltieData");
    convert_struct();
    prefer.end();
    
}

void PREF::pref_getInt(uint32_t &output, const char * key)
{
    uint32_t number = prefer.getInt(key,  0);//pref.getInt("count", 0);
    output = number;
}

void PREF::pref_getBool(bool &booleanOutput, const char * key)
{
    bool out = prefer.getBool(key,  false);//pref.getInt("count", 0);
    booleanOutput = out;
}
void PREF::pref_putInt(int value, const char * key)
{
    prefer.begin("ltie-sensor", false);
    prefer.putInt(key, value);
    prefer.end();
}

void PREF::pref_putBool(bool value, const char * key)
{
    prefer.begin("ltie-sensor", false);
    prefer.putBool(key, value);
    prefer.end();
}
void PREF::pref_putStr(const char* value, const char *key){
    prefer.begin("ltie-sensor", false);
    prefer.putString(key, value);
    prefer.end();
}
void PREF::pref_getString(String &buff, const char *key){
    String _temp;
    prefer.begin("ltie-sensor", false);
    _temp = prefer.getString(key, "");
    buff = _temp;
    Serial.println("buffer: ");
    Serial.print(buff);
    prefer.end();
}
void PREF::convert_struct()
{
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, buffer);
    if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    }
    ltieData.line = doc["line"].as<const char*>(); // 6099
    ltieData.station = doc["station"];
    ltieData.gmtoffsetval = doc["gmtOffset"];
    doc.clear();
}
