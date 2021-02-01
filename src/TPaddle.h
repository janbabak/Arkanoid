/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 01.05.20
*/

#pragma once

#include <iostream>

/**
 * represent paddle which player uses for bouncing ball
 */
struct TPaddle {

    static const size_t PADDLE_INIT_SIZE = 5;

    TPaddle()
            : m_X( 0 ), m_Y( 0 ), m_Width( 0 ) {}

    /**
     * constructor with parameters
     * @param playingBoardWidth Not width of paddle but of playing board!!!
     * @param playingBoardHeight Not height of paddle but of playing board!!!
     * @param paddleWidth default is set to PADDLE_INIT_SIZE
     */
    TPaddle( std::size_t playingBoardWidth, std::size_t playingBoardHeight,
             std::size_t paddleWidth = PADDLE_INIT_SIZE );

    ~TPaddle() = default;

    /** move paddle oe position to the left */
    void MoveLeft();

    /** move paddle oe position to the right */
    void MoveRight();

    std::size_t m_X; //coordinates
    std::size_t m_Y;
    std::size_t m_Width;
};

