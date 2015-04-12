/*
 * MyTopic.cpp
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#include "MyTopic.h"

Topic* MyTopic::_topic = 0;

MyTopic::MyTopic (const char * name){
	_topic = new Topic(name);
}
