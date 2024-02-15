#ifndef ASSERT_HANDLER_H
#define ASSERT_HANDLER_H

#include<stdint.h>

#define ASSERT(expression)                                        \
                                                                  \
      do {                                                        \
    if(!(expression)){                                            \
        uint16_t pc;                                              \
        asm volatile("MOV PC ,%0" : "=r"(pc));                    \
        assert_handler(pc);                                       \
    }                                                             \
} while(0)                                                         \

  void assert_handler(const uint16_t program_counter);

#endif // ASSERT_HANDLER_H
