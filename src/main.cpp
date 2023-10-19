#define SENSOR 33
#define REDLED 10
#include "data_prov.h"
#include "halleffect.h"
#include <M5StickC.h>
#include <Arduino.h>
#include "pref.h"
#include "assets/public_icon.h"
#include "assets/icons.h"
#include "assets/reset_icon.h"
#include "assets/reset_output.h"
#include "assets/play.h"
#include <time.h>

#include "mqtt.h"
#include <ArduinoJson.h>


MQTT mqtt;

PREF pref;
HALLEFFECT halleffect;
PREF::data_t deviceData;
DATAPROV prov;

void output_scr();
void network();
void reset();
int masterData[25][2];
unsigned int outputNumber;
struct tm timeinfo;

const uint8_t *iconptrbuff[4] = {
    reset_icon,
    public_icon,
    output,
    reset_output
};

uint16_t iconpos[4][2] = {
    {0, 15},
    {60, 15},
    {112, 15},
    {160, 15},
};

uint16_t colorBuf[3] = {
    TFT_WHITE,
    TFT_BLUE,
    TFT_WHITE
};

bool isSensorStop = false;
int lastCount = 0;
float findEff();
static void getdeviceName(char *service_name, size_t max)
{
    uint8_t eth_mac[6];
    const char *ssid_prefix = "PROV_";
    esp_wifi_get_mac(WIFI_IF_STA, eth_mac);
    snprintf(service_name, max, "%s%02X%02X%02X",
             ssid_prefix, eth_mac[3], eth_mac[4], eth_mac[5]);
}
void mqtt_task(void *params)
{
  mqtt.mqtt_begin();
  while (1)
  {
    
    if(deviceData.count != lastCount)
    {
      char payload[200];
      char serviceName[12];
      StaticJsonDocument<128> doc;
      getdeviceName(serviceName, sizeof(serviceName));
      doc["count"] = deviceData.count;
      doc["location"] = "Location";
      doc["station"] = pref.ltieData.station;
      doc["output"] = deviceData.count;
      doc["deviceSerial"] = serviceName;

      serializeJson(doc, payload);
      while (!mqtt.mqtt_public(payload))
      {
        mqtt.mqtt_public(payload);
      }
      
      lastCount = deviceData.count;
    }
    
    mqtt.mqtt_loop();
    
    // 1 - 159 159/100*255
    vTaskDelay(10);
  }
  
}
void setup()
{
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setRotation(1);
  prov.prov_init();
  // get timezone
  pref.pref_init(deviceData);
  Serial.print(deviceData.mode);
  if(deviceData.mode == 0) deviceData.learned = true;
  halleffect.sensor_begin(SENSOR);
  xTaskCreate(&mqtt_task, "mqtt", 4*2048, NULL, 1, NULL);
  configTime(25200, 0, "kh.pool.ntp.org");
  
}
unsigned long count_millis;
unsigned int percent;
bool lastBtn = false;
bool flash = false;
int i = 1999;
int btnB = 2999;
void learn();
float findEff()
{
    if(!getLocalTime(&timeinfo))
    {
      Serial.print("Cannot get time");
    }

    int _tempAttMinute = (timeinfo.tm_hour * 60) + timeinfo.tm_min;
    deviceData.attMinute = _tempAttMinute - pref.ltieData.startTime;
    
    float smv = pref.ltieData.totalSmv;
    float attendance = deviceData.attMinute;
    return (deviceData.count * smv) / attendance;
}
void sensorRead(){
  halleffect.sensor_update();
  if(deviceData.mode != 0) {
    percent = ( halleffect.getRevs() * 100) / deviceData.mode;
    if(!isSensorStop)
    {
      M5.Lcd.drawRect(0, 65, 160, 10, TFT_WHITE);
      M5.Lcd.fillRect(1, 66, (percent*159)/100, 8, TFT_BLUE);
      if(halleffect.getRpm() == 0)
      {
        count_millis++;
        if(count_millis >= 1500)
        {
          if(percent >= 100)
          {
            M5.Lcd.fillRect(1, 66, 159, 8, TFT_BLACK); // 1 - 159 159/100*255
            deviceData.count++;
            pref.pref_putInt(deviceData.count, "count");
            halleffect.resetRevs();
            percent = 0;
          } 
          count_millis = 0;
        }
        if(percent < 100 && percent != 0 && M5.BtnA.wasReleasefor(2000))
        {
          deviceData.mode = halleffect.getRevs();
          M5.Lcd.fillRect(1, 66, 159, 8, TFT_BLACK);
          deviceData.count++;
          pref.pref_putInt(deviceData.mode, "mode");
          halleffect.resetRevs();
          percent = 0;
        }
      } else {
        count_millis = 0;
      }
      // Serial.printf("%d RPM: %d \n", deviceData.count, halleffect.getRpm());
        M5.Lcd.setCursor(1, 0, 2);
      M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
      // M5.Lcd.printf("Efficiency: %.2f", findEff());

      M5.Lcd.drawXBitmap(0, 10, output, 48, 48, TFT_BLUE);
      M5.Lcd.setCursor(70, 20, 6);
      M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
      M5.Lcd.printf("%03d", deviceData.count);
    }
  }
}
void purseSensor(){
  if(M5.BtnA.wasPressed() && !lastBtn && deviceData.mode != 0)
  {
    isSensorStop = !isSensorStop;
    M5.Lcd.fillScreen(TFT_BLACK);
    isSensorStop?M5.Lcd.drawXBitmap(52, 20, playicon, 48, 48, TFT_WHITE): M5.Lcd.fillScreen(TFT_BLACK);
  }
}
void loop()
{ 
  purseSensor();
  isSensorStop && deviceData.mode != 0 ? halleffect.sensorPurse(): sensorRead(); 
  if(deviceData.mode <= 0) {
    learn();
  }

  if(M5.BtnB.pressedFor(3000) && !lastBtn && !isSensorStop)
  { 
    M5.Lcd.fillScreen(TFT_BLACK);
    isSensorStop = !isSensorStop;
    flash = isSensorStop;
    lastBtn = !lastBtn;
  } else if(isSensorStop && lastBtn)
  {
    if(flash)
    { 
      flash = !flash;
      for(int j = 0; j < 4; j++)
      {
        M5.Lcd.drawXBitmap(iconpos[j][0], iconpos[j][1], iconptrbuff[(btnB + j) % 4], 48, 48, colorBuf[j] );
      }
    }
    else if(M5.BtnB.wasReleased())
    {
      btnB = (btnB>=6000)?3000: btnB;
      btnB++;
      flash = !flash;
      M5.Lcd.fillScreen(TFT_BLACK);
    } else if(M5.BtnA.wasReleased())
    {
      M5.Lcd.fillScreen(TFT_BLACK);
      switch ((btnB+2)%4)
      {
      case 0:
        lastBtn = false;
        isSensorStop = false;
        break;
      case 1:
        deviceData.mode = 0;
        wifi_prov_mgr_reset_provisioning();
        break;
      
      default:
        break;
      }
    }
  }

  M5.update();
}

