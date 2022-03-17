/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "InputHandler.h"

#include "../Controller/IGameController.h"
#include "../Services/ServiceLocator.h"

#include <iostream>

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

using namespace Challenge;
using namespace std;

InputHandler::InputHandler () : mousePosition (0, 0), mouseDownThisFrame (false) {
	this->provideService ();

	for (int i = 0; i < 3; i ++) {
		this->mouseButtonStates.push_back (false);
	}
}

type_index InputHandler::getInterfaceType () {
	return typeid (IInputHandler);
}

bool InputHandler::getMouseButtonState (MouseButton button) {
	return this->mouseButtonStates[(int) button];
}

Vector2D InputHandler::getMousePosition () {
	return this->mousePosition;
}

void InputHandler::handleEvents () {
	SDL_Event event;

	while (SDL_PollEvent (&event)) {
		switch (event.type) {
		case SDL_MOUSEMOTION:
			this->onMouseMove (event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			this->onMouseButtonDown (event);
			break;

		case SDL_MOUSEBUTTONUP:
			this->onMouseButtonUp (event);
			break;

		case SDL_QUIT:
		{
			ServiceLocator* serviceLocator = ServiceLocator::getInstance ();
			IGameController* controller = serviceLocator->getServiceProvider<IGameController> ();
			controller->quit ();
		} 
		break;

		default:
			break;
		}
	}
}

void InputHandler::onMouseButtonDown (SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		this->mouseButtonStates[(int) MouseButton::Left] = true;
		this->mouseDownThisFrame = true;
	} else if (event.button.button == SDL_BUTTON_MIDDLE) {
		this->mouseButtonStates[(int) MouseButton::Middle] = true;
	} else if (event.button.button == SDL_BUTTON_RIGHT) {
		this->mouseButtonStates[(int) MouseButton::Right] = true;
	}
}

void InputHandler::onMouseButtonUp (SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		this->mouseButtonStates[(int) MouseButton::Left] = false;
		this->mouseDownThisFrame = false;
	} else if (event.button.button == SDL_BUTTON_MIDDLE) {
		this->mouseButtonStates[(int) MouseButton::Middle] = false;
	} else if (event.button.button == SDL_BUTTON_RIGHT) {
		this->mouseButtonStates[(int) MouseButton::Right] = false;
	}
}

void InputHandler::onMouseMove (SDL_Event& event) {
	this->mousePosition.setX ((float) event.motion.x);
	this->mousePosition.setY ((float) event.motion.y);
}

void InputHandler::reset () {
	for (unsigned int i = 0; i < this->mouseButtonStates.size (); i ++) {
		this->mouseButtonStates[i] = false;
	}
}

bool InputHandler::wasMouseDown () {
	return this->mouseDownThisFrame;
}

