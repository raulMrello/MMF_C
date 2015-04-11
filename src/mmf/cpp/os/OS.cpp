/*
 * OS.cpp
 *
 *  Created on: 11/3/2015
 *      Author: raulMrello
 */


#include "OS.h"
using namespace MMF;

//------------------------------------------------------------------------------------
//-- PRIVATE VARIABLES ---------------------------------------------------------------
//------------------------------------------------------------------------------------

Task**  _tasklist;			///< List of max number of allocatable tasks
uint8_t _taskcount;			///< Count of current allocated tasks
uint8_t _numTasks;			///< Count of current allocated tasks
uint32_t _tick_us;			///< System tick in microseconds

