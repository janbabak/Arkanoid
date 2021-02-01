/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 30.04.20
*/

#include "CPlayingBoard.h"

CPlayingBoard::CPlayingBoard()
        : m_Data( {} ), m_NumberOfBricks( 0 ) {}

std::ostream & CPlayingBoard::Print( std::ostream & os ) const {
    for ( size_t i = 0; i < m_Height; ++i ) {
        for ( size_t j = 0; j < m_Width; ++j )
            switch ( m_Data[ i ][ j ] ) {
                case BRICK_CHAR :
                    os << BRIGHT_MAGENTA << m_Data[ i ][ j ] << DEFAULT_COLOR;
                    break;
                case BALL_CHAR :
                    os << BRIGHT_RED << m_Data[ i ][ j ] << DEFAULT_COLOR;
                    break;
                case PADDLE_CHAR :
                    os << BRIGHT_BLUE << m_Data[ i ][ j ] << DEFAULT_COLOR;
                    break;
                default :
                    os << m_Data[ i ][ j ];
            }
        os << '\n';
    }
    return os;
}

void CPlayingBoard::InitPaddle( TPaddle & paddle ) {
    for ( std::size_t i = paddle.m_X; i < paddle.m_X + paddle.m_Width; ++i )
        m_Data[ paddle.m_Y ][ i ] = PADDLE_CHAR;
}

void CPlayingBoard::InitBall( TBall & ball, TPaddle & paddle ) {
    m_Data[ paddle.m_Y - 1 ][ paddle.m_X + paddle.m_Width / 2 ] = BALL_CHAR;
    ball = TBall { paddle.m_X + paddle.m_Width / 2, paddle.m_Y - 1 };
}

bool CPlayingBoard::CheckLoss( TBall & ball, TPaddle & paddle ) {
    return ball.m_Y >= paddle.m_Y;  //if ball is above paddle
}

bool CPlayingBoard::CheckWin() const {
    return m_NumberOfBricks == 0;  //if there any bricks left
}

CBonus *CPlayingBoard::RemoveBricks( TBall & ball ) {
    int numberOfDeletedBricks = 0;

    if ( m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] == BRICK_CHAR ) {  //left up
        m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] = EMPTY_CHAR;
        m_NumberOfBricks--;
        numberOfDeletedBricks++;
    }
    if ( m_Data[ ball.m_Y - 1 ][ ball.m_X ] == BRICK_CHAR ) {  //up
        m_Data[ ball.m_Y - 1 ][ ball.m_X ] = EMPTY_CHAR;
        m_NumberOfBricks--;
        numberOfDeletedBricks++;
    }
    if ( m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] == BRICK_CHAR ) {  //right up
        m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] = EMPTY_CHAR;
        m_NumberOfBricks--;
        numberOfDeletedBricks++;
    }
    if ( m_Data[ ball.m_Y ][ ball.m_X + 1 ] == BRICK_CHAR ) {  //right
        m_Data[ ball.m_Y ][ ball.m_X + 1 ] = EMPTY_CHAR;
        m_NumberOfBricks--;
        numberOfDeletedBricks++;
    }
    if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == BRICK_CHAR ) {  //right down
        m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] = EMPTY_CHAR;
        m_NumberOfBricks--;
        numberOfDeletedBricks++;
    }
    if ( m_Data[ ball.m_Y + 1 ][ ball.m_X ] == BRICK_CHAR ) {  //down
        m_Data[ ball.m_Y + 1 ][ ball.m_X ] = EMPTY_CHAR;
        m_NumberOfBricks--;
        numberOfDeletedBricks++;
    }
    if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == BRICK_CHAR ) {  //left down
        m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] = EMPTY_CHAR;
        m_NumberOfBricks--;
        numberOfDeletedBricks++;
    }
    if ( m_Data[ ball.m_Y ][ ball.m_X - 1 ] == BRICK_CHAR ) {  //left
        m_Data[ ball.m_Y ][ ball.m_X - 1 ] = EMPTY_CHAR;
        m_NumberOfBricks--;
        numberOfDeletedBricks++;
    }
    if ( numberOfDeletedBricks == 0 )  //no deleted bricks means no bonus
        return new CBonusNothing;

    std::mt19937 generator;
    const int PROBABILITY = 15;
    generator.seed(std::time(0) );
    std::uniform_int_distribution<int> nums(0, PROBABILITY - numberOfDeletedBricks );
    int bonusProbability = nums( generator );
    if ( bonusProbability == 0 )
        return new CBonusLongerPaddle;
    else if ( bonusProbability == 1 )
        return new CBonusSlowTime;
    else if ( bonusProbability == 2 )
        return new CBonusSlowTimeLongerPaddle;
    else
        return new CBonusNothing;
}

