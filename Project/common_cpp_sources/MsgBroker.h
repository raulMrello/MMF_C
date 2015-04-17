/*
 * MsgBroker.h
 *
 *  Created on: 16/4/2015
 *      Author: dptoid
 */

#ifndef MSGBROKER_H_
#define MSGBROKER_H_

#include "List.h"
#include <string.h>
#include <stdlib.h>


class MsgBroker {
public:
	enum Errors{NULL_POINTER, DEINIT, OUT_OF_MEMORY, TOPIC_EXISTS, TOPIC_NOT_FOUND, SUBSCRIBER_NOT_FOUND};
	typedef int MsgBrokerException;

	/** Observer data */
	template<typename K>
	struct Observer{
		K		*observer;
		void(K::*notify)(void);
	};

	/** Topic data */
	struct Topic{
		List		*observer_list;
		const char 	*name;
		void 		*data;
		uint32_t 	datasize;
	};

	static void init() {
		if(!MsgBroker::topic_list){
			MsgBroker::topic_list = new List();
		}
	}

	static void deinit() {
		if(MsgBroker::topic_list){
			delete(MsgBroker::topic_list);
			MsgBroker::topic_list = 0;
		}

	}

	static MsgBroker::Topic * installTopic(const char* name, uint32_t datasize) throw (MsgBrokerException){
		if(!MsgBroker::topic_list){
			throw DEINIT;
		}
		MsgBroker::Topic * topic = findTopic(name);
		if(topic){
			throw TOPIC_EXISTS;
		}
		topic = (MsgBroker::Topic*)malloc(sizeof(MsgBroker::Topic));
		if(!topic){
			throw OUT_OF_MEMORY;
		}
		topic->observer_list = new List();
		topic->name = name; topic->datasize = datasize; topic->data = 0;
		topic_list->addItem(topic);
		return topic;
	}

	static void removeTopic(const char * topic_name) throw (MsgBrokerException){
		if(!MsgBroker::topic_list){
			throw DEINIT;
		}
		MsgBroker::Topic * topic = findTopic(topic_name);
		if(!topic){
			throw TOPIC_NOT_FOUND;
		}
		topic_list->removeItem(topic);
		free(topic);
	}

	static void removeTopic(Topic * t) throw (MsgBrokerException){
		if(!MsgBroker::topic_list){
			throw DEINIT;
		}
		MsgBroker::removeTopic(t->name);
	}

	template<typename K>
	static MsgBroker::Observer<K> * attach (const char * topic_name, K *subscriber, void(K::*notify)(void)){
		if(!MsgBroker::topic_list){
			throw DEINIT;
		}
		MsgBroker::Topic * topic = findTopic(topic_name);
		if(!topic){
			throw TOPIC_NOT_FOUND;
		}
		MsgBroker::Observer<K> *obs = malloc(sizeof(MsgBroker::Observer<K>));
		obs->observer = subscriber;
		obs->notify = notify;
		topic->observer_list->addItem(obs);
		return obs;
	}

	template<typename K>
	static void detach (const char * topic_name, K * subscriber){
		if(!MsgBroker::topic_list){
			throw DEINIT;
		}
		MsgBroker::Topic * topic = findTopic(topic_name);
		if(!topic){
			throw TOPIC_NOT_FOUND;
		}
		MsgBroker::Observer<K> *obs = (MsgBroker::Observer<K> *)findObserver(topic->observer_list, subscriber);
		if(!obs){
			throw SUBSCRIBER_NOT_FOUND;
		}

		topic->observer_list->removeItem(obs);
		free(obs);
	}

private:
	static List * topic_list;

	static MsgBroker::Topic * findTopic(const char * topic_name){
		if(!MsgBroker::topic_list){
			throw DEINIT;
		}
		MsgBroker::Topic *topic = (MsgBroker::Topic*)topic_list->getFirstItem();
		do{
			if(strcmp(topic_name, topic->name) == 0){
				return topic;
			}
			topic = (MsgBroker::Topic*)topic_list->getNextItem();
		}while(topic);
		return 0;
	}

	template<typename K>
	static MsgBroker::Observer<K> * findObserver(List * list, K *subscriber){
		if(!MsgBroker::topic_list){
			throw DEINIT;
		}
		MsgBroker::Observer<K> *obs = (MsgBroker::Observer<K> *)list->getFirstItem();
		do{
			if(subscriber == obs->observer){
				return obs;
			}
			obs = (MsgBroker::Observer<K> *)list->getNextItem();
		}while(obs);
		return 0;
	}


};

#endif /* MSGBROKER_H_ */
