/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Decoration.h"

#include "../Tiled/TiledObject.h"
#include <iostream>

using namespace Challenge;
using namespace std;

Decoration::Decoration () : GameObject () {

}

void Decoration::initialize (TiledObject* data) {
	GameObject::initialize (data);

}

void Decoration::render () {
	GameObject::render ();
}

void Decoration::update () {
	GameObject::update ();
}
