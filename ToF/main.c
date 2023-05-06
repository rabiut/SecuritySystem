#include <stdio.h>
#include <unistd.h>
#include "VL53L1X_api.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h> // Add this include to use the bool data type
#include "capture_image.h"

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "motion_sensor.h"


const char *image_folder = "/home/pi/PiCam";
const char *image_path = "/home/pi/PiCam/security_cam.jpg";
const char *info_text = "Motion detected";
const char *url = "http://192.168.2.20:5000/motion-sensor";
int start=0;

#define LOW 0
#define HIGH 1

int main() {
    uint16_t dev = 0x29;
    int status = 0;
    int adapter_nr = 1;
    uint8_t I2cDevAddr = 0x29;
    VL53L1X_Result_t Results;
    int count = -1;

    bool data_sent; // Add this flag to track whether the data has been sent or not

    int range_detect;
    int range_mode = 2; //1 for short range   2 for long

    if (range_mode == 1){
        range_detect = 100;
    }
    else{
        range_detect = 1000;
    }

    
    // Create the folder if it doesn't exist
    if (mkdir(image_folder, 0755) == -1) {
        if (errno != EEXIST) {
            perror("Error creating image folder");
        return 1;
        }
    }

    
    //code starts here

    if (0 == (status = VL53L1X_UltraLite_Linux_I2C_Init(dev, adapter_nr, I2cDevAddr))) {
        printf("Sensor successfully initialized!\n");
    } else {
        printf("Sensor initialization failed with error code: %d\n", status);
        return 1;
    }

    VL53L1X_SensorInit(dev);
    VL53L1X_SetDistanceMode(dev, range_mode); // 1 = short range, 2 = long range
    VL53L1X_SetTimingBudgetInMs(dev, 20); // 20 ms is the minimum
    VL53L1X_SetInterMeasurementInMs(dev, 25); // 25 ms is the minimum
    VL53L1X_StartRanging(dev);

    uint8_t isDataReady;
    uint16_t distance;

    while (1) {
        VL53L1X_CheckForDataReady(dev, &isDataReady);
        //Results.Distance = 3000;
        if (isDataReady) {
            VL53L1X_GetResult(dev, &Results);
            printf("MEASUREMENTS: %u, %u, %u, %u, %u\r\n", Results.Status, Results.Distance, Results.SigPerSPAD, Results.Ambient, Results.NumSPADs);
            printf("Distance: %d mm\n", Results.Distance);
            VL53L1X_ClearInterrupt(dev);
        }
        if(Results.Status!=0)
            continue;
        bool extxp = false;//take one picture during extended exposure
        while (Results.Distance<=range_detect){
            if (extxp == false){ 
                capture_image(Results, image_folder);//camera
                //send_motion_sensor_data(image_path, info_text, url);
            }
            else{//true
                //printf("Extended Exposure...");
                //do nothing
            }
            VL53L1X_GetResult(dev, &Results);
            if ((int) Results.Distance <= range_detect){ 
                extxp = true;
            }
            else{
                extxp = false;
            }
            sleep(2);
        }

        usleep(100000); // Wait for 25 ms
    }
    return 0;
}