void network()
{
  M5.Lcd.setCursor(0,0, 2);
  ///
  M5.Lcd.println("SSID: LTH-WIFI");
  M5.Lcd.println("IP: 10.18.200.122");
  M5.Lcd.println("MAC: 0X00FF00");
}

void output_scr()
{
  M5.Lcd.setCursor(0,0, 2);
  M5.Lcd.printf("OUTPUT: %d\n", deviceData.count);
  M5.Lcd.printf("EFFECIENCY: %.2f \n", findEff());
  M5.Lcd.printf("SMV: %.2f\n", pref.ltieData.totalSmv);
  M5.Lcd.printf("Attendance minute: %.2f", deviceData.attMinute); // Eff = output * smv / attendance minute
}
void reset()
{
  deviceData.learned = true;
  pref.pref_putBool(deviceData.learned, "learn");
  wifi_prov_mgr_reset_provisioning();
  isSensorStop = true;
}

void findlowandHigh(int arr[25][2], int size)
{
    int lowestValue = arr[1][1];
    int highestValue = arr[1][1];

    for(int i = 0; i<=size;i++)
    {
        if (arr[i][1] < highestValue) {
            lowestValue = arr[i][1];
        }
        if (arr[i][1] > highestValue) {
            highestValue = masterData[i][1];
        }
    }
    Serial.printf("low %d, %d \n", lowestValue, highestValue);
    deviceData.mode = lowestValue;
    pref.pref_putInt(deviceData.mode, "mode");
}
void learn()
{
    halleffect.sensor_update();
    if(M5.BtnA.wasPressed())
    {
      outputNumber++;
      halleffect.resetRevs();
      M5.Lcd.fillScreen(TFT_BLACK);
    }
    masterData[outputNumber][0] = outputNumber; 
    masterData[outputNumber][1] = halleffect.getRevs(); 

    if(M5.BtnB.wasReleased())
    {
      findlowandHigh(masterData, outputNumber);
      deviceData.count = outputNumber+1;
      pref.pref_putInt(deviceData.count, "count");
      // save to pref
      deviceData.learned = false;
      isSensorStop = false;
      vTaskDelay(1000);
      // wifi_prov_mgr_reset_provisioning();
      ESP.restart();
    } else if(M5.BtnB.pressedFor(2000))
    {
      wifi_prov_mgr_reset_provisioning();
    }
    M5.Lcd.setCursor(0, 0, 2);
    M5.Lcd.print("No");
    M5.Lcd.setCursor(90, 0, 2);
    M5.Lcd.print("Output");

    M5.Lcd.setCursor(0, 15, 4);
    M5.Lcd.printf("%d", outputNumber+1);

    M5.Lcd.setCursor(90, 15, 4);
    M5.Lcd.printf("%d", halleffect.getRevs());
}