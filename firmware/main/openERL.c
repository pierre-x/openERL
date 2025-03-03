#include <stdio.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "wifi.h"
#include "freertos/task.h"

#define YELLOW_LED_GPIO 13
#define GREEN_LED_GPIO  14
#define UART_NUM UART_NUM_1   // Using UART1
#define UART_RX_PIN    4      // GPIO4 as RX
#define UART_TX_PIN   -1      // No TX (optional)
#define BUF_SIZE       256    // Buffer size (should be > 128)

void uart_task(void *arg) {
    uint8_t byte;

    while (1) {
        int len = uart_read_bytes(UART_NUM, &byte, 1, 100 / portTICK_PERIOD_MS);  // Lire 1 octet
        if (len > 0) {
            printf("%c", byte);
        }
    }
}

void app_main(void) {

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << YELLOW_LED_GPIO) | (1ULL << GREEN_LED_GPIO),
        .mode = GPIO_MODE_OUTPUT_OD,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    wifi_init();
    
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_7_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    // Configure UART1 with RX on GPIO4
    uart_driver_install(UART_NUM, BUF_SIZE, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // Start UART reading task
    xTaskCreate(uart_task, "uart_task", 4096, NULL, 5, NULL);

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
