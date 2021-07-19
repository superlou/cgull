#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_

#include <stdint.h>

typedef struct {
  uint8_t count[32];
  uint8_t threshold;
  uint32_t state;
} Debouncer;

void debouncer_new(Debouncer *debouncer, uint8_t threshold);
uint32_t debouncer_update(Debouncer *debouncer, uint32_t input);

#endif
