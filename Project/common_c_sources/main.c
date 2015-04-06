
#include "../../src/mmf/c/os/mmf.h"

#include "tasks/Subscriber.h"
#include "tasks/Publisher.h"
#include "tasks/SysTask.h"
#include "topics/MyTopic.h"

int main(void) {
	// Creates an exception to handle errors and initializes to default data
	Exception e = Exception_INIT();


	// 1 - Kernel allocation and initialization.
	//     This creates a static task list in the form: 	static Task* mmf_os_tasklist[2];
	//     And invokes to init member in the form:			OS_init(mmf_os_tasklist, 2, 10000, &e);
	//     Exception handling should be checked afterwards.

	OS_ALLOC(os_tasklist, 3, 10000, &e);
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

	Task subscriber;
	Task_ALLOC_TOPIC_POOL(subscriber, 5);
	Task_initialize(&subscriber,
					"subscriber",
					PRIO_MAX,
					mmf_topicpool_subscriber,
					5,
					Subscriber_init,
					Subscriber_OnYieldTurn,
					Subscriber_OnResume,
					Subscriber_OnEventFlag,
					Subscriber_OnTopicUpdate,
					&subscriber,
					&e);
	catch(&e){
		Exception_clear(&e);
		return -1;
	}

	Task publisher;
	Task_initialize(&publisher,
					"publisher",
					PRIO_MAX+1,
					(TopicData*)0,				//Publisher doesn't needs a topic pool
					0,							//no topic pool size
					Publisher_init,
					Publisher_OnYieldTurn,
					Publisher_OnResume,
					Publisher_OnEventFlag,
					(OnTopicUpdateCallback)0,	//Publisher_OnTopicUpdate not required
					&publisher,
					&e);
	catch(&e){
		Exception_clear(&e);
		return -1;
	}

	Task systask;
	Task_initialize(&systask,
					"systask",
					PRIO_MAX+2,
					(TopicData*)0,				//SysTask doesn't needs a topic pool
					0,							//no topic pool size
					SysTask_init,
					SysTask_OnYieldTurn,
					SysTask_OnResume,
					SysTask_OnEventFlag,
					SysTask_OnTopicUpdate,
					&systask,
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


