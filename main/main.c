#include "main.h"

/* Function prototypes*/



void press_handler(uint gpio, uint32_t events){

    reset_usb_boot(0,0);

}

int main(){

    ssd1306_t display_ssd;

    stdio_init_all();

    gpio_init(5);
    gpio_set_dir(5, GPIO_IN);
    gpio_pull_up(5);

    gpio_set_irq_enabled_with_callback(5, GPIO_IRQ_EDGE_FALL, true, &press_handler);

    /* Display initialization*/
    i2c_init(DISPLAY_I2C_PORT, DISPLAY_I2C_FREQ);

    gpio_set_function(DISPLAY_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(DISPLAY_I2C_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(DISPLAY_I2C_SDA);
    gpio_pull_up(DISPLAY_I2C_SCL);

    ssd1306_init(&display_ssd, WIDTH, HEIGHT, false, DISPLAY_I2C_ADDRESS, DISPLAY_I2C_PORT);
    ssd1306_config(&display_ssd);
    ssd1306_send_data(&display_ssd);


    /* Clean display */
    ssd1306_fill(&display_ssd, false);
    ssd1306_send_data(&display_ssd);

    while (true) {
        ssd1306_draw_string(&display_ssd, "The Quick", 8, 10);
        ssd1306_draw_string(&display_ssd, "Brown fox", 20, 30);
        ssd1306_draw_string(&display_ssd, "Jumps Over", 15, 48);
        ssd1306_send_data(&display_ssd);

        sleep_ms(1000);

    }
}
