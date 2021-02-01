/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 02.06.20
*/

#include "CBonusSlowTimeLongerPaddle.h"

CBonusSlowTimeLongerPaddle::CBonusSlowTimeLongerPaddle()
        : CBonus( ACTIVATION_TIME ) {}

void CBonusSlowTimeLongerPaddle::Deactivate( TPaddle & paddle, std::chrono::milliseconds & speed,
                                     std::vector<std::string> & board ) const {
    board[ paddle.m_Y ][ paddle.m_X ] = ' ';
    board[ paddle.m_Y ][ paddle.m_X + paddle.m_Width - 1 ] = ' ';
    paddle.m_Width -= 2;
    paddle.m_X++;
    speed /= 2;

}

void CBonusSlowTimeLongerPaddle::Activate( TPaddle & paddle, std::chrono::milliseconds & speed,
                                   std::vector<std::string> & board ) const {
    //paddle expand on both sides by one char
    if ( paddle.m_X > 1 && paddle.m_X + paddle.m_Width < board[ 0 ].size() - 1 ) {
        board[ paddle.m_Y ][ paddle.m_X - 1 ] = 'X';
        board[ paddle.m_Y ][ paddle.m_X + paddle.m_Width ] = 'X';
        paddle.m_Width += 2;
        paddle.m_X--;
        //paddle expand on the right
    } else if ( paddle.m_X == 1 ) {
        board[ paddle.m_Y ][ paddle.m_X + paddle.m_Width + 1 ] = 'X';
        board[ paddle.m_Y ][ paddle.m_X + paddle.m_Width ] = 'X';
        paddle.m_Width += 2;
    }
        //expand paddle on the left
    else {
        board[ paddle.m_Y ][ paddle.m_X - 1 ] = 'X';
        board[ paddle.m_Y ][ paddle.m_X - 2 ] = 'X';
        paddle.m_Width += 2;
        paddle.m_X -= 2;
    }
    speed *= 2;
}

std::ostream & CBonusSlowTimeLongerPaddle::Print( std::ostream & os ) const {
    if ( m_ActivationTime >= END_OF_ACTIVATION_COLOR_CHANGE )
        return os << BRIGHT_GREEN << "LONGER PADDLE and SLOW TIME bonus active (remaining time: " << m_ActivationTime << ")" << DEFAULT_COLOR << std::endl;
    else
        return os << BRIGHT_RED << "LONGER PADDLE and SLOW TIME bonus active (remaining time: " << m_ActivationTime << ")" << DEFAULT_COLOR << std::endl;
}
