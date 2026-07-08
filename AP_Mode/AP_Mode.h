#ifndef AP_MODE_H
#define AP_MODE_H

typedef enum {
  MODE_STABILIZE = 0,
  MODE_ALT_HOLD = 2,
  MODE_AUTO = 3,
  MODE_GUIDED = 4,
  MODE_LOITER = 5
} AP_Mode_t;

extern AP_Mode_t current_mode;

void AP_Mode_Set(AP_Mode_t mode);

#endif
