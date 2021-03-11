/*
    \file   main.c
    \brief  Using DAC as negative input for AC
    (c) 2021 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

/* 3.33 MHz (needed for delay) */
#define F_CPU                         (3333333UL)
/* 1.4V output @ VREF = 1.5V */
#define DAC_DATA_1V4                  (239)
/* VREF Startup time */
#define VREF_STARTUP_MICROS           (25)

#include <avr/io.h>
#include <util/delay.h>

void VREF_init(void);
void DAC0_setVal(uint8_t val);
void DAC0_init(void);
void AC0_init(void);

void VREF_init(void)
{
    /* Voltage reference at 1.5V */
    VREF.CTRLA |= VREF_DAC0REFSEL_1V5_gc;
    /* DAC0/AC0 reference enable: enabled */
    VREF.CTRLB |= VREF_DAC0REFEN_bm;
    /* Wait VREF start-up time */
    _delay_us(VREF_STARTUP_MICROS);
}

void DAC0_setVal(uint8_t val)
{
    DAC0.DATA = val;
}

void DAC0_init(void)
{
    /* Disable digital input buffer */
    PORTA.PIN6CTRL &= ~PORT_ISC_gm;
    PORTA.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
    /* Disable pull-up resistor */
    PORTA.PIN6CTRL &= ~PORT_PULLUPEN_bm;
    
    /* Enable DAC, Output Buffer, Run in Standby */
    DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm | DAC_RUNSTDBY_bm;
}

void AC0_init(void)
{
    /* Negative input from DAC0 */
    /* Positive input from pin PA7 */
    AC0.MUXCTRLA = AC_MUXNEG_DAC_gc
                 | AC_MUXPOS_PIN0_gc;
    
    /* Enable, Output on PA5, Low Power mode */
    AC0.CTRLA = AC_ENABLE_bm
              | AC_OUTEN_bm
              | AC_RUNSTDBY_bm
              | AC_LPMODE_bm;
}

int main(void)
{
    /* Voltage divider -> VDD/2 input on PA7 */
    /* AC output on LED on PA5 */

    VREF_init();
    DAC0_init();
    AC0_init();

    /* 1.4V output @ VREF = 1.5V */
    DAC0_setVal(DAC_DATA_1V4);
    
    while (1)
    {
        ;
    }
}