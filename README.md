# minimal_multithreaded_framework

Minimal Multithreaded framework (MMF) is a run-to-completion cooperative kernel in which small blocking tasks are executed in a cooperative manner. Due to its run-to-completion semantics, tasks must return control as soon as possible, in order to allow other low priority tasks to be executed. If a task blocks, then the rest of the task will not execute anymore.
It has been specially designed for microcontrollers with extremely constrained memory resources. Tasks shares the same memory space, and hence there is only one common stack for all of them.

## Features
1. Run-to-completion cooperative kernel (no tasks limit)
2. Fixed priority tasks
3. No task context switching. All tasks shares the same memory space.
4. Tasks can be suspended and yielded.
5. Tasks can be subscribed to published "topics" (Observer pattern) and/or waiting for event flags (or/and conditions).
6. Can be ported to any platform by implementing macros PLATFORM_TIMER_START and PLATFORM_TIMER_STOP. No more is needed.
7. Framework coded in ANSI C (MMF_C) and C++ (MMF)
8. MMF_C uses static allocation. No malloc, calloc, realloc primitives are used.

## Changelog

> 27.03.2015-001 (MMF_C) ------------------------------------------------------------------
 - Improvements from eclipse_windows_mmf_c project.
 - Fully compatible with event flags (OS_send_event, Task_wait_or, Task_wait_and)
 - Tasks can wait for event flags and topic updates at the same time
 - Added primitive "Exception_clear" to reset exception objects at any time.
 - KNOWN ISSUES:
 	- Topic pools (in Tasks) are arrays that are checked sequentially. They should behave as FIFOs.
 	- Combination of task waiting by: suspension timer, event flags and topic updates hasn't been tested yet.
 	
 
 
 

