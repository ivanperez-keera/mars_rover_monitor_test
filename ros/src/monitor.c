#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "monitor_types.h"
#include "monitor.h"

static double_t thing_cpy[(6)];

static bool propTooFast_guard(void) {
  return ((thing_cpy)[(uint32_t)(0)]) > ((double_t)(3.0));
}

void step(void) {
  (memcpy)((thing_cpy), (thing), ((6) * (sizeof(double_t))));
  if ((propTooFast_guard)()) {
    {(propTooFast)();}
  };
}
