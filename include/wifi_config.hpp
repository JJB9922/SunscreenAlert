#ifndef WIFI_CONFIG_HPP
#define WIFI_CONFIG_HPP

#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"

void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data);
void wifi_init();

#endif 
