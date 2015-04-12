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

class MyTopic {
public:

	MyTopic (const char * name = "");

	static void publish(void * data, int datasize,  TopicConsumedCallback done, TopicConsumedHandlerObj publisher) throw (Exception){
		_topic->notify(data, datasize, done, publisher);
	}
	static int getRef(){
		return _topic->getId();
	}
	static const char * getName(){
		return _topic->getName();
	}
	static void attach(TopicSubscribedHandlerObj handler){
		_topic->attach(handler);
	}

private:
	static Topic* _topic;
};

#endif /* SRC_TOPICS_MYTOPIC_H_ */
