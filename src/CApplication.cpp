/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 30.04.20
*/

#include "CApplication.h"


CApplication::CApplication()
        : m_Bonus( new CBonusNothing ), m_Score( 0 ) {}

CApplication::~CApplication() {
    m_Buffer.TurnOn();  //turn on the buffering before leaving application
    delete m_Bonus;
    std::system( "clear" );  //clear the screen
}

void CApplication::Init() {
    m_Paddle = TPaddle { m_PlayingBoard.GetWidth(), m_PlayingBoard.GetHeight() };
    m_PlayingBoard.InitPaddle( m_Paddle );
    m_PlayingBoard.InitBall( m_Ball, m_Paddle );
    m_Score = 0;
    delete m_Bonus;
    m_Bonus = new CBonusNothing;
    m_Speed = INIT_SPEED;
}

EReturnVal CApplication::WaitBeforeStart() {
    //wait until player press the "s" or "5"
    while ( true ) {
        bool pause = false;
        std::system( "clear" );  //clear the screen
        m_PlayingBoard.Print();  //print the playing board
        if ( TKeyboardDetector::KeyboardPressed() ) {
            EReturnVal kReaction = KeyboardReactionBeforeShot();
            switch ( kReaction ) {
                case EReturnVal::QUIT :  //quit
                    return EReturnVal::QUIT;  //quit from game
                case EReturnVal::PAUSE :  //pause
                    if ( Pause() == EReturnVal::QUIT )
                        return EReturnVal::QUIT;  //quit from pause
                    pause = true;
                    break;
                case EReturnVal::NEXT_PART:  //move to the next part ( space bar pressed )
                    return EReturnVal::NEXT_PART;
                default :  //can not happend
                    break;
            }
        }
        if ( !pause ) {  //help instructions don't print immediately after pause ( use blue color for text in quotation marks )
            std::cout
                    << "use " << BRIGHT_CYAN << "\"a\"" << DEFAULT_COLOR <<
                       " or " << BRIGHT_CYAN << "\"4\"" << DEFAULT_COLOR << " to move left\n"
                       "use " << BRIGHT_CYAN << "\"d\"" << DEFAULT_COLOR <<
                       " or " << BRIGHT_CYAN << "\"6\"" << DEFAULT_COLOR << " to move right\n"
                       "use " << BRIGHT_CYAN << "\"s\"" << DEFAULT_COLOR <<
                       " or " << BRIGHT_CYAN << "\"5\"" << DEFAULT_COLOR << "to release the ball"
                    << std::endl;
        }
        std::this_thread::sleep_for( m_Speed );
    }
}

int CApplication::Run() {
    bool playAgain = false;
    bool quit = false;
    //loop of menu, game, final menu
    while ( true ) {
        //play again -> player menu is not shown -> player play the map which selected last turn
        if ( playAgain ) {
            //random map
            if ( m_PlayingBoard.m_Mode == EReturnVal::RANDOM_MAP )
                m_PlayingBoard.LoadRandom();
                //map from file
            else {
                if ( !m_PlayingBoard.LoadFromFile( m_PlayingBoard.m_Map ) ) {
                    //file was corrupted
                    playAgain = false;
                    continue;
                }
            }
        } else {
            //menu loads the map from file or randomly
            if ( CMenu::LoadPlayingBoard( m_PlayingBoard, m_Buffer ) == EReturnVal::QUIT )
                return 0;
        }

        Init();  //initialization of playing board, paddle and ball

        if ( WaitBeforeStart() == EReturnVal::QUIT ) { //player set up start position and release the ball
            playAgain = false;
            continue;  //if player wants to quit from WaitsBeforeStart;
        }

        int retarder = 4;  //slow down the ball - ball move 4x slower thad the paddle
        bool result = false;
        //game loop - while player didn't lose of win
        while ( true ) {
            std::system( "clear" );  //clear the screen

            if ( m_Bonus->m_ActivationTime <= 0 ) {
                m_Bonus->Deactivate( m_Paddle, m_Speed, m_PlayingBoard.m_Data );
                delete m_Bonus;
                m_Bonus = m_PlayingBoard.RemoveBricks( m_Ball );
                m_Bonus->Activate( m_Paddle, m_Speed, m_PlayingBoard.m_Data );
            } else {
                m_Bonus->m_ActivationTime--;
                delete m_PlayingBoard.RemoveBricks( m_Ball );
            }
            m_PlayingBoard.Print() << BRIGHT_YELLOW <<"Score: " << ++m_Score << DEFAULT_COLOR << std::endl;
            m_Bonus->Print( std::cout );
            //check if player lost
            if ( CPlayingBoard::CheckLoss( m_Ball, m_Paddle ) )
                break;
            //check if player won
            if ( m_PlayingBoard.CheckWin() ) {
                result = true;
                break;
            }
            //move ball, ball move 4x slower than paddle
            if ( retarder == 0 ) {
                m_PlayingBoard.MoveBall( m_Ball );  //move ball
                retarder = 4;
            } else {
                retarder--;
            }
            //if keyboard was pressed
            if ( TKeyboardDetector::KeyboardPressed() ) {
                EReturnVal kReaction = KeyboardReactionInGame();  //keyboard reaction
                if ( kReaction == EReturnVal::QUIT ) { //quit
                    quit = true;
                    break;
                } else if ( kReaction == EReturnVal::PAUSE )  //pause
                    if ( Pause() == EReturnVal::QUIT ) {//quit from pause
                        quit = true;
                        break;
                    }
            }
            std::this_thread::sleep_for( m_Speed );  //sleep
        }
        long long bestScore = BestScore( "saveFiles/score.txt" );
        if ( m_Score > bestScore )
            SaveScore( "saveFiles/score.txt" );

        if ( quit ) {
            quit = false;
            playAgain = false;
            continue;  //return to the main menu
        }

        playAgain = CMenu::finalScreenMenu( result, m_Score, bestScore ) == EReturnVal::PLAY_AGAIN;
    }
}

