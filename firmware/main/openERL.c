#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "wifi.h"

#define YELLOW_LED_GPIO 13
#define GREEN_LED_GPIO  14

void app_main(void) {

    /*
     * Init GPIO 
     */
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << YELLOW_LED_GPIO) | (1ULL << GREEN_LED_GPIO),
        .mode = GPIO_MODE_OUTPUT_OD,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    /*
     * Init WiFi 
     */
    wifi_init();

    /*
     * Toggle leds
     */
    while (1) {
        gpio_set_level(YELLOW_LED_GPIO, 1);
        gpio_set_level(GREEN_LED_GPIO,  0);
        vTaskDelay(pdMS_TO_TICKS(300));
        gpio_set_level(YELLOW_LED_GPIO, 0);
        gpio_set_level(GREEN_LED_GPIO,  1);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}
