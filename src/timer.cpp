#include "pros/rtos.hpp"
#include "timer.hpp"

Timer::Timer(Time time)
    : period(time) {
    lastTime = from_ms(pros::millis());
}

Time Timer::getTimeSet() {
    const Time time = now(); // get time from RTOS
    if (!paused) timeWaited += time - lastTime; // don't update if paused
    lastTime = time; // update last time
    return period;
}

Time Timer::getTimeLeft() {
    const Time time = now(); // get time from RTOS
    if (!paused) timeWaited += time - lastTime; // don't update if paused
    lastTime = time; // update last time
    const Time delta = period - timeWaited; // calculate how much time is left
    return (delta.val() > 0) ? delta : 0; // return 0 if timer is done
}

Time Timer::getTimePassed() {
    const Time time = now(); // get time from RTOS
    if (!paused) timeWaited += time - lastTime; // don't update if paused
    lastTime = time; // update last time;
    return timeWaited;
}

bool Timer::isDone() {
    const Time time = now(); // get time from RTOS
    if (!paused) timeWaited += time - lastTime; // don't update if paused
    lastTime = time; // update last time
    const Time delta = period - timeWaited; // calculate how much time is left
    return delta.val() <= 0;
}

bool Timer::isPaused() {
    const Time time = now(); // get time from RTOS
    if (!paused) timeWaited += time - lastTime; // don't update if paused
    return paused;
}

void Timer::set(Time time) {
    period = time; // set how long to wait
    reset();
}

void Timer::reset() {
    timeWaited = from_sec(0);
    lastTime = now();
}

void Timer::pause() {
    if (!paused) lastTime = now();
    paused = true;
}

void Timer::resume() {
    if (paused) lastTime = now();
    paused = false;
}

void Timer::waitUntilDone() {
    do delay(5_ms);
    while (!this->isDone());
}