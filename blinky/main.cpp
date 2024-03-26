#include "mbed.h"


// main() runs in its own thread in the OS
int main()
{
    
    DigitalOut redLed(PTB2);


    redLed = 0;


    while (true) {
       
        redLed = !redLed;
        printf("Blink!\n");
        ThisThread::sleep_for(500ms);
    }
}
