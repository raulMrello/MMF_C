/*
 * task.cpp
 *
 *  Created on: 11/3/2015
 *      Author: raulMrello
 */

#include "Task.h"
#include "../port/platforms.h" 

#ifndef true
#define true (char)1
#endif

#ifndef false
#define false (char)0
#endif

//------------------------------------------------------------------------------------
//-- REQUIRED MMF DEPENDENCIES -------------------------------------------------------
//------------------------------------------------------------------------------------

/** Required local members from other mmf modules */
extern void OS_start(Task* t, Exception *e);

//------------------------------------------------------------------------------------
//-- PRIVATE MEMBERS -----------------------------------------------------------------
//------------------------------------------------------------------------------------

/** \fn Task_start
 *  \brief Starts task (invokes init callback internally)
 *  \param t Task
 *  \param e Exception code (0: success)
 */
void Task_start(Task* t, Exception *e);

/** \fn Task_isYield
 *  \brief Checks if it is yielded
 *  \param t Task
 *  \param e Exception code (0: success)
 *  \return true or false
 */
char Task_isYield(Task* t, Exception *e);

/** \fn Task_isReady
 *  \brief Checks if it is ready for execution
 *  \param t Task
 *  \param e Exception code (0: success)
 *  \return true or false
 */
char Task_isReady(Task* t, Exception *e);

/** \fn Task_setReady
 *  \brief Sets a task ready, indicating which event has caused it.
 *  \param t Task
 *  \param evt Event code which causes the state change
 *  \param e Exception code (0: success)
 */
void Task_setReady(Task* t, int evt, Exception *e);

/** \fn Task_setStop
 *  \brief Sets a task stopped
 *  \param t Task
 *  \param e Exception code (0: success)
 */
void Task_setStop(Task* t, Exception *e);

/** \fn Task_prio
 *  \brief Get task priority
 *  \param t Task
 *  \param e Exception code (0: success)
 *  \return Priority
 */
int Task_prio(Task* t, Exception *e);

/** \fn Task_exec
 *  \brief Executes task exec callback
 *  \param t Task
 *  \param evt Event
 *  \param e Exception code (0: success)
 */
void Task_execCb(Task* t, Exception *e);

/** \fn Task_addTopic
 *  \brief Adds a new topic update to the topic pool
 *  \param t Task
 *  \param id Topic id
 *  \param name Topic name id
 *  \param data Topic data
 *  \param datasize Topic data size
 *  \param e Exception code (0: success)
 */
void Task_addTopic(Task*t, int id, const char * name, void *data, int datasize, int* pcount, void (*done)(void*), void* publisher, Exception *e);

/** \fn Task_addTopic
 *  \brief Adds a new topic update to the topic pool
 *  \param t Task
 *  \param td Topic data extracted from topic fifo pool
 *  \param e Exception code (0: success)
 */
void Task_popTopic(Task*t, TopicData *td, Exception *e);

//------------------------------------------------------------------------------------
//-- PRIVATE MEMBERS -----------------------------------------------------------------
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
static void timertask_callback(void* handler){
	if(!handler) 
		return;
	Task* t = (Task*)handler;
	Task_resume(t, false, 0);	
}

//------------------------------------------------------------------------------------
void Task_initialize(	Task* task,
						char* name,
						int prio,
						TopicData * topic_pool,
						int topic_pool_size,
						InitCallback init,
						OnYieldTurnCallback onYieldTurn,
						OnResumeCallback onResume,
						OnEventFlagCallback onEventFlag,
						OnTopicUpdateCallback onTopicUpdate,
						void * cbhandler,
						Exception *e){
	int i;
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_initialize task is null");
		return; 
	}
	task->status = STOPPED;
	task->isSuspended = false;
	Timer_initialize(&(task->tmr), 0, 0, timertask_callback, task, e);
	catch(e){
		return;
	}
	task->event = EVT_NONE;
	task->name = name;
	if(!name)
		task->name = "";
	task->evhandler = (EvtFlag){WAIT_AND, 0};
	task->prio = prio;
	task->topicpool.topicdata = topic_pool;
	task->topicpool.poolsize = topic_pool_size;
	task->topicpool.pread = 0;
	task->topicpool.pwrite = 0;
	task->topicpool.status = POOL_EMPTY;
	if(task->topicpool.topicdata){
		for(i=0; i < task->topicpool.poolsize; i++){
			task->topicpool.topicdata[i].id = 0;
			task->topicpool.topicdata[i].data = 0;
			task->topicpool.topicdata[i].datasize = 0;
		}
	}
	task->init = init;
	task->onYieldTurn = onYieldTurn;
	task->onResume = onResume;
	task->onEventFlag = onEventFlag;
	task->onTopicUpdate = onTopicUpdate;
	task->cbhandler = cbhandler;
	OS_start(task, e);
}


