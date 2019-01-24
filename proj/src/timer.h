#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdbool.h>
#include <stdint.h>

/** @defgroup timer timer
 * @{
 * Functions to manipulate the timer
 */


/**
 * @brief Subscribes Timer 0 interrupts
 *
 * @return Returns 0 upon success and 1 otherwise
 */
int(timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Timer 0 interrupts
 *
 * @return Returns 0 upon success and 1 otherwise
 */
int(timer_unsubscribe_int)();


//void (timer_int_handler)();

/**
 * @brief Sets the clock_tick flag and the timer interrupt handler
 */
void game_timer_ih();

/**
 * @brief Timer 0 interrupt handler (increments counter)
 */
extern void timer_int_asm();

/**
 * @brief Makes possible to access to the static variable counter
 *
 * @return Returns counter value
 */
int timer_get_counter();

/**
 * @brief Gets variable clock_tick
 *
 * @return Returns clock_tick boolean
 */
bool get_clock_tick();

/**
 * @brief Sets the flag clock_tick
 */
void set_clock_tick();

/**
 * @brief Unsets the flag clock_tick
 */
void unset_clock_tick();

/**
 * @brief Puts the counter back to 0
 */
void reset_timer();

/** @} end of Timer */

#endif /* _TIMER_H */
