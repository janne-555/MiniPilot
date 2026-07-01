//------------------------------------------------------------------------------
// File    : AP_Mixer.h
// Purpose : Quad X Motor Mixer
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_MIXER_H
#define AP_MIXER_H

typedef struct
{
    float motor1;
    float motor2;
    float motor3;
    float motor4;

} AP_Mixer_Output_t;

// Initialize mixer
void AP_Mixer_Init(void);

// Update mixer
void AP_Mixer_Update(void);

// Read motor outputs
const AP_Mixer_Output_t *AP_Mixer_GetOutput(void);
#endif