void CPlayingBoard::MovePaddleLeft( TPaddle & paddle ) {
    if ( m_Data[ paddle.m_Y ][ paddle.m_X - 1 ] == EMPTY_CHAR ) {  //if there is space where paddle can move
        paddle.MoveLeft();
        m_Data[ paddle.m_Y ][ paddle.m_X + paddle.m_Width ] = EMPTY_CHAR;  // replace right char by space
        m_Data[ paddle.m_Y ][ paddle.m_X ] = PADDLE_CHAR;  //makes from space on left paddle char 'O'
    }
}

void CPlayingBoard::MovePaddleRight( TPaddle & paddle ) {
    if ( m_Data[ paddle.m_Y ][ paddle.m_X + paddle.m_Width ] ==
         EMPTY_CHAR ) {  ////if there is space where paddle can move
        paddle.MoveRight();
        m_Data[ paddle.m_Y ][ paddle.m_X + paddle.m_Width - 1 ] = PADDLE_CHAR;  //makes from space on right char 'O'
        m_Data[ paddle.m_Y ][ paddle.m_X - 1 ] = ' ';  //replace left char by space
    }
}

void CPlayingBoard::MovePaddleWithBallLeft( TPaddle & paddle, TBall & ball ) {
    if ( m_Data[ paddle.m_Y ][ paddle.m_X - 1 ] == EMPTY_CHAR ) { //if there is space where paddle can move
        paddle.MoveLeft();
        //move the paddle
        m_Data[ paddle.m_Y ][ paddle.m_X + paddle.m_Width ] = EMPTY_CHAR;  // replace right char by space
        m_Data[ paddle.m_Y ][ paddle.m_X ] = PADDLE_CHAR;  //makes from space on left paddle char 'O'
        //move the ball
        ball.MoveLeft();
        m_Data[ ball.m_Y ][ ball.m_X ] = BALL_CHAR;
        m_Data[ ball.m_Y ][ ball.m_X + 1 ] = EMPTY_CHAR;
    }
}

void CPlayingBoard::MovePaddleWithBallRight( TPaddle & paddle, TBall & ball ) {
    if ( m_Data[ paddle.m_Y ][ paddle.m_X + paddle.m_Width ] ==
         EMPTY_CHAR ) {  //if there is space where paddle can move
        paddle.MoveRight();
        m_Data[ paddle.m_Y ][ paddle.m_X + paddle.m_Width - 1 ] = PADDLE_CHAR;  //makes from space on right char 'O'
        m_Data[ paddle.m_Y ][ paddle.m_X - 1 ] = EMPTY_CHAR;  //replace left char by space
        //move the ball
        ball.MoveRight();
        m_Data[ ball.m_Y ][ ball.m_X ] = BALL_CHAR;
        m_Data[ ball.m_Y ][ ball.m_X - 1 ] = EMPTY_CHAR;
    }
}

