/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Chopper.h"

#include "../Audio/IAudioManager.h"
#include "../Input/IInputHandler.h"
#include "../Services/ServiceLocator.h"
#include "../Tiled/TiledObject.h"
#include "../Tiled/TiledTileData.h"
#include <algorithm>
#include <iostream>

using namespace Challenge;
using namespace std;

Chopper::Chopper () : GameObject (), initialPosition (0, 0), shooting (false), shootingStart (0) {
	ServiceLocator* locator = ServiceLocator::getInstance ();
	this->audioManager = locator->getServiceProvider<IAudioManager> ();
	this->inputHandler = locator->getServiceProvider<IInputHandler> ();
}

void Chopper::initialize (TiledObject* data) {
	GameObject::initialize (data);

	this->initialPosition.set (this->position.getX (), this->position.getY ());
	this->position.set (- 100, 100);

	this->initializeFlare ();
}

void Chopper::initializeFlare () {
	// TODO: implement premade objects on Tiled, to avoid hardcoding these values
	TiledObject flareData = TiledObject (5, Vector2D (61, 42), Vector2D (32, 32));
	TiledTileData* tileData = new TiledTileData (0);

	tileData->setProperty ("AtlasID", "atlas.png");
	tileData->setProperty ("TextureID", "shooting.png");
	flareData.setData (tileData);

	this->shootingFlare.initialize (&flareData);
}

void Chopper::render () {
	GameObject::render ();

	if (shooting) {
		this->shootingFlare.render ();
	}
}

void Chopper::update () {
	Vector2D mousePosition = this->inputHandler->getMousePosition ();

	this->velocity.set (
		this->initialPosition.getX () - this->position.getX (),
		min (mousePosition.getY (), 325.0f) - this->position.getY ()
	);

	this->velocity /= 50.0f;

	this->rotation = atan2 (
		mousePosition.getY () - this->position.getY (),
		mousePosition.getX () - this->position.getX ()
	);

	// convert to degrees
	this->rotation *= 180.0 / M_PI;
	
	this->rotation = max (-20.0, min (20.0, this->rotation));

	GameObject::update ();

	this->updateShooting ();
	this->updateFlare ();
}

void Chopper::updateFlare () {
	this->shootingFlare.setRotation (this->rotation);

	// convert to radians
	double rotation = this->rotation * M_PI / 180.0;

	// where (x, y) is the center of the pivot: (x + r * cos, y + r * sin)
	Vector2D position = Vector2D (
		this->getPosition ().getX () + 60.0 * cos (rotation),
		this->getPosition ().getY () + 60.0 * sin (rotation) - 5 // small adjustment to center the sprite
	);

	this->shootingFlare.setPosition (position);
}

void Chopper::updateShooting () {
	IInputHandler* input = this->inputHandler;
	bool mouseDown = input->getMouseButtonState (MouseButton::Left) || input->wasMouseDown ();
	bool startedShooting = false;

	if (this->shooting) {
		if (this->shootingStart + 500 < SDL_GetTicks ()) {
			if (mouseDown) {
				startedShooting = true;
			} else {
				this->shooting = false;
			}
		}
	} else if (mouseDown) {
		this->shooting = true;
		startedShooting = true;
	}

	if (startedShooting) {
		this->shootingStart = SDL_GetTicks ();
		this->audioManager->playSound ("shooting");
	}

}