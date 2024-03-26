
#include "mbed.h"
#include "board_freedom.h"
#include "adc.h"
#include <cstdio>

#define WAIT 3s //define waiting time in sec

DigitalOut Garden_Lamp(PTB18);
DigitalOut Garage_Door(PTB11);
DigitalIn  Car_Sensor(PTE25);
DigitalOut Fan (PTC12);
DigitalOut FrontDoor (PTE24);
DigitalOut Curtain (PTC7);

int main() {
    board_init();
    FrontDoor = Garage_Door = Curtain = Fan = 0;

    ThisThread::sleep_for(WAIT);

    //open door
    FrontDoor = 1;

    ThisThread::sleep_for(WAIT);

    //close door
    FrontDoor = 0;

    ThisThread::sleep_for(WAIT);

    //open garage
    Garage_Door = 1;

    ThisThread::sleep_for(WAIT);

    //close garage
    Garage_Door = 0;

    ThisThread::sleep_for(WAIT);

    //open curtain
    Curtain = 1;

    ThisThread::sleep_for(WAIT);

    //close curtain
    Curtain = 0;

    ThisThread::sleep_for(WAIT);

    //heater on
    pwm3.write(0.5); //heater on
    pwm3.period_ms(10);
    //turn on fan
    Fan = 1;

    ThisThread::sleep_for(WAIT);

    //turn on front door light
    //turn on garage light
    //turn on inside light
    //turn on garden light
    pwm0.write (0.5); //lights on!
    pwm0.period_ms(10);
    pwm1.write (0.5);
    pwm1.period_ms(10);  
    pwm2.write (0.5);
    pwm2.period_ms(10);
    Garden_Lamp = 1;

    while(true){
        //print temp inside
        printf("Temperature: %d\n", adc_read(0) );
        //print light outside
        printf("Light: %d\n", adc_read(1) );

        //print hall sensor trigger
        if (Car_Sensor == 0) {
            ThisThread::sleep_for(1s);
            printf("Hall sensor trigger!\n");
            ThisThread::sleep_for(WAIT);
        }

        ThisThread::sleep_for(1s);
    }

}