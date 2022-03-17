/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "RandomGenerator.h"
#include <iostream>

using namespace Challenge;
using namespace std;

RandomGenerator::RandomGenerator () : engine (device ()) {
	this->provideService ();
}

RandomGenerator::~RandomGenerator () {

}

type_index RandomGenerator::getInterfaceType () {
	return typeid (IRandomGenerator);
}

int RandomGenerator::getRandom (int minimum, int maximum) {
	 return (int) round ((this->distribution (this->engine) * (maximum - minimum) / 100.0f) + minimum);
}