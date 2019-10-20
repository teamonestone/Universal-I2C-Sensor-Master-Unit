#include "utility.h"

/**
 * @brief Delay based on millis() (milliseconds resolution).
 * 
 * @param delay_time time to wait in milliseconds.
 */
void _delay(uint32_t delay_time) {
    uint64_t time_to_wait = millis() + delay_time;

    while (millis() <= time_to_wait);
}

/**
 * @brief Delay based on micros() (microseconds resolution).
 * 
 * @param delay_time time to wait in microseconds.
 */
void _micro_delay(uint32_t delay_time) {
    uint64_t time_to_wait = micros() + delay_time;

    while (micros() <= time_to_wait);
}

/**
 * @brief Delay based on millis() with function call during the delay (milliseconds resolution).
 * 
 * @param delay_time time to wait in milliseconds.
 * @param funct function pointer to a void function with a uint64_t argument.
 */
void _delay_f(uint32_t delay_time, void (*funct)(uint64_t)) {
    uint64_t time_to_wait = millis() + delay_time;

    while (millis() <= time_to_wait) {
        funct(time_to_wait);
    }
}

/**
 * @brief Delay based on micros() with function call during the delay  (microseconds resolution).
 * 
 * @param delay_time time to wait in microseconds.
 * @param funct function pointer to a void function with a uint64_t argument.
 */
void _micro_delay_f(uint32_t delay_time, void (*funct)(uint64_t)) {
    uint64_t time_to_wait = micros() + delay_time;

    while (micros() <= time_to_wait) {
        funct(time_to_wait);
    }
}

/**
 * @brief Delay based on millis() with additional break condition (milliseconds resolution).
 * 
 * @param delay_time time to wait in milliseconds.
 * @param funct function pointer to a bool function with a uint64_t argument.
 */
void _delay_with_condition(uint32_t delay_time, bool (*condition)(uint64_t)) {
    uint64_t time_to_wait = millis() + delay_time;

    while (millis() <= time_to_wait && condition(time_to_wait));
}

/**
 * @brief Delay based on micros() with additional break condition (microseconds resolution).
 * 
 * @param delay_time time to wait in microseconds
 * @param funct function pointer to a bool function with a uint64_t argument.
 */
void _micro_delay_with_condition(uint32_t _delay_time, bool (*_condition)(uint64_t)) {
    uint64_t _time_to_wait = micros() + _delay_time;

    while (micros() <= _time_to_wait && _condition(_time_to_wait));
}