
#include "../../src/mmf/c/os/mmf.h"

#include "tasks/Subscriber.h"
#include "tasks/Publisher.h"
#include "tasks/SysTask.h"
#include "topics/MyTopic.h"

int main(void) {
	// Creates an exception to handle errors and initializes to default data
	Exception e = Exception_INIT();


	// 1 - Kernel allocation and initialization. Exception handling should be checked afterwards.

	OS_init(3, 10000, &e);
	catch(&e){
		Exception_clear(&e);
		return -1;
	}

	// 2- [optional] Topics initialization, it can be done in tasks implementation. Nevertheless is done
	//	  here for clarification to ensure that observerlist is not accidentally cleared.

	MyTopic_initialize("/counter");

	// 3 - Tasks creation, init callback is invoked internally.
	//     Exception checking should be done afterwards with "catch" macro
	//	   It allocates memory to get up to 5 topic updates pending. The aray is named: mmf_topicpool_TASKNAME

	Task_create("subscriber",
				PRIO_MAX,
				5*sizeof(TopicData),
				Subscriber_init, Subscriber_OnYieldTurn, Subscriber_OnResume,
				Subscriber_OnEventFlag, Subscriber_OnTopicUpdate,
				0,	// null handler implies that returned "TaskPtr" object, will be the default callback handler
				&e);
	catch(&e){
		Exception_clear(&e);
		return -1;
	}

	Task_create("publisher",
				PRIO_MAX+1,
				0,	//no topic pool fifo is required
				Publisher_init,
				Publisher_OnYieldTurn,
				Publisher_OnResume,
				Publisher_OnEventFlag,
				(OnTopicUpdateCallback)0,	//Publisher_OnTopicUpdate not required
				0,	// null handler implies that returned "TaskPtr" object, will be the default callback handler
				&e);
	catch(&e){
		Exception_clear(&e);
		return -1;
	}

	Task_create("systask",
				PRIO_MAX+2,
				0,	//no topic pool size
				SysTask_init,
				SysTask_OnYieldTurn,
				SysTask_OnResume,
				SysTask_OnEventFlag,
				SysTask_OnTopicUpdate,
				0,	// null handler implies that returned "TaskPtr" object, will be the default callback handler
				&e);
	catch(&e){
		Exception_clear(&e);
		return -1;
	}

	// 4 - Kernel scheduling. Runs forever, else call OS_schedule_once
	//	   Exception handling should be done if scheduling finish

	OS_schedule(&e);
	catch(&e){
		Exception_clear(&e);
	}

	return 0;
}


