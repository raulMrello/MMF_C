/*
 * MySubscriber.cpp
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#include "Subscriber.h"
#include "../topics/MyTopic.h"
#include <string.h>	///< required for strcmp

static Exception e = Exception_INIT();

//------------------------------------------------------------------------------------
void Subscriber_init(SubscriberTaskPtr t){
	printf("Subscriber_init\r\n");
	// attaches to mytopic updates...
	Topic_attach(MyTopic_getRef(), t, &e);
	catch(&e){
		printf("Exception on Subscriber_init: %s\r\n", e.msg);
		Exception_clear(&e);
	}
	// and also waits for event_code = 1 with a timeout of 100 milliseconsd
	Task_wait_and(t, 1, 100000, &e);
	catch(&e){
		printf("Exception on Subscriber_init: %s\r\n", e.msg);
		Exception_clear(&e);
	}
}

//------------------------------------------------------------------------------------
void Subscriber_OnYieldTurn(SubscriberTaskPtr t){
	printf("Subscriber_OnYieldTurn\r\n");
	Task_yield(t, &e);		///< IMPORTANT!!! in order to get control later, else it won't be executed
	catch(&e){
		printf("Exception on Subscriber_OnYieldTurn: %s\r\n", e.msg);
		Exception_clear(&e);
	}
}

//------------------------------------------------------------------------------------
void Subscriber_OnResume(SubscriberTaskPtr t){
	printf("Subscriber_OnResume\r\n");

}

//------------------------------------------------------------------------------------
void Subscriber_OnEventFlag(SubscriberTaskPtr t, uint16_t event){
	printf("Subscriber_OnEventFlag\r\n");
	// if event_code = 1 then waits for event 2 | 4
	if(event==1){
		// and also waits for event_code = 2|4 forever (no timeout limit)
		Task_wait_or(t, (2|4), 0, &e);
		catch(&e){
			printf("Exception on Subscriber_OnEventFlag: %s\r\n", e.msg);
			Exception_clear(&e);
		}
	}
	// if event_code = 2|4 then waits for event 8&16 forever (no timeout limit)
	else if(event==2 || event==4){
		// and also waits for event_code = 8&16
		Task_wait_and(t, (8|16), 0, &e);
		catch(&e){
			printf("Exception on Subscriber_OnEventFlag: %s\r\n", e.msg);
			Exception_clear(&e);
		}
	}
	// if event_code = 8&16 then waits for event 1 again
	else if(event==(8|16)){
		// waits for event_code = 1 with timeout limit of 100 milliseconds
		Task_wait_and(t, 1, 100000, &e);
		catch(&e){
			printf("Exception on Subscriber_OnEventFlag: %s\r\n", e.msg);
			Exception_clear(&e);
		}
	}
}

//------------------------------------------------------------------------------------
void Subscriber_OnTopicUpdate(SubscriberTaskPtr t, TopicData * td){
	printf("Subscriber_OnTopicUpdate\r\n");
	// if subscribed to several topics, then must check with type of topic, by its id
	// if topic type MyTopic...
	if(td->id == (int)MyTopic_getRef()){
		if(td->data && td->datasize){
			printf("Topic update processed, id=%d, data=%d, size=%d", td->id, *((int*)td->data), td->datasize);
		}
	}
	// also it can check by its name
	if(strcmp(td->name, MyTopic_getName()) == 0){
		if(td->data && td->datasize){
			printf("Topic update processed, id=%d, data=%d, size=%d", td->id, *((int*)td->data), td->datasize);
		}
	}
	// also it can check by its name with a constant string
	if(strcmp(td->name, "/counter") == 0){
		if(td->data && td->datasize){
			printf("Topic update processed, id=%d, data=%d, size=%d", td->id, *((int*)td->data), td->datasize);
		}
	}
}
