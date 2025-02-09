#ifndef WS2812_H
#define WS2812_H


#include "pico/stdlib.h"
#include "hardware/pio.h"

#define MTX_NUM_LEDS 25 //Total de leds na matriz
#define MTX_NUM_ROWS 5 //Numero de linhas na matriz

extern const uint GPIO_LED_MTX; // GPIO da matriz de leds
extern const uint numbers_mapping[10][MTX_NUM_ROWS][MTX_NUM_ROWS];  //Numbers frames

extern const double RED_INTENSITY;      //Intensity of the red RGB
extern const double BLUE_INTENSITY;     //Intensity of the blue RGB
extern const double GREEN_INTENSITY;    //Intensity of the green RGB

/*
*   @brief Função para definir a intensidade de cores do LED
*/
uint32_t matrix_rgb(double b, double r, double g);


void matrix_turn_all(PIO pio, uint state_machine, double red, double green, double blue);


/*
*   @brief When called, this function displays the digit on the WS2812 corresponding 
*   to the counter value mtx_counter
*/
void matrix_display_number(PIO pio, uint state_machine, uint8_t value);

#endif