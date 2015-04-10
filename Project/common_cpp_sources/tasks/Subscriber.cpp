/*
 * MySubscriber.cpp
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */


#include "Subscriber.h"
#include "../topics/MyTopic.h"


Subscriber::~Subscriber() {
	// TODO Auto-generated destructor stub
}

//------------------------------------------------------------------------------------
void Subscriber::init(){
	// attaches to mytopic updates...
	MyTopic::attachListener(this);

	// and also waits for event_code = 1 with a timeout of 100 milliseconsd
	try{
		wait_and(1, 100000);
	}
	catch(Exception &e){
		e.getMessage();
	}
}

//------------------------------------------------------------------------------------
void Subscriber::onYieldTurn(){
	try{
		yield();	///< IMPORTANT!!! in order to get control later, else it won't be executed
	}
	catch(Exception &e){
		e.getMessage();
	}
}

//------------------------------------------------------------------------------------
void Subscriber::onResume(){
}

//------------------------------------------------------------------------------------
void Subscriber::onEventFlag(uint16_t event){
	// if event_code = 1 then waits for event 2 | 4
	if(event==1){
		// and also waits for event_code = 2|4 forever (no timeout limit)
		try{
			wait_or((2|4), 0);
		}
		catch(Exception &e){
			e.getMessage();
		}
	}
	// if event_code = 2|4 then waits for event 8&16 forever (no timeout limit)
	else if(event==2 || event==4){
		// and also waits for event_code = 8&16
		try{
			wait_and((8|16), 0);
		}
		catch(Exception &e){
			e.getMessage();
		}
	}
	// if event_code = 8&16 then waits for event 1 again
	else if(event==(8|16)){
		// waits for event_code = 1 with timeout limit of 100 milliseconds
		try{
			wait_and(1, 100000);
		}
		catch(Exception &e){
			e.getMessage();
		}
	}
}

//------------------------------------------------------------------------------------
void Subscriber::onTopicUpdate(TopicData * td){
	// if subscribed to several topics, then must check with type of topic, by its id
	// if topic type MyTopic...
	if(td->id == (int)MyTopic::getRef()){
		if(td->data && td->datasize){
			//printf("Topic update processed, id=%d, data=%d, size=%d", td->id, *((int*)td->data), td->datasize);
		}
	}
	// also it can check by its name
	if(strcmp(td->name, MyTopic::getName()) == 0){
		if(td->data && td->datasize){
			//printf("Topic update processed, id=%d, data=%d, size=%d", td->id, *((int*)td->data), td->datasize);
		}
	}
	// also it can check by its name with a constant string
	if(strcmp(td->name, "/counter") == 0){
		if(td->data && td->datasize){
			//printf("Topic update processed, id=%d, data=%d, size=%d", td->id, *((int*)td->data), td->datasize);
		}
	}
}
