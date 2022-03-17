/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Cell.h"

#include "../Tiled/TiledObject.h"
#include <iostream>

using namespace Challenge;
using namespace std;

Cell::Cell () : GameObject (), active (false), gridPosition (0, 0), inhabitant (nullptr) {

}

IInhabitant* Cell::getInhabitant () {
	return this->inhabitant;
}

Cell* Cell::getNeighbour (Direction direction) {
	return this->neighbours[direction];
}

void Cell::initialize (TiledObject* data) {
	GameObject::initialize (data);

	this->active = data->getProperty ("Active") == "true";
}

void Cell::render () {
	GameObject::render ();
}

void Cell::setGridPosition (int column, int row) {
	this->gridPosition.set (column, row);
}

void Cell::setInhabitant (IInhabitant* inhabitant) {
	this->inhabitant = inhabitant;
}

void Cell::setNeighbour (Direction direction, Cell* cell) {
	this->neighbours[direction] = cell;
}

void Cell::update () {
	
}
