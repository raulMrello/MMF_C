/*
 * Observer.cpp
 *
 *  Created on: 12/3/2015
 *      Author: raulMrello
 */

#include "Observer.h"
#include <cstdlib>		///< required for malloc
#include <cstring>		///< required for memcpy


//------------------------------------------------------------------------------------
Observer::Observer() {
	_topicdatalist.clear();
}

//------------------------------------------------------------------------------------
Observer::~Observer() {
	// TODO Auto-generated destructor stub
}

//------------------------------------------------------------------------------------
void Observer::update(void * data, int datasize) throw (Exception){
	if(!data || !datasize)
		throw Exception(Exception::BAD_ARGUMENT);
	// add new topic data (allocates topic data and topic itself)
	void * allocdata = malloc(datasize);
	if(!allocdata)
		throw Exception(Exception::MEMORY_ALLOC);
	topicdata_t * td = (topicdata_t *)malloc((sizeof(topicdata_t)));
	if(!td){
		free(allocdata);
		throw Exception(Exception::MEMORY_ALLOC);
	}
	// copies topic data and builds topicdata_t structure
	memcpy(allocdata, data, datasize);
	td->data = allocdata;
	td->size = datasize;
	// adds to the pending topic list to be processed by the inherited class
	_topicdatalist.push_back(td);
	// get next topic in list and dispatch
	_topicdata = _topicdatalist.front();
	update();
}

//------------------------------------------------------------------------------------
void Observer::done(){
	// remove topic done from list deallocating memories
	_topicdatalist.remove(_topicdata);
	free((char*)_topicdata->data);
	free(_topicdata);
	// if there are pending topics...
	if(_topicdatalist.size()){
		// get next one and dispatch again
		_topicdata = _topicdatalist.front();
		update();
	}
}
