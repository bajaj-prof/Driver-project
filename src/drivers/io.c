#include "drivers/io.h"
#include "common/defines.h"
#include <msp430.h>
#include <stdint.h>

#define IO_PORT_OFFSET (3u)
#define IO_PORT_MASK (0x3u << IO_PORT_OFFSET)
#define IO_PIN_MASK (7u)
#define IO_PORT_CNT (2u)

/* We define pointer arrays of all the required port configuration registers.
 * Now to access a particular port register we need to extract the port number
 * and then use the corresponding array element [1] or [2] for P1 and P2
 */
static volatile uint8_t *const port_dir_regs[IO_PORT_CNT] = {&P1DIR, &P2DIR};
static volatile uint8_t *const port_ren_regs[IO_PORT_CNT] = {&P1REN, &P2REN};
static volatile uint8_t *const port_in_regs[IO_PORT_CNT] = {&P1IN, &P2IN};
static volatile uint8_t *const port_out_regs[IO_PORT_CNT] = {&P1OUT, &P2OUT};
static volatile uint8_t *const port_psel1_regs[IO_PORT_CNT] = {&P1SEL, &P2SEL};
static volatile uint8_t *const port_psel2_regs[IO_PORT_CNT] = {&P1SEL2,
                                                               &P2SEL2};

void io_configuration(io_e io, const struct io_config *config) {
  io_set_select(io, config->select);
  io_set_direction(io, config->dir);
  io_set_resistor(io, config->res);
  io_set_out(io, config->out);
}

/* To extract the port and pin number from io_e we use the generic enums and
 * then mask the last 3 bits to get pin number and the next 2 bits (Bit 4 and 5)
 * to get Port number
 */

static inline uint8_t io_port(io_e io) {
  return (io & IO_PORT_MASK) >> IO_PORT_OFFSET;
}

static inline uint8_t io_pin_idx(io_e io) { return io & IO_PIN_MASK; }

static inline uint8_t io_pin_bit(io_e io) { return 1 << io_pin_idx(io); }
/*
 * Sets the P1SEL and P2SEL registers of the given io
 */

void io_set_select(io_e io, io_select_e select) {
  const uint8_t port = io_port(io);
  const uint8_t pin = io_pin_bit(io);

  switch (select) {
  case IO_SELECT_GPIO:
    *port_psel1_regs[port] &= ~pin;
    *port_psel2_regs[port] &= ~pin;
    break;
  case IO_SELECT_ALT1:
    *port_psel1_regs[port] |= pin;
    *port_psel2_regs[port] &= ~pin;
    break;
  case IO_SELECT_ALT2:
    *port_psel1_regs[port] &= ~pin;
    *port_psel2_regs[port] |= pin;
    break;
  case IO_SELECT_ALT3:
    *port_psel1_regs[port] |= pin;
    *port_psel2_regs[port] |= pin;
    break;
  }
}

void io_set_direction(io_e io, io_dir_e direction) {
  const uint8_t port = io_port(io);
  const uint8_t pin = io_pin_bit(io);

  switch (direction) {
  case IO_DIR_OUTPUT:
    *port_dir_regs[port] |= pin; // sets the pin in Dir reg. indicating output
    break;
  case IO_DIR_INPUT:
    *port_dir_regs[port] &= ~pin; // clears the pin in DIR reg. indicating input
    break;
  }
}

void io_set_resistor(io_e io, io_resistor_e resistor) {
  const uint8_t port = io_port(io);
  const uint8_t pin = io_pin_bit(io);

  switch (resistor) {
  case IO_RESISTOR_ENABLED:
    *port_ren_regs[port] |= pin;
    break;
  case IO_RESISTOR_DISABLED:
    *port_ren_regs[port] &= ~pin;
    break;
  }
}

void io_set_out(io_e io, io_out_e out) {
  const uint8_t port = io_port(io);
  const uint8_t pin = io_pin_bit(io);

  switch (out) {
  case IO_OUT_HIGH:
    *port_out_regs[port] |= pin;
    break;
  case IO_OUT_LOW:
    *port_out_regs[port] &= ~pin;
    break;
  }
}

io_in_e io_get_input(io_e io) {
  const uint8_t port = io_port(io);
  const uint8_t pin = io_pin_bit(io);

  return (*port_in_regs[port] & pin) ? IO_IN_HIGH : IO_IN_LOW;
}
