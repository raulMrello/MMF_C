/*
 * MyTopic.cpp
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#include "MyTopic.h"

static TopicPtr topic;
static Exception e = Exception_INIT();		///< Module's exception handling

//------------------------------------------------------------------------------------
TopicPtr MyTopic_initialize(const char * name){
	topic = Topic_create(name, &e);
	catch(&e){
		Exception_clear(&e);
		return 0;
	}
	return &topic;
}

//------------------------------------------------------------------------------------
TopicPtr MyTopic_getRef(void){
	return &topic;
}

//------------------------------------------------------------------------------------
const char * MyTopic_getName(void){
	return Topic_getName(topic, &e);
}
