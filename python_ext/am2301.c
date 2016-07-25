//
// Created by kang on 7/25/16.
//

#include "am2301.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <zconf.h>
#include <time.h>

// GPIO pin for input and output, GPIO24
// note that physical connector pin number is different
static int am2301_gpio = 24;

// if no data, loop max count and exit
#define MAX_LOOP_COUNT 10000

// GPIO high (3.3V or 5V)
#define HIGH 1

// GPIO low (0V)
#define LOW 0




void udelay(unsigned int us)
{
    usleep(us);
}
/*
 * Wait until GPIO changes to state
 *
 * returns 0 if changed successfully, 1 if no change
 */
int wait_for_gpio(int state)
{
    int i;

    /// MAX_LOOP_COUNT prevents driver from crashing when there is no data
    for (i=0; i<MAX_LOOP_COUNT; i++) {
        if (digitalRead(am2301_gpio) == state) {
            return 0;
        }
    }

    // always fail if max loop count hit
    return 1;
}

am2301_data_t get_am2301_data()
{
    am2301_data_t am2301_data;
    memset(&am2301_data,0, sizeof(am2301_data));
    int i, res;
    int databyte = 0L;
    int d = 0, b = 0;
    int data[5];
    int humidity,temperature;

    time_t start, stop;
    int nodata_error = 0; // 1 if no data from AM2301

    pinMode(am2301_gpio, OUTPUT);

    udelay(2000);

    /*
     * Set pin low and wait for at least 800 us.
     * Set it high again, then wait for the sensor to put out a low pulse.
     */
    digitalWrite(am2301_gpio, LOW);
    udelay(1000);

    // Disable interrupts during measurement, this is critical for
    // reliable time measurements when receiving high speed data.
    // All Kernel interrupts are disabled for about 2-3 milliseconds.


    digitalWrite(am2301_gpio, 1);

    pinMode(am2301_gpio,INPUT);

    nodata_error |= wait_for_gpio(LOW);
    nodata_error |= wait_for_gpio(HIGH);
    nodata_error |= wait_for_gpio(LOW);


    for ( i=0; i<40; i++) {
        wait_for_gpio(HIGH);

        // now measure length of high state in nanoseconds

        start = time(NULL);
        wait_for_gpio(LOW);
        stop = time(NULL);
        res = (int)(stop - start);

        // 1st data bit is shorter, why ?

        if ((i==0 && res > 29000) || ( i!=0 && res > 40000)) {
            databyte|=0x01;
        }
        d++;
        if (d==8) {
            d=0;
            data[b]=databyte;
            b=b+1;
            databyte=0x00;
        }
        databyte<<=1;
    }

    wait_for_gpio(HIGH);

    pinMode(am2301_gpio, OUTPUT);

    if (((data[0] + data[1] + data[2] + data[3]) & 0xff) == data[4]) {
        am2301_data.status=AM2301_STATUS_OK
    } else  {
        am2301_data.status=AM2301_STATUS_ERR;
    }
    if (nodata_error) {
        am2301_data.status=AM2301_STATUS_NODATA;
    }

    // check flag for negative temperatures
    humidity = ((data[0]<<8) + data[1] );

    if (data[2] & 0x80) {
        data[2] = data[2] & 0x7f;
        temperature  = (data[2]<<8) + data[3];
        am2301_data.humidity= (float) (humidity / 10.0);
        am2301_data.temperature= (float) (temperature / 10.0);
    } else {
        temperature = (data[2]<<8) + data[3];
        am2301_data.humidity= (float) (humidity / 10.0);
        am2301_data.temperature= (float) (temperature / 10.0);
    }

    return am2301_data;
}


