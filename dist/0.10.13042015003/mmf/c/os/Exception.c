/*
 * Exception.cpp
 *
 *  Created on: 12/3/2015
 *      Author: dptoid
 */

#include "Exception.h"

//------------------------------------------------------------------------------------
//-- PRIVATE TYPEDEFS ----------------------------------------------------------------
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//-- PUBLIC FUNCTIONS ----------------------------------------------------------------
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
void Exception_throw(ExceptionPtr e, ExceptionCode code, const char * message){
	if(!e)
		return;
	e->code = code;
	e->msg = message;
}

//------------------------------------------------------------------------------------
char Exception_raised(ExceptionPtr e){
	if(!e)
		return 1;
	if(e->code != NO_EXCEPTIONS)
		return 1;
	return 0;
}

//------------------------------------------------------------------------------------
void Exception_clear(ExceptionPtr e){
	if(!e)
		return;
	e->code = NO_EXCEPTIONS;
	e->msg = "";
}
