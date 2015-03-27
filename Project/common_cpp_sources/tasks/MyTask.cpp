/*
 * MyTask.cpp
 *
 *  Created on: 12/3/2015
 *      Author: raulMrello
 */

#include "MyTask.h"

#include "../topics/MyTopic.h"
MyTopic topic;

#include <iostream>
using namespace std;


MyTask::~MyTask() {
	// TODO Auto-generated destructor stub
}

int MyTask::init(){
	MyTopic::initialize();
	_counter=1;
	std::cout << "#" << _name << "# starts counter=" << _counter << endl;
	return 0;
}

int MyTask::exec(int evt){
	switch(evt){
		case EVT_RESUMED:{
			print();
			suspend(_delay);
			break;
		}
		case EVT_TOPIC:{
			break;
		}
		case EVT_FLAGS:{
			break;
		}
		default:{
			break;
		}
	}
	return 0;
}

void MyTask::print(){
	_counter++;
	std::cout << "#" << _name << "# prints counter=" << _counter << endl;
}

int MyTask::kill(){
	return 0;

}
