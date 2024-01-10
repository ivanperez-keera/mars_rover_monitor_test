#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "monitor_types.h"
#include "monitor.h"

static double_t wheel_velocity_controller_commands_cpy[(6)];

static bool propTooFast_guard(void) {
  return ((wheel_velocity_controller_commands_cpy)[(uint32_t)(0)]) > ((double_t)(3.0));
}

void step(void) {
  (memcpy)((wheel_velocity_controller_commands_cpy), (wheel_velocity_controller_commands), ((6) * (sizeof(double_t))));
  if ((propTooFast_guard)()) {
    {(propTooFast)();}
  };
}
