/*
 * MyTopic.h
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#ifndef SRC_TOPICS_MYTOPIC_H_
#define SRC_TOPICS_MYTOPIC_H_

#include "../../../src/mmf/cpp/os/mmf.h"

class MyTopic: public Topic {
public:

	MyTopic (const char * name = "") : Topic(name) {
		_data = 0;
		_datasize = 0;
	}

	static void publish(void * data, int datasize){
		MyTopic::_data = data;
		MyTopic::_datasize = datasize;
		notify(data, datasize, 0, 0);
	}

	static void attachListener(void * listener){
		attach(listener);
	}

	static const char * getName(){
		return _name;
	}
	static int  getRef(){
		return _id;
	}
private:
	static void * _data;
	static int _datasize;
};

#endif /* SRC_TOPICS_MYTOPIC_H_ */
