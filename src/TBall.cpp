/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 02.05.20
*/

#include "TBall.h"

TBall::TBall()
        : m_Direction( EDirection::LEFT_UP ), m_X( 0 ), m_Y( 0 ) {}

TBall::TBall( std::size_t x, std::size_t y )
        : m_Direction( EDirection::LEFT_UP ), m_X( x ), m_Y( y ) {}

void TBall::MoveLeft() {
    m_X--;
}

void TBall::MoveRight() {
    m_X++;
}

void TBall::Move() {
    switch ( m_Direction ) {
        case EDirection::LEFT_UP :
            m_Y--;
            m_X--;
            break;
        case EDirection::RIGHT_UP :
            m_Y--;
            m_X++;
            break;
        case EDirection::LEFT_DOWN :
            m_Y++;
            m_X--;
            break;
        case EDirection::RIGHT_DOWN :
            m_Y++;
            m_X++;
            break;
    }
}


