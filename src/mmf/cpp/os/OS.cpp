/*
 * os.cpp
 *
 *  Created on: 11/3/2015
 *      Author: raulMrello
 */


#include "OS.h"

//------------------------------------------------------------------------------------
//-- PRIVATE VARIABLES ---------------------------------------------------------------
//------------------------------------------------------------------------------------

static Task**  _tasklist;			///< List of max number of allocatable tasks
static uint8_t _taskcount;			///< Count of current allocated tasks
static uint8_t _numTasks;			///< Count of current allocated tasks
static uint32_t _tick_us;			///< System tick in microseconds

