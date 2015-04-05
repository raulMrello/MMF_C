/*
 * Topic.h
 *
 *  Created on: 12/3/2015
 *      Author: raulMrello
 */

#ifndef SRC_OS_TOPIC_H_
#define SRC_OS_TOPIC_H_

#include "../port/platforms.h" ///< platform dependent
#include <list>
#include <cstddef>
#include "Observer.h"
#include "Exception.h"


/** \class Topic
 *  \brief Topic class represents the dynamic piece of software in which Observers can subscribe to get
 *  track of its evolution (updates)
 */
class Topic {
public:


	/** \fn initialize
	 *  \brief Static function to initialize Topics internals, like observer list.
	 */
	static void initialize(){
		if(!Topic::_initalized){
			Topic::_observerlist.clear();
			Topic::_initalized = true;
		}
	}

	/** \fn notify
	 *  \brief Static function to notify the subscribed observers about the update/change of the topic
	 *  \param data Topic's data
	 *  \param datasize	Topic's data size in bytes
	 */
	static void notify(void * data, int datasize) throw (Exception){
		if((data == NULL && datasize > 0) || (data != NULL && !datasize))
			throw new Exception(Exception::BAD_ARGUMENT);
		for (std::list<Observer*>::iterator it=Topic::_observerlist.begin(); it != Topic::_observerlist.end(); ++it){
			(*it)->update(data, datasize);
		}
	}

	/** \fn attach
	 *  \brief Static function to attach (subscribe) an observer class to a topic
	 *  \param o Observer
	 */
	static void attach(Observer& o){
		Topic::_observerlist.push_back(&o);
	}

	/** \fn dettach
	 *  \brief Static function to dettach (unsubscribe) an observer class from a topic
	 *  \param o Observer
	 */
	static void dettach(Observer& o){
		Topic::_observerlist.remove(&o);
	}

private:
	static std::list<Observer *>_observerlist;	///< List of subscribed observers
	static bool _initalized;					///< Flag to inidicate if static list is initialized yet
};

#endif /* SRC_OS_TOPIC_H_ */
