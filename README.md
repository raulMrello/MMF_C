# minimal_multithreaded_framework

Minimal Multithreaded framework (MMF) is a run-to-completion cooperative kernel in which small blocking tasks are executed in a cooperative manner. Due to its run-to-completion semantics, tasks must return control as soon as possible, in order to allow other low priority tasks to be executed. If a task blocks, then the rest of the tasks will not execute anymore.
It has been specifically designed for microcontrollers with extremely constrained memory resources. Tasks shares the same memory space, and hence there is only one common stack for all of them, saving a huge quantity of RAM.

## Features
1. Run-to-completion cooperative kernel (no tasks limit)
2. Fixed priority tasks
3. No task context switching. All tasks shares the same memory space.
4. Tasks can be suspended and yielded.
5. Tasks can be subscribed to published "topics" (Observer pattern) and/or waiting for event flags (or/and conditions with/without timeout limit).
6. Can be ported to any platform by implementing macros PLATFORM_TIMER_START / PLATFORM_TIMER_STOP, and PLATFORM_ENTER_CRITICAL / PLATFORM_EXIT_CRITICAL.
7. Framework coded in ANSI C (MMF_C) and C++ (MMF)
8. MMF_C uses static allocation. No malloc, calloc, realloc primitives are used.

## Changelog

> 31.03.2015-001 (MMF_C) branch: topic_pools_as_queues -----------
 - PENDING: critical sections testing.
 - Added 'done' callback to topic publishing in order to warn the publisher when all subscribers had processed the topic update.
 - KNOWN ISSUES: 
  	- NONE

> 30.03.2015-001 (MMF_C) branch: topic_pools_as_queues -----------
 - PENDING: critical sections testing.
 - Changed status=SUSPENDED by a new property, named isSuspended to allow combination of suspension and event/topic waits.
 - Added a parameter to Task_wait_or / Task_wait_and to enable a safety timer
 - KNOWN ISSUES: 
  	- NONE

> 29.03.2015-001 (MMF_C) branch: topic_pools_as_queues -----------
 - PENDING: test critical sections.
 - Changed Exception_ALLOC by Exception_INIT
 - Added critical sections to Topic_notify
 - KNOWN ISSUES: 
  	- Change status=SUSPENDED by a new property, named isSuspended to allow combination of suspension and event/topic waits.
  	- Add a parameter to Task_wait_or / Task_wait_and to enable a safety timer

> 28.03.2015-002 (MMF_C) branch: topic_pools_as_queues -----------
 - Added critical section. Tested PENDIG!
 - KNOWN ISSUES: 
  	- Combination of task waiting by: suspension timer, event flags hasn't been tested yet.

> 28.03.2015-001 (MMF_C) branch: topic_pools_as_queues -----------
 - Topic pools now act as fifo memory pools. Tested OK!
 - Added macros PLATFORM_ENTER_CRITICAL and PLATFORM_EXIT_CRITICAL to platforms.h
 - KNOWN ISSUES: 
 	- It is necessary to define critical sections to avoid memory leaks with interrupts.
 	- Combination of task waiting by: suspension timer, event flags hasn't been tested yet.

> 27.03.2015-003 (MMF_C) branch: topic_pools_as_queues -----------
 - Branch start to change the way Tasks handles its internal topic pool (see knwown issues on previous logs).

> 27.03.2015-002 (MMF_C) -----------------------------------------
 - Cleared some content in "platforms.h" for being fully platform independent.
 
> 27.03.2015-001 (MMF_C) -----------------------------------------
 - Improvements from eclipse_windows_mmf_c project.
 - Fully compatible with event flags (OS_send_event, Task_wait_or, Task_wait_and)
 - Tasks can wait for event flags and topic updates at the same time
 - Added primitive "Exception_clear" to reset exception objects at any time.
 - KNOWN ISSUES:
 	- Topic pools (in Tasks) are arrays that are checked sequentially. They should behave as FIFOs.
 	- Combination of task waiting by: suspension timer, event flags hasn't been tested yet.
 	
 
 
 