//------------------------------------------------------------------------------------
void Task_start(Task* task, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_start task is null");
		return; 
	}
	PLATFORM_ENTER_CRITICAL();
	task->status = READY;
	task->init(task->cbhandler);
	// if task keeps READY (not suspended nor waiting), then allows execution
	if(task->status == READY){
		task->event |= EVT_YIELD;
	}
	PLATFORM_EXIT_CRITICAL();
}

//------------------------------------------------------------------------------------
void Task_suspend(Task* task, int delay_us, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_suspend task is null");
		return; 
	}
	PLATFORM_ENTER_CRITICAL();
	task->isSuspended = true;
	Timer_start(&(task->tmr), delay_us, e);
	PLATFORM_EXIT_CRITICAL();
}

//------------------------------------------------------------------------------------
void Task_resume(Task* task, char forced, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_resume task is null");
		return; 
	}
	PLATFORM_ENTER_CRITICAL();
	// if resume forced, stops running timer, and do not apply READY state.
	if(forced){
		task->isSuspended = false;
		Timer_stop(&(task->tmr), e);
		PLATFORM_EXIT_CRITICAL();
		return;
	}
	task->isSuspended = false;
	task->status = READY;
	task->event &= ~EVT_YIELD;
	task->event |= EVT_RESUMED;
	PLATFORM_EXIT_CRITICAL();
}

//------------------------------------------------------------------------------------
void Task_yield(Task* task, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_yield task is null");
		return; 
	}
	PLATFORM_ENTER_CRITICAL();
	task->status = YIELD;
	PLATFORM_EXIT_CRITICAL();
}

//------------------------------------------------------------------------------------
char Task_isYield(Task* task, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_isYield task is null");
		return false; 
	}
	return ((task->status == YIELD)? true : false);
}

//------------------------------------------------------------------------------------
char Task_isReady(Task* task, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_isReady task is null");
		return false; 
	}
	return ((task->status == READY)? true : false);
}

//------------------------------------------------------------------------------------
void Task_setReady(Task* task, int evt, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_setReady task is null");
		return; 
	}
	PLATFORM_ENTER_CRITICAL();
	task->event |= evt;
	task->status = READY;
	if(task->isSuspended){
		Task_resume(task, true, e);
	}
	PLATFORM_EXIT_CRITICAL();
}

//------------------------------------------------------------------------------------
void Task_setStop(Task* task, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_setStop task is null");
		return; 
	}
	PLATFORM_ENTER_CRITICAL();
	task->status = STOPPED;
	PLATFORM_EXIT_CRITICAL();
}

//------------------------------------------------------------------------------------
void Task_execCb(Task* task, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_execCb task is null");
		return; 
	}
	task->status &= ~READY;
	if((task->event & EVT_RESUMED)==EVT_RESUMED && task->onResume){
		task->event &= ~EVT_RESUMED;
		task->onResume(task->cbhandler);
	}
	if((task->event & EVT_TOPIC)==EVT_TOPIC && task->onTopicUpdate){
		task->event &= ~EVT_TOPIC;
		// processes all pending topics until topic fifo pool is empty
		for(;;){
			TopicData td;
			Task_popTopic(task, &td, e);
			catch(e){
				Exception_clear(e);
				break;
			}
			task->onTopicUpdate(task->cbhandler, &td);
			// decrease topic count and if reaches 0, then notifies to publisher, that
			// topic has been completely processed by all the subscribers.
			*(td.pcount) -= 1;
			if(*(td.pcount) <= 0 && td.done){
				td.done(td.publisher);
			}
		}
	}
	if((task->event & EVT_FLAGS)==EVT_FLAGS && task->onEventFlag){
		PLATFORM_ENTER_CRITICAL();
		int event = (task->event >> 4);
		// checks if waiting_or or waiting_and
		if(task->evhandler.mode == WAIT_OR && (task->evhandler.events & event)!=0){
			task->evhandler.events &= ~event;
			task->event &= ~EVT_FLAGMASK;
			PLATFORM_EXIT_CRITICAL();
			task->onEventFlag(task->cbhandler, event);
		}
		else if(task->evhandler.mode == WAIT_AND && (task->evhandler.events & event)==task->evhandler.events){
			task->evhandler.events &= ~event;
			task->event &= ~EVT_FLAGMASK;
			PLATFORM_EXIT_CRITICAL();
			task->onEventFlag(task->cbhandler, event);
		}
		else{
			PLATFORM_EXIT_CRITICAL();
		}
	}
	if(task->event == EVT_YIELD && task->onYieldTurn){
		task->event &= ~EVT_YIELD;
		task->onYieldTurn(task->cbhandler);
	}
}

