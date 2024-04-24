#include "wifi_config.h"

#include "esp_system.h"
#include "driver/gpio.h"

#define KEYPAD_1 GPIO_NUM_15
#define LIGHT GPIO_NUM_5

extern "C" {
    void app_main(void);
}

void app_main()
{
    //wifi_init();

    esp_rom_gpio_pad_select_gpio(KEYPAD_1);
    gpio_set_direction(KEYPAD_1, GPIO_MODE_INPUT);

    esp_rom_gpio_pad_select_gpio(LIGHT);
    gpio_set_direction(LIGHT, GPIO_MODE_OUTPUT);

    bool led_state = false;
    bool dummyUVBad = true;
    int flashes = 10;

    while (true) {
        int button_state = gpio_get_level(KEYPAD_1);

        if(button_state == 0) {
            printf("Button is pressed\n");
            
            if(dummyUVBad == false){
                gpio_set_level(LIGHT, 1);
                for(int i = 0; i < flashes; i++){
                    vTaskDelay(500 / portTICK_PERIOD_MS);
                    gpio_set_level(LIGHT, 0);
                    vTaskDelay(500 / portTICK_PERIOD_MS);
                    gpio_set_level(LIGHT, 1);
                }
                gpio_set_level(LIGHT, 0);
            } else if (dummyUVBad == true){
                gpio_set_level(LIGHT, 1);
                vTaskDelay(10000 / portTICK_PERIOD_MS);
                gpio_set_level(LIGHT, 0);
            }
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}