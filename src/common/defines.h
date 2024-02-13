#ifndef DEFINES_H
#define DEFINES_H

#define UNUSED(x) (void)(x)
#define SUPPRESS_UNUSED __attribute__((unused))
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))


#define CYCLES_1MHZ (1000000u)
#define CYCLES_PER_MS (CYCLES_1MHZ/1000u)
#define ms_TO_CYCLES(ms) (CYCLES_PER_MS * ms)
#define BUSY_WAIT_ms(ms) (__delay_cycles(ms_TO_CYCLES(ms)))

#endif // Defines_H
