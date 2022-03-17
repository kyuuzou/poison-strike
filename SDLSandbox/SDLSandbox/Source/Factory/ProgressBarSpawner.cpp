/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "ProgressBarSpawner.h"

#include "../Actors/ProgressBar.h"

using namespace Challenge;

GameObject* ProgressBarSpawner::spawn () const {
	return new ProgressBar ();
}