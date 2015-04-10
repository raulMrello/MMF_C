/*
 * Memory.h
 *
 *  Created on:	09/04/2015
 *  Author: 	raulMrello
 *
 *  Memory module, manages dynamic memory allocation-deallocation, keeping track of the maximum number of allocated
 *  memory.
 */

#ifndef SRC_OS_MEMORY_H_
#define SRC_OS_MEMORY_H_

#ifdef __cplusplus
 extern "C" {
#endif


//------------------------------------------------------------------------------------
//-- DEPENDENCIES --------------------------------------------------------------------
//------------------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>			///< required for malloc|free
#include "Exception.h"


//------------------------------------------------------------------------------------
//-- PROTOTYPES ----------------------------------------------------------------------
//------------------------------------------------------------------------------------

/**
 * Allocates a memory block
 * @param size Block size
 * @throw Exception
 * @return Pointer to the allocated block
 */
void* Memory_alloc(uint32_t size) throw (Exception);

/**
 * Frees an allocated memory block
 * @param ptr Pointer to the block
 * @throw Exception
 */
void Memory_free(void *ptr) throw (Exception);

/**
 * Get maximum allocation memory
 * @return Max allocated size ever
 */
uint32_t Memory_getMaxAllocation(void);

#ifdef __cplusplus
}
#endif


#endif	/* SRC_OS_MEMORY_H_ */
