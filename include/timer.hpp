#pragma once

#include "units/units.hpp"

class Timer {
    public:
        /**
         * @brief Construct a new Timer
         *
         * @note the timer will start counting down as soon as it is created
         * @note the timer constructor is non-blocking so code after it will be executed immediately
         * @note if the timer is constructed in a global scope, its behavior is undefined. You can
         *       call set() before using the timer if you absolutely need to construct it in a global scope
         *
         * @param time how long to wait
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * @endcode
         */
        Timer(Time time);
        /**
         * @brief Get the amount of time the timer was set to
         *
         * @return Time
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // get the time the timer was set to
         * Time time = timer.getTimeSet(); // time = 1_sec
         * @endcode
         */
        Time getTimeSet();
        /**
         * @brief Get the amount of time left on the timer
         *
         * @return Time
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // delay for 300ms
         * Timer::delay(300_ms);
         * // get the time left on the timer
         * Time time = timer.getTimeLeft(); // time = 700_ms
         * @endcode
         */
        Time getTimeLeft();
        /**
         * @brief Get the amount of time passed on the timer
         *
         * @return Time
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // delay for 300ms
         * Timer::delay(300_ms)
         * // get the time passed on the timer
         * Time time = timer.getTimePassed(); // time = 300_ms
         * @endcode
         */
        Time getTimePassed();
        /**
         * @brief Get whether the timer is done or not
         *
         * @return true the timer is done
         * @return false the timer is not done
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // delay for 500ms
         * pros::delay(500_ms);
         * // check if the timer is done
         * timer.isDone(); // false
         * // delay for another 500ms
         * Timer::delay(500_ms);
         * // check if the timer is done
         * timer.isDone(); // true
         * @endcode
         */
        bool isDone();
        /**
         * @brief Get whether the timer is paused or not
         *
         * @return true the timer is paused
         * @return false the timer is not paused
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // pause the timer
         * timer.pause();
         * // check if the timer is paused
         * timer.isPaused(); // true
         * // resume the timer
         * timer.resume();
         * // check if the timer is paused
         * timer.isPaused(); // false
         * @endcode
         */
        bool isPaused();
        /**
         * @brief Set the amount of time the timer should count down. Resets the timer
         *
         * @param time time to count down from
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // set the timer to wait for 2 seconds
         * timer.set(2_sec);
         * @endcode
         */
        void set(Time time);
        /**
         * @brief reset the timer
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // delay for 500ms
         * Timer::delay(500_ms);
         * // reset the timer
         * timer.reset();
         * // delay for another 500ms
         * Timer::delay(500_ms);
         * // check if the timer is done
         * timer.isDone(); // false
         * @endcode
         */
        void reset();
        /**
         * @brief pause the timer
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // pause the timer
         * timer.pause();
         * // delay for 2000ms
         * pros::delay(2000_ms);
         * // check if the timer is done
         * timer.isDone(); // false
         * @endcode
         */
        void pause();
        /**
         * @brief resume the timer
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // pause the timer
         * timer.pause();
         * // delay for 500ms
         * Timer::delay(500_ms);
         * // resume the timer
         * timer.resume();
         * // delay for another 500ms
         * Timer::delay(500_ms);
         * // check if the timer is done
         * timer.isDone(); // false
         * @endcode
         */
        void resume();
        /**
         * @brief wait until the timer is done
         *
         * @b Example
         * @code {.cpp}
         * // create a timer that will wait for 1 second
         * Timer timer(1_sec);
         * // wait until the timer is done
         * timer.waitUntilDone();
         * std::cout << "done!" << std::endl;
         * @endcode
         */
        void waitUntilDone();
        /**
         * @brief get the current system time
         *
         * @return Time
         *
         * @b Example
         * @code {.cpp}
         * // get the current system time
         * Time time = Timer::now();
         * @endcode
         */
        static Time now();
        /**
         * @brief block the current task for a certain amount of time
         *
         * @param time
         *
         * @b Example
         * @code {.cpp}
         * // delay for 1 second
         * Timer::delay(1_sec);
         * @endcode
         */
        static void delay(Time time);
    private:
        Time period;
        Time lastTime;
        Time timeWaited = 0;
        bool paused = false;
};