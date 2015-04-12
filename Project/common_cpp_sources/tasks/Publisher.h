/*
 * Publisher.h
 *
 *  Created on: 13/3/2015
 *      Author: RaulM
 */

#ifndef SRC_MODULES_PUBLISHER_H_
#define SRC_MODULES_PUBLISHER_H_

#include <stdint.h>
#include "../../../src/mmf/cpp/os/mmf.h"
using namespace MMF;

class Publisher : public Task {
public:
	Publisher(const char * name, uint8_t prio, uint32_t topic_pool_size) : Task(name, prio, topic_pool_size) {
	}
	virtual ~Publisher();
private:
	/** Task interface */
	void init();
	void onYieldTurn();
	void onResume();
	void onEventFlag(uint16_t event);
	void onTopicUpdate(TopicData * topicdata);
};

#endif /* SRC_MODULES_PUBLISHER_H_ */
