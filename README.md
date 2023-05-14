# SecuritySystem
Develops a simple, homemade security system that utilizes a ToF (vl53l1x) sensor to detect motion, and a camera (pi cam or any usb cam) to capture instance. 
## Getting Started

Ensure to run the make file prior to using "run" command i.e (./main)
### Prerequisites

on raspberrry pi: libfuse2 (for c/c++), libcamera, as well as visual studio packages (optional)


## Additional Settings
image config:
User Controls

                     brightness 0x00980900 (int)    : min=30 max=255 step=1 default=133 value=100
                       contrast 0x00980901 (int)    : min=0 max=10 step=1 default=5 value=5
                     saturation 0x00980902 (int)    : min=0 max=200 step=1 default=83 value=150
        white_balance_automatic 0x0098090c (bool)   : default=1 value=1
           power_line_frequency 0x00980918 (menu)   : min=0 max=2 default=2 value=2
      white_balance_temperature 0x0098091a (int)    : min=2800 max=10000 step=1 default=4500 value=4500 flags=inactive
                      sharpness 0x0098091b (int)    : min=0 max=50 step=1 default=25 value=25
         backlight_compensation 0x0098091c (int)    : min=0 max=10 step=1 default=0 value=0

Camera Controls

                  auto_exposure 0x009a0901 (menu)   : min=0 max=3 default=1 value=3
         exposure_time_absolute 0x009a0902 (int)    : min=5 max=20000 step=1 default=156 value=156 flags=inactive
                   pan_absolute 0x009a0908 (int)    : min=-201600 max=201600 step=3600 default=0 value=0
                  tilt_absolute 0x009a0909 (int)    : min=-201600 max=201600 step=3600 default=0 value=0
                  zoom_absolute 0x009a090d (int)    : min=0 max=10 step=1 default=0 value=0
![image](https://github.com/rabiut/SecuritySystem/assets/90636484/f4475c60-2bb9-4cbd-b674-8c619fab6335)
