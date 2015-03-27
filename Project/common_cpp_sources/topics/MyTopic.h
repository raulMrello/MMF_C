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
	static void publish(void * data, int datasize){
		MyTopic::_data = data;
		MyTopic::_datasize = datasize;
		notify(data, datasize);
	}
private:
	static void * _data;
	static int _datasize;
};

#endif /* SRC_TOPICS_MYTOPIC_H_ */
