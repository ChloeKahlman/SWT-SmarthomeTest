# mbed-os-u8g2-master  
Freedom controller code with latest u8g2 lib (master)  
(c)2021-10-24 Niels Althuisius, Vrije Universiteit Amsterdam  
(c)2021-10-24 Niels Althuisius, Duck&Cover Electronics, IJM, NL  

INSTALLATION with mbed-cli:  
- Clone repo  
  git clone git@github.com:mtx-nelis/mbed-os-u8g2-master.git  
- Change dir to project  
  cd mbed-os-u8g2-master  
- Set mbed options, something like this  
  mbed config TARGET k66f  
  mbed config GCC_ARM_PATH /opt/dev/gcc-arm-none-eabi/bin  
  mbed config TOOLCHAIN=GCC_ARM  
- Check settings if you want  
  mbed config -L  
- Get libraries (mbed-os, MCP23017, ..)  
  mbed deploy  
- Compile  
  mbed compile  
- If succesfull, the binary is located here:  
  ls BUILD/K66F/GCC_ARM/mbed-os-u8g2-master.bin  
- Transfer the file to your board any way you like  

## Important Extra Steps
- Set u8g2 to use 16 bit instead of 8 bit mode.
- Comment out `#include <sys/types.h>` in the u8g2 headers.


TODO:  
- Testing digital inputs  (din0 .. din6)  
- Testing digital outputs (dout0 .. dout6)  
- Testing PWM outputs     (pwm0 .. pwm3)  
- Write code for the MCP4728 DAC  
- Figure out how to deal with the analog inputs (all on pins that aren't supported on Mbed)  
  
  

