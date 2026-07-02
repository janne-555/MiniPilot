//------------------------------------------------------------------------------
// File    : AP_Keyboard.h
// Purpose : Linux Non-blocking Keyboard Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_KEYBOARD_H
#define AP_KEYBOARD_H

/* Initialize keyboard */
void AP_Keyboard_Init(void);

/* Restore terminal */
void AP_Keyboard_Close(void);

/* Read one key
 *
 * Returns:
 *    0  -> No key pressed
 *    key -> ASCII character
 */
char AP_Keyboard_Read(void);

#endif
