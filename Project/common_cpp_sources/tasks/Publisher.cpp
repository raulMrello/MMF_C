/*
 * Publisher.cpp
 *
 *  Created on: 13/3/2015
 *      Author: RaulM
 */

#include "Publisher.h"
#include "../../../src/mmf/cpp/os/Exception.h"
#include "../topics/MyTopic.h"
#include <string>	///< required for string
#include <sstream>	///< required for ostringstream
#include <cstring>	///< required for strlen

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
			MyTopic::publish(&counter, sizeof(int));
			Topic_notify(MyTopic_getRef(), &counter, sizeof(int), topicDone, t, &e);
			catch(&e){
				printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
				Exception_clear(&e);
			}
			break;
		}
		// in this case sends event 1
		case 3:{
			OS_send_event(0, "subscriber", 1, &e);
			catch(&e){
				printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
				Exception_clear(&e);
			}
			break;
		}
		// in this case sends event 2
		case 4:{
			OS_send_event(0, "subscriber", 2, &e);
			catch(&e){
				printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
				Exception_clear(&e);
			}
			break;
		}
		// in this case sends event 8
		case 5:{
			OS_send_event(0, "subscriber", 8, &e);
			catch(&e){
				printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
				Exception_clear(&e);
			}
			break;
		}
		// in this case sends event 16
		case 6:{
			OS_send_event(0, "subscriber", 16, &e);
			catch(&e){
				printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
				Exception_clear(&e);
			}
			break;
		}
		// in this case sends event 1 and post topic update
		case 7:{
			OS_send_event(0, "subscriber", 1, &e);
			catch(&e){
				printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
				Exception_clear(&e);
			}
			Topic_notify(MyTopic_getRef(), &counter, sizeof(int), topicDone, t, &e);
			catch(&e){
				printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
				Exception_clear(&e);
			}
			break;
		}
		// in this case sends an event to an unknown task
		case 8:{
			OS_send_event(0, "subscriBER", 1, &e);
			catch(&e){
				printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
				Exception_clear(&e);
			}
			break;
		}
		// in this case colapses susbscriber topic pool
		case 9:{
			int j;
			for(j=0;j<10;j++){
				Topic_notify(MyTopic_getRef(), &counter, sizeof(int), topicDone, t, &e);
				catch(&e){
					printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
					Exception_clear(&e);
					break;
				}
			}
			break;
		}
	}

	// keeps task running
	Task_yield(t, &e);	///< IMPORTANT!!! in order to get control later, else it won't be executed
	catch(&e){
		printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
		Exception_clear(&e);
	}
}


//------------------------------------------------------------------------------------
void Publisher_OnResume(PublisherTaskPtr t){
	printf("Publisher_OnResume\r\n");
	// keeps task running
	Task_yield(t, &e);	///< IMPORTANT!!! in order to get control later, else it won't be executed
	catch(&e){
		printf("Exception on Publisher_OnYieldTurn: %s\r\n", e.msg);
		Exception_clear(&e);
	}
}

//------------------------------------------------------------------------------------
void Publisher_OnEventFlag(PublisherTaskPtr t, uint16_t event){
	printf("Publisher_OnEventFlag\r\n");

}

//------------------------------------------------------------------------------------
//void Publisher_OnTopicUpdate(PublisherTaskPtr t, TopicData * td){
//	printf("Publisher_OnTopicUpdate\r\n");
//
//}

