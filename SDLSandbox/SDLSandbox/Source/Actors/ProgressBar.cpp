/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "ProgressBar.h"

#include "../Gameplay/IGameplay.h"
#include "../Math/Math.h"
#include "../Services/ServiceLocator.h"
#include "../Tiled/TiledObject.h"
#include <iostream>

using namespace Challenge;
using namespace std;

ProgressBar::ProgressBar () : GameObject (), gameplay (nullptr), initialWidth (0) {
	this->gameplay = ServiceLocator::getInstance ()->getServiceProvider<IGameplay> ();
}

void ProgressBar::initialize (TiledObject* data) {
	GameObject::initialize (data);

	this->initialWidth = this->size.getX ();
	this->size.setX (0);
}

void ProgressBar::render () {
	GameObject::render ();
}

void ProgressBar::update () {
	if (this->getSize ().getX () == this->initialWidth) {
		this->size.setX (0);

		this->gameplay->scheduleColumnIncrease ();
	}

	float size = Math::moveTowards (this->size.getX (), 0, this->initialWidth, 0.002f);
	this->size.setX (size);
}
