#include "drivers/uart.h"
#include "common/defines.h"
#include "common/ring_buffer.h"
#include <msp430.h>
#include <assert.h>
#include <stdint.h>

#define SMCLK (1000000u)
#define BAUD_RATE (9600u)
#define BRCLK (SMCLK)
static_assert(BAUD_RATE < (BRCLK / 3.0f),
              "Baud-rate must be smaller than 1/3rd of input clock in low-frequency mode");
#define UART_PRESCLAR ((float)BRCLK / BAUD_RATE)
static_assert(UART_PRESCLAR < 0xFFFFu, "Sanity check UART-presclar fits in 16 bits");
#define UART_PRESCLAR_INT ((uint16_t)UART_PRESCLAR)
#define UART_PRESCLAR_INT_LOWER_BYTE (UART_PRESCLAR_INT & 0xFF)
#define UART_PRESCLAR_INT_UPPER_BYTE (UART_PRESCLAR_INT >> 8)
#define UART_PRESCLAR_FRACTIONAL (UART_PRESCLAR - UART_PRESCLAR_INT)
#define UART_UCBRS ((uint8_t)(8 * UART_PRESCLAR_FRACTIONAL))
#define UART_UCBRF (0u)
#define UART_UC0S16 (0u)
static_assert(UART_UCBRS < 8, "UCBRS should be less than equal to 7(3 bit number)");

#define UART_BUFFER_SIZE (16)
static uint8_t buffer[UART_BUFFER_SIZE];

struct ring_buffer tx_buffer = { .size = sizeof(buffer), .head = 0, .tail = 0, .buffer = buffer };

static inline void uart_enable_tx_interrupt(void)
{
    UC0IE |= UCA0TXIE;
}

static inline void uart_disable_tx_interrupt(void)
{
    UC0IE &= ~UCA0TXIE;
}

static inline void uart_clear_tx_interrupt(void)
{
    IFG2 &= ~UCA0TXIFG;
}

static void uart_start_tx(void)
{
    if (!ring_buffer_empty(&tx_buffer)) {
        UCA0TXBUF = ring_buffer_peek(&tx_buffer);
    }
}

__attribute__((interrupt(USCIAB0TX_VECTOR))) void isr_uart_tx()
{
    if (ring_buffer_empty(&tx_buffer)) {
        // TODO: Assert
        while (1)
            ;
    }
    // Remove byte from buffer
    ring_buffer_get(&tx_buffer);

    uart_clear_tx_interrupt();

    uart_start_tx();
}

void uart_init()
{

    UCA0CTL1 |= UCSWRST; // ENable software reset
    UCA0CTL1 |= UCSSEL_3; // Select SMCLK = 1 MHz as clock source

    UCA0CTL0 = 0;

    // Set presclar registers
    UCA0BR0 = UART_PRESCLAR_INT_LOWER_BYTE;
    UCA0BR1 = UART_PRESCLAR_INT_UPPER_BYTE;

    // Set Modulation register
    /* UCA0MCTL = [UCBRF (4 bits) | UCBRS (3 bits) | UC0S16 (1 bit) ] */
    UCA0MCTL = (UART_UCBRF << 4) + (UART_UCBRS << 1) + UART_UC0S16;

    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    // Setup interrupts
    uart_clear_tx_interrupt();
    uart_enable_tx_interrupt(); // Enable Tx interrupt
    // Remove from software reset mode
    UCA0CTL1 &= ~UCSWRST;
}

// mpland/printf needs this to be named as _putchar
void _putchar(char c)
{
    // Poll if full
    while (ring_buffer_full(&tx_buffer))
        ;

    uart_disable_tx_interrupt();
    const bool tx_ongoing = !ring_buffer_empty(&tx_buffer);
    ring_buffer_put(&tx_buffer, c);

    if (!tx_ongoing) {
        uart_start_tx();
    }
    uart_enable_tx_interrupt();
    if (c == '\n') {
        _putchar('\r');
    }
}
