/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 01.05.20
*/

#pragma once

#include <unistd.h>
#include <termios.h>

/**
 * can turn buffering off, so player doesn't have to press enter after entering something
 */
class CBufferSwitch {
public:
    /** save the old settings */
    CBufferSwitch();

    /** turn buffering off - disables buffered input
     * @source http://www.cplusplus.com/forum/unices/18395/ */
    void TurnOff();

    /** turn buffering on - enables buffered input
     * @source http://www.cplusplus.com/forum/unices/18395/ */
    void TurnOn();

private:
    struct termios m_OldSettings;
    struct termios m_NewSettings;
};

