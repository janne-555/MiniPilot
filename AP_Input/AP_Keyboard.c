//------------------------------------------------------------------------------
// File    : AP_Keyboard.c
// Purpose : Linux Non-blocking Keyboard Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Keyboard.h"

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

/*---------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static struct termios old_term;
static struct termios new_term;

/*---------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_Keyboard_Init(void)
{
    tcgetattr(STDIN_FILENO, &old_term);

    new_term = old_term;

    /* Disable canonical mode */
    new_term.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO,
              TCSANOW,
              &new_term);

    /* Non-blocking input */
    fcntl(STDIN_FILENO,
          F_SETFL,
          O_NONBLOCK);
}

/*---------------------------------------------------------------------------
 * Restore Terminal
 *---------------------------------------------------------------------------*/

void AP_Keyboard_Close(void)
{
    tcsetattr(STDIN_FILENO,
              TCSANOW,
              &old_term);
}

/*---------------------------------------------------------------------------
 * Read Keyboard
 *---------------------------------------------------------------------------*/

char AP_Keyboard_Read(void)
{
    char key;

    if (read(STDIN_FILENO,
             &key,
             1) > 0)
    {
        return key;
    }

    return 0;
}
