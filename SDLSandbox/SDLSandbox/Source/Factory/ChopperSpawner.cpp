/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "ChopperSpawner.h"

#include "../Actors/Chopper.h"

using namespace Challenge;

GameObject* ChopperSpawner::spawn () const {
	return new Chopper ();
}