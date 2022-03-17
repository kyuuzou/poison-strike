/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "CreditsState.h"

#include "IGameController.h"
#include "MainMenuState.h"
#include "../Services/ServiceLocator.h"

using namespace Challenge;
using namespace std;

const std::string CreditsState::file = "Credits.tmx";
const std::string CreditsState::id = "Credits";

string CreditsState::getStateFile () const {
	return CreditsState::file;
}

string CreditsState::getStateID () const {
	return CreditsState::id;
}

bool CreditsState::onEnter () {
	GameState::onEnter ();

	this->addCallback ("MainMenu", &CreditsState::onPressedMainMenu);

	return true;
}

bool CreditsState::onExit () {
	GameState::onExit ();

	return true;
}

void CreditsState::onPressedMainMenu () {
	IGameController* controller = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
	controller->changeState (new MainMenuState ());
}

void CreditsState::render () {
	GameState::render ();
}

void CreditsState::update () {
	GameState::update ();
}
