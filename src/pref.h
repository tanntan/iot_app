#ifndef PREF_H
#define PREF_H

#include <Preferences.h>

class PREF
{
private:
    void convert_struct();
public:
    typedef struct {
        double totalSmv;
        const char * operatorId;
        const char * line;
        int station;
        unsigned long startTime;
        long gmtoffsetval;
    } ltie_data_t;

    typedef struct 
    {
        unsigned long totalTimeInSecound = 0;
        uint32_t count = 0;
        uint32_t mode = 1;
        uint32_t diff = 0;
        bool learned = false;
        double attMinute = 0;
    } data_t;
    ltie_data_t ltieData;

    void pref_init(data_t &deviceData);
    void pref_putInt();
    void pref_getInt(uint32_t &output, const char * key);
    void pref_getBool(bool &booleanOutput, const char * key);
    void pref_putInt(int value, const char * key);
    void pref_putBool(bool value, const char * key);
    void pref_putStr(const char* value, const char *key);
    void pref_getString(String &buff, const char *key);
};

#endif