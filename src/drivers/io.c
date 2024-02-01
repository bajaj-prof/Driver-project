#include "drivers/io.h"
#include "common/defines.h"
#include <msp430.h>

void io_set_select(io_e io, io_select_e select) {
  UNUSED(io);
  UNUSED(select);
  // TODO: implement function
}

void io_set_direction(io_e io, io_dir_e direction) {
  UNUSED(io);
  UNUSED(direction);
  // TODO: implement function
}

void io_set_resistor(io_e io, io_resistor_e resistor) {
  UNUSED(io);
  UNUSED(resistor);
  // TODO:implement function
}

void io_set_out(io_e io, io_out_e out) {
  UNUSED(io);
  UNUSED(out);
  // TODO:implement function
}

io_in_e io_get_input(io_e io) {
  UNUSED(io);
  return 0;
  // TODO:implement function
}
