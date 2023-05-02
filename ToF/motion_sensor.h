#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include <stdio.h>
#include <curl/curl.h>

int send_motion_sensor_data(const char *image_path, const char *info_text, const char *url);

#endif // MOTION_SENSOR_H
