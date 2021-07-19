#include "bsp.h"
#include "frame.h"
#include "debouncer.h"

int main(void) {
  uint32_t discrete_inputs = 0;
  uint32_t debounced_inputs = 0;
  frame_init(10);

  Debouncer debouncer;
  debouncer_new(&debouncer, 5);

  while (1) {
    discrete_inputs = bsp_read_din();
    debounced_inputs = debouncer_update(&debouncer, discrete_inputs);
    bsp_set_dout(0, debounced_inputs & (1 << 3) ? true : false);
    frame_wait_for_next();
  }

  return 0;
}
