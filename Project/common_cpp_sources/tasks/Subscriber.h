/*
 * MySubscriber.h
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#ifndef SRC_TASKS_SUBSCRIBER_H_
#define SRC_TASKS_SUBSCRIBER_H_

#include <iostream>
#include "../../../src/mmf/cpp/os/mmf.h"

class Subscriber : public Task, public Observer {
public:
	Subscriber(const std::string& name="") : Task(name), Observer() {
		std::cout << "#" << _name << "# Created!" << std::endl;
	}
	virtual ~Subscriber();
	///< Inherit from Task interface
	int init();
	int exec(int evt);
	int kill();
	///< Inherit from Observer interface
	void update();
};

#endif /* SRC_TASKS_SUBSCRIBER_H_ */
