/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "GameObjectFactory.h"

#include "ISpawner.h"
#include "BoxSpawner.h"
#include "CellSpawner.h"
#include "ChopperSpawner.h"
#include "DecorationSpawner.h"
#include "MenuButtonSpawner.h"
#include "ProgressBarSpawner.h"
#include "../Actors/GameObject.h"
#include "../Services/ServiceLocator.h"
#include "../Tiled/TiledObject.h"

#include <iostream>

using namespace Challenge;
using namespace std;

GameObjectFactory::GameObjectFactory () {
	this->provideService ();

	this->initialize ();
}

GameObject* GameObjectFactory::createGameObject (string type) {
	map<string, ISpawner*>::iterator SpawnerPair = this->spawners.find (type);

	if (SpawnerPair == this->spawners.end ()) {
		cerr << "Could not find type: " << type << endl;
		return nullptr;
	}

	ISpawner* Spawner = SpawnerPair->second;
	return Spawner->spawn ();
}

type_index GameObjectFactory::getInterfaceType () {
	return typeid (IGameObjectFactory);
}

void GameObjectFactory::initialize () {
	this->registerSpawner ("Box", new BoxSpawner ());
	this->registerSpawner ("Cell", new CellSpawner ());
	this->registerSpawner ("Chopper", new ChopperSpawner ());
	this->registerSpawner ("Decoration", new DecorationSpawner ());
	this->registerSpawner ("MenuButton", new MenuButtonSpawner ());
	this->registerSpawner ("ProgressBar", new ProgressBarSpawner ());
}

bool GameObjectFactory::registerSpawner (string objectType, ISpawner* spawner) {

	// if the type is already registered, do nothing
	if (this->spawners.find (objectType) != this->spawners.end ()) {
		delete spawner;
		return false;
	}

	this->spawners[objectType] = spawner;

	return true;
}

GameObject* GameObjectFactory::spawn (TiledObject* object) {
	GameObject* gameObject = this->createGameObject (object->getType ());

	if (gameObject == nullptr) {
		cerr << "Could not create object of type: " << object->getType () << endl;
	}

	return gameObject;
}
