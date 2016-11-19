//
// Created by kang on 7/25/16.
//

#include "python_warpper.h"
#include <wiringPi.h>
#include <stdio.h>
#include "gpio.h"
#define IS_INITED 0
#define ISNOT_INIT 1
static int g_isInited=ISNOT_INIT;
/*
 * init
 */
static PyObject *Init(PyObject *self, PyObject *args){

    wiringPiSetup();
    lcdinit();
    //rx433_init();
    g_isInited=IS_INITED;
    return Py_BuildValue("i",0);
}

static PyObject *GetAM2301Data(PyObject *self, PyObject *args)
{
    if(g_isInited!=IS_INITED){
        return NULL;
    }

    am2301_data_t data;
    data = get_am2301_data();

    return Py_BuildValue("ffi",data.humidity,data.temperature,data.status);
}

static PyObject *LcdSendCmd(PyObject *self,PyObject *args){
   if(g_isInited!=IS_INITED){
	return NULL;
    }
   unsigned char cmd;
   if(!PyArg_ParseTuple(args,"b",&cmd)){
	return NULL;
   }
   write_com(cmd);
   return Py_BuildValue("i",0);
}

static PyObject *LcdShow(PyObject *self,PyObject *args){
    if(g_isInited!=IS_INITED){
        return NULL;
    }
    char *data=NULL;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "y#", &data,&len)) {
        return NULL;
    }
    lcd_show(data);
    return Py_BuildValue("i",1);
}

static PyObject *GPIOSetMode(PyObject *self,PyObject *args){
    if(g_isInited!=IS_INITED){
        return NULL;
    }
    int who,mode;
    char* p_mode=NULL;
    Py_ssize_t len;
    if (!PyArg_ParseTuple(args, "iy#", &who,&p_mode,&len)) {
        printf("GPIOSetMode ParseTuple Fail! %s \n",p_mode);
        return NULL;
    }

    printf("GPIOSetMode ParseTuple! %s \n",p_mode);
    if(strcmp(p_mode,"INPUT")==0){
        mode=INPUT;
    }
    else if(strcmp(p_mode,"OUTPUT")==0){
        mode=OUTPUT;
    }
    printf("set mode:%s %d\n",p_mode,mode);
    gpio_pinMode(who,mode);
    return Py_BuildValue("i",1);

}
static PyObject *GPIOSetPullUpDn(PyObject *self,PyObject *args){
        if(g_isInited!=IS_INITED){
                  return NULL;
              }
        int who,mode;
        char* p_mode=NULL;
        Py_ssize_t len;
        if (!PyArg_ParseTuple(args, "iy#", &who,&p_mode,&len)) {
                  return NULL;
        }
        if(strcmp(p_mode,"PUD_OFF")==0){
            mode=PUD_OFF;
        }
        else if(strcmp(p_mode,"PUD_DOWN")==0){
            mode=PUD_DOWN;
        }
        else if(strcmp(p_mode,"PUD_UP")==0){
            mode=PUD_UP;
        }
        gpio_set_pullUpDnCtl(who,mode);
        printf("set mode:%s %d\n",p_mode,mode);
        return Py_BuildValue("i",1);
}
static PyObject *GPIODWrite(PyObject *self,PyObject *args){
          if(g_isInited!=IS_INITED){
                              return NULL;
                          }
          int who,mode;
          if (!PyArg_ParseTuple(args, "ii", &who,&mode)) {
                              return NULL;
                          }
          gpio_write(who,mode);
          return Py_BuildValue("i",1);
  }

/* Module method table */
static PyMethodDef SampleMethods[] = {
        {"Init",  Init, METH_VARARGS, "native init Gpio"},
        {"GetAM2301Data", GetAM2301Data, METH_VARARGS, "GetAM2301Data "},
        {"LcdSendCmd", LcdSendCmd, METH_VARARGS, "LcdShow data"},
        {"LcdShow", LcdShow, METH_VARARGS, "LcdShow data"},
        {"GPIOSetMode",GPIOSetMode, METH_VARARGS, "GPIOSetMode data"},
        {"GPIOSetPullUpDn", GPIOSetPullUpDn, METH_VARARGS, "GPIOSetPullUpDn data"},
        {"GPIODWrite", GPIODWrite, METH_VARARGS, "GPIODWrite data"},
        { NULL, NULL, 0, NULL}
};

/* Module structure */
static struct PyModuleDef samplemodule = {
        PyModuleDef_HEAD_INIT,

        "SensorLib",           /* name of module */
        "SensorLib by C",  /* Doc string (may be NULL) */
        -1,                 /* Size of per-interpreter state or -1 */
        SampleMethods       /* Method table */
};

/* Module initialization function */
PyMODINIT_FUNC
PyInit_SensorLib(void) {
    return PyModule_Create(&samplemodule);
}
