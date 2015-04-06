/*
 * Topic.cpp
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#include "Topic.h"

std::list<Observer *>Topic::_observerlist;	///< declaration of static member
bool Topic::_initalized = false;			///< declaration of static member
