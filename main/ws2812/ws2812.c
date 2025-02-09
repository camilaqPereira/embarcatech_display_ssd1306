#include "ws2812.h"



/* Definicao de constantes*/
const uint GPIO_LED_MTX = 7;

const double BLUE_INTENSITY = 0.1;
const double RED_INTENSITY = 0;
const double GREEN_INTENSITY = 0.1;

const uint numbers_mapping[10][MTX_NUM_ROWS][MTX_NUM_ROWS] = {
    //0
    {
        { 0, 1, 1, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 1, 1, 1, 0 }
    },
    //1
    {
        { 0, 0, 1, 0, 0 },
        { 0, 1, 1, 0, 0 },
        { 0, 0, 1, 0, 0 },
        { 0, 0, 1, 0, 0 },
        { 0, 1, 1, 1, 0 },
    },
    //2
    {
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 1, 0, 0, 0 },
        { 0, 1, 1, 1, 0 }
    },
    //3
    {
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 1, 1, 1, 0 }
    },
    //4
    {
        { 0, 1, 0, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 0, 0, 1, 0 }
    },
    //5
    {
        { 0, 1, 1, 1, 0 },
        { 0, 1, 0, 0, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 1, 1, 1, 0 }
    },
    //6
    {
        { 0, 1, 1, 1, 0 },
        { 0, 1, 0, 0, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 1, 1, 1, 0 }
    },
    //7
    {
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 0, 0, 1, 0 }
    },
    //8
    {
        { 0, 1, 1, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 1, 1, 1, 0 }
    },
    //9
    {
        { 0, 1, 1, 1, 0 },
        { 0, 1, 0, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
        { 0, 1, 1, 1, 0 }
    }
};




uint32_t matrix_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}



void matrix_turn_all(PIO pio, uint state_machine, double red, double green, double blue){
    uint32_t led_value = matrix_rgb(blue, red, green);

    for (int i = 0; i < MTX_NUM_LEDS; i++){
        pio_sm_put_blocking(pio, state_machine, led_value);
    }
}

void matrix_display_number(PIO pio, uint state_machine, uint8_t value){
    uint32_t led_value;
    uint pixel_status;

    for (size_t i = 0; i < MTX_NUM_ROWS; i++){
        for (size_t j = 0; j < MTX_NUM_ROWS; j++){

            pixel_status = (i & 1) ? numbers_mapping[value][4-i][j] : numbers_mapping[value][4-i][4-j];
            
            led_value = matrix_rgb(pixel_status*BLUE_INTENSITY, pixel_status*RED_INTENSITY, pixel_status*GREEN_INTENSITY);
            pio_sm_put_blocking(pio, state_machine, led_value);
            
        }
        
    }
    

}
