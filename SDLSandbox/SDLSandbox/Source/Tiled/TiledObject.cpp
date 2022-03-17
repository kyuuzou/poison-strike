/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "TiledObject.h"
#include "TiledTileData.h"

#include <iostream>

using namespace Challenge;
using namespace std;

TiledObject::TiledObject ()
	: TiledObject (0, 0, 0, Vector2D (0, 0), Vector2D (0, 0), string ())
{

}

TiledObject::TiledObject (const TiledObject& object) 
	: TiledObject (object.id, object.gid, object.layer, object.position, object.size, object.type) {
	
	this->data = new TiledTileData (*object.data);

	for (auto propertyPair : object.properties) {
		this->setProperty (propertyPair.first, propertyPair.second);
	}
}

TiledObject::TiledObject (int layer, Vector2D position, Vector2D size)
	: TiledObject (0, 0, layer, position, size, string ())
{

}

TiledObject::TiledObject (int id, int gid, int layer, Vector2D position, Vector2D size, string type)
	: id (id), gid (gid), layer (layer), position (position), size (size), type (type), data (nullptr)
{

}

TiledObject::~TiledObject () {
	delete this->data;
}

TiledTileData* TiledObject::getData () {
	return this->data;
}

int TiledObject::getId () {
	return this->id;
}

int TiledObject::getGid () {
	return this->gid;
}

int TiledObject::getLayer () {
	return this->layer;
}

Vector2D TiledObject::getPosition () {
	return this->position;
}

string TiledObject::getProperty (string key) {
	auto iterator = this->properties.find (key);

	if (iterator == this->properties.end ()) {
		return string ();
	}

	return iterator->second;
}

Vector2D TiledObject::getSize () {
	return this->size;
}

string TiledObject::getType () {
	return this->type;
}

void TiledObject::setData (TiledTileData* data) {
	this->data = data;
}

void TiledObject::setLayer (int layer) {
	this->layer = layer;
}

void TiledObject::setPosition (Vector2D position) {
	this->position = position;
}

void TiledObject::setProperty (string key, string value) {
	this->properties[key] = value;
}

void TiledObject::setSize (Vector2D size) {
	this->size = size;
}
