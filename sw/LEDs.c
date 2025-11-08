#include "ti_msp_dl_config.h"
#include "LEDs.h"

const watch_led_t hour_1 = {1, 1, GPIO_GRP_0_PIN_12_PIN, GPIO_GRP_0_PIN_7_PIN, 34, 14};
const watch_led_t hour_2 = {1, 2, GPIO_GRP_0_PIN_12_PIN, GPIO_GRP_0_PIN_13_PIN, 34, 35};
const watch_led_t hour_3 = {1, 3, GPIO_GRP_0_PIN_12_PIN, GPIO_GRP_0_PIN_25_PIN, 34, 55};
const watch_led_t hour_4 = {1, 4, GPIO_GRP_0_PIN_12_PIN, GPIO_GRP_0_PIN_10_PIN, 34, 21};
const watch_led_t hour_5 = {1, 5, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_12_PIN, 14, 34};
const watch_led_t hour_6 = {1, 6, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_13_PIN, 14, 35};
const watch_led_t hour_7 = {1, 7, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_25_PIN, 14, 55};
const watch_led_t hour_8 = {1, 8, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_10_PIN, 14, 21};
const watch_led_t hour_9 = {1, 9, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_8_PIN, 14, 19};
const watch_led_t hour_10 = {1, 10, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_5_PIN, 14, 10};
const watch_led_t hour_11 = {1, 11, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_2_PIN, 14, 7};
const watch_led_t hour_12 = {1, 12, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_4_PIN, 14, 9};
const watch_led_t hour_12_rollover = {1, 12, GPIO_GRP_0_PIN_7_PIN, GPIO_GRP_0_PIN_4_PIN, 14, 9};

const watch_led_t *hour_leds[13] = {&hour_12,&hour_1, &hour_2, &hour_3, &hour_4, &hour_5, &hour_6, &hour_7, &hour_8, &hour_9, &hour_10, &hour_11};
uint8_t hour_index = 11;

void one_led_out(watch_led_t led) {
    DL_GPIO_enableOutput(GPIO_GRP_0_PORT, led.anode_pin |
    led.cathode_pin);

    DL_GPIO_enableOutput(GPIO_GRP_0_PORT, ~(led.anode_pin |
    led.cathode_pin));

    DL_GPIO_setPins(GPIO_GRP_0_PORT, led.anode_pin);
    DL_GPIO_clearPins(GPIO_GRP_0_PORT, led.cathode_pin);
}

void next_led_out() {
    const watch_led_t *hour_led = hour_leds[hour_index];

    GPIOA->DOE31_0 &= ~(hour_led->anode_pin | hour_led->cathode_pin);

    hour_index = (hour_index + 1) % 12;
    
    hour_led = hour_leds[hour_index];

    GPIOA->DOE31_0 |= (hour_led->anode_pin | hour_led->cathode_pin);

    GPIOA->DOUT31_0 |= hour_led->anode_pin;
    GPIOA->DOUT31_0 &= ~(hour_led->cathode_pin);
}