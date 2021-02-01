/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 02.05.20
*/

#pragma once

#include <iostream>
#include "EDirection.h"

/**
 * ball represent ball from game, which is used for destroying bricks, ball has width height, and direction
 */
struct TBall {

    TBall();

    /**
     * constructor with parameters
     * @param x coordinate x
     * @param y coordinate y
     */
    TBall( std::size_t x, std::size_t y );

    TBall( const TBall & src ) = default;

    virtual ~TBall() = default;

    /** move ball to one pos left ( for moving with paddle, before releasing the ball ) */
    void MoveLeft();

    /** move ball one pos to right ( for moving with paddle, before releasing the ball ) */
    void MoveRight();

    /** ball moves every frame */
    void Move();

    EDirection m_Direction;
    std::size_t m_X;  //coordinate x
    std::size_t m_Y;  //coordinate y
};

