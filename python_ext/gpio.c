#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "gpio.h"

/*
 *  *设置GPIO模式INPUT, OUTPUT, PWM_OUTPUT or GPIO_CLOCK
 *   */
int gpio_pinMode(int who,int mode)
{
    pinMode(who,mode);
    return 0;
}
/*
 *  *设置上拉、下拉或悬空模式 :PUD_OFF、PUD_DOWN、PUD_UP
 *   */
int gpio_set_pullUpDnCtl(int who,int mode)
{
    pullUpDnControl(who,mode);
    return 0;
}
/*
 *  * gpio 写 HIGH or LOW (1 or 0)
 *   */
int gpio_write(int who,int value)
{
    digitalWrite(who,value);
    return 0;
}
/*
 *  *gpio 读
 *   */
int gpio_read(int who)
{
    return digitalRead(who);
}
/*
 *  *gpio PWM 写
 *   */
int gpio_pwm_write(int who,int value)
{
    pwmWrite(who,value);
    return 0;
}
