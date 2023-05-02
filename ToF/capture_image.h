#ifndef CAPTURE_IMAGE_H
#define CAPTURE_IMAGE_H

#include "VL53L1X_api.h"
#include <stdint.h>

void capture_image(VL53L1X_Result_t Results, int count, int *extxp, const char *image_folder);

#endif // CAPTURE_IMAGE_H