//------------------------------------------------------------------------------------
int Task_prio(Task* task, Exception *e){
	if(!task){ 
		Exception_throw(e, BAD_ARGUMENT, "Task_prio task is null");
		return -1; 
	}
	return task->prio;
}

//------------------------------------------------------------------------------------
void Task_addTopic(Task* task, int id, const char * name, void *data, int datasize, int *count, void (*done)(void*), void* publisher, Exception *e){
	if(!task || !id){
		Exception_throw(e, BAD_ARGUMENT, "Task_addTopic task or id null");
		return;
	}
	PLATFORM_ENTER_CRITICAL();
	if(task->topicpool.status == POOL_FULL){
		Exception_throw(e, MEMORY_ALLOC, "Task_addTopic topic_pool is full");
		PLATFORM_EXIT_CRITICAL();
		return;
	}
	int i = task->topicpool.pwrite;
	task->topicpool.status = POOL_DATA;
	task->topicpool.topicdata[i].id = id;
	task->topicpool.topicdata[i].name = name;
	task->topicpool.topicdata[i].data = data;
	task->topicpool.topicdata[i].datasize = datasize;
	task->topicpool.topicdata[i].pcount = count;
	task->topicpool.topicdata[i].done = done;
	task->topicpool.topicdata[i].publisher = publisher;
	task->topicpool.pwrite = (task->topicpool.pwrite < (task->topicpool.poolsize-1))? (task->topicpool.pwrite+1) : 0;
	if(task->topicpool.pwrite == task->topicpool.pread){
		task->topicpool.status = POOL_FULL;
	}
	PLATFORM_EXIT_CRITICAL();
	Task_setReady(task, EVT_TOPIC, e);
}

//------------------------------------------------------------------------------------
void Task_popTopic(Task* task, TopicData* td, Exception *e){
	if(!task || !td){
		Exception_throw(e, BAD_ARGUMENT, "Task_addTopic task or topic null");
		return;
	}
	PLATFORM_ENTER_CRITICAL();
	if(task->topicpool.status == POOL_EMPTY){
		Exception_throw(e, MEMORY_ALLOC, "Task_addTopic topic_pool is empty");
		PLATFORM_EXIT_CRITICAL();
		return;
	}
	int i = task->topicpool.pread;
	*td = task->topicpool.topicdata[i];
	task->topicpool.pread = (task->topicpool.pread < (task->topicpool.poolsize-1))? (task->topicpool.pread+1) : 0;
	if(task->topicpool.pread == task->topicpool.pwrite){
		task->topicpool.status = POOL_EMPTY;
	}
	PLATFORM_EXIT_CRITICAL();
}

//------------------------------------------------------------------------------------
void Task_wait_or(Task* task, uint16_t evt, uint32_t delay_us, Exception *e){
	if(!task){
		Exception_throw(e, BAD_ARGUMENT, "Task_wait_or task null");
		return;
	}
	PLATFORM_ENTER_CRITICAL();
	task->evhandler.mode = WAIT_OR;
	task->evhandler.events = evt;
	if(delay_us > 0){
		Task_suspend(task, delay_us, e);
	}
	PLATFORM_EXIT_CRITICAL();
}

//------------------------------------------------------------------------------------
void Task_wait_and(Task* task, uint16_t evt, uint32_t delay_us, Exception *e){
	if(!task){
		Exception_throw(e, BAD_ARGUMENT, "Task_wait_and task null");
		return;
	}
	PLATFORM_ENTER_CRITICAL();
	task->evhandler.mode = WAIT_AND;
	task->evhandler.events = evt;
	if(delay_us > 0){
		Task_suspend(task, delay_us, e);
	}
	PLATFORM_EXIT_CRITICAL();
}
