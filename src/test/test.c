#include "drivers/io.h"
#include "drivers/mcu_init.h"
#include "common/defines.h"
#include "common/trace.h"
#include "external/printf/printf.h"
#include "common/assert_handler.h"
#include <msp430.h>

SUPPRESS_UNUSED
static void test_setup(void)
{
    mcu_init();
}

SUPPRESS_UNUSED
static void test_assert(void)
{
    test_setup();
    ASSERT(0);
}

SUPPRESS_UNUSED
static void test_blink_led(void)
{
    const struct io_config led_config = { .dir = IO_DIR_OUTPUT,
                                          .select = IO_SELECT_GPIO,
                                          .res = IO_RESISTOR_DISABLED,
                                          .out = IO_OUT_LOW };
    io_configuration(IO_TEST_LED, &led_config);
    io_out_e out = IO_OUT_LOW;
    while (1) {
        out = (out == IO_OUT_LOW) ? IO_OUT_HIGH : IO_OUT_LOW;
        io_set_out(IO_TEST_LED, out);
        __delay_cycles(100000); // internal delay function 250 ms
    }
}

SUPPRESS_UNUSED
static void test_uart(void)
{
    test_setup(); // stop watchdog timer
    trace_init();
    __enable_interrupt();
    while (1) {
        _putchar('V');
        _putchar('I');
        _putchar('\n');
        BUSY_WAIT_ms(100);
    }
}

SUPPRESS_UNUSED
static void test_trace(void)
{
    test_setup();
    trace_init();
    __enable_interrupt();

    while (1) {
        TRACE("Trace called here %d", 905);
        BUSY_WAIT_ms(100);
    }
}
int main()
{
    test_assert();
}
