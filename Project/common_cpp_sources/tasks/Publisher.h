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

class Publisher : public Task {
public:
	Publisher(const std::string& name="") : Task(name) {
		std::cout << "#" << _name << "# Created!" << std::endl;
	}
	virtual ~Publisher();
	///< Inherit from Task interface
	int init();
	int exec(int evt);
	int kill();
};

#endif /* SRC_MODULES_PUBLISHER_H_ */
