#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/bootrom.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "ssd1306/ssd1306.h"
#include "ws2812/ws2812.h"

#include "main.pio.h"

#define DISPLAY_I2C_SDA 14          // GPIO SSD1306 SDA
#define DISPLAY_I2C_SCL 15          //GPIO SSD1306 SCL
#define DISPLAY_I2C_PORT i2c1       // GPIO SSD1306 PORT
#define DISPLAY_I2C_FREQ 400000     //DISPLAY I2C FREQUENCY
#define DISPLAY_I2C_ADDRESS 0x3c    //DISPLAY I2C ADDRESS

#define GPIO_BUTTON_A 5     //GPIO pushbutton A
#define GPIO_BUTTON_B 6     //GPIO pushbutton B
#define GPIO_GREEN_LED 11   //GPIO green led
#define GPIO_BLUE_LED 12    //GPIO blue led

#define RGB_LED_MASK 0b1100000000000    //Initialization mask for LEDs
#define BUTTONS_MASK 0b1100000          //Initialization mask for pushbuttons

#define DEBOUNCE_TIME_US 200000         //Debounce time




#endif