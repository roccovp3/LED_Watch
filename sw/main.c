/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "LEDs.h"

uint32_t second_count = 0;
uint64_t master_count = 0;

uint8_t time_set_mode = 1;
void handle_button_press(void)
{
    next_led_out(time_set_mode);
}

void handle_button_long_press(void)
{
    // toggle bt 1 and 2
    time_set_mode--;
    time_set_mode = !time_set_mode;
    time_set_mode++;
}

uint64_t timer_on_press = 0;
void GROUP1_IRQHandler(void)
{
    // Determine which pin triggered the interrupt
    switch (DL_GPIO_getPendingInterrupt(GPIOA)) {
        case DL_GPIO_IIDX_DIO3:  // Check if the interrupt was from PA3
            if (second_count == 0) {
                next_led_out(0);
            }
            led_out(second_count);
            second_count = (second_count + 1) % 32768;
            master_count++;
            break;

        case DL_GPIO_IIDX_DIO9:
            if(GPIOA->DIN31_0 & 0x200) {
                uint64_t delta = master_count - timer_on_press;
                if(delta < 32768) {
                    handle_button_press();
                } else {
                    handle_button_long_press();
                }
            }
            else {
                timer_on_press = master_count;
            }
            break;

        default:
            break;
    }
}

int main(void)
{
    SYSCFG_DL_init();
    
    NVIC_EnableIRQ(GPIOA_INT_IRQn);
    NVIC_EnableIRQ(TIMA0_INT_IRQn);

    while (1) {
        __WFI();
    }

    return 0;
}

