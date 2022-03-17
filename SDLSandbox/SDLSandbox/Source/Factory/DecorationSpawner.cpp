/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "DecorationSpawner.h"

#include "../Actors/Decoration.h"

using namespace Challenge;

GameObject* DecorationSpawner::spawn () const {
	return new Decoration ();
}