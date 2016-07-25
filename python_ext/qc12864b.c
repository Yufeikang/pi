//
// Created by kang on 7/25/16.
//

#include "qc12864b.h"
#include <wiringPi.h>
#include <stdio.h>
#include <zconf.h>
// GPIO high (3.3V or 5V)
#define HIGH 1

// GPIO low (0V)
#define LOW 0

#define uchar unsigned char
#define uint  unsigned int

static int CS=21;
static int SID=22;
static int SCLK=23;

static void udelay(unsigned int t)
{
    usleep(t);
}

/********************************************************************
* 名称 : sendbyte()
* 功能 : 按照液晶的串口通信协议，发送数据
* 输入 : zdata
* 输出 : 无
***********************************************************************/
void sendbyte(unsigned char zdata)
{
    unsigned int i;
    for(i=0; i<8; i++)
    {
        if((zdata << i) & 0x80)
        {
            digitalWrite(SID,1);
        }
        else
        {
            digitalWrite(SID,0);
        }
        digitalWrite(SCLK,0);
        udelay(10);
        digitalWrite(SCLK,1);
    }
}

/********************************************************************
* 名称 : write_com()
* 功能 : 写串口指令
* 输入 : cmdcode
* 输出 : 无
***********************************************************************/
void write_com(unsigned char cmdcode)
{
    digitalWrite(CS,1);
    sendbyte(0xf8);
    sendbyte(cmdcode & 0xf0);
    sendbyte((cmdcode << 4) & 0xf0);
    udelay(2);
}

/********************************************************************
* 名称 : write_data()
* 功能 : 写串口指令
* 输入 : cmdcode
* 输出 : 无
***********************************************************************/
void write_data(unsigned char Dispdata)
{
    digitalWrite(CS,1);
    sendbyte(0xfa);
    sendbyte(Dispdata & 0xf0);
    sendbyte((Dispdata << 4) & 0xf0);
    udelay(2);
}

/********************************************************************
* 名称 : lcdinit()
* 功能 : 初始化函数
* 输入 : cmdcode
* 输出 : 无
***********************************************************************/
void lcdinit()
{
    pinMode(CS, OUTPUT);
    pinMode(SID, OUTPUT);
    pinMode(SCLK,OUTPUT);
    udelay(200);
    write_com(0x30);
    udelay(50);
    write_com(0x0c);
    udelay(50);
}

/********************************************************************
* 名称 : show()
* 功能 : 显示字符串
* 输入 : *s
* 输出 : 无
***********************************************************************/
void lcd_show(unsigned char *s)
{
    while(*s > 0)
    {
        write_data(*s);
        s++;
        udelay(50);
    }
}



