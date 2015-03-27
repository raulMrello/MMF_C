/*
 * Exception.cpp
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#include "Exception.h"

//------------------------------------------------------------------------------------
Exception::Exception(Code c) {
	_code = c;
}

//------------------------------------------------------------------------------------
Exception::~Exception() {
	// TODO Auto-generated destructor stub
}

//------------------------------------------------------------------------------------
std::string Exception::getMessage(){
	switch(_code){
		case NO_EXCEPTIONS:
			return "NO_EXCEPTIONS";
		case BAD_ARGUMENT:
			return "BAD_ARGUMENT";
		case MEMORY_ALLOC:
			return "MEMORY_ALLOC";
		case MEMORY_DEALLOC:
			return "MEMORY_DEALLOC";
		default:
			return "UNKNOWN_EXCEPTION";
	}
}

//------------------------------------------------------------------------------------
int Exception::getCode(){
	return (int)_code;
}
