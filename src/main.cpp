#include "wifi_config.h"

#include "esp_system.h"
#include "driver/gpio.h"

#define KEYPAD_1 GPIO_NUM_36

extern "C" {
    void app_main(void);
}

void app_main()
{
    wifi_init();

    esp_rom_gpio_pad_select_gpio(KEYPAD_1);
    gpio_set_direction(KEYPAD_1, GPIO_MODE_INPUT);

    while (true) {
        int button_state = gpio_get_level(KEYPAD_1);
        
        if(button_state == 1){
            printf("Button is pressed\n");
            
        }

        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}
