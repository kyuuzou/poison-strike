/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Gameplay.h"

#include "../Audio/IAudioManager.h"
#include "../Actors/Box.h"
#include "../Actors/Cell.h"
#include "../Actors/GameObject.h"
#include "../Controller/IGameController.h"
#include "../Controller/GameOverState.h"
#include "../Controller/GameState.h"
#include "../Services/ServiceLocator.h"
#include "../Tiled/TiledObject.h"
#include "../Tiled/TiledTileData.h"
#include <iostream>

using namespace Challenge;
using namespace std;

Gameplay::Gameplay (GameState* state) : state (state), scheduledColumnIncrease (false) {
	this->provideService ();

	this->audioManager = ServiceLocator::getInstance ()->getServiceProvider<IAudioManager> ();
}

Gameplay::~Gameplay () {
	this->revokeService ();
}

void Gameplay::collapseColumns () {
	Vector2D size = this->grid.getSize ();
	
	for (int column = (int) size.getX () - 1; column >= this->grid.getFrontier (); column --) {
		if (! this->grid.isColumnEmpty (column)) {
			continue;
		}

		bool movedNeighbour = false;

		do {
			for (int row = 0; row < size.getY (); row ++) {
				for (int neighbourColumn = column; neighbourColumn >= 0; neighbourColumn --) {
					Cell* neighbourCell = this->grid.getCell (neighbourColumn, row);
				
					if (neighbourCell->isFree ()) {
						continue;
					}

					IInhabitant* neighbour = neighbourCell->getInhabitant ();
					Cell* neighbourCurrentCell = neighbourCell->getNeighbour (Direction::East);
				
					neighbourCell->setInhabitant (nullptr);
					neighbourCurrentCell->setInhabitant (neighbour);
					neighbour->setCurrentCell (neighbourCurrentCell);

					movedNeighbour = true;
				}
			}
		} while (movedNeighbour && this->grid.isColumnEmpty (column));

		if (! movedNeighbour) {
			break;
		}
	}

	this->grid.calculateFrontier ();
}

void Gameplay::dropInhabitants () {
	Vector2D size = this->grid.getSize ();

	for (int column = (int) size.getX () - 1; column >= this->grid.getFrontier (); column --) {
		for (int row = 0; row < size.getY (); row ++) {
			Cell* cell = this->grid.getCell (column, row);

			if (cell->isFree ()) {
				IInhabitant* inhabitant = nullptr;

				for (int freeRow = row + 1; freeRow < size.getY (); freeRow ++) {
					Cell *neighbour = this->grid.getCell (column, freeRow);

					if (! neighbour->isFree ()) {
						inhabitant = neighbour->getInhabitant ();
						break;
					}
				}

				if (inhabitant != nullptr) {
					inhabitant->getCurrentCell ()->setInhabitant (nullptr);
					inhabitant->setCurrentCell (cell);
					cell->setInhabitant (inhabitant);
				}
			}
		}
	}
}

type_index Gameplay::getInterfaceType () {
	return typeid (IGameplay);
}

void Gameplay::increaseColumns () {
	Vector2D size = this->grid.getSize ();

	for (int column = 1; column < size.getX (); column ++) {
		for (int row = 0; row < size.getY (); row ++) {
			Cell* cell = this->grid.getCell (column, row);
			IInhabitant* inhabitant = cell->getInhabitant ();

			if (inhabitant != nullptr) {
				Cell* neighbour = cell->getNeighbour (Direction::West);
				neighbour->setInhabitant (inhabitant);
				inhabitant->setCurrentCell (neighbour);
				cell->setInhabitant (nullptr);
			}
		}
	}

	for (int row = 0; row < size.getY (); row ++) {
		Cell* cell = this->grid.getCell ((int) size.getX () - 1, row);
		this->spawnBox (cell);
	}

	this->grid.calculateFrontier ();

	this->audioManager->playSound ("advance");

	if (this->grid.getFrontier () == 0) {
		this->audioManager->playSound ("gameover");

		IGameController* gameController = ServiceLocator::getInstance ()->getServiceProvider<IGameController> ();
		gameController->changeState (new GameOverState ());
	}
}

void Gameplay::initializeGrid (std::vector<GameObject*> cells) {
	for (auto gameObject : cells) {
		if (gameObject->type () == "Cell") {
			Cell* cell = dynamic_cast<Cell*> (gameObject);

			if (cell != nullptr) {
				this->grid.addCell (cell);

				if (cell->isActive ()) {
					this->spawnBox (cell);
				}
			}
		}
	}

	this->grid.calculateNeighbours ();
	this->grid.calculateFrontier ();
}

void Gameplay::onSpawnedCells (std::vector<GameObject*> cells) {
	this->initializeGrid (cells);
}

void Gameplay::scheduleColumnIncrease () {
	this->scheduledColumnIncrease = true;
}

Box* Gameplay::spawnBox (Cell* cell) {
	Box* box = new Box (&this->grid);
	box->initialize ();

	box->setCurrentCell (cell);
	cell->setInhabitant (box);
	box->setPosition (cell->getPosition ());

	this->state->addGameObject (box);

	return box;
}

void Gameplay::update () {
	this->dropInhabitants ();

	if (! this->grid.hasBusyInhabitants ()) {
		this->collapseColumns ();
	}

	if (! this->grid.hasBusyInhabitants () && this->scheduledColumnIncrease) {
		this->scheduledColumnIncrease = false;

		this->increaseColumns ();
	}
}