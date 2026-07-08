//------------------------------------------------------------------------------
// File    : AP_Mission.h
// Purpose : Mission Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_MISSION_H
#define AP_MISSION_H

#include <stdint.h>

#define AP_MISSION_MAX_ITEMS 50

typedef struct {
  uint16_t seq;

  uint16_t command;

  double lat;

  double lon;

  float alt;

  float param1;
  float param2;
  float param3;
  float param4;

} AP_Mission_Item_t;

typedef struct {
  AP_Mission_Item_t item[AP_MISSION_MAX_ITEMS];

  uint16_t count;

  uint16_t current;

  uint8_t active;

} AP_Mission_t;

void AP_Mission_Init(void);

void AP_Mission_Clear(void);

uint8_t AP_Mission_AddItem(AP_Mission_Item_t *item);

uint16_t AP_Mission_Count(void);

AP_Mission_Item_t *AP_Mission_GetItem(uint16_t seq);

void AP_Mission_Start(void);

void AP_Mission_Stop(void);

void AP_Mission_Update(void);

const AP_Mission_t *AP_Mission_Get(void);

#endif
