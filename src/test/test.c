#include<msp430.h>
#include"drivers/io.h"

static void test_blink_led(void)
{
    const struct io_config led_config =
    {
     .dir = IO_DIR_OUTPUT,
     .select = IO_SELECT_GPIO,
     .res = IO_RESISTOR_DISABLED,
     .out = IO_OUT_LOW
    };
    io_configuration(IO_TEST_LED, &led_config);
    io_out_e out = IO_OUT_LOW;
    while(1)
    {
        out = (out == IO_OUT_LOW) ? IO_OUT_HIGH : IO_OUT_LOW ;
        io_set_out(IO_TEST_LED,out);
        __delay_cycles(100000); // internal delay function 250 ms
    }
}
int main(void)
{
    WDTCTL =WDTPW + WDTHOLD; // stop watchdog timer
    test_blink_led();

}

