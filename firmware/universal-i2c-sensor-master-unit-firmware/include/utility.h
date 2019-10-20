#ifndef utility_h
#define utility_h

#include <inttypes.h>
#include <Arduino.h>

void _delay(uint32_t delay_time);			                    						// Delay based on millis() (milliseconds resolution).
void _micro_delay(uint32_t delay_time);		                    						// Delay based on micros() (microseconds resolution).
void _delay_f(uint32_t delay_time, void (*funct)(uint64_t));							// Delay based on millis() with function call during the delay (milliseconds resolution).
void _micro_delay_f(uint32_t delay_time, void (*funct)(uint64_t));						// Delay based on micros() with function call during the delay  (microseconds resolution).
void _delay_with_condition(uint32_t delay_time, bool (*condition)(uint64_t));			// Delay based on millis() with additional break condition (milliseconds resolution).
void _micro_delay_with_condition(uint32_t delay_time, bool (*condition)(uint64_t));		// Delay based on micros() with additional break condition (microseconds resolution).

#endif