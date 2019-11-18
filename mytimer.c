#include "mytimer.h"

/*
 * 07A_TIMER_A0_interrupt: counts up on timer A0 and then interrupts
 * The interrupt then toggles the LED.  Uses LPM3.
 *
 * MCLK defaults to ~1.045 MHz
 * ACLK defaults to ~32768 Hz
 * Timer divides ACLK by 32 so  ~1024 MHZ
 * With TIMER_PERIOD set to 512 an interrupt occurs every 1/2 secs
 *     The frequency is approximately 1 Hz for full cycle
 *
 * Frank Milburn 	25 August 2016
 * Developed on MSP-EXP430F5529 LaunchPad Rev1.5 on CCS V6.1, TIv16.6.0.STS
 */

#define TIMER_PERIOD 4096

//--------------------------------  m a i n  -----------------------------------
void setup_timer_interrupts(void)
{
    //Start timer
    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);

    Timer_A_initUpModeParam param =
    {
        TIMER_A_CLOCKSOURCE_ACLK,               // ACLK clock source ~32.768kHz
        TIMER_A_CLOCKSOURCE_DIVIDER_1,          // ACLK/?? = ??kHz
        32,                                  // debounce period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR,                       // Clear value
        true                                    // Start Timer
    };

    Timer_A_initUpMode(TIMER_A0_BASE, &param);
}

//-------------------------  T I M E R A 0 _ I S R  ----------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMERA0_VECTOR)))
#endif
    void
    TIMERA0_ISR(void)
{
    if (uv_test(TRIG_PORT, TRIG_PIN, U_SENSOR4_PORT, U_SENSOR4_PIN) < 400)
    {
        showHex(1);
    }
    else {
        showHex(0);
    }
}
/* This code contains fragments and sections subject to the following
 * copyright:
 *
 * --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
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
 * --/COPYRIGHT--*/
