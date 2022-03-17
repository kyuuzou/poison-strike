/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "PlayState.h"

#include "IGameController.h"
#include "PauseState.h"
#include "../Audio/IAudioManager.h"
#include "../Factory/IGameObjectFactory.h"
#include "../Gameplay/Gameplay.h"
#include "../Services/ServiceLocator.h"
#include "../Actors/GameObject.h"
#include "../Tiled/TiledObject.h"
#include "../Tiled/TiledState.h"

using namespace Challenge;
using namespace std;

const string PlayState::file = "Play.tmx";
const string PlayState::id = "Play";

PlayState::PlayState () : gameplay (nullptr) {

}

string PlayState::getStateFile () const {
	return PlayState::file;
}

string PlayState::getStateID () const {
	return PlayState::id;
}

bool PlayState::onEnter () {
	this->gameplay = new Gameplay (this);

	GameState::onEnter ();

	this->addCallback ("Advance", &PlayState::onPressedAdvance);
	this->addCallback ("Mute", &PlayState::onPressedMute);
	this->addCallback ("Pause", &PlayState::onPressedPause);

	return true;
}

bool PlayState::onExit () {
	GameState::onExit ();

	delete this->gameplay;

	return true;
}

void PlayState::onPressedAdvance () {
	IGameplay* gameplay = ServiceLocator::getInstance ()->getServiceProvider<IGameplay> ();
	gameplay->scheduleColumnIncrease ();
}

void PlayState::onPressedMute () {
	IAudioManager* audioManager = ServiceLocator::getInstance ()->getServiceProvider<IAudioManager> ();
	audioManager->toggleMute ();
}

void PlayState::onPressedPause () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->pushState (new PauseState ());
}

void PlayState::render () {
	GameState::render ();
}

void PlayState::spawnObjects () {
	GameState::spawnObjects ();

	this->gameplay->onSpawnedCells (this->getGameObjects ("Cell"));
}

void PlayState::update () {
	this->gameplay->update ();

	GameState::update ();
}
