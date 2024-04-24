#include "wifi_config.h"
#include "secrets.h"

int retry_num=0;

void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data){
    if(event_id == WIFI_EVENT_STA_START)
    {
        printf("WIFI CONNECTING....\n");
    }
    else if (event_id == WIFI_EVENT_STA_CONNECTED)
    {
        printf("WiFi CONNECTED\n");
    }
    else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        printf("WiFi lost connection\n");
        if(retry_num<5){esp_wifi_connect(); retry_num++; printf("Retrying to Connect...\n");}
    }
    else if (event_id == IP_EVENT_STA_GOT_IP)
    {
        printf("Wifi got IP...\n\n");
    }
}

void wifi_init(){
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);

    //Edited the library a bit so this is 16 and 16 ssid and pass
    wifi_config_t wifi_config;

    strcpy((char*)wifi_config.sta.ssid, WIFI_SSID);
    strcpy((char*)wifi_config.sta.password, WIFI_PASS);

    esp_wifi_set_config((wifi_interface_t)ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
    esp_wifi_set_mode(WIFI_MODE_STA);

    esp_wifi_connect();
    printf("wifi_init_softap finished. SSID:%s\n\n", WIFI_SSID);

    esp_wifi_stop();
    esp_wifi_deinit();
}