void CPlayingBoard::MoveBall( TBall & ball ) {
    switch ( ball.m_Direction ) {

        case EDirection::LEFT_UP :
            if ( m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                MoveBallLeftUp( ball );
            } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X ] == EMPTY_CHAR ) {
                if ( m_Data[ ball.m_Y ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                    if ( m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                        if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                            MoveBallRightDown( ball );
                        } else {
                            MoveBallRightUp( ball );
                        }
                    } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                        MoveBallLeftDown( ball );
                    } else {
                        MoveBallRightDown( ball );
                    }
                } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                    MoveBallRightUp( ball );
                } else {
                    MoveBallRightDown( ball );
                }
            } else if ( m_Data[ ball.m_Y ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                    MoveBallLeftDown( ball );
                } else {
                    MoveBallRightDown( ball );
                }
            } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                MoveBallRightUp( ball );
            } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                MoveBallLeftDown( ball );
            } else {
                MoveBallRightDown( ball );
            }
            break;

        case EDirection::RIGHT_UP :
            if ( m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                MoveBallRightUp( ball );
            } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X ] == EMPTY_CHAR ) {
                if ( m_Data[ ball.m_Y ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                    if ( m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                        if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                            MoveBallLeftDown( ball );
                        } else {
                            MoveBallLeftUp( ball );
                        }
                    } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                        MoveBallRightDown( ball );
                    } else {
                        MoveBallLeftDown( ball );
                    }
                } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                    MoveBallLeftUp( ball );
                } else {
                    MoveBallLeftDown( ball );
                }
            } else if ( m_Data[ ball.m_Y ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                    MoveBallRightDown( ball );
                } else {
                    MoveBallLeftDown( ball );
                }
            } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                MoveBallLeftUp( ball );
            } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                MoveBallRightDown( ball );
            } else {
                MoveBallLeftDown( ball );
            }
            break;

        case EDirection::LEFT_DOWN :
            if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                MoveBallLeftDown( ball );
            } else if ( m_Data[ ball.m_Y ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                if ( m_Data[ ball.m_Y + 1 ][ ball.m_X ] == EMPTY_CHAR ) {
                    if ( m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                        if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                            MoveBallRightUp( ball );
                        } else {
                            MoveBallLeftUp( ball );
                        }
                    } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                        MoveBallRightDown( ball );
                    } else {
                        MoveBallRightUp( ball );
                    }
                } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                    MoveBallLeftUp( ball );
                } else {
                    MoveBallRightUp( ball );
                }
            } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X ] == EMPTY_CHAR ) {
                if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                    MoveBallRightDown( ball );
                } else {
                    MoveBallRightUp( ball );
                }
            } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                MoveBallLeftUp( ball );
            } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                MoveBallRightDown( ball );
            } else {
                MoveBallRightUp( ball );
            }
            break;

        case EDirection::RIGHT_DOWN :
            if ( m_Data[ ball.m_Y + 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                MoveBallRightDown( ball );
            } else if ( m_Data[ ball.m_Y ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                if ( m_Data[ ball.m_Y + 1 ][ ball.m_X ] == EMPTY_CHAR ) {
                    if ( m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                        if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                            MoveBallLeftUp( ball );
                        } else {
                            MoveBallRightUp( ball );
                        }
                    } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                        MoveBallLeftDown( ball );
                    } else {
                        MoveBallLeftUp( ball );
                    }
                } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                    MoveBallRightUp( ball );
                } else {
                    MoveBallLeftUp( ball );
                }
            } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X ] == EMPTY_CHAR ) {
                if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                    MoveBallLeftDown( ball );
                } else {
                    MoveBallLeftUp( ball );
                }
            } else if ( m_Data[ ball.m_Y - 1 ][ ball.m_X + 1 ] == EMPTY_CHAR ) {
                MoveBallRightUp( ball );
            } else if ( m_Data[ ball.m_Y + 1 ][ ball.m_X - 1 ] == EMPTY_CHAR ) {
                MoveBallLeftDown( ball );
            } else {
                MoveBallLeftUp( ball );
            }
    }

}

void CPlayingBoard::MoveBallRightDown( TBall & ball ) {
    ball.m_Direction = EDirection::RIGHT_DOWN;
    m_Data[ ball.m_Y ][ ball.m_X ] = EMPTY_CHAR;
    ball.Move();
    m_Data[ ball.m_Y ][ ball.m_X ] = BALL_CHAR;
}

void CPlayingBoard::MoveBallRightUp( TBall & ball ) {
    ball.m_Direction = EDirection::RIGHT_UP;
    m_Data[ ball.m_Y ][ ball.m_X ] = EMPTY_CHAR;
    ball.Move();
    m_Data[ ball.m_Y ][ ball.m_X ] = BALL_CHAR;
}

void CPlayingBoard::MoveBallLeftDown( TBall & ball ) {
    ball.m_Direction = EDirection::LEFT_DOWN;
    m_Data[ ball.m_Y ][ ball.m_X ] = EMPTY_CHAR;
    ball.Move();
    m_Data[ ball.m_Y ][ ball.m_X ] = BALL_CHAR;
}

