/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 04.05.20
*/

#pragma once

#include "TPaddle.h"
#include "Colors.h"

#include <chrono>
#include <vector>
#include <string>

/** abstract class
 * child classes are CBonusNothing, CBonusLongerPaddle, CBonusSlowTime
 */
class CBonus {
public:
    explicit CBonus( int x = 0 )
            : m_ActivationTime( x ) {}

    CBonus( const CBonus & ) = default;

    virtual ~CBonus() = default;

    /**
     * activate bonus
     * @param paddle
     * @param speed speed/time/frequency
     * @param board playing board
     */
    virtual void
    Activate( TPaddle & paddle, std::chrono::milliseconds & speed, std::vector<std::string> & board ) const = 0;

    /**
     * deactivate bonus, return settings to default
     * @param paddle
     * @param speed speed/time/frequency
     * @param board playing board
     */
    virtual void
    Deactivate( TPaddle & paddle, std::chrono::milliseconds & speed, std::vector<std::string> & board ) const = 0;

    /**
     * print name of bonus and remaining time to the output stream
     * @param os output stream
     * @return output stream
     */
    virtual std::ostream & Print( std::ostream & ) const = 0;

    int m_ActivationTime;  //how long will be bonus active
};

