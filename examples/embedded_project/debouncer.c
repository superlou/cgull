#include <stdbool.h>
#include "debouncer.h"

#define NUM_DEBOUNCE_INPUTS 32

void debouncer_new(Debouncer *debouncer, uint8_t threshold) {
  uint32_t i;

  for (i = 0; i < NUM_DEBOUNCE_INPUTS; i++) {
    debouncer->count[i] = 0;
  }

  debouncer->threshold = threshold;
  debouncer->state = 0;
}

uint32_t debouncer_update(Debouncer *debouncer, uint32_t input) {
  uint32_t i;
  uint32_t new_state = 0;
  bool input_is_active;
  bool debounce_was_active;

  for (i = 0; i < NUM_DEBOUNCE_INPUTS; i++) {
    input_is_active = (input & (1 << i)) != 0;
    debounce_was_active = (debouncer->state & (1 << i)) != 0;

    if (input_is_active) {
      if (debouncer->count[i] < debouncer->threshold) {
        debouncer->count[i]++;
      }
    } else {
      if (debouncer->count[i] > 0) {
        debouncer->count[i]--;
      }
    }

    if (debouncer->count[i] >= debouncer->threshold) {
      new_state += (1 << i);
    } else if (debounce_was_active && (debouncer->count[i] != 0)) {
      new_state += (1 << i);
    }
  }

  debouncer->state = new_state;
  return debouncer->state;
}
