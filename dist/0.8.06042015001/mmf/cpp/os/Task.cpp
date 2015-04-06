/*
 * task.cpp
 *
 *  Created on: 11/3/2015
 *      Author: raulMrello
 */

#include "Task.h"
#include "OS.h"

//------------------------------------------------------------------------------------
static void timertask_callback(void* handler){
	Task* t = (Task*)handler;
	t->resume(false);
}

//------------------------------------------------------------------------------------
Task::~Task() {
	_evtlist.clear();
}

//------------------------------------------------------------------------------------
void Task::start(int vprio) throw (Exception){
	if(vprio >= NUM_TASKS)
		throw Exception(Exception::BAD_ARGUMENT);
	prio = vprio;
	_status = READY;
	_evtlist.clear();
	init();
}

//------------------------------------------------------------------------------------
void Task::suspend(unsigned int delay_us){
	_status = WAITING;
	_isSuspended = true;
	PLATFORM_TIMER_START(delay_us, timertask_callback, this);
}

//------------------------------------------------------------------------------------
void Task::resume(bool forced){
	if(forced){
		PLATFORM_TIMER_STOP(this);
	}
	_isSuspended = false;
	_evtlist.push_back((int)EVT_RESUMED);
}

//------------------------------------------------------------------------------------
void Task::yield(){
	_status = YIELD;
}

//------------------------------------------------------------------------------------
bool Task::isYield(){
	return ((_status == YIELD)? true : false);
}

//------------------------------------------------------------------------------------
bool Task::isReady(){
	return ((_status == READY)? true : false);
}

//------------------------------------------------------------------------------------
void Task::setRunning(){
	_status = RUNNING;
}

//------------------------------------------------------------------------------------
void Task::setWaiting(){
	_status = WAITING;
}

//------------------------------------------------------------------------------------
void Task::setReady(int evt){
	_evtlist.push_back(evt);
	_status = READY;
}

//------------------------------------------------------------------------------------
void Task::setStop(){
	_status = STOPPED;
}

//------------------------------------------------------------------------------------
int Task::getNextEvt(){
	if(_evtlist.size() == 0)
		return EVT_NONE;
	int evt = _evtlist.front();
	_evtlist.pop_front();
	return evt;
}


