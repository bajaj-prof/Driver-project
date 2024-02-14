#ifndef DISABLE_TRACE
#include "common/trace.h"
#include "external/printf/printf.h"
#include "drivers/uart.h"

void trace_init(void)
{
    uart_init();
}
void trace(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

#endif // DISABLE_TRACE
