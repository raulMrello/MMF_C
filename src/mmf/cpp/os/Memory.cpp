/*
 * Memory.cpp
 *
 *  Created on:	09/04/2015
 *  Author: 	raulMrello
 *
 *  Memory module, manages dynamic memory allocation-deallocation, keeping track of the maximum number of allocated
 *  memory.
 */

#include "Memory.h"

//------------------------------------------------------------------------------------
//-- PRIVATE VARIABLES ---------------------------------------------------------------
//------------------------------------------------------------------------------------

/** Max allocated memory ever */
static uint32_t maxAllocation = 0;

//------------------------------------------------------------------------------------
//-- PUBLIC FUNCTIONS ----------------------------------------------------------------
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void* Memory_alloc(uint32_t size) throw (Exception){
	void *ptr;
	if(!size){
		throw Exception(Exception::BAD_ARGUMENT, "Memory_alloc size is null");
		return 0;
	}
	ptr = malloc(size);
	if(!ptr){
		throw Exception(Exception::MEMORY_ALLOC, "Memory_alloc out of bounds");
		return 0;
	}
	maxAllocation += size;
	return ptr;
}
//------------------------------------------------------------------------------------
void Memory_free(void *ptr) throw (Exception){
	if(!ptr){
		throw Exception(Exception::BAD_ARGUMENT, "Memory_free ptr is null");
		return;
	}
	free(ptr);
}

//------------------------------------------------------------------------------------
uint32_t Memory_getMaxAllocation(void){
	return maxAllocation;
}
