#include "matriz_led.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

PIO np_pio = pio0;          // Define o PIO a ser usado (pio0)
uint sm = 0;                // Define o State Machine
npLED_t leds[LED_COUNT];  
volatile bool update_display = false; // Flag para indicar quando atualizar o display
volatile int counter = 0;   // Contador usado para controle

// Inicializa o controle dos LEDs WS2812
void np_init(unsigned int pin) {
    uint offset = pio_add_program(np_pio, &ws2812_program); // Adiciona o programa WS2812 ao PIO
    sm = pio_claim_unused_sm(np_pio, true);  // Requisita uma máquina de estados (SM) disponível
    ws2812_program_init(np_pio, sm, offset, pin, 800000); // Inicializa o programa WS2812 com a frequência desejada
    np_clear(); 
}

void np_clear(void) {
    for (unsigned int i = 0; i < LED_COUNT; i++)
        np_set_led(i, 0, 0, 0);  
}

void np_set_led(unsigned int index, uint8_t r, uint8_t g, uint8_t b) {
    leds[index].R = r;  
    leds[index].G = g;  
    leds[index].B = b;  
}


void np_write(void) {
    for (unsigned int i = 0; i < LED_COUNT; i++) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G); 
        pio_sm_put_blocking(np_pio, sm, leds[i].R); 
        pio_sm_put_blocking(np_pio, sm, leds[i].B); 
    }
    sleep_us(100);
}
