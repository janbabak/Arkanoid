/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 04.05.20
*/

#include "CBonusLongerPaddle.h"

CBonusLongerPaddle::CBonusLongerPaddle()
        : CBonus( ACTIVATION_TIME ) {}

void CBonusLongerPaddle::Deactivate( TPaddle & paddle, std::chrono::milliseconds & speed,
                                     std::vector<std::string> & board ) const {
    board[ paddle.m_Y ][ paddle.m_X ] = ' ';
    board[ paddle.m_Y ][ paddle.m_X + paddle.m_Width - 1 ] = ' ';
    paddle.m_Width -= 2;
    paddle.m_X++;
    ( void ) speed;  //don't use
}

void CBonusLongerPaddle::Activate( TPaddle & paddle, std::chrono::milliseconds & speed,
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
    ( void ) speed;  //don't use
}

std::ostream & CBonusLongerPaddle::Print( std::ostream & os ) const {
    if ( m_ActivationTime >= END_OF_ACTIVATION_COLOR_CHANGE )
       return os << BRIGHT_GREEN << "LONGER PADDLE bonus active (remaining time: " << m_ActivationTime << ")" << DEFAULT_COLOR << std::endl;
    else
       return os << BRIGHT_RED << "LONGER PADDLE bonus active (remaining time: " << m_ActivationTime << ")" << DEFAULT_COLOR << std::endl;
}
