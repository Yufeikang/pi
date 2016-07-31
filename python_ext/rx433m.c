#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "rx433m.h"
#define rx433_PIN 25
void rx433m_interrupt(void){

    if(digitalRead(rx433_PIN)==1){
        struct timespec start_time;
        struct timespec stop_time;
        clock_gettime(CLOCK_REALTIME,&start_time); // ms
        long loop_count=0;
        while(digitalRead(rx433_PIN)==0){
            loop_count++;
            if(loop_count>1000000){
                break;
            }
            usleep(1);
        }
        clock_gettime(CLOCK_REALTIME,&stop_time);
        double  split_time =(stop_time.tv_nsec-start_time.tv_nsec)/1000000.0;//ms
        if(split_time<=0.2){
           printf("time_split<0.2ms split_time=%f  time=%d\n",split_time,stop_time.tv_nsec/1000);
            return ;
        }
        if(loop_count>=1000000){
            printf("time out\n");
            return;
        }
        printf("433m RX HIGHT :%3.2fms\n",split_time);
    }
}
void rx433m_interrupt_test(void){
    if(digitalRead(rx433_PIN)!=1){
        return;
    }
    static struct timespec start_time,stop_time;
    // 低电平持续时间
    clock_gettime(CLOCK_REALTIME,&start_time);
    long low_time = start_time.tv_nsec-stop_time.tv_nsec;
    printf("Low   Time :%05.2f us form %012.3f us to %012.3f us\n",\
            low_time/1000.0,stop_time.tv_nsec/1000.0,\
            start_time.tv_nsec/1000.0);
    long loop_count=0;
    while(digitalRead(rx433_PIN)==0){
        // 等待地点评出现
        loop_count++;
        if(loop_count>1000000){
            clock_gettime(CLOCK_REALTIME,&stop_time);
            printf("TimeOut!\n");
            return;
        }
        usleep(1);
    }
    clock_gettime(CLOCK_REALTIME,&stop_time);
    long hight_time = stop_time.tv_nsec-start_time.tv_nsec;
    printf("Hight Time :%05.2f us form %012.3f us to %012.3f us\n",\
            hight_time/1000.0,start_time.tv_nsec/1000.0,\
            stop_time.tv_nsec/1000.0);
}

int rx433_init(){
    wiringPiISR(rx433_PIN,INT_EDGE_RISING,rx433m_interrupt_test);
}