EReturnVal CApplication::KeyboardReactionBeforeShot() {
    char userInput;
    std::cin >> userInput;
    switch ( userInput ) {
        case '4' :  //move paddle with ball left
        case 'a' :  //move paddle with ball left
        case 'A' :  //move paddle with ball left
            m_PlayingBoard.MovePaddleWithBallLeft( m_Paddle, m_Ball );
            break;
        case '6' :  //move paddle with ball right
        case 'd' :  //move paddle with ball right
        case 'D' :  //move paddle with ball right
            m_PlayingBoard.MovePaddleWithBallRight( m_Paddle, m_Ball );
            break;
        case '5' :  //wanna move to the next part
        case 's' :  //wanna move to the next part
        case 'S' :  //wanna move to the next part
            return EReturnVal::NEXT_PART;
        case 'q' :  //quit
        case 'Q' :  //quit
            return EReturnVal::QUIT;
        case 'p' :  //pause
        case 'P' :  //pause
            return EReturnVal::PAUSE;
        default :
            break;
    }
    return EReturnVal::NOT_INTERESTED;
}

EReturnVal CApplication::KeyboardReactionInGame() {
    char userInput;
    std::cin >> userInput;
    switch ( userInput ) {
        case '4' :  //move paddle left
        case 'a' :  //move paddle left
        case 'A' :  //move paddle left
            m_PlayingBoard.MovePaddleLeft( m_Paddle );
            break;
        case '6' :  //move paddle right
        case 'd' :  //move paddle right
        case 'D' :  //move paddle right
            m_PlayingBoard.MovePaddleRight( m_Paddle );
            break;
        case 'q' :  //quit
        case 'Q' :  //quit
            return EReturnVal::QUIT;
        case 'p' :  //pause
        case 'P' :  //pause
            return EReturnVal::PAUSE;
    }
    return EReturnVal::NOT_INTERESTED;
}

EReturnVal CApplication::KeyboardReactionInPause() {
    char userInput;
    std::cin >> userInput;
    if ( userInput == 'p' || userInput == 'P' )
        return EReturnVal::PAUSE;
    else if ( userInput == 'q' || userInput == 'Q' )
        return EReturnVal::QUIT;
    return EReturnVal::NOT_INTERESTED;
}

EReturnVal CApplication::Pause() {
    std::cout << " GAME IS PAUSED\n"  //GAME IS PAUSED in default color
              << BRIGHT_GREEN << " -press \"p\" to resume\n"
              << BRIGHT_RED << " -press \"q\" to quit" << DEFAULT_COLOR  //-press "q" to quit in red color
              << std::endl;
    //sleep until player press 'p' again or quit the game
    while ( true ) {
        std::this_thread::sleep_for( SLEEP_TIME );
        EReturnVal kReaction = KeyboardReactionInPause();
        if ( kReaction == EReturnVal::PAUSE )
            return EReturnVal::PAUSE;  //end of pause
        else if ( kReaction == EReturnVal::QUIT )
            return EReturnVal::QUIT;  //quit
        std::this_thread::sleep_for( SLEEP_TIME );
    }
}

bool CApplication::SaveScore( const char *fileName ) const {
    //output stream
    std::ofstream out { fileName };
    if ( !out )
        return false;
    //save the score
    out << m_Score;
    return true;
}

long long CApplication::BestScore( const char *fileName ) {
    std::ifstream in { fileName };
    if ( !in )
        return -1;
    long long tmp;
    if ( !( in >> tmp ) )
        return -1;
    return tmp;
}


