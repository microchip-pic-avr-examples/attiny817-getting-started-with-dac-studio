/*
    \file   main.c
    \brief  Reading DAC internally with ADC
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
/* VREF Startup time */
#define VREF_STARTUP_MICROS           (25)

#include <avr/io.h>
#include <util/delay.h>

void VREF_init(void);
void DAC0_init(void);
void ADC0_init(void);
uint16_t ADC0_read(void);
void DAC0_setVal(uint8_t val);

void VREF_init(void)
{
    /* Voltage reference at 4.34V */
    VREF_CTRLA |= VREF_DAC0REFSEL_4V34_gc; 
    /* DAC0/AC0 reference enable: enabled */
    VREF_CTRLB |= VREF_DAC0REFEN_bm;
    /* Voltage reference at 4.34V */
    VREF_CTRLA |= VREF_ADC0REFSEL_4V34_gc; 
    /* ADC0 reference enable: enabled */
    VREF_CTRLB |= VREF_ADC0REFEN_bm;    
    /* Wait VREF start-up time */
    _delay_us(VREF_STARTUP_MICROS);
}

void DAC0_init(void)
{
    /* Enable DAC */
    DAC0.CTRLA = DAC_ENABLE_bm;
}

void ADC0_init(void)
{
    ADC0.CTRLC = ADC_PRESC_DIV4_gc     /* CLK_PER divided by 4 */
               | ADC_REFSEL_INTREF_gc  /* Internal reference */
               | ADC_SAMPCAP_bm;       /* Sample Capacitance Selection: enabled */

    ADC0.CTRLA = ADC_ENABLE_bm         /* ADC Enable: enabled */
               | ADC_RESSEL_10BIT_gc;  /* 10-bit mode */
    
    /* Select ADC channel */
    ADC0.MUXPOS = ADC_MUXPOS_DAC0_gc;
}

uint16_t ADC0_read(void)
{
    /* Start ADC conversion */
    ADC0.COMMAND = ADC_STCONV_bm;
    
    /* Wait until ADC conversion done */
    while ( !(ADC0.INTFLAGS & ADC_RESRDY_bm) )
    {
        ;
    }
    
    /* Clear the interrupt flag by writing 1: */
    ADC0.INTFLAGS = ADC_RESRDY_bm;
    
    return ADC0.RES;
}

void DAC0_setVal(uint8_t val)
{
    DAC0.DATA = val;
}

int main(void)
{
    uint8_t dacVal = 0;
    volatile uint16_t adcVal = 0;
    
    VREF_init();
    DAC0_init();
    ADC0_init();
    
    DAC0_setVal(dacVal);
    
    while (1) 
    {
        adcVal = ADC0_read();
        
        /* do something with the adcVal */
        
        dacVal++;
        DAC0_setVal(dacVal); 
    }
}
