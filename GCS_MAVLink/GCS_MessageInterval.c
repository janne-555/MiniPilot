//------------------------------------------------------------------------------
// File    : GCS_MessageInterval.c
// Purpose : Handle MAVLink Message Interval Requests
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"

#include "GCS_MAVLink.h"

typedef struct {
  uint32_t msg_id;

  int32_t interval_us;

} GCS_MessageRate_t;

#define MAX_MESSAGE_RATES 20

static GCS_MessageRate_t rates[MAX_MESSAGE_RATES];

void GCS_MessageInterval_Init(void) {
  for (uint8_t i = 0; i < MAX_MESSAGE_RATES; i++) {

    rates[i].msg_id = 0;

    rates[i].interval_us = -1;
  }
}

void GCS_set_message_interval(uint32_t msg_id, int32_t interval_us) {

  for (uint8_t i = 0; i < MAX_MESSAGE_RATES; i++) {

    if (rates[i].msg_id == msg_id || rates[i].interval_us == -1) {

      rates[i].msg_id = msg_id;

      rates[i].interval_us = interval_us;

      printf("SET MESSAGE INTERVAL\n"
             "MSG ID : %u\n"
             "RATE   : %d us\n",

             msg_id, interval_us);

      return;
    }
  }
}

int32_t GCS_get_message_interval(uint32_t msg_id) {

  for (uint8_t i = 0; i < MAX_MESSAGE_RATES; i++) {

    if (rates[i].msg_id == msg_id) {

      return rates[i].interval_us;
    }
  }

  return -1;
}
