//------------------------------------------------------------------------------
// File    : AP_Mixer.c
// Purpose : Quad X Motor Mixer
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Mixer.h"

#include "../AP_Control/AP_Control.h"

static AP_Mixer_Output_t mixer_output;

// Initialize mixer
void AP_Mixer_Init(void)
{
    mixer_output.motor1 = 0.0f;
    mixer_output.motor2 = 0.0f;
    mixer_output.motor3 = 0.0f;
    mixer_output.motor4 = 0.0f;
}
// Update mixer
void AP_Mixer_Update(void)
{
    const AP_Control_Output_t *control;

    control = AP_Control_GetOutput();

    mixer_output.motor1 =
        control->throttle_output +
        control->roll_output -
        control->pitch_output +
        control->yaw_output;

    mixer_output.motor2 =
        control->throttle_output -
        control->roll_output -
        control->pitch_output -
        control->yaw_output;

    mixer_output.motor3 =
        control->throttle_output -
        control->roll_output +
        control->pitch_output +
        control->yaw_output;

    mixer_output.motor4 =
        control->throttle_output +
        control->roll_output +
        control->pitch_output -
        control->yaw_output;

printf("\n===== MIXER =====\n");

printf("Throttle : %.2f\n", control->throttle_output);
printf("Roll     : %.2f\n", control->roll_output);
printf("Pitch    : %.2f\n", control->pitch_output);
printf("Yaw      : %.2f\n", control->yaw_output);

printf("M1 = %.2f\n", mixer_output.motor1);
printf("M2 = %.2f\n", mixer_output.motor2);
printf("M3 = %.2f\n", mixer_output.motor3);
printf("M4 = %.2f\n", mixer_output.motor4);

}
// Read motor outputs
const AP_Mixer_Output_t *AP_Mixer_GetOutput(void)
{
    return &mixer_output;
}
