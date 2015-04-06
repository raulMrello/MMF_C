/*
 * Topic.h
 *
 *  Created on: 12/3/2015
 *      Author: raulMrello
 */

#ifndef SRC_OS_EXCEPTION_H_
#define SRC_OS_EXCEPTION_H_

#include "../port/platforms.h" ///< platform dependent
#include <list>
#include <cstddef>
#include <string>


/** \class Exception
 *  \brief Exception class gives information about errors during execution
 */
class Exception {
public:

	/** \enum Code
	 *  \brief Exception codes
	 */
	typedef enum {
		NO_EXCEPTIONS,		///< No exceptions
		BAD_ARGUMENT,		///< A function argument out of range
		MEMORY_ALLOC,		///< Memory allocation error
		MEMORY_DEALLOC,		///< Memory deallocation error
		UNKNOWN_EXCEPTION	///< Other exceptions
	}Code;

	/** \fn ~Exception
	 *  \brief Default constructor.
	 */
	Exception(Code c = NO_EXCEPTIONS);

	/** \fn ~Exception
	 *  \brief Default destructor. It will deallocate all resources
	 */
	virtual ~Exception();

	/** \fn getMessage
	 *  \brief Get exception code message
	 *  \return Exception code message
	 */
	std::string getMessage();

	/** \fn getCode
	 *  \brief Get exception code
	 *  \return Exception code
	 */
	int getCode();

private:
	Code _code;
};

#endif /* SRC_OS_EXCEPTION_H_ */
