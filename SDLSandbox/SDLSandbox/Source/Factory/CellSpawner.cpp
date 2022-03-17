/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "CellSpawner.h"

#include "../Actors/Cell.h"

using namespace Challenge;

GameObject* CellSpawner::spawn () const {
	return new Cell ();
}