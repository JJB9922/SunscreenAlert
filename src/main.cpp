#include "wifi_config.hpp"
#include "fetch_uv_index.hpp"

#include "esp_system.h"
#include "nvs_flash.h"

#include "driver/gpio.h"

#define BTN GPIO_NUM_15
#define LIGHT GPIO_NUM_5

extern "C" {
    void app_main(void);
}

bool check_uv(){
    if(fetch_uv_index() > 3.0){
        return true;
    } else {
        return false;
    }
}

void app_main()
{
    nvs_flash_init();
    wifi_init();

    esp_rom_gpio_pad_select_gpio(BTN);
    gpio_set_direction(BTN, GPIO_MODE_INPUT);

    esp_rom_gpio_pad_select_gpio(LIGHT);
    gpio_set_direction(LIGHT, GPIO_MODE_OUTPUT);

    int flashes = 10;
    bool badUV = false;

    while (true) {
        int button_state = gpio_get_level(BTN);

        if(button_state == 0) {
            printf("Button is pressed\n");
            badUV = check_uv();
            
            // If the UV index is nothing to worry about, flash the light 10 times
            if(badUV == false){
                gpio_set_level(LIGHT, 1);
                for(int i = 0; i < flashes; i++){
                    vTaskDelay(500 / portTICK_PERIOD_MS);
                    gpio_set_level(LIGHT, 0);
                    vTaskDelay(500 / portTICK_PERIOD_MS);
                    gpio_set_level(LIGHT, 1);
                }
                gpio_set_level(LIGHT, 0);
            } else if (badUV == true){
                gpio_set_level(LIGHT, 1);
                vTaskDelay(10000 / portTICK_PERIOD_MS);
                gpio_set_level(LIGHT, 0);
            }
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}