/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "MainMenuState.h"

#include "CreditsState.h"
#include "IGameController.h"
#include "PlayState.h"
#include "../Audio/IAudioManager.h"
#include "../Services/ServiceLocator.h"
#include "../Tiled/TiledParser.h"

using namespace Challenge;
using namespace std;

const string MainMenuState::file = "MainMenu.tmx";
const string MainMenuState::id = "MainMenu";

string MainMenuState::getStateFile () const {
	return MainMenuState::file;
}

string MainMenuState::getStateID () const {
	return MainMenuState::id;
}

bool MainMenuState::onEnter () {
	GameState::onEnter ();

	this->addCallback ("Credits", &MainMenuState::onPressedCredits);
	this->addCallback ("Mute", &MainMenuState::onPressedMute);
	this->addCallback ("Play", &MainMenuState::onPressedPlay);
	this->addCallback ("Quit", &MainMenuState::onPressedQuit);

	return true;
}

bool MainMenuState::onExit () {
	GameState::onExit ();

	return true;
}

void MainMenuState::onPressedCredits () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->pushState (new CreditsState ());
}

void MainMenuState::onPressedMute () {
	IAudioManager* audioManager = ServiceLocator::getInstance ()->getServiceProvider<IAudioManager> ();
	audioManager->toggleMute ();
}

void MainMenuState::onPressedPlay () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->changeState (new PlayState ());
}

void MainMenuState::onPressedQuit () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->quit ();
}

void MainMenuState::render () {
	GameState::render ();
}

void MainMenuState::update () {
	GameState::update ();
}