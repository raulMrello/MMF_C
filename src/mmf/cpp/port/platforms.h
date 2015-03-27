/*
 * Timer.h
 *
 *  Created on: 12/3/2015
 *      Author: raulMrello
 */

#ifndef SRC_PORT_TIMER_H_
#define SRC_PORT_TIMER_H_


/** \def PLATFORM_TIMER_START
 *  \brief PLATFORM_TIMER_START external function provides the way to start a platform specific
 *  timer. This function must be implemented for each platform porting
 *  \param delay Delay in microseconds
 *  \param timerCb Callback to be called on timer timeout
 *  \param handler Object reference to pass as argument of the timer callback
 */
#define PLATFORM_TIMER_START(delay_us, timer_callback, callback_handler)
//extern void PLATFORM_TIMER_START(int delay, void(*timerCb)(void*), void* handler);


/** \def PLATFORM_TIMER_STOP
 *  \brief PLATFORM_TIMER_STOP external function provides the way to stop a platform specific
 *  timer. This function must be implemented for each platform porting
 *  \param handler Object reference assigned to the specific timer callback
 */
#define PLATFORM_TIMER_STOP(callback_handler)
//extern void PLATFORM_TIMER_STOP(void* handler);

#include "common.h"

#endif /* SRC_PORT_TIMER_H_ */
