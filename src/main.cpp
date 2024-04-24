#include "wifi_config.h"

#include "esp_system.h"
#include "driver/gpio.h"

#define BOOT_BUTTON_PIN GPIO_NUM_0

extern "C" {
    void app_main(void);
}

void app_main()
{
    wifi_init();
}
