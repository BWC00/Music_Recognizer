/**
 * ```text
 * ╒══════════════════════════════════════════════════════════════╕
 * │                       Audio Recognizer                       │
 * │                      Talen en Automaten                      │
 * │                          UAntwerpen                          │
 * │                         LIBRARY FILE                         │
 * │ SOURCE: https://gist.github.com/mcleary/b0bf4fa88830ff7c882d │
 * ╘══════════════════════════════════════════════════════════════╛
 * ```
 *
 * @file Timer.h
 * @author mcleary
 */

#ifndef TAL_TO_GROEP_TIMER_H
#define TAL_TO_GROEP_TIMER_H


#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

/**
 * @class Timer
 * @brief A stopwatch-like timer.
 * Each instance has its seperate schedule and can be used independently.
 */
class Timer
{
public:
    /**
     * @brief Starts the timer.
     */
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    /**
     * @brief Stops the timer.
     */
    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    /**
     * @brief Fetches the elapsed milliseconds.
     * If the timer is still running, it will assume the time of this function call as the end of the timed period, it
     * will not stop the timer.
     * If the timer is no longer running, the elapsed milliseconds from the last start to the last stop are returned.
     *
     * @return
     */
    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    /**
     * @brief Fetches the elapsed seconds.
     * See also: elapsedMilliseconds()
     *
     * @return
     */
    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};


#endif //TAL_TO_GROEP_TIMER_H
