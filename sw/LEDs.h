#ifndef LEDS_H
#define LEDS_H

typedef struct {
    uint8_t inner;
    uint8_t position;
    uint32_t anode_pin;
    uint32_t cathode_pin;
    uint8_t anode_pincm;
    uint8_t cathode_pincm;
} watch_led_t;

void next_led_out(uint8_t mode);
void led_out(uint32_t cycle_count);
void increment_min();

#endif