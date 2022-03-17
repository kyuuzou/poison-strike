/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "GameState.h"

#include "../Factory/IGameObjectFactory.h"
#include "../Services/ServiceLocator.h"
#include "../Actors/GameObject.h"
#include "../Tiled/TiledObject.h"
#include "../Tiled/TiledParser.h"

#include <iostream>

using namespace Challenge;
using namespace std;

GameState::GameState () : stateData (nullptr) {

}

GameState::~GameState () {
	cout << "Destroying state (" << this << ") " << endl;

	for (auto type : this->gameObjectsByType) {
		for (auto object : type.second) {
			delete object;
		}
	}

	this->gameObjectsByType.clear ();
	this->gameObjectsByLayer.clear ();

	cout << "~GameState: " << ! this->stateData << endl;

	// TODO: Have the factory return a unique_ptr, and don't store the state data locally at all
	//delete this->stateData;
}

void GameState::addCallback (string key, function<void ()> callback) {
	this->callbacks[key] = callback;
}

void GameState::addGameObject (GameObject* gameObject) {
	// Add by type
	string type = gameObject->type ();
	auto typeIterator = this->gameObjectsByType.find (type);

	if (typeIterator == this->gameObjectsByType.end ()) {
		this->gameObjectsByType[type] = vector<GameObject*> ();
	}

	this->gameObjectsByType[type].push_back (gameObject);

	// Add by layer
	int layer = gameObject->getLayer ();
	auto layerIterator = this->gameObjectsByLayer.find (layer);

	if (layerIterator == this->gameObjectsByLayer.end ()) {
		this->gameObjectsByLayer[layer] = vector<GameObject*> ();
	}

	this->gameObjectsByLayer[layer].push_back (gameObject);
}

std::vector<GameObject*> GameState::getGameObjects (string type) {
	return this->gameObjectsByType[type];
}

bool GameState::onEnter () {
	cout << "Entering state (" << this << "): " << this->getStateID () << endl;

	TiledParser parser;
	string path = string ("Assets/Data/") + this->getStateFile ();
	this->stateData = move (parser.parse (path));

	this->spawnObjects ();

	return true;
}

bool GameState::onExit () {
	return true;
}

void GameState::onPressedButton (string key) {
	auto iterator = this->callbacks.find (key);

	if (iterator == this->callbacks.end ()) {
		cerr << "Did not find a callback for button: " << key << endl;
		return;
	}

	iterator->second ();
}

void GameState::render () {
	for (auto iterator : this->gameObjectsByLayer) {
		for (unsigned int i = 0; i < iterator.second.size (); i ++) {
			iterator.second[i]->render ();
		}
	}
}

void GameState::removeObjectFromLayer (GameObject* gameObject) {
    auto layerIterator = this->gameObjectsByLayer.find (gameObject->getLayer ());

	if (layerIterator != this->gameObjectsByLayer.end ()) {
		for (int i = (int) layerIterator->second.size () - 1; i >= 0; i --) {
			if (layerIterator->second[i] == gameObject) {
				layerIterator->second.erase (layerIterator->second.begin () + i);
				break;
			}
		}
	}
}

void GameState::spawnObjects () {
	IGameObjectFactory* factory = ServiceLocator::getInstance ()->getServiceProvider<IGameObjectFactory> ();

	for (TiledObject* tiledObject : this->stateData->getObjects ()) {
		GameObject* gameObject = factory->spawn (tiledObject);
		gameObject->initialize (tiledObject);

		this->addGameObject (gameObject);
	}
}

void GameState::update () {
	for (auto& iterator : this->gameObjectsByType) {
		for (int i = (int) iterator.second.size () - 1; i >= 0; i --) {
			GameObject* gameObject = iterator.second[i];
			gameObject->update ();

			if (gameObject->isDead ()) {
				this->removeObjectFromLayer (gameObject);

				delete gameObject;
				iterator.second.erase (iterator.second.begin () + i);
			}
		}
	}
}