/*
 * MySubscriber.cpp
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */


#include "Subscriber.h"
#include "../topics/MyTopic.h"

#include <iostream>
using namespace std;


Subscriber::~Subscriber() {
	// TODO Auto-generated destructor stub
}

///< Inherit from Task interface
int Subscriber::init(){
	std::cout << "#" << _name << "# started!" << endl;
	MyTopic::attach(*this);
	std::cout << "#" << _name << "# attached to MyTopic!" << endl;
	return 0;
}

int Subscriber::exec(int evt){
	switch(evt){
		case EVT_RESUMED:{
			break;
		}
		case EVT_TOPIC:{
			std::string data((char*)_topicdata->data, _topicdata->size);
			std::cout << "#" << _name << "# processing topic=" << data << endl;
			done();
			break;
		}
		case EVT_FLAGS:{
			break;
		}
		default:{
			std::cout << "#" << _name << "# no events." << endl;
			break;
		}
	}
	return 0;
}

int Subscriber::kill(){
	return 0;
}


///< Inherit from Observer interface
void Subscriber::update(){
	setReady(EVT_TOPIC);
}



