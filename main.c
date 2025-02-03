#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "src/matriz_led.h"
#include "src/led_rgb.h"
#include "src/buttons.h"

int main() {
    stdio_init_all();
    init_buttons();
    init_rgb();
    np_init(LED_PIN);

    absolute_time_t next_blink = get_absolute_time(); // Tempo para a próxima piscada do LED
    bool led_state = false;

    while (true) {
        // Alterna o estado do LED a cada 100ms
        if (absolute_time_diff_us(next_blink, get_absolute_time()) >= 100000) {
            led_state = !led_state;
            gpio_put(LED_R, led_state);
            next_blink = make_timeout_time_ms(3); // Reseta o tempo para a próxima piscada
        }
        
        if (update_display) {
            np_clear();
            for (int i = 0; i < LED_COUNT; i++) {
                if (numbers[counter][i])
                    np_set_led(i, 20, 0, 0);
            }
            np_write();
            update_display = false; // Reseta a flag de atualização
        }
    }
}
