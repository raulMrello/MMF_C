/*
 * os.h
 *
 *  Created on: 11/3/2015
 *      Author: raulMrello
 */

#ifndef OS_OS_H_
#define OS_OS_H_

#include "../port/platforms.h" ///< platform dependent
#include <string>
#include "Task.h"
#include "Exception.h"

/** \def NUM_TASKS
 *  \brief Max number of allowed tasks
 */
#define NUM_TASKS 			(int)32

/**
 *  \brief Error codes raised by this module
 */
#define ERR_NONE 			(int)0		///< Error code for successful termination
#define ERR_TASK_ALLOC 		(int)-1		///< Error code during task allocation
#define ERR_TASK_DEALLOC 	(int)-2		///< Error code during task deallocation
#define ERR_OS_BAD_ARG 		(int)-3		///< Error code due to wrong argument (value, range...)
#define ERR_NO_SCHED 		(int)-4		///< Error code due scheduling with no task ready


/** \class OS
 *  \brief OS class defines the cooperative run-to-completion kernel. Tasks have fixed priorities
 *  and always is executed the highest priority one. Tasks can be suspended, yielded or waiting for
 *  a flag or a subscribed topic update. They can get activated due to these event sources:
 *   1. After the suspension timeout (if suspended status)
 *   2. After a complete scheduling cycle, all pending tasks are executed (if yielded status)
 *   3. After a topic update (if susbscribed to any kind of topic)
 *   4. [future work] After a flag update (if flagwait status)
 */
class OS {
public:

	/** \fn OS
	 *  \brief Default constructor
	 *  \param enable_log Enables log_task as the lowest priority one.
	 *  \param logCb Callback to invoke after logging execution, passing a string with the log
	 */
	OS(bool enable_log = false, void(*logCb)(std::string&) = (void(*)(std::string&))NULL);

	/** \fn init
	 *  \brief Initializes kernel internals
	 */
	void init();

	/** \fn run
	 *  \brief Allocates a new task inside the kernel and sets it up for execution. On error it
	 *  throws exception code ERR_TASK_ALLOC
	 *  \param t Task reference to be allocated in the kernel
	 *  \param prio Task priority
	 *  \throws exception code ERR_TASK_ALLOC
	 */
	void run(Task& t, int prio)  throw (Exception);

	/** \fn kill
	 *  \brief Deallocates a task out of the kernel. On error it throws exception code ERR_TASK_DEALLOC
	 *  \param t Task reference to be deallocated from the kernel
	 *  \throws exception code ERR_TASK_DEALLOC
	 */
	void kill(Task& t)  throw (Exception);

	/**
	 * @brief kernel scheduling mechanism. Evaluates next highest priority task and
	 * executes it.
	 * @return TaskId of the executed task
	 */

	/** \fn schedule
	 *  \brief kernel scheduling mechanism. Evaluates next highest priority task and executes it. On
	 *  error it throws exception code ERR_NO_SCHED
	 */
	void schedule() throw (Exception);

private:
	Task* _tasklist[NUM_TASKS];		///< List of max number of allocatable tasks
	int _taskcount;					///< Count of current allocated tasks
	bool _log_enabled;				///< Flag to enable/disable log operations
	void(*_logCb)(std::string&);	///< Installed log callback
	void getAnalytics();			///< Private function to get log report
};


#endif /* OS_OS_H_ */
