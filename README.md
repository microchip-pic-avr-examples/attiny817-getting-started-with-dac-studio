<!-- Please do not change this logo with link -->
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Getting Started with Digital-to-Analog Converter (DAC) Examples (Microchip Studio)

  This repository contains examples of bare metal source code for Digital-to-Analog Converter (DAC) as described in the [TB3210-Getting Started with Digital-to-Analog Converter (DAC)](http://ww1.microchip.com/downloads/en/Appnotes/TB3210-Getting-Started-with-DAC-DS-90003210.pdf) document from Microchip. The repository contains an Atmel Studio Solution with multiple projects inside:

* [<strong>Generating Constant Analog Signal:</strong>](Generating_Constant_Analog_Signal) This use case shows how to use  the DAC to generate a constant analog signal on an output pin (for more details, see [<strong>Generating Constant Analog Signal</strong>](Generating_Constant_Analog_Signal))
* [<strong>Generating Sine Wave Signal:</strong>](Generating_Sine_Wave_Signal) This use case shows how to use the DAC to generate a sine wave signal (for more details, see [<strong>Generating Sine Wave Signal</strong>](Generating_Sine_Wave_Signal))
* [<strong>Reading DAC Internally with ADC:</strong>](Reading_DAC_Internally_with_ADC) This use case shows how to use the DAC to generate an output voltage internally (no pin involved). The ADC will read the value. The DAC voltage output will increment by one step every iteration (for more details, see [<strong>Reading DAC Internally with ADC</strong>](Reading_DAC_Internally_with_ADC))
* [<strong>Using DAC as Negative Input for AC:</strong>](Using_DAC_as_Negative_Input_for_AC) This use case describes how to use the DAC as negative input for the AC and trigger an LED when the positive input is higher than the DAC reference (for more details, see [<strong>Using DAC as Negative Input for AC</strong>](Using_DAC_as_Negative_Input_for_AC))

## Related Documentation
More details and code examples on ATtiny817 can be found at the following links:
- [TB3210-Getting Started with Digital-to-Analog Converter (DAC)](http://ww1.microchip.com/downloads/en/Appnotes/TB3210-Getting-Started-with-DAC-DS-90003210.pdf)
- [ATtiny817 Product Page](https://www.microchip.com/wwwproducts/en/ATTINY817)
- [ATtiny817 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=attiny817)
- [ATtiny817 Project Examples in START](https://start.atmel.com/#examples/ATTINY817XplainedMini)


## Software Used
- Microchip Studio 7.0.2542 or newer [(https://www.microchip.com/mplab/microchip-studio)](https://www.microchip.com/mplab/microchip-studio)
- ATtiny_DFP 1.7.330 or newer Device Pack


## Hardware Used
- ATtiny817 Xplained Mini [(attiny817-xmini)](https://www.microchip.com/developmenttools/ProductDetails/attiny817-xmini)
