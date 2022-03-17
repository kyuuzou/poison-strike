/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "TiledState.h"

#include "TiledObject.h"
#include "TiledTileset.h"

#include <iostream>

using namespace Challenge;
using namespace std;

TiledState::TiledState () {

}

TiledState::~TiledState () {
	for (auto object : this->objects) {
		delete object;
	}

	for (auto tileset : this->tilesets) {
		delete tileset;
	}
}

void TiledState::addObject (TiledObject* object) {
	TiledTileset* tileset = this->findTileset (object->getGid ());
	TiledTileData* data = tileset->getData (object->getGid ());

	object->setData (data);

	this->objects.push_back (object);
}

void TiledState::addTileset (TiledTileset* tileset) {
	this->tilesets.push_back (tileset);
}

TiledTileset* TiledState::findTileset (int gid) {
	TiledTileset* closestTileset = nullptr;
	int closestGid = INT_MIN;

	for (auto& tileset : this->tilesets) {
		// if it's above the firstGid, this is not the right tileset
		if (tileset->getFirstGid () > gid) {
			continue;
		}

		// if we already found a gid higher than this one, this isn't the right tileset either
		if (closestGid > tileset->getFirstGid ()) {
			continue;
		}

		closestGid = tileset->getFirstGid ();
		closestTileset = tileset;
	}

	if (closestTileset == nullptr) {
		cerr << "Could not find an appropriate tileset for gid: " << gid << endl;
	}

	return closestTileset;
}


