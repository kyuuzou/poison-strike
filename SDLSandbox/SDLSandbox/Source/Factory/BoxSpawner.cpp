/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "BoxSpawner.h"

#include "../Actors/Box.h"

using namespace Challenge;

GameObject* BoxSpawner::spawn () const {
	return new Box ();
}