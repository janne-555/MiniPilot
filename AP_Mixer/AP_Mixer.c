//------------------------------------------------------------------------------
// File    : AP_Mixer.c
// Purpose : Quad X Motor Mixer
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Mixer.h"
#include "AP_Debug/AP_Debug.h"
#include "../AP_Control/AP_Control.h"

static AP_Mixer_Output_t mixer_output;
static float last_m1 = -999.0f;
// Initialize mixer
void AP_Mixer_Init(void)
{
	for (int i = 0; i < 4; i++)
	{
		mixer_output.motor[i] = 0.0f;
	}
}
// Update mixer
void AP_Mixer_Update(void)
{
	const AP_Control_Output_t *control;

	control = AP_Control_GetOutput();

	mixer_output.motor[0]  =
		control->throttle_output +
		control->roll_output -
		control->pitch_output +
		control->yaw_output;

	mixer_output.motor[1] =
		control->throttle_output -
		control->roll_output -
		control->pitch_output -
		control->yaw_output;

	mixer_output.motor[2] =
		control->throttle_output -
		control->roll_output +
		control->pitch_output +
		control->yaw_output;

	mixer_output.motor[3] =
		control->throttle_output +
		control->roll_output +
		control->pitch_output -
		control->yaw_output;
	if ((mixer_output.motor[0] - last_m1 > 0.2f) ||
			(last_m1 - mixer_output.motor[0] > 0.2f))
	{
		AP_Debug_Print(DBG_MIXER,
				"\n===== MIXER =====\n"
				"Throttle : %.2f\n"
				"Roll     : %.2f\n"
				"Pitch    : %.2f\n"
				"Yaw      : %.2f\n"
				"M1 = %.2f\n"
				"M2 = %.2f\n"
				"M3 = %.2f\n"
				"M4 = %.2f\n",
				control->throttle_output,
				control->roll_output,
				control->pitch_output,
				control->yaw_output,
				mixer_output.motor[0],
				mixer_output.motor[1],
				mixer_output.motor[2],
				mixer_output.motor[3]);


		last_m1 = mixer_output.motor[0];
	}
}
// Read motor outputs
const AP_Mixer_Output_t *AP_Mixer_GetOutput(void)
{
	return &mixer_output;
}