void CPlayingBoard::MoveBallLeftUp( TBall & ball ) {
    ball.m_Direction = EDirection::LEFT_UP;
    m_Data[ ball.m_Y ][ ball.m_X ] = EMPTY_CHAR;
    ball.Move();
    m_Data[ ball.m_Y ][ ball.m_X ] = BALL_CHAR;
}

size_t CPlayingBoard::GetWidth() const {
    return m_Width;
}

size_t CPlayingBoard::GetHeight() const {
    return m_Height;
}

void CPlayingBoard::LoadRandom() {
    m_Data = {};  //because data may contain map from last game
    const int BRICKS_PROBABILITY = 20;
    const size_t EMPTY_LINES = 3;  //empty lines at the bottom, where are not bricks

    //random dimensions
    std::mt19937 generator;
    generator.seed(std::time(0) );
    std::uniform_int_distribution<int> randomWidth( MIN_WIDTH, MAX_WIDTH );
    std::uniform_int_distribution<int> randomHeight( MIN_HEIGHT, MAX_HEIGHT );
    m_Width = randomWidth( generator );
    m_Height = randomHeight( generator );
    std::cout << m_Height << m_Width << std::endl;

    //empty playing board
    m_Data.resize( m_Height );
    m_Data[ 0 ].resize( m_Width, BORDER_CHAR );
    for ( size_t i = 1; i < m_Height - 1; ++i )
        m_Data[ i ].resize( m_Width, EMPTY_CHAR );
    m_Data[ m_Height - 1 ].resize( m_Width, BORDER_CHAR );
    for ( size_t i = 1; i < m_Height - 1; ++i ) {
        m_Data[ i ][ 0 ] = BORDER_CHAR;
        m_Data[ i ][ m_Width - 1 ] = BORDER_CHAR;
    }

    //add random bricks
    std::uniform_int_distribution<int> randomBrick( 0, BRICKS_PROBABILITY );
    m_NumberOfBricks = 0;
    for ( size_t i = 1; i < m_Height - 1 - EMPTY_LINES; ++i )
        for ( size_t j = 1; j < m_Width - 1; ++j )
            if ( randomBrick(generator) == 0 ) {
                m_Data[ i ][ j ] = BRICK_CHAR;
                m_NumberOfBricks++;
            }
}

bool CPlayingBoard::LoadFromFile( std::string fileName ) {
    m_Data = {};  //because data may contain map from last game

    std::ifstream in { fileName };
    if ( !in ) {
        in.close();
        return false;  //problem with file
    }
    std::string tmp;
    //read file
    while ( true ) {
        if ( !( in >> tmp ) ) {
            if ( in.eof() )
                break;
            in.close();
            return false;  //problem with file
        }
        m_Data.push_back( tmp );
    }
    //check file
    if ( ( m_Height = m_Data.size() ) < MIN_HEIGHT || m_Height > MAX_HEIGHT ) {  //2 border rows, paddle row, 2 empty rows
        in.close();
        return false;  //wrong map, or corrupted map
    }
    if ( ( m_Width = m_Data[ 0 ].size() ) < MIN_WIDTH || m_Width > MAX_WIDTH ) {
        in.close();
        return false;
    }
    for ( std::size_t i = 0; i < m_Width; ++i )
        if ( m_Data[ 0 ][ i ] != '#' || m_Data[ m_Height - 1 ][ i ] != '#' ) {
            in.close();
            return false;  // the first and last line must be borders
        }
    m_NumberOfBricks = 0;
    for ( std::size_t i = 0; i < m_Height; ++i ) {
        if ( m_Data[ i ].size() != m_Width || m_Data[ i ][ 0 ] != '#' || m_Data[ i ][ m_Width - 1 ] != '#' ) {
            in.close();
            return false;  //all lines must be the same length, first and last char must be border char
        }
        for ( std::size_t j = 0; j < m_Width; ++j )
            if ( m_Data[ i ][ j ] == '.' )  //replace dot by space
                m_Data[ i ][ j ] = ' ';
            else if ( m_Data[ i ][ j ] == '*' )
                m_NumberOfBricks++;
            else if ( m_Data[ i ][ j ] != '#' ) {
                in.close();
                return false;  //file contains invalid character
            }
    }
    in.close();
    return true;
}



