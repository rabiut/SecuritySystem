CC = gcc
CFLAGS = -g -Wall

SRCS = main.c VL53L1X_api.c VL53L1X_calibration.c vl53l1_linux_platform.c gpio.c capture_image.c motion_sensor.c -lcurl
OBJS = $(SRCS:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)
