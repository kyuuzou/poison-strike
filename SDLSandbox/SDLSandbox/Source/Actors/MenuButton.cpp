/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "MenuButton.h"

#include "../Audio/IAudioManager.h"
#include "../Controller/IGameController.h"
#include "../Input/IInputHandler.h"
#include "../Services/ServiceLocator.h"
#include "../Tiled/TiledObject.h"

using namespace Challenge;
using namespace std;

MenuButton::MenuButton () : GameObject (), pressed (false) {
	ServiceLocator* locator = ServiceLocator::getInstance ();
	this->gameController = locator->getServiceProvider<IGameController> ();
	this->inputHandler = locator->getServiceProvider<IInputHandler> ();
}

void MenuButton::initialize (TiledObject* data) {
	GameObject::initialize (data);

	this->callback = data->getProperty ("Callback");
}

void MenuButton::onPressed () {
	IAudioManager* audioManager = ServiceLocator::getInstance ()->getServiceProvider<IAudioManager> ();
	audioManager->playSound ("click");

	this->gameController->onPressedButton (this->callback);
}

void MenuButton::render () {
	GameObject::render ();
}

void MenuButton::update () {
	Vector2D mousePosition = this->inputHandler->getMousePosition ();

	if (this->contains (mousePosition)) {
		if (this->inputHandler->getMouseButtonState (MouseButton::Left)) {
			this->pressed = true;
		} else {
			if (this->pressed) {
				this->pressed = false;
				this->onPressed ();
			}
		}
	} else {
		this->pressed = false;
	}
}
