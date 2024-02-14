#ifndef TRACE_H
#define TRACE_H

#define TRACE(fmt, ...) trace("%s:%d: " fmt "\n",__FILE__, __LINE__, ##__VA_ARGS__)

#ifndef DISABLE_TRACE
//If disable trace is not defined define trace functions as usual
void trace_init(void);
void trace (const char*format, ...);
#else
//This defines the trace function as empty functions and any call to them will be replaced with a no-op.
#define trace_init();
#define trace(fmt,...);
#endif //DISABLE_TRACE

#endif //TRACE_H
