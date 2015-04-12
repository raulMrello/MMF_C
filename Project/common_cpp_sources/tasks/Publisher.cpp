/*
 * Publisher.cpp
 *
 *  Created on: 13/3/2015
 *      Author: RaulM
 */

#include "Publisher.h"
#include "../topics/MyTopic.h"
#include "../../../src/mmf/cpp/os/mmf.h"
using namespace MMF;

static int counter;
static Exception e;



//------------------------------------------------------------------------------------
static void topicDone(TaskHandlerObj t){
	//printf("topic done\r\n");
}

//------------------------------------------------------------------------------------
Publisher::~Publisher() {
	// TODO Auto-generated destructor stub
}

//------------------------------------------------------------------------------------
void Publisher::init(){
	//printf("Publisher_init\r\n");
	counter = 0;
}

//------------------------------------------------------------------------------------
void Publisher::onYieldTurn(){
	//printf("Publisher_OnYieldTurn\r\n");
	counter++;

	switch(counter){
		// in this case checks task suspension
		case 1:{
			try{
				suspend(20000);
			}
			catch(Exception &e){
				//printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
			}
			return;
		}
		// in this case sends a topic update
		case 2:{
			try{
				MyTopic::publish(&counter, sizeof(int), topicDone, this);
			}
			catch(Exception &e){
				e.getMessage();
			}
			break;
		}
		// in this case sends event 1
		case 3:{
			try{
				OS::sendEvent(0, "subscriber", 1);
			}
			catch(Exception &e){
				e.getMessage();
			}
			break;
		}
		// in this case sends event 2
		case 4:{
			try{
				OS::sendEvent(0, "subscriber", 2);
			}
			catch(Exception &e){
				e.getMessage();
			}
			break;
		}
		// in this case sends event 8
		case 5:{
			try{
				OS::sendEvent(0, "subscriber", 8);
			}
			catch(Exception &e){
				e.getMessage();
			}
			break;
		}
		// in this case sends event 16
		case 6:{
			try{
				OS::sendEvent(0, "subscriber", 16);
			}
			catch(Exception &e){
				e.getMessage();
			}
			break;
		}
		// in this case sends event 1 and post topic update
		case 7:{
			try{
				OS::sendEvent(0, "subscriber", 1);
				MyTopic::publish(&counter, sizeof(int), topicDone, this);
			}
			catch(Exception &e){
				e.getMessage();
			}
			break;
		}
		// in this case sends an event to an unknown task
		case 8:{
			try{
				OS::sendEvent(0, "subscriBER", 1);
			}
			catch(Exception &e){
				e.getMessage();
			}
			break;
		}
		// in this case colapses susbscriber topic pool
		case 9:{
			int j;
			for(j=0;j<10;j++){
				try{
					MyTopic::publish(&counter, sizeof(int), topicDone, this);
				}
				catch(Exception &e){
					e.getMessage();
				}
			}
			break;
		}
	}

	// keeps task running
	yield();	///< IMPORTANT!!! in order to get control later, else it won't be executed
}


//------------------------------------------------------------------------------------
void Publisher::onResume(){
	// keeps task running
	yield();	///< IMPORTANT!!! in order to get control later, else it won't be executed
}

//------------------------------------------------------------------------------------
void Publisher::onEventFlag(uint16_t event){

}

//------------------------------------------------------------------------------------
void Publisher::onTopicUpdate(TopicData * td){
}

