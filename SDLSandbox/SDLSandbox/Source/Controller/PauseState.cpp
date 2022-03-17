/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "PauseState.h"

#include "IGameController.h"
#include "MainMenuState.h"
#include "../Audio/IAudioManager.h"
#include "../Services/ServiceLocator.h"

using namespace Challenge;
using namespace std;

const std::string PauseState::file = "PauseMenu.tmx";
const std::string PauseState::id = "PauseMenu";

string PauseState::getStateFile () const {
	return PauseState::file;
}

string PauseState::getStateID () const {
	return PauseState::id;
}

bool PauseState::onEnter () {
	GameState::onEnter ();

	this->addCallback ("MainMenu", &PauseState::onPressedMainMenu);
	this->addCallback ("Mute", &PauseState::onPressedMute);
	this->addCallback ("Resume", &PauseState::onPressedResume);

	return true;
}

bool PauseState::onExit () {
	GameState::onExit ();

	return true;
}

void PauseState::onPressedMainMenu () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->changeState (new MainMenuState ());
}

void PauseState::onPressedMute () {
	IAudioManager* audioManager = ServiceLocator::getInstance ()->getServiceProvider<IAudioManager> ();
	audioManager->toggleMute ();
}

void PauseState::onPressedResume () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->popState ();
}

void PauseState::render () {
	GameState::render ();
}

void PauseState::update () {
	GameState::update ();
}
