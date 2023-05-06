#include "capture_image.h"
#include <stdio.h>
#include <stdlib.h>

void capture_image(VL53L1X_Result_t Results, const char *image_folder) {
    //if (Results.Distance <= 100) {

        printf("Motion Detected!\n");

        // Generate the command for capturing the image
        char command[256];
        // Use 'fswebcam' instead of 'libcamera-still' to capture the image with the USB camera
        snprintf(command, sizeof(command), "fswebcam --no-banner --resolution 720x480 --jpeg 50 -S 10 -r 720x480 %s/security_cam.jpg", image_folder);
        // snprintf(command, sizeof(command), "fswebcam --no-banner -r 640x480 %s/security_cam.jpg", image_folder);
        // Execute the command to take a picture and store it in the folder
        system(command);
    //}
}


//to use pi cam

// if (Results.Distance <= 100) {
            //     printf("Motion Detected!\n");
            //     // Generate the command for capturing the image
            //     char command[256];
            //     //snprintf(command, sizeof(command), "libcamera-still -o %s/test.jpg", image_folder);
            //     snprintf(command, sizeof(command), "libcamera-still --width 640 --height 480 --shutter 10000 --quality 50 -o %s/test.jpg", image_folder);

            //     // Execute the command to take a picture and store it in the folder
            //     system(command);
            // }