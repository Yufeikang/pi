#ifndef _RX433M_H_
#define _RX433M_H_

/*
 *设置GPIO模式INPUT, OUTPUT, PWM_OUTPUT or GPIO_CLOCK
 */
int gpio_pinMode(int who,int mode);
/*
 *设置上拉、下拉或悬空模式 :PUD_OFF、PUD_DOWN、PUD_UP
 */
int gpio_set_pullUpDnCtl(int who,int mode);
/*
 * gpio 写 HIGH or LOW (1 or 0)
 */
int gpio_write(int who,int value);
/*
 *gpio 读
 */
int gpio_read(int who);
/*
 *gpio PWM 写
 */
int gpio_pwm_write(int who,int value);

#endif
