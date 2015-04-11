/*
 * MyTopic.h
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#ifndef SRC_TOPICS_MYTOPIC_H_
#define SRC_TOPICS_MYTOPIC_H_

#include "../../../src/mmf/cpp/os/mmf.h"
using namespace MMF;

class MyTopic: public Topic {
public:

	MyTopic (const char * name = "") : Topic(name) {
		_data = 0;
		_datasize = 0;
	}


	/** Topic interface */
	static void publish(void * data, int datasize, TopicConsumedCallback done, TopicConsumedHandlerObj cbhandler){
		MyTopic::_data = data;
		MyTopic::_datasize = datasize;
		notify(data, datasize, done, cbhandler);
	}

	static void attachListener(void * listener){
		attach(listener);
	}
	static const char * getTopicName(){
		return getName();
	}
	static int  getTopicRef(){
		return getId();
	}


private:
	static void * _data;
	static int _datasize;
};

#endif /* SRC_TOPICS_MYTOPIC_H_ */
