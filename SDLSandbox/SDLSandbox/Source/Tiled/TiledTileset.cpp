/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "TiledTileset.h"

using namespace Challenge;
using namespace std;

TiledTileset::TiledTileset (int firstGid) : firstGid (firstGid) {

}

void TiledTileset::addTile (TiledTileData* tileData) {
	this->tiles[tileData->getGid ()] = tileData;
}

TiledTileData* TiledTileset::getData (int gid) {
	auto iterator = tiles.find (gid - this->firstGid);

	if (iterator == tiles.end ()) {
		cerr << "Could not find data for object gid: " << gid << endl;
		return nullptr;
	}

	return new TiledTileData (*iterator->second);
}

int TiledTileset::getFirstGid () {
	return this->firstGid;
}