//============================================================================
// Name        : main.cpp
// Author      : raulMrello
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "../../src/mmf/cpp/os/mmf.h"
OS kernel;

#include "tasks/MyTask.h"
MyTask task1("task1", 1000000), task2("task2", 100000);

#include "tasks/Subscriber.h"
Subscriber subscriber("subscriber");

#include "tasks/Publisher.h"
Publisher publisher("publisher");

int main() {
	cout << "#main# Starts!" << endl;

	// Initializes kernel
	kernel.init();

	// Allocates tasks
	try{
		kernel.run(task1, PRIO_HIGH + SUBPRIO_MAX);
		kernel.run(task2, PRIO_LOW + 5);
		kernel.run(subscriber, PRIO_MED);
		kernel.run(publisher, PRIO_LOW);

		// Run kernel scheduling (doesn't return)
		kernel.schedule();

		// Kill tasks
		kernel.kill(task1);
		kernel.kill(task2);
		kernel.kill(subscriber);
		kernel.kill(publisher);
	}
	catch(Exception& err){
		cout << "#main# Exception=" << err.getMessage() << endl;
	}

	cout << "#main# Terminates!" << endl;
	return 0;
}
