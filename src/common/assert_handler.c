#include "common/assert_handler.h"
#include "common/defines.h"
#include "drivers/uart.h"
#include "external/printf/printf.h"
#include <msp430.h>
#include <stdint.h>

#define BREAKPOINT __asm volatile("CLR.B R3");
//                             Text + PC + Null Termination
#define ASSERT_STRING_MAX_SIZE (15u + 6u + 1u)

static void assert_trace(uint16_t program_counter)
{
    // UART Tx
    P1SEL |= BIT1;
    P1SEL2 |= BIT1;
    uart_init_assert();

    char assert_string[ASSERT_STRING_MAX_SIZE];
    snprintf(assert_string, sizeof(assert_string), "ASSERT 0x%x \n", program_counter);
    uart_trace_assert(assert_string);
}

void assert_blink_led(void)
{
    P1SEL &= ~(BIT0);
    P1SEL2 &= ~(BIT0);
    P1DIR |= BIT0;
    P1REN &= ~(BIT0);

    while (1) {
        // Blink LED
        P1OUT ^= BIT0;
        BUSY_WAIT_ms(250);
    }
}

void assert_handler(uint16_t program_counter)
{

    BREAKPOINT
    assert_trace(program_counter);
    assert_blink_led();
}
