#include "drivers/io.h"
#include "common/defines.h"
#include <msp430.h>

/* Watchdog is enabled by default and must
 * be stopped to prevent the micro-controller from resetting
 */
static void watchdog_stop(void)
{
    WDTCTL = WDTPW + WDTHOLD;
}

// calibrates the DCO to run at 16 MHZ
SUPPRESS_UNUSED
static void clock_init(void)
{

    BCSCTL1 = CALBC1_16MHZ; // Set range
    DCOCTL = CALDCO_16MHZ; // Set's DCO step + modulation
}

void mcu_init(void)
{
    watchdog_stop();
}
