/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "GameOverState.h"

#include "IGameController.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "../Audio/IAudioManager.h"
#include "../Services/ServiceLocator.h"

using namespace Challenge;
using namespace std;

const std::string GameOverState::file = "GameOver.tmx";
const std::string GameOverState::id = "GameOver";

string GameOverState::getStateFile () const {
	return GameOverState::file;
}

string GameOverState::getStateID () const {
	return GameOverState::id;
}

bool GameOverState::onEnter () {
	GameState::onEnter ();

	this->addCallback ("MainMenu", &GameOverState::onPressedMainMenu);
	this->addCallback ("Mute", &GameOverState::onPressedMute);
	this->addCallback ("Retry", &GameOverState::onPressedRetry);

	return true;
}

bool GameOverState::onExit () {
	GameState::onExit ();

	return true;
}

void GameOverState::onPressedMainMenu () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->changeState (new MainMenuState ());
}

void GameOverState::onPressedMute () {
	IAudioManager* audioManager = ServiceLocator::getInstance ()->getServiceProvider<IAudioManager> ();
	audioManager->toggleMute ();
}

void GameOverState::onPressedRetry () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->changeState (new PlayState ());
}

void GameOverState::render () {
	GameState::render ();
}

void GameOverState::update () {
	GameState::update ();
}
