#include "drivers/io.h"
#include <msp430.h>

/* Watchdog is enabled by default and must
 * be stopped to prevent the micro-controller from resetting
 */
static void watchdog_stop(void) { WDTCTL = WDTPW + WDTHOLD; }

void mcu_init(void) { watchdog_stop(); }
