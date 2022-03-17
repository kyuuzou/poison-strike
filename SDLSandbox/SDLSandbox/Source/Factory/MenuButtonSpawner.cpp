/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "MenuButtonSpawner.h"

#include "../Actors/MenuButton.h"

using namespace Challenge;

GameObject* MenuButtonSpawner::spawn () const {
	return new MenuButton ();
}
