#ifndef RESPONSE_CI_H
#define RESPONSE_CI_H
#include "main.h"
#include "stm32h7xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

void response_print(const char* str, ...);

#endif
