/*
 * os.cpp
 *
 *  Created on: 11/3/2015
 *      Author: raulMrello
 */

#include "OS.h"


//------------------------------------------------------------------------------------
void OS::getAnalytics(){
	std::string result = "TODO";
//	result = "ID    Name      Status     EventList\r\n";
//			//01   nombre     READY         4
//	for(int i=0;i<NUM_TASKS;i++){
//		// if taskentry is not empty...
//		if(_tasklist[i] != NULL){
//			// and allocated task is ready for execution...
//			if(_tasklist[i]->isReady()){
//				// change task to run mode and executes it
//				_tasklist[i]->setRunning();
//				// get the event code which causes the task to be ready and passes to exec func.
//				_tasklist[i]->exec(_tasklist[i]->getNextEvt());
//				break;
//			}
//		}
//	}
	if(_logCb){
		_logCb(result);
	}
}

//------------------------------------------------------------------------------------
OS::OS(bool enable_log, void(*logCb)(std::string&)){
	_log_enabled = enable_log;
	_logCb = logCb;
}

//------------------------------------------------------------------------------------
void OS::init(){
	// clears task list and task count
	for(int i = 0; i < NUM_TASKS; i++){
		_tasklist[i] = NULL;
	}
	_taskcount = 0;
}

//------------------------------------------------------------------------------------
void OS::run(Task& t, int prio)  throw (Exception){
	if(prio >= NUM_TASKS)
		throw Exception(Exception::BAD_ARGUMENT);
	// if priority assigned, throws an exception
	if(_tasklist[prio] !=  NULL)
		throw Exception(Exception::MEMORY_ALLOC);
	// inserts task in list, increase counter and starts it
	_tasklist[prio] = &t;
	_taskcount++;
	_tasklist[prio]->start(prio);
}

//------------------------------------------------------------------------------------
void OS::kill(Task& t)  throw (Exception){
	// if task doesn't match with requested one, throws exception
	if(_tasklist[t.prio] != &t)
		throw Exception(Exception::MEMORY_DEALLOC);
	// get prio level, remove task from list and decrease counter
	int prio = t.prio;
	_tasklist[prio]->~Task();
	_taskcount--;
	_tasklist[prio] = 0;
}

//------------------------------------------------------------------------------------
void OS::schedule() throw (Exception){
	// scheduler runs forever
	for(;;){
		int i;
		// search from highest priority to lowest one...
		for(i = 0; i < NUM_TASKS; i++){
			// if taskentry is not empty...
			if(_tasklist[i] != NULL){
				// and allocated task is ready for execution...
				if(_tasklist[i]->isReady()){
					// change task to run mode and executes it
					_tasklist[i]->setRunning();
					// get the event code which causes the task to be ready and passes to exec func.
					_tasklist[i]->exec(_tasklist[i]->getNextEvt());
					break;
				}
			}
		}
		// after a complete cycle of scheduling (no more executable task pending)
		// yielded tasks must be set to READY again
		if(i >= NUM_TASKS){
			// executes log callback if enabled
			if(_log_enabled){
				getAnalytics();
			}
			for(i = 0; i < NUM_TASKS; i++){
				// ensure check only allocated tasks
				if(_tasklist[i] != NULL){
					// ensure set ready only those which are yielded
					if(_tasklist[i]->isYield()){
						_tasklist[i]->setReady();
					}
				}
			}
		}
	}
	// never should reach this point, else throws an exception
	throw Exception(Exception::UNKNOWN_EXCEPTION);
}
