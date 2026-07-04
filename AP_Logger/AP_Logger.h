//------------------------------------------------------------------------------
// File    : AP_Logger.h
// Purpose : Flight Data Logger
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_LOGGER_H
#define AP_LOGGER_H


#include <stdint.h>


typedef struct
{
    uint8_t enabled;

    uint32_t messages;

} AP_Logger_t;



void AP_Logger_Init(void);


void AP_Logger_Update(void);



void AP_Logger_Write_Attitude(void);


void AP_Logger_Write_Battery(void);


void AP_Logger_Write_Motors(void);


void AP_Logger_Write_Mode(void);


void AP_Logger_Write_Arming(void);


void AP_Logger_Write_Failsafe(void);


void AP_Logger_Write_Event(const char *event);



uint64_t AP_Logger_TimeUS(void);



const AP_Logger_t *AP_Logger_Get(void);


#endif
