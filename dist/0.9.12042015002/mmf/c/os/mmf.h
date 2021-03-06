/*
 * mmf.h
 *
 *  Created on: 12/3/2015
 *      Author: raulMrello
 *
 *  MMF(_C)	is the ANSI C implementation of the Minimal Multithreaded Framework MMF.
 *  It provides a Run-To-Completion, Cooperative and Fixed-priority-based Kernel, in which
 *  tasks can be executed.
 *
 *  As tasks can not block, they must be driven by different event handling callbacks, which
 *  the kernel will invoke. Tasks do their work and return as soon as possible.
 *
 *  The number of task is not limitied, users can allocate enough space for whatever number
 *  of tasks, through the macro OS_ALLOC.
 *
 *  For example:	OS_ALLOC(mmf, 10); Allocates space for 10 tasks.
 *  				OS_ALLOC(mmf, 1000); Allocates space for 1000 tasks.
 *
 *  The basic procedure for using this framework is extremely simple, and reduced to 4 steps:
 *
 *  	1 - Kernel allocation and initialization (OS_ALLOC)
 *  	2 - [optionally] Topics initialization (if defined a publish/subscribe system)
 *  	3 - Task creation (Task_initialize)
 *  	4 - Kernel scheduling (OS_schedule)
 *
 */

#ifndef MMF_OS_MMF_H_
#define MMF_OS_MMF_H_

#ifdef __cplusplus
 extern "C" {
#endif

//------------------------------------------------------------------------------------
//-- DEPENDENCIES --------------------------------------------------------------------
//------------------------------------------------------------------------------------

#include "../port/platforms.h"	///< required for porting
#include "OS.h"					///< required for OS primitives like: OS_ALLOC, OS_schedule ...
#include "Task.h"				///< required for Task primitives like: Task_initialize ...
#include "Topic.h"				///< required for Topic primitives like: Topic_notify ...
#include "Exception.h"			///< required for Exception primitives like: catch ...
#include "Timer.h"				///< required for Timming primitives like: Timer_start ...
#include "Fifo.h"				///< required for Fifo management
#include "Memory.h"				///< required for Memory management
#include "List.h"				///< required for List management

//------------------------------------------------------------------------------------
//-- DEFINES -------------------------------------------------------------------------
//------------------------------------------------------------------------------------

#define __MMF_C_VERSION "0.9.10042015002"




#ifdef __cplusplus
}
#endif

#endif /* MMF_OS_MMF_H_ */
