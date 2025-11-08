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

void one_led_out(watch_led_t led);
void next_led_out();

#endif