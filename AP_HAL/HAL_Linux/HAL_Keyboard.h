//------------------------------------------------------------------------------
// File    : AP_Keyboard.h
// Purpose : Linux Non-blocking Keyboard Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef HAL_KEYBOARD_H
#define HAL_KEYBOARD_H

/* Initialize keyboard */
void HAL_Keyboard_Init(void);

/* Restore terminal */
void HAL_Keyboard_Close(void);

/* Read one key
 *
 * Returns:
 *    0  -> No key pressed
 *    key -> ASCII character
 */
char HAL_Keyboard_Read(void);

#endif
