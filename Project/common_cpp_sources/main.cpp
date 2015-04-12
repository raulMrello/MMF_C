//============================================================================
// Name        : main.cpp
// Author      : raulMrello
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "../../src/mmf/cpp/os/mmf.h"
#include "tasks/Subscriber.h"
#include "tasks/Publisher.h"
#include "topics/MyTopic.h"

int main() {
	try{

		// Initializes kernel
		MMF::OS::init(2, 10000);

		// Initializes topics
		MMF::Topic("/counter");
		MyTopic("/myt");

		// Creates tasks objects
		new Subscriber("subscriber", PRIO_MAX, 5);
		new Publisher("publisher", PRIO_MAX+1, 0);

		// Run kernel scheduling (never returns)
		MMF::OS::schedule();

	}
	catch(MMF::Exception& e){
	}
	return 0;
}
