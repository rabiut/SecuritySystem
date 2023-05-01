#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO_ROOT "/sys/class/gpio"
#define EXPORT "/sys/class/gpio/export"
#define UNEXPORT "/sys/class/gpio/unexport"

#define LOW 0
#define HIGH 1

int export_pin(int num);
int unexport_pin(int num);
int set_direction(char *mode, int num);
int set_value(int val, int num);

#endif // GPIO_CONTROL_H
