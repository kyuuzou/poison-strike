/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "IServiceProvider.h"

#include "ServiceLocator.h"

using namespace Challenge;

void IServiceProvider::provideService () {
	 ServiceLocator::getInstance ()->registerServiceProvider (this);
}

void IServiceProvider::revokeService () {
	ServiceLocator::getInstance ()->unregisterServiceProvider (this);
}