/*
 * MyTask.h
 *
 *  Created on: 12/3/2015
 *      Author: raulMrello
 */

#ifndef SRC_TASKS_MYTASK_H_
#define SRC_TASKS_MYTASK_H_

#include <iostream>
#include "../../../src/mmf/cpp/os/mmf.h"

class MyTask: public Task {
public:
	MyTask(const std::string& name="", int delay_us=0) : Task(name){
		_counter = 0;
		_delay = delay_us;
		std::cout << "#" << _name << "# Created!" << std::endl;
	}
	virtual ~MyTask();
	void print();
	int init();
	int exec(int evt);
	int kill();

private:
	int _counter;
	int _delay;
};

#endif /* SRC_TASKS_MYTASK_H_ */
