//------------------------------------------------------------------------------
// File    : AP_Mission.c
// Purpose : Mission Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#include "AP_Mission.h"

#include "../AP_Mode/AP_Mode.h"
#include "../AP_Nav/AP_Nav.h"

static AP_Mission_t mission;

void AP_Mission_Init(void)
{
    memset(&mission, 0, sizeof(mission));

  printf("Mission Started\n");
}

void AP_Mission_Clear(void)
{
    mission.count = 0;

  mission.current = 0;

  mission.active = 0;

  printf("Mission Cleared\n");
}

uint8_t AP_Mission_AddItem(AP_Mission_Item_t *item) {

  if (mission.count >= AP_MISSION_MAX_ITEMS) {
    return 0;
  }

  mission.item[mission.count] = *item;

  mission.count++;

  printf("MISSION ADD seq=%u\n", item->seq);

  return 1;
}

uint16_t AP_Mission_Count(void)
{
    return mission.count;
}

AP_Mission_Item_t *AP_Mission_GetItem(uint16_t seq) {

  if (seq >= mission.count) {
    return 0;
  }

  return &mission.item[seq];
}

void AP_Mission_Start(void) {

  if (mission.count == 0) {
    printf("NO MISSION\n");

    return;
  }

  mission.current = 0;

  mission.active = 1;

  AP_Mode_Set(MODE_AUTO);

  printf("MISSION START\n");
}

void AP_Mission_Stop(void)
{
    mission.active = 0;

  printf("MISSION STOP\n");
}

void AP_Mission_Update(void) {

  if (!mission.active) {
    return;
  }

  AP_Mission_Item_t *wp;

  wp = &mission.item[mission.current];

  AP_Nav_SetTarget(wp->lat, wp->lon);

  AP_Nav_Enable(1);

  if (AP_Nav_GetDistance() < 2.0f) {

    printf("WAYPOINT COMPLETE %u\n", mission.current);

    mission.current++;

    if (mission.current >= mission.count) {

      mission.active = 0;

      AP_Nav_Enable(0);

      printf("MISSION COMPLETE\n");
    }
  }
}

const AP_Mission_t *AP_Mission_Get(void) { return &mission; }
