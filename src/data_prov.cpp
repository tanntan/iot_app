#include "data_prov.h"
#include <M5StickC.h>
#include <ArduinoJson.h>
#include "Preferences.h"

static const char *TAG = "app";
/* Signal Wi-Fi events on this event-group */
const int WIFI_CONNECTED_EVENT = BIT0;
static EventGroupHandle_t wifi_event_group;
bool provisioned = false;
Preferences preferences;

static void event_handler(void* arg, esp_event_base_t event_base,
                          int event_id, void* event_data)
{
    if (event_base == WIFI_PROV_EVENT) {
        switch (event_id) {
            case WIFI_PROV_START:
                break;
            case WIFI_PROV_CRED_RECV: {
                wifi_sta_config_t *wifi_sta_cfg = (wifi_sta_config_t *)event_data;
                break;
            }
            case WIFI_PROV_CRED_FAIL: {
                wifi_prov_sta_fail_reason_t *reason = (wifi_prov_sta_fail_reason_t *)event_data;
                break;
            }
            case WIFI_PROV_CRED_SUCCESS:
                break;
            case WIFI_PROV_END:
                wifi_prov_mgr_deinit();
                break;
            default:
                break;
        }
    } else if (event_base == WIFI_EVENT) {
        switch (event_id) {
            case WIFI_EVENT_STA_START:
                // esp_wifi_connect();
                WiFi.begin();
                break;
            case WIFI_EVENT_STA_DISCONNECTED:
                // esp_wifi_connect();
                WiFi.begin();
               
                break;
            default:
                break;
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_EVENT);
    }
}
static void get_device_service_name(char *service_name, size_t max)
{
    uint8_t eth_mac[6];
    const char *ssid_prefix = "PROV_";
    esp_wifi_get_mac(WIFI_IF_STA, eth_mac);
    snprintf(service_name, max, "%s%02X%02X%02X",
             ssid_prefix, eth_mac[3], eth_mac[4], eth_mac[5]);
}

static void wifi_init_sta(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin();
    // /* Start Wi-Fi in station mode */
    // ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    // ESP_ERROR_CHECK(esp_wifi_start());
}
esp_err_t custom_prov_data_handler(uint32_t session_id, const uint8_t *inbuf, ssize_t inlen,
                                          uint8_t **outbuf, ssize_t *outlen, void *priv_data)
{
    if (inbuf) {
        char buf[256];
        sprintf(buf, "%.*s", inlen, (char *)inbuf);
        preferences.begin("ltie-sensor", false);
        preferences.putString("ltieData", buf);
        preferences.end();
        delay(1000);
    }
    char response[] = "SUCCESS";
    *outbuf = (uint8_t *)strdup(response);
    if (*outbuf == NULL) {
        ESP_LOGE(TAG, "System out of memory");
        return ESP_ERR_NO_MEM;
    }
    *outlen = strlen(response) + 1; /* +1 for NULL terminating byte */

    return ESP_OK;
}

void DATAPROV::prov_init()
{
    preferences.begin("ltie-sensor", true);
    preferences.end();
    wifi_event_group = xEventGroupCreate();
    esp_err_t ret = nvs_flash_init();
     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        /* Retry nvs_flash_init */
        nvs_flash_init();
    }
    // esp_netif_init();
    esp_event_loop_create_default();
    
    esp_event_handler_register(WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL);

    WiFi.mode(WIFI_AP_STA);
    // esp_netif_create_default_wifi_sta();
    // wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    // ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_prov_mgr_config_t conf = {
        .scheme = wifi_prov_scheme_ble,
        .scheme_event_handler = WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BTDM
    };

    wifi_prov_mgr_init(conf);
    provisioned = false;
    wifi_prov_mgr_is_provisioned(&provisioned);

    if(!provisioned){
        char service_name[12];
        get_device_service_name(service_name, sizeof(service_name));
        wifi_prov_security_t security = WIFI_PROV_SECURITY_1;

        const char *pop = "abcd1234";
        const char *service_key = NULL;
       
        uint8_t custom_service_uuid[] = {
            0xb4, 0xdf, 0x5a, 0x1c, 0x3f, 0x6b, 0xf4, 0xbf,
            0xea, 0x4a, 0x82, 0x03, 0x04, 0x90, 0x1a, 0x02,
        };
         
        wifi_prov_scheme_ble_set_service_uuid(custom_service_uuid);
        wifi_prov_mgr_endpoint_create("custom-data");
        wifi_prov_mgr_start_provisioning(security, pop, service_name, service_key);
        wifi_prov_mgr_endpoint_register("custom-data", custom_prov_data_handler, NULL);

    } else {
        wifi_prov_mgr_deinit();
        wifi_init_sta();
    }
    xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_EVENT, true, true, portMAX_DELAY);
}

bool DATAPROV::isProvisioned()
{
    return provisioned;
}