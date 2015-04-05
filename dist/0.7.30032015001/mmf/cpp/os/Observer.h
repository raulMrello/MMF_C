/*
 * Observer.h
 *
 *  Created on: 12/3/2015
 *      Author: raulMrello
 */

#ifndef SRC_OS_OBSERVER_H_
#define SRC_OS_OBSERVER_H_

#include "../port/platforms.h" ///< platform dependent
#include <list>
#include "Exception.h"


/** \struct topicdata_t
 *  \brief Data structure to allocate a topic update
 */
typedef struct{
	void * data;	///< pointer to the allocated topic data
	int size;		///< size (in bytes) of the allocated topic data
}topicdata_t;


/** \class Observer
 *  \brief Observer class represents the subscriber actor in a publish/subscribe environment defined
 *  by the Observer design pattern.
 */
class Observer {
public:

	/** \fn Observer
	 *  \brief Default constructor
	 */
	Observer();

	/** \fn ~Observer
	 *  \brief Default destructor. It will deallocate all resources
	 */
	virtual ~Observer();

	/** \fn update
	 *  \brief Updates the oberserver object due a topic update
	 *  \param data Topic data
	 *  \param datasize Topic data size
	 *  \throw Exception
	 */
	void update(void * data, int datasize) throw (Exception);

	/** \fn done
	 *  \brief Releases last processed topic, deallocating automatically all resources.
	 */
	void done();

	/** \fn update
	 *  \brief Interface to be implemented by the inherited class. This class can use
	 *  member "_topicdata" to access the topic update.
	 */
	virtual void update()=0;

protected:
	topicdata_t* _topicdata;	///< Pointer to the lastest updated topic data

private:
	std::list<topicdata_t *>_topicdatalist;	///< List of pending topic updates not yet processed
};

#endif /* SRC_OS_OBSERVER_H_ */
