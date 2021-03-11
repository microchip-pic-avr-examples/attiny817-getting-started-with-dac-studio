/*
    \file   main.c
    \brief  Sine wave generation using DAC
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

/* 20 MHz (needed for delay) */
#define F_CPU                            (20000000UL)
/* VREF Startup time */
#define VREF_STARTUP_MICROS              (25)
/* Number of steps for a sine wave period */
#define SINE_WAVE_STEPS                  (100)
/* Sine wave amplitude */
#define SINE_AMPLITUDE                   (127)
/* Sine wave DC offset */
#define SINE_DC_OFFSET                   (128)
/* 2*PI */
#define M_2PI                            (2 * M_PI)
/* Frequency of the sine wave */
#define OUTPUT_FREQ                      (50)
/* Step delay for the synthesis loop */
#define STEP_DELAY_MICROS                ((1000000 / OUTPUT_FREQ) / SINE_WAVE_STEPS)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/cpufunc.h>
#include <math.h>

/* Buffer to store the sine wave samples */
uint8_t sineWave[SINE_WAVE_STEPS];

void sineWaveInit(void);
void CLKCTRL_init(void);
void VREF_init(void);
void DAC0_init(void);
void DAC0_setVal(uint8_t val);

void sineWaveInit(void)
{
    for(uint16_t i = 0; i < SINE_WAVE_STEPS; i++)
    {
        sineWave[i] = SINE_DC_OFFSET + SINE_AMPLITUDE * sin(i * M_2PI / SINE_WAVE_STEPS);
    }
}

void CLKCTRL_init(void)
{
	/* Disable the main clock prescaler */
	ccp_write_io((void *) & (CLKCTRL.MCLKCTRLB), CLKCTRL.MCLKCTRLB & (~CLKCTRL_PEN_bm));
}

void VREF_init(void)
{
    /* Voltage reference at 4.34V */
    VREF.CTRLA |= VREF_DAC0REFSEL_4V34_gc;
    /* DAC0/AC0 reference enable: enabled */
    VREF.CTRLB |= VREF_DAC0REFEN_bm;
    /* Wait VREF start-up time */
    _delay_us(VREF_STARTUP_MICROS);
}

void DAC0_init(void)
{
    /* Disable digital input buffer */
    PORTA.PIN6CTRL &= ~PORT_ISC_gm;
    PORTA.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
    /* Disable pull-up resistor */
    PORTA.PIN6CTRL &= ~PORT_PULLUPEN_bm;
    
    /* default value */
    DAC0.DATA = SINE_DC_OFFSET;
    /* Enable DAC, Output Buffer, Run in Standby */
    DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm | DAC_RUNSTDBY_bm;
}

void DAC0_setVal(uint8_t val)
{
    DAC0.DATA = val;
}

int main(void)
{
    uint16_t i = 0;
	
	CLKCTRL_init();
    VREF_init();
    DAC0_init();
    
    sineWaveInit();
    
    while (1)
    {
        DAC0_setVal(sineWave[i++]);    
        i = i % SINE_WAVE_STEPS;        
        _delay_us(STEP_DELAY_MICROS);
    }
}