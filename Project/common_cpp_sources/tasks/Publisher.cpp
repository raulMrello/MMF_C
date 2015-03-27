/*
 * Publisher.cpp
 *
 *  Created on: 13/3/2015
 *      Author: RaulM
 */

#include "Publisher.h"
#include "../../../src/mmf/cpp/os/Exception.h"
#include "../topics/MyTopic.h"
#include <string>	///< required for string
#include <sstream>	///< required for ostringstream
#include <cstring>	///< required for strlen


Publisher::~Publisher() {
	// TODO Auto-generated destructor stub
}

///< Inherit from Task interface
int Publisher::init(){
	std::cout << "#" << _name << "# started!" << std::endl;
	std::cout << "#" << _name << "# initializing MyTopic topics!" << std::endl;
	MyTopic::initialize();
	return 0;
}

/**
 * Publisher task is executed continuosly yielding each time is executed.
 * After 4 execution times, it publish a new MyTopic topic.
 */
int Publisher::exec(int evt){
	static int exectimes = 0;
	switch(evt){
		case EVT_RESUMED:{
			break;
		}
		case EVT_TOPIC:{
			break;
		}
		case EVT_FLAGS:{
			break;
		}
		default:{
			if(exectimes++ >= 3){
				exectimes = 0;
				static int newscounter = 1;
				std::ostringstream converted;   // stream used for the conversion
				converted << "Published new_id=" << newscounter;
				std::string news = converted.str();
				std::cout << "#" << _name << "# publishing topic=" << news << std::endl;
				try{
					MyTopic::publish((void*)news.data(), news.length());
				}
				catch(Exception& e){
					std::cout << "#" << _name << "# exception=" << e.getMessage() << std::endl;
				}
				newscounter++;
			}
			break;
		}
	}
	yield();
	return 0;
}

int Publisher::kill(){
	return 0;
}

