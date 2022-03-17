/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "GameObject.h"
#include "../Tiled/TiledObject.h"
#include "../Tiled/TiledTileData.h"
#include "../Services/ServiceLocator.h"
#include "../Textures/ITextureManager.h"

#include <iostream>
#include <string>

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

using namespace Challenge;
using namespace std;

GameObject::GameObject () :
	acceleration (0, 0),
	animationSpeed (100),
	color (Color::White),
	colorValue ({ 255, 255, 255 }),
	currentFrame (0),
	dead (false),
	layer (0),
	position (0, 0),
	rotation (0),
	size (0, 0),
	velocity (0, 0),
	visible (false),
	textureManager (nullptr)
{

}

GameObject::~GameObject () {

}

bool GameObject::contains (Vector2D position) {
	if (position.getX () < this->position.getX ()) {
		return false;
	} else if (position.getX () >= this->position.getX () + this->size.getX ()) {
		return false;
	}

	if (position.getY () < this->position.getY ()) {
		return false;
	} else if (position.getY () >= this->position.getY () + this->size.getY ()) {
		return false;
	}

	return true;
}

void GameObject::die () {
	this->dead = true;
}

SDL_Color GameObject::getColorValue () {
	return this->colorValue;
}

Color GameObject::getColor () {
	return this->color;
}

Vector2D& GameObject::getPosition () {
	return this->position;
}

Vector2D& GameObject::getSize () {
	return this->size;
}

void GameObject::initialize (TiledObject* objectData) {
	this->textureManager = ServiceLocator::getInstance ()->getServiceProvider<ITextureManager> ();

	this->layer = objectData->getLayer ();
	this->atlasID = objectData->getData ()->getProperty ("AtlasID");
	this->textureID = objectData->getData ()->getProperty ("TextureID");

	this->animationSpeed = 100;

	int frames = objectData->getData ()->getIntProperty ("Frames", 0);

	if (frames > 0) {
		unsigned long index = this->textureID.find ("{0}");

		if (index == string::npos) {
			cerr << "Object expects multiple frames, but texture name does not contain placeholder {0}." << endl;
			this->frames.push_back (this->textureID);
		} else {
			for (int i = 0; i < frames; i ++) {
				string frame = this->textureID;
				frame.replace (index, 3, to_string (i));
				this->frames.push_back (frame);
			}

			this->textureID = this->frames[0];

			this->animationSpeed = objectData->getData ()->getIntProperty ("AnimationSpeed", 100);
		}
	} else {
		this->frames.push_back (this->textureID);
	}

	this->currentFrame = 0;
	
	this->size = objectData->getSize ();
	this->position = objectData->getPosition ();

	this->setColor (ColorFromString () (objectData->getProperty ("Color")));

	this->visible = (objectData->getProperty ("Visible") != "false");
}

bool GameObject::isDead () {
	return this->dead;
}

bool GameObject::overlaps (GameObject* otherObject) {
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	leftA = this->position.getX ();
	rightA = this->position.getX () + this->size.getX ();
	topA = this->position.getY ();
	bottomA = this->position.getY () + this->size.getY ();

	leftB = otherObject->position.getX ();
	rightB = otherObject->position.getX () + otherObject->size.getX ();
	topB = otherObject->position.getY ();
	bottomB = otherObject->position.getY () + otherObject->size.getY ();

	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA > rightB) {
		return false;
	}

	return true;
}

void GameObject::render () {
	if (this->visible) {
		this->textureManager->renderFrame (
			this->atlasID,
			this->frames[this->currentFrame],
			this->position,
			this->size,
			this->rotation,
			this->colorValue
		);
	}
}

void GameObject::setColor (Color identifier) {
	this->color = identifier;
	this->colorValue = ColorFromIdentifier () (this->color);
}

void GameObject::setPosition (Vector2D position) {
	this->position.set (position.getX (), position.getY ());
}

void GameObject::setRotation (double rotation) {
	this->rotation = rotation;
}

void GameObject::update () {
	this->velocity += this->acceleration;
	this->position += this->velocity;

	this->currentFrame = int ((SDL_GetTicks () / this->animationSpeed) % this->frames.size ());
}
