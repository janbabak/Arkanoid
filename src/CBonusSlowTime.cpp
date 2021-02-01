/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 04.05.20
*/

#include "CBonusSlowTime.h"

CBonusSlowTime::CBonusSlowTime()
        : CBonus( ACTIVATION_TIME ) {}

void CBonusSlowTime::Activate( TPaddle & paddle, std::chrono::milliseconds & speed,
                               std::vector<std::string> & board ) const {
    speed *= 3;
    ( void ) paddle;  //not used
    ( void ) board;  //not used
}

void CBonusSlowTime::Deactivate( TPaddle & paddle, std::chrono::milliseconds & speed,
                                 std::vector<std::string> & board ) const {
    speed /= 3;
    ( void ) paddle;  //not used
    ( void ) board;  //not used
}

std::ostream & CBonusSlowTime::Print( std::ostream & os ) const {
    if ( m_ActivationTime >= END_OF_ACTIVATION_COLOR_CHANGE )
        return os << BRIGHT_GREEN << "SLOWER TIME bonus active (remaining time: " << m_ActivationTime << ")" << DEFAULT_COLOR << std::endl;
    else
        return os << BRIGHT_RED << "SLOWER TIME bonus active (remaining time: " << m_ActivationTime << ")" << DEFAULT_COLOR << std::endl;
}
