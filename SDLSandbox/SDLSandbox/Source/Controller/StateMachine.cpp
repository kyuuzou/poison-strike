/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "StateMachine.h"

#include "GameState.h"
#include <iostream>

using namespace Challenge;
using namespace std;

void StateMachine::changeState (GameState* state) {
	while (! this->gameStates.empty ()) {
		if (this->gameStates.back ()->onExit ()) {
			this->scheduleDisposal (this->gameStates.back ());
			this->gameStates.pop_back ();
		}
	}

	this->gameStates.push_back (state);
	this->getCurrentState ()->onEnter ();
}

void StateMachine::popState () {
	if (! this->gameStates.empty ()) {
		if (this->gameStates.back ()->onExit ()) {
			this->scheduleDisposal (gameStates.back ());
			this->gameStates.pop_back ();
		}
	}
}

void StateMachine::pushState (GameState* state) {
	this->gameStates.push_back (state);
	this->getCurrentState ()->onEnter ();
}

void StateMachine::render () {
	this->getCurrentState ()->render ();
}

void StateMachine::scheduleDisposal (GameState* state) {
	this->disposableStates.push_back (state);
}

void StateMachine::update () {
	for (auto state : this->disposableStates) {
		delete state;
	}

	this->disposableStates.clear ();

	this->getCurrentState ()->update ();
}
