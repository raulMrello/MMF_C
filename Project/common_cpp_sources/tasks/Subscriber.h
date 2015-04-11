/*
 * MySubscriber.h
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#ifndef SRC_TASKS_SUBSCRIBER_H_
#define SRC_TASKS_SUBSCRIBER_H_

#include <cstdint>
#include "../../../src/mmf/cpp/os/mmf.h"
using namespace MMF;

class Subscriber : public Task {
public:
	Subscriber(const char * name="", uint8_t prio, uint32_t topic_pool_size) : Task(name, prio, topic_pool_size) {
		std::cout << "#" << _name << "# Created!" << std::endl;
	}
	virtual ~Subscriber();
private:
	/** Task interface */
	void init();
	void onYieldTurn();
	void onResume();
	void onEventFlag(uint16_t event);
	void onTopicUpdate(TopicData * topicdata);

};

#endif /* SRC_TASKS_SUBSCRIBER_H_ */
