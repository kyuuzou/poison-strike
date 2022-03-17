/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "ServiceLocator.h"

#include "IServiceProvider.h"
#include <iostream>
#include <string>

using namespace Challenge;
using namespace std;

ServiceLocator* ServiceLocator::instance = nullptr;

ServiceLocator::ServiceLocator () {

}

ServiceLocator* ServiceLocator::getInstance () {
	if (ServiceLocator::instance == nullptr) {
		ServiceLocator::instance = new ServiceLocator ();
	}

	return ServiceLocator::instance;
}

void ServiceLocator::registerServiceProvider (IServiceProvider* service) {
	if (this->services.find (service->getInterfaceType ()) != this->services.end ()) {
		cerr << "Tried to register redundant service: " << service->getInterfaceType ().name () << endl;
		return;
	}

	cout << "Registering service of type: " << service->getInterfaceType ().name () << endl;

	this->services[service->getInterfaceType ()] = service;
}

void ServiceLocator::unregisterServiceProvider (IServiceProvider* service) {
	auto iterator = this->services.find (service->getInterfaceType ());

	if (iterator == this->services.end ()) {
		cerr << "Tried to unregister non-existent service: " << service->getInterfaceType ().name () << endl;
		return;
	}

	cout << "Unregistering service of type: " << service->getInterfaceType ().name () << endl;

	this->services.erase (iterator);
}