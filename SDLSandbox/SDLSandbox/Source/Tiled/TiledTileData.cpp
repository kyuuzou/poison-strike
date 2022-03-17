/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "TiledTileData.h"

#include <iostream>

using namespace Challenge;
using namespace std;

TiledTileData::TiledTileData (int gid) : gid (gid) {

}

TiledTileData::TiledTileData (const TiledTileData& data) : TiledTileData (gid) {
	for (auto propertyPair : data.properties) {
		this->setProperty (propertyPair.first, propertyPair.second);
	}
}

int TiledTileData::getGid () {
	return this->gid;
}

int TiledTileData::getIntProperty (string key, int defaultValue) {
	string property = this->getProperty (key);

	if (property.length () > 0) {
		try {
			return stoi (property);
		} catch (invalid_argument exception) {
			return defaultValue;
		}
	}

	return defaultValue;
}

string TiledTileData::getProperty (string key) {
	auto iterator = this->properties.find (key);

	if (iterator == this->properties.end ()) {
		return string ();
	}

	return iterator->second;
}

void TiledTileData::setProperty (std::string key, std::string value) {
	this->properties[key] = value;
}
