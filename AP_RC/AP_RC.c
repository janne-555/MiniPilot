//------------------------------------------------------------------------------
// File    : AP_RC.c
// Purpose : Radio Control Receiver
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_RC.h"

#include "../AP_Config/AP_Config.h"
#include "../AP_Input/AP_Keyboard.h"
#include "../AP_Arming/AP_Arming.h"
#include "../AP_Debug/AP_Debug.h"


static float last_roll = 999.0f;
/*----------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static AP_RC_t rc;

static uint8_t roll_left  = 0;
static uint8_t roll_right = 0;

static uint8_t pitch_up   = 0;
static uint8_t pitch_down = 0;

static uint8_t yaw_left   = 0;
static uint8_t yaw_right  = 0;

/*----------------------------------------------------------------------------
 * Private Functions
 *---------------------------------------------------------------------------*/

static void RC_ProcessKey(char key);
static void RC_UpdateRoll(void);
static void RC_UpdatePitch(void);
static void RC_UpdateYaw(void);
static void RC_Clamp(void);
static void RC_Debug(void);

/*----------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_RC_Init(void)
{
	rc.roll = 0.0f;
	rc.pitch = 0.0f;
	rc.yaw = 0.0f;
	rc.throttle = 0.5f;

	rc.arm = 1;
	rc.mode = 0;
}

/*----------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_RC_Update(void)
{
	char key;

	key = AP_Keyboard_Read();

	RC_ProcessKey(key);

	RC_UpdateRoll();

	RC_UpdatePitch();

	RC_UpdateYaw();

	RC_Clamp();

	RC_Debug();
}

/*----------------------------------------------------------------------------
 * Process Keyboard
 *---------------------------------------------------------------------------*/

static void RC_ProcessKey(char key)
{
	switch (key)
	{
		case 'a':
			roll_left = 1;
			roll_right = 0;
			break;

		case 'd':
			roll_right = 1;
			roll_left = 0;
			break;

		case 'w':
			pitch_up = 1;
			pitch_down = 0;
			break;

		case 's':
			pitch_down = 1;
			pitch_up = 0;
			break;

		case 'q':
			yaw_left = 1;
			yaw_right = 0;
			break;

		case 'e':
			yaw_right = 1;
			yaw_left = 0;
			break;

		case 'r':
			rc.throttle += 0.05f;
			break;

		case 'f':
			rc.throttle -= 0.05f;
			break;

		case 'x':

			roll_left = 0;
			roll_right = 0;

			pitch_up = 0;
			pitch_down = 0;

			yaw_left = 0;
			yaw_right = 0;

			break;

		case ' ':

			AP_Arming_Toggle();

			break;

		default:
			break;
	}
}

/*----------------------------------------------------------------------------
 * Update Roll
 *---------------------------------------------------------------------------*/

static void RC_UpdateRoll(void)
{
	if (roll_right)
	{
		rc.roll += 0.03f;
	}
	else if (roll_left)
	{
		rc.roll -= 0.03f;
	}
	else
	{
		if (rc.roll > 0.0f)
		{
			rc.roll -= 0.03f;

			if (rc.roll < 0.0f)
				rc.roll = 0.0f;
		}

		if (rc.roll < 0.0f)
		{
			rc.roll += 0.03f;

			if (rc.roll > 0.0f)
				rc.roll = 0.0f;
		}
	}
}

/*----------------------------------------------------------------------------
 * Update Pitch
 *---------------------------------------------------------------------------*/

static void RC_UpdatePitch(void)
{
	if (pitch_up)
	{
		rc.pitch += 0.03f;
	}
	else if (pitch_down)
	{
		rc.pitch -= 0.03f;
	}
	else
	{
		if (rc.pitch > 0.0f)
		{
			rc.pitch -= 0.03f;

			if (rc.pitch < 0.0f)
				rc.pitch = 0.0f;
		}

		if (rc.pitch < 0.0f)
		{
			rc.pitch += 0.03f;

			if (rc.pitch > 0.0f)
				rc.pitch = 0.0f;
		}
	}
}

/*----------------------------------------------------------------------------
 * Update Yaw
 *---------------------------------------------------------------------------*/

static void RC_UpdateYaw(void)
{
	if (yaw_right)
	{
		rc.yaw += 0.03f;
	}
	else if (yaw_left)
	{
		rc.yaw -= 0.03f;
	}
	else
	{
		if (rc.yaw > 0.0f)
		{
			rc.yaw -= 0.03f;

			if (rc.yaw < 0.0f)
				rc.yaw = 0.0f;
		}

		if (rc.yaw < 0.0f)
		{
			rc.yaw += 0.03f;

			if (rc.yaw > 0.0f)
				rc.yaw = 0.0f;
		}
	}
}

/*----------------------------------------------------------------------------
 * Clamp
 *---------------------------------------------------------------------------*/

static void RC_Clamp(void)
{
	if (rc.roll > RC_MAX) rc.roll = RC_MAX;
	if (rc.roll < RC_MIN) rc.roll = RC_MIN;

	if (rc.pitch > RC_MAX) rc.pitch = RC_MAX;
	if (rc.pitch < RC_MIN) rc.pitch = RC_MIN;

	if (rc.yaw > RC_MAX) rc.yaw = RC_MAX;
	if (rc.yaw < RC_MIN) rc.yaw = RC_MIN;

	if (rc.throttle > RC_THROTTLE_MAX)
		rc.throttle = RC_THROTTLE_MAX;

	if (rc.throttle < RC_THROTTLE_MIN)
		rc.throttle = RC_THROTTLE_MIN;
}

/*----------------------------------------------------------------------------
 * Debug
 *---------------------------------------------------------------------------*/

static void RC_Debug(void)
{
	if (rc.roll != last_roll)
	{
		AP_Debug_Print(DBG_RC,
				"\n===== RC =====\n"
				"Roll      : %.2f\n"
				"Pitch     : %.2f\n"
				"Yaw       : %.2f\n"
				"Throttle  : %.2f\n"
				"Arm       : %d\n"
				"Mode      : %d\n",
				rc.roll,
				rc.pitch,
				rc.yaw,
				rc.throttle,
				rc.arm,
				rc.mode);


		last_roll = rc.roll;
	}
}

/*----------------------------------------------------------------------------
 * Get RC Data
 *---------------------------------------------------------------------------*/

const AP_RC_t *AP_RC_Get(void)
{
	return &rc;
}
