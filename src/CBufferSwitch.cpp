/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 01.05.20
*/

#include "CBufferSwitch.h"

CBufferSwitch::CBufferSwitch() {
    tcgetattr( STDIN_FILENO, &m_OldSettings );  //get the terminal settings for stdin
    m_NewSettings = m_OldSettings;  //need to keep the old settings, so i can restore them in the future
}

void CBufferSwitch::TurnOff() {
    m_NewSettings.c_lflag &= ( ~ICANON & ~ECHO ); //disable canonical mode (buffered i/o) and local echo
    tcsetattr( STDIN_FILENO, TCSANOW, &m_NewSettings );  //set the new settings immediately
}

void CBufferSwitch::TurnOn() {
    tcsetattr( STDIN_FILENO, TCSANOW, &m_OldSettings );  //restore the former settings
}
