SparkFun ADC Block for Edison C++ Library
========================================

SparkFun’s ADC Block for the Intel Edison allows you to add four channels of 
I2C controlled ADC input to your Edison stack. These four channels can be 
used as single-ended inputs, or in pairs as differential inputs. A ground 
reference is provided for each channel.

The maximum resolution of the converters is 12 bits, or 11 bits bipolar in 
differential mode. Step sizes range from 125uV per count to 3mV per count.

Repository Contents
-------------------

* **SparkFunADS1015.h** - Header file containing class, function, and
constant definitions used by the ads1015 C++ library.
* **SparkFunADS1015.cpp** - Class implementation for ads1015 class.
* **SparkFun_ADC_Edison_Block_Example.cpp** - example code which will show you
how to access all of the functions in the library.

Documentation
--------------

* **[Programming the Intel Edison](https://learn.sparkfun.com/tutorials/edison-getting-started-guide)** -
Getting up and running with the Edison. Start here!
* **[General Block Information](https://learn.sparkfun.com/tutorials/general-guide-to-sparkfun-blocks-for-intel-edison)** - 
Information applicable to all blocks, such as power requirements and how to
install them.
* **[Programming the Edison](https://learn.sparkfun.com/tutorials/programming-the-intel-edison-beyond-the-arduino-ide)** -
This library uses Intel's [mraa](https://github.com/intel-iot-devkit/mraa) 
library to access hardware resources. This tutorial will help you get started
using mraa to write code in C++. **This is not an Arduino library.**
* **[ADC Block Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-blocks-for-intel-edison---adc)** - 
Hookup guide specific to this block, which includes information on the circuits
used in the demo code.

Products that use this Library 
---------------------------------

* [ADC Block](https://www.sparkfun.com/products/13046)

License Information
-------------------

This product is _**open source**_! 

The code is released under GPL. 

Distributed as-is; no warranty is given.

- Your friends at SparkFun.

