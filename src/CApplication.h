/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 30.04.20
*/

#pragma once

#include "CPlayingBoard.h"
#include "CBufferSwitch.h"
#include "TPaddle.h"
#include "CMenu.h"
#include "TBall.h"
#include "CBonus.h"
#include "CBonusNothing.h"
#include "CBonusLongerPaddle.h"
#include "CBonusSlowTimeLongerPaddle.h"
#include "EReturnVal.h"
#include "Colors.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;  //because of using time unit suffix ( ms )

static constexpr auto SLEEP_TIME = 50ms;  //how often is new frame printed

/**
 * CApplication is game Arkanoid (Breakout)
 */
class CApplication {
public:

    CApplication();

    CApplication( const CApplication & ) = delete;

    ~CApplication();

    CApplication & operator =( const CApplication & ) = delete;

    /**
     * launch the application
     * @return false if something fails, otherwise true
     */
    int Run();

private:

    /** initialize and load playing board, init paddle and ball */
    void Init();

    /**
     * in this player can set the paddle to position he/she wants, wait until player press the 's' or '5'
     * @return QUIT -> quit or NEXT_PART -> move to the next part
     */
    EReturnVal WaitBeforeStart();

    /**
     * react on keyboard before the ball was shoot
     * @return QUIT or PAUSE or NEXT_PART or NOT_INTERESTED -> something else was hit - not interested
     */
    EReturnVal KeyboardReactionBeforeShot();

    /**
     * react when keyboard was hit - player can move the paddle by numpad ( 4 = left, 6 = right ) or ( a = left, d = right )
     * @return QUIT or PAUSE or NOT_INTERESTED -> player moved with paddle
     */
    EReturnVal KeyboardReactionInGame();

    /**
     * keyboard reaction in pause
     * @return QUIT or PAUSE (end of pause) or NOT_INTERESTED -> something else was hit - not interested
     */
    static EReturnVal KeyboardReactionInPause();

    /**
     * pause the game until player press the 'p' again or 'q' (quit)
     * @return QUIT or PAUSE (pause ended)
     */
    static EReturnVal Pause();

    /**
     * save the best score to file
     * @param fileName
     * @return false if something went wrong ( e.g. no rights for creating files in its directory ), otherwise true
     */
    bool SaveScore( const char *fileName ) const;

    /**
     * return best score from file
     * @param fileName is name of save file, where best score is saved
     * @return best score from file, if file not exists or is corrupted, return -1
     */
    static long long BestScore( const char *fileName ) ;

    const std::chrono::milliseconds INIT_SPEED = 24ms;
    CMenu m_Menu;
    TKeyboardDetector m_KeyboardDetector;
    CPlayingBoard m_PlayingBoard;
    TPaddle m_Paddle;
    TBall m_Ball;
    CBonus *m_Bonus;
    CBufferSwitch m_Buffer;  //for switching buffering on and off
    std::chrono::milliseconds m_Speed = INIT_SPEED;
    long long m_Score;
};

