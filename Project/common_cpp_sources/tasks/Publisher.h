/*
 * Publisher.h
 *
 *  Created on: 13/3/2015
 *      Author: RaulM
 */

#ifndef SRC_MODULES_PUBLISHER_H_
#define SRC_MODULES_PUBLISHER_H_

#include <iostream>
#include "../../../src/mmf/cpp/os/mmf.h"
using namespace MMF;

class Publisher : public Task {
public:
	Publisher(const std::string& name="") : Task(name) {
		std::cout << "#" << _name << "# Created!" << std::endl;
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
