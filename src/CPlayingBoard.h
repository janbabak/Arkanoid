/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 30.04.20
*/

#pragma once

#include "TBall.h"
#include "TPaddle.h"
#include "CBonus.h"
#include "CBonusNothing.h"
#include "CBonusSlowTime.h"
#include "CBonusLongerPaddle.h"
#include "CBonusSlowTimeLongerPaddle.h"
#include "EReturnVal.h"
#include "EDirection.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <random>


const char BORDER_CHAR = '#';
const char EMPTY_CHAR = ' ';
const char BRICK_CHAR = '*';
const char PADDLE_CHAR = 'X';
const char BALL_CHAR = 'O';

/**
 * playing board represented by chars
 */
class CPlayingBoard {
public:

    static const std::size_t MAX_HEIGHT = 23;
    static const std::size_t MIN_HEIGHT = 10;
    static const std::size_t MAX_WIDTH = 50;
    static const std::size_t MIN_WIDTH = 20;

    CPlayingBoard();

    CPlayingBoard( const CPlayingBoard & ) = default;

    virtual ~CPlayingBoard() = default;

    /** load random map - width, height and number of bricks are random */
    void LoadRandom();

    /**
     * load map from file
     * @param fileName fileName is name of text file, where the map is saved
     * @return true if everything was ok, false if something went wrong (file was corrupted, file not exist)
     */
    bool LoadFromFile( std::string fileName );

    /**
     * print playing board to the output stream
     * @param os output stream - default is std::cout
     * @return output stream
     */
    std::ostream & Print( std::ostream & os = std::cout ) const;

    /**
     * initialize paddle, set it to default position
     * @param paddle
     */
    void InitPaddle( TPaddle & paddle );

    /**
     * initialize ball - set it to the playing board
     * @param ball used for destroying bricks
     * @param paddle paddle is used for bouncing the ball
     */
    void InitBall( TBall & ball, TPaddle & paddle );

    /**
     * check if player loss
     * @param ball
     * @param paddle
     * @return true if player lost ( ball in not above paddle ), false if player didn't lose
     */
    static bool CheckLoss( TBall & ball, TPaddle & paddle ) ;

    /**
     * check if player won
     * @return true if player win ( 0 bricks left ), false if player didn't win
     */
    bool CheckWin() const;

    /**
     * remove bricks ( all 8 ), which are next to the ball (if there are any)
     * @param ball
     * @return pointer on bonus which is randomly generated
     */
    CBonus * RemoveBricks( TBall & ball );

    /**
     * move paddle one position left
     * @param paddle reference on paddle which you want to move
     */
    void MovePaddleLeft( TPaddle & paddle );

    /**
     * move paddle one position right
     * @param paddle reference on paddle which you want to move
     */
    void MovePaddleRight( TPaddle & paddle );

    /**
     * move paddle and the ball left - when player set the paddle before ball is released
     * @param paddle paddle which is used for bouncing ball
     * @param ball ball is used for destroying bricks
     */
    void MovePaddleWithBallLeft( TPaddle & paddle, TBall & ball );

    /**
     * move paddle and the ball right - when player set the paddle before ball is released
     * @param paddle paddle which is used for bouncing ball
     * @param ball ball is used for destroying bricks
     */
    void MovePaddleWithBallRight( TPaddle & paddle, TBall & ball );

    /**
     * move with the ball, depend on ball position and objects next to it
     * @param ball ball from the game
     */
    void MoveBall( TBall & ball );

    size_t GetWidth() const;

    size_t GetHeight() const;

    std::vector<std::string> m_Data;  //vector of rows (strings) - represent the playing board
    EReturnVal m_Mode;  //from file of random, is saved because if player wants to  play again, I need choose the same mode
    std::string m_Map;  //name of map -> if player wants to play again, I need choose the same map

private:
    std::size_t m_Width;
    std::size_t m_Height;
    std::size_t m_NumberOfBricks;

    //move ball one tile right down
    void MoveBallRightDown( TBall & ball );

    //move ball one tile right up
    void MoveBallRightUp( TBall & ball );

    //move ball one tile left down
    void MoveBallLeftDown( TBall & ball );

    //move ball one tile left up
    void MoveBallLeftUp( TBall & ball );
};

