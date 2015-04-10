/*
 * task.h
 *
 *  Created on: 11/3/2015
 *      Author: raulMrello
 */

#ifndef MMF_OS_TASK_TASK_H_
#define MMF_OS_TASK_TASK_H_

#include "../port/platforms.h" ///< platform dependent
#include <list>
#include <string>
#include <cstddef>		///< required for NULL macro
#include "Exception.h"

/**
 *  \brief Macros to convert time units
 */
#define SECONDS(v)		(v*1000000)		///< time conversion us -> sec
#define MILLIS(v)		(v*1000)		///< time conversion us -> us
#define MICROS(v)		(v)				///< time macro in usec

/**
 *  \brief Macros to define priority levels. There are 4 priority levels, each divided in other
 *  8 sublevels, obtaining up to 32 fixed priority levels.
 */
#define PRIO_CRITICAL	(int)0			///< highest priority level (critical)
#define PRIO_HIGH 		(int)8			///< high priority level
#define PRIO_MED  		(int)16			///< medium priority level
#define PRIO_LOW  		(int)24			///< low priority level
#define SUBPRIO_MAX 	(int)0			///< max priority sublevel
#define SUBPRIO_MIN 	(int)7			///< min priority sublevel


/**
 *  \brief Macros to define event codes handled by kernel tasks. Tasks can get ready state after a
 *  suspension timeout, a scheduling executin cycle if yielded, a topic update if subscribed to any
 *  kind of topic or an event flag notification
 */
#define EVT_NONE		(int)0x00000000	///< event which sets a yield->ready transition
#define EVT_RESUMED 	(int)0x00000001 ///< event which sets a suspended->ready transition
#define EVT_TOPIC	 	(int)0x00000002 ///< event due to a topic update
#define EVT_FLAGS		(int)0x00000004 ///< event which sets a flagwait->ready transition


/** \class Task
 *  \brief Tasks are pieces of software capable to be executed in a run-to-completion manner, this
 *  implies that they must return to allow other tasks to be executed (they never must block).
 *  Tasks can be STOPPED during initialization, WAITING for an event, READY for execution,
 *  RUNNING during execution and YIELD if allow other tasks to take control of the cpu.
 */
class Task {
public:

	enum Stat {STOPPED, READY, WAITING, RUNNING, YIELD};	///< \enum Stat (task status)


	/** \fn Task
	 *  \brief Default constructor. Task name can be assigned during object creation.
	 *  \name Task name
	 */
	Task(const std::string& name = "") : _name(name){
		_status = STOPPED;
		_isSuspended = false;
		_evtlist.clear();
		prio = PRIO_LOW + SUBPRIO_MIN;
	}

	/** \fn ~Task
	 *  \brief Default destructor. It will deallocate all resources
	 */
	virtual ~Task();

	/** \fn init
	 *  \brief Interface to initialize inherited classes during task creation
	 */
	virtual int init()=0;

	/** \fn exec
	 *  \brief Interface to execute task implementation of the inherited classes
	 *  \param evt Event code which causes the tast to execute (see above EVT_...)
	 */
	virtual int exec(int evt) = 0;

	/** \fn kill
	 *  \brief Interface to kill inherited classes
	 */
	virtual int kill()=0;

	/** \fn start
	 *  \brief Starts task assigning a fixed priority
	 *  \param vprio Task priority
	 */
	void start(int vprio) throw (Exception);

	/** \fn suspend
	 *  \brief Suspends a task during several microseconds
	 *  \param delay_us Microsendos to suspend
	 */
	void suspend(unsigned int delay_us);

	/** \fn resume
	 *  \brief Sets a task ready after a period of suspension
	 *  \param forced Boolean flag to force a resume while the task is under suspension and
	 *  its timer has not yet finished.
	 */
	void resume(bool forced = true);

	/** \fn yield
	 *  \brief Sets a task yielded to allow other tasks to take control of the cpu
	 */
	void yield();

	/** \fn isYield
	 *  \brief Checks if it is yielded
	 *  \return true or false
	 */
	bool isYield();

	/** \fn isReady
	 *  \brief Checks if it is ready for execution
	 *  \return true or false
	 */
	bool isReady();

	/** \fn setReady
	 *  \brief Sets a task ready, indicating which event has caused it.
	 *  \param evt Event code which causes the state change
	 */
	void setReady(int evt=0);

	/** \fn setWaiting
	 *  \brief Sets a task waiting for some situation
	 */
	void setWaiting();

	/** \fn setRunning
	 *  \brief Sets a task running
	 */
	void setRunning();

	/** \fn setStop
	 *  \brief Sets a task stopped
	 */
	void setStop();

	/** \fn getNextEvt
	 *  \brief Get the next event which causes the task to be executed.
	 *  \return Event code
	 */
	int getNextEvt();

	int prio;		///< Task priority in the range PRIO_CRITICAL .. PRIO_LOW + SUBPRIO_MIN
private:
	Stat _status;				///< Task status flag
	bool _isSuspended;			///< Suspension flag
	std::list<int> _evtlist;	///< List of pending events to be handled
protected:
	std::string _name;			///< Task name
};

#endif /* MMF_OS_TASK_TASK_H_ */
