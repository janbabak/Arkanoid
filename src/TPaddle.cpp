/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 01.05.20
*/


#include "TPaddle.h"

TPaddle::TPaddle( std::size_t playingBoardWidth, std::size_t playingBoardHeight, std::size_t paddleWidth )
        : m_X( playingBoardWidth / 2 - paddleWidth / 2 ),
          m_Y( playingBoardHeight - 2 ),
          m_Width( paddleWidth ) {}


void TPaddle::MoveLeft() {
    m_X--;
}

void TPaddle::MoveRight() {
    m_X++;
}
