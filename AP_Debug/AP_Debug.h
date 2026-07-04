//------------------------------------------------------------------------------
// File    : AP_Debug.h
// Purpose : MiniPilot Debug Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_DEBUG_H
#define AP_DEBUG_H

#include <stdint.h>

/* Debug Flags */
#define DBG_IMU          (1U << 0)
#define DBG_RC           (1U << 1)
#define DBG_AHRS         (1U << 2)
#define DBG_CONTROL      (1U << 3)
#define DBG_PID          (1U << 4)
#define DBG_MIXER        (1U << 5)
#define DBG_MOTORS       (1U << 6)
#define DBG_GPS          (1U << 7)
#define DBG_GCS          (1U << 8)
#define DBG_FLIGHTMODE   (1U << 9)
#define DBG_SIM          (1U << 10)
#define DBG_ARMING	 (1U << 11)
#define DBG_FAILSAFE	 (1U << 12)
#define DBG_BATTERY	 (1U << 13)
#define DBG_BARO 	 (1U << 14)
#define DBG_NAV		 (1U << 15)
#define DBG_POS		 (1U << 16)
#define DBG_INAV 	 (1U << 17)
#define DBG_EKF          (1U << 18)
#define DBG_VEHICLE      (1U << 19)
#define DBG_ALL          0xFFFFFFFFU
#define DBG_SENSORS   (DBG_IMU | DBG_GPS | DBG_AHRS)
#define DBG_CONTROLS  (DBG_CONTROL | DBG_PID | DBG_MIXER | DBG_MOTORS)
#define DBG_SYSTEM    (DBG_ARMING | DBG_FAILSAFE)

void AP_Debug_Init(void);

void AP_Debug_Enable(uint32_t flag);

void AP_Debug_Disable(uint32_t flag);

uint32_t AP_Debug_GetFlags(void);

void AP_Debug_Toggle(uint32_t flag);

void AP_Debug_Print(uint32_t flag,
                    const char *fmt,
                    ...);

#endif
