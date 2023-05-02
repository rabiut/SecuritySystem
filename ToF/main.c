#include <stdio.h>
#include <unistd.h>
#include "VL53L1X_api.h"
#include <stdlib.h>
#include <stdint.h>

const char *image_folder = "/home/pi/PiCam";


#define LOW 0
#define HIGH 1

int main() {
    uint16_t dev = 0x29;
    int status = 0;
    int adapter_nr = 1;
    uint8_t I2cDevAddr = 0x29;
    VL53L1X_Result_t Results;

    /*GPIO Controls*/
    int rslt;
    int num;

    if (0 == (status = VL53L1X_UltraLite_Linux_I2C_Init(dev, adapter_nr, I2cDevAddr))) {
        printf("Sensor successfully initialized!\n");
    } else {
        printf("Sensor initialization failed with error code: %d\n", status);
        return 1;
    }

    VL53L1X_SensorInit(dev);
    VL53L1X_SetDistanceMode(dev, 1); // 1 = short range, 2 = long range
    VL53L1X_SetTimingBudgetInMs(dev, 20); // 20 ms is the minimum
    VL53L1X_SetInterMeasurementInMs(dev, 25); // 25 ms is the minimum
    VL53L1X_StartRanging(dev);

    uint8_t isDataReady;
    uint16_t distance;

    while (1) {
        VL53L1X_CheckForDataReady(dev, &isDataReady);

        if (isDataReady) {
            VL53L1X_GetResult(dev, &Results);
            printf("Measured distance: %d mm\n", Results.Distance);
            VL53L1X_ClearInterrupt(dev);
        }

        


        /******GPIO CONTROL*/
        rslt;
        num;

        num=13;
        rslt = export_pin(num);
        sleep(1);
        rslt = set_direction("out", num);
        rslt = set_value(LOW, num);

        while(Results.Distance<=100){
            rslt = set_value(HIGH, num);//Turn on LED
            // if (Results.Distance <= 100) {
            //     printf("Motion Detected!\n");
            //     // Generate the command for capturing the image
            //     char command[256];
            //     //snprintf(command, sizeof(command), "libcamera-still -o %s/test.jpg", image_folder);
            //     snprintf(command, sizeof(command), "libcamera-still --width 640 --height 480 --shutter 10000 --quality 50 -o %s/test.jpg", image_folder);

            //     // Execute the command to take a picture and store it in the folder
            //     system(command);
            // }
             if (Results.Distance <= 100) {
                printf("Motion Detected!\n");
                // Generate the command for capturing the image
                char command[256];
                // Use 'fswebcam' instead of 'libcamera-still' to capture the image with the USB camera
                snprintf(command, sizeof(command), "fswebcam --no-banner --resolution 640x480 --jpeg 50 -S 5 -r 640x480 %s/test.jpg", image_folder);

                // Execute the command to take a picture and store it in the folder
                system(command);
            }
            VL53L1X_GetResult(dev, &Results);
            sleep(2);
        }
        rslt = set_value(LOW, num);//


        usleep(100000); // Wait for 25 ms
    }


    rslt = set_value(LOW, num);
    rslt = set_direction("in", num);
    rslt = unexport_pin(num);   
    return 0;
}