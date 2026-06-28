#include <stdio.h>
#include "pico/stdlib.h"

// How much to slow down spinner, 1-256
// 1 is full speed
// Using a power of 2 is recommended
#define SPINNER_DIVIDER 2

uint16_t p1_counter = 0;
uint8_t p1_a_prev = 0;
uint8_t p1_b_prev = 0;

int main() {
    for (int i = 0; i < 16; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
        gpio_pull_up(i);
        gpio_put(i, 0);
    }
    for (int i = 16; i < 20; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
        gpio_pull_up(i);
    }
    stdio_init_all();
    while(1) {
        // quad decode
        uint32_t in = gpio_get_all();
        uint8_t p1_a = (in >> 16) & 1;
        uint8_t p1_b = (in >> 17) & 1;
        if (p1_a ^ p1_b ^ p1_a_prev ^ p1_b_prev) {
            if (p1_a ^ p1_b_prev) {
                p1_counter++;
            } else {
                p1_counter--;
            }
        }
        p1_a_prev = p1_a;
        p1_b_prev = p1_b;
        // output
        uint8_t p1_out = (uint8_t)(p1_counter / SPINNER_DIVIDER);
        gpio_put_masked(0xFF, p1_out);
    }
    return 0;
}
