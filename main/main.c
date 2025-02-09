#include "main.h"

/* Function prototypes*/
void button_irq_handler(uint gpio, uint32_t events);


/* Global variables */

static ssd1306_t display_ssd;   //SSD1306 config pointer

static volatile absolute_time_t button_a_last_pressed_time;     //Stores the last time button A was pressed (debounce)
static volatile absolute_time_t button_b_last_pressed_time;     //Stores the last time button A was pressed (debounce)

static volatile bool led_green_state = false;   //State of the green led
static volatile bool led_blue_state = false;    //Satet of the blue led


int main(){
    PIO pio;
    char input_message[] = "Input:  ";


    /* Clock configuration for PIO*/
    if(set_sys_clock_khz(128000, false)){
        printf("Configuration of system clock completed!\n");
    }else{
        printf("Configuration of system clock failed\n");
        exit(-1);
    }


    /* GPIO initialization*/
    stdio_init_all();
    
    //Leds and pushbuttons
    gpio_init_mask(RGB_LED_MASK | BUTTONS_MASK);
    gpio_set_dir_masked(RGB_LED_MASK | BUTTONS_MASK, RGB_LED_MASK);
    
    gpio_pull_up(GPIO_BUTTON_A);
    gpio_pull_up(GPIO_BUTTON_B);

    // IRQ setup for the pushbuttons
    gpio_set_irq_enabled_with_callback(GPIO_BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);
    gpio_set_irq_enabled(GPIO_BUTTON_B, GPIO_IRQ_EDGE_FALL, true);


    /* Display initialization*/
    i2c_init(DISPLAY_I2C_PORT, DISPLAY_I2C_FREQ);

    gpio_set_function(DISPLAY_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(DISPLAY_I2C_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(DISPLAY_I2C_SDA);
    gpio_pull_up(DISPLAY_I2C_SCL);

    ssd1306_init(&display_ssd, WIDTH, HEIGHT, false, DISPLAY_I2C_ADDRESS, DISPLAY_I2C_PORT);
    ssd1306_config(&display_ssd);
    ssd1306_send_data(&display_ssd);


    /* Clear display */
    ssd1306_fill(&display_ssd, false);
    ssd1306_send_data(&display_ssd);

    /* Configure PIO*/
    pio = pio0;
    uint offset = pio_add_program(pio, &main_program);
    uint state_machine = pio_claim_unused_sm(pio, true);
    main_program_init(pio, state_machine, offset, GPIO_LED_MTX);
    
    /* Clear WS2812*/
    matrix_turn_all(pio, state_machine, 0, 0, 0);


    while (true) {
        /* Serial connection via USB cable fo the BitDogLab */
        if(stdio_usb_connected()){
            char char_input = getchar(); //blocking reading

            if (char_input != '\n'){
                // Display read input
                input_message[7] = char_input;
                
                ssd1306_rect(&display_ssd, 3, 3, 122, 58, true, false);                
                ssd1306_draw_string(&display_ssd, input_message, 8, 10);
                ssd1306_send_data(&display_ssd);
            }

            /* Display number in WS2812*/
            if(char_input >= '0' && char_input <= '9'){
                matrix_display_number(pio, state_machine, (uint8_t) char_input - '0');
            }else{
                matrix_turn_all(pio, state_machine, 0, 0, 0);
            }
        }
    }
}  

/*
*   @brief Callback for the pushbuttons IRQ
*/
void button_irq_handler(uint gpio, uint32_t events){

    absolute_time_t current_time = get_absolute_time(); //current absolute time for the debounce

    /* Routine for the pushbutton A*/
    if(gpio == GPIO_BUTTON_A && absolute_time_diff_us(button_a_last_pressed_time, current_time) > DEBOUNCE_TIME_US){
        button_a_last_pressed_time = current_time;
        
        //Toggle and update green led state
        led_green_state = !led_green_state;
        gpio_put(GPIO_GREEN_LED, led_green_state);
        
        /* Inform update: serial monitor and SSD1306*/
        printf("Button A pressed. Switching green LED state!\n");
        ssd1306_rect(&display_ssd, 3, 3, 122, 58, true, false);                
        ssd1306_draw_string(&display_ssd, (led_green_state) ? "Green: on " : "Green: off", 40, 50);
        ssd1306_send_data(&display_ssd);       
    
    } else if(gpio == GPIO_BUTTON_B && absolute_time_diff_us(button_b_last_pressed_time, current_time) > DEBOUNCE_TIME_US){
        /* Routine for the pushbutton A*/
        button_b_last_pressed_time = current_time;
        
        //Toggle and update green led state
        led_blue_state = !led_blue_state;   //toggle blue led state
        gpio_put(GPIO_BLUE_LED, led_blue_state);
        
        /* Inform update: serial monitor and SSD1306*/
        printf("Button B pressed. Switching blue LED state!\n"); 
        ssd1306_rect(&display_ssd, 3, 3, 122, 58, true, false);                
        ssd1306_draw_string(&display_ssd, (led_blue_state) ? "Blue:  on " : "Blue:  off", 40, 40);
        ssd1306_send_data(&display_ssd);   

    }
}