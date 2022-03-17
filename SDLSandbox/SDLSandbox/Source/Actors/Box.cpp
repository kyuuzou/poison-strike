/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Box.h"

#include "Cell.h"
#include "../Audio/IAudioManager.h"
#include "../Gameplay/Grid.h"
#include "../Input/IInputHandler.h"
#include "../Math/IRandomGenerator.h"
#include "../Math/Math.h"
#include "../Services/ServiceLocator.h"
#include "../Tiled/TiledTileData.h"
#include <iostream>

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

using namespace Challenge;
using namespace std;

const vector<string> Box::textureNames = {
	"obj_box001.png",
	"obj_box002.png",
	"obj_box003.png",
	"obj_box004.png",
	"obj_box005.png",
	"obj_crate001.png",
	"obj_crate002.png",
	"obj_crate003.png",
	"obj_crate004.png",
	"obj_crate005.png"
};

TiledObject Box::defaultData;

Box::StaticConstructor Box::DefaultDataInitializer;

Box::StaticConstructor::StaticConstructor () {

	// TODO: implement premade objects on Tiled, to avoid hardcoding these values

	Box::defaultData.setSize (Vector2D (32, 32));
	Box::defaultData.setPosition (Vector2D (32, 32));
	Box::defaultData.setLayer (2);

	TiledTileData* tileData = new TiledTileData (0);

	tileData->setProperty ("AtlasID", "atlas.png");
	tileData->setProperty ("TextureID", "obj_box001.png");

	Box::defaultData.setData (tileData);
}

Box::Box () : Box (nullptr) {

}

Box::Box (Grid* grid) 
	: GameObject (), grid (grid), currentCell (nullptr), lastCell (nullptr), busy (false), pressed (false)
{
	ServiceLocator* locator = ServiceLocator::getInstance ();
	this->audioManager = locator->getServiceProvider<IAudioManager> ();
	this->inputHandler = locator->getServiceProvider<IInputHandler> ();
}

void Box::die () {
	if (this->currentCell != nullptr) {
		this->currentCell->setInhabitant (nullptr);
		this->currentCell = nullptr;
	}

	GameObject::die ();
}

Color Box::getColor () {
	return GameObject::getColor ();
}

Cell* Box::getCurrentCell () {
	return this->currentCell;
}

void Box::handleInput () {
	Vector2D mousePosition = this->inputHandler->getMousePosition ();

	bool mouseDown = this->inputHandler->getMouseButtonState (MouseButton::Left);

	if (this->pressed) {
		if (! mouseDown) {
			this->pressed = false;
		}
	} else if (this->contains (mousePosition) && mouseDown) {
		this->pressed = true;
		this->onPressed ();

		IInputHandler* inputHandler = ServiceLocator::getInstance ()->getServiceProvider<IInputHandler> ();
		inputHandler->reset ();
	}
}

void Box::initialize () {
	TiledObject* data = new TiledObject (Box::defaultData);
	this->initialize (data);

	this->randomizeColor ();
	this->randomizeTexture ();
}

void Box::initialize (TiledObject* data) {
	GameObject::initialize (data);
}

bool Box::isDead () {
	return GameObject::isDead ();
}

bool Box::killGroup () {
	vector<IInhabitant*> closedSet;
	vector<IInhabitant*> openSet = { this };

	do {
		IInhabitant* inhabitant = openSet[0];
		openSet.erase (openSet.begin ());
		closedSet.push_back (inhabitant);

		for (int d = (int) Direction::North; d <= (int) Direction::West; d ++) {
			Cell* cell = inhabitant->getCurrentCell ()->getNeighbour ((Direction) d);

			if (cell == nullptr) {
				continue;
			}

			IInhabitant* neighbour = cell->getInhabitant ();

			if (neighbour == nullptr) {
				continue;
			}

			if (find (openSet.begin (), openSet.end (), neighbour) != openSet.end ()) {
				continue;
			}

			// we're not looking for a path, so we don't want to visit any node more than once,
			// so check closedSet too
			if (find (closedSet.begin (), closedSet.end (), neighbour) != closedSet.end ()) {
				continue;
			}

			if (neighbour->getColor () != this->getColor ()) {
				continue;
			}

			// Ignore boxes on the last (offscreen) column
			if (neighbour->getCurrentCell ()->getGridPosition ().getX () < this->grid->getSize ().getX () - 1) {
				openSet.push_back (neighbour);
			}
		}
	} while (openSet.size () > 0);

	// There has to be at least more than one contiguous box of the same color for the group to die
	if (closedSet.size () > 1) {
		for (auto inhabitant : closedSet) {
			inhabitant->die ();
		}

		return true;
	}

	return false;
}

bool Box::moveTowardsTarget () {
	if (this->currentCell != nullptr && this->lastCell != nullptr) {
		Vector2D targetPosition = this->currentCell->getPosition ();

		bool moving = false;

		for (int axis = 1; axis >= 0; axis --) {
			if (*this->getPosition ()[axis] == *targetPosition[axis]) {
				*this->velocity[axis] = 0;
			} else {
				moving = true;

				float velocity = Math::moveTowards (
					*this->getPosition ()[axis],
					*this->lastCell->getPosition ()[axis],
					*targetPosition[axis],
					0.075f
				);

				*this->velocity[axis] = velocity - *this->getPosition ()[axis];

				break;
			}
		}

		return moving;
	}

	return false;
}

void Box::onPressed () {
	if (this->currentCell == nullptr) {
		this->audioManager->playSound ("explosion1");
		this->die ();
		return;
	}

	if (this->busy || this->grid->hasBusyInhabitants ()) {
		return;
	}

	if (this->killGroup ()) {
		//TODO: Implement variadic template on AudioManager, for random sounds from a given range
		//this->audioManager->playSound ("explosion1", "explosion2");
		this->audioManager->playSound ("explosion1");
	}
}

void Box::randomizeColor () {
	IRandomGenerator* generator = ServiceLocator::getInstance ()->getServiceProvider<IRandomGenerator> ();
	Color identifier = (Color) generator->getRandom (
		(int) Color::Blue,
		(int) Color::Yellow
	);

	this->setColor (identifier);
}

void Box::randomizeTexture () {
	IRandomGenerator* generator = ServiceLocator::getInstance ()->getServiceProvider<IRandomGenerator> ();
	int index = generator->getRandom (0, (int) this->textureNames.size () - 1);
	this->frames[0] = this->textureNames[index];
}

void Box::render () {
	GameObject::render ();
}

void Box::setCurrentCell (Cell* cell) {
	this->lastCell = this->currentCell;
	this->currentCell = cell;

	if (this->lastCell != nullptr) {
		// Nothing should disturb this box until it reaches its current cell
		this->busy = true;
	}
}

void Box::update () {
	this->busy = this->moveTowardsTarget ();

	GameObject::update ();

	this->handleInput ();
}

