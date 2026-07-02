//------------------------------------------------------------------------------
// File    : AP_Debug.c
// Purpose : MiniPilot Debug Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Debug.h"

#include <stdio.h>
#include <stdarg.h>

static uint32_t debug_flags = 0;

void AP_Debug_Init(void)
{
    debug_flags = 0;
}

void AP_Debug_Enable(uint32_t flag)
{
    debug_flags |= flag;
}

void AP_Debug_Disable(uint32_t flag)
{
    debug_flags &= ~flag;
}

uint32_t AP_Debug_GetFlags(void)
{
    return debug_flags;
}

void AP_Debug_Toggle(uint32_t flag)
{
    debug_flags ^= flag;
}

void AP_Debug_Print(uint32_t flag,
                    const char *fmt,
                    ...)
{
    if ((debug_flags & flag) == 0)
    {
        return;
    }

    va_list args;

    va_start(args, fmt);

    vprintf(fmt, args);

    va_end(args);
}
