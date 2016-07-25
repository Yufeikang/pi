//
// Created by kang on 7/25/16.
//

#ifndef PI_AM2301_H
#define PI_AM2301_H

#define AM2301_STATUS_OK 0;
#define AM2301_STATUS_ERR 1;
#define AM2301_STATUS_NODATA 2;

typedef struct _am2301_data_t{
    float temperature;
    float humidity;
    int status;
}am2301_data_t;


am2301_data_t get_am2301_data();
#endif //PI_AM2301_H
