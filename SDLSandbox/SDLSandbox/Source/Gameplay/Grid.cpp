/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Grid.h"

#include "Direction.h"
#include "../Actors/Cell.h"
#include <algorithm>
#include <iostream>

using namespace Challenge;
using namespace std;

Grid::Grid () : frontier (0), size (0, 0) {

}

Grid::~Grid () {

}

void Grid::addCell (Cell* cell) {
	this->cells.push_back (cell);
}

void Grid::calculateFrontier () {
	for (int column = (int) this->size.getX () - 1; column >= 0; column --) {
		if (this->isColumnEmpty (column)) {
			this->frontier = column + 1;
			return;
		}
	}

	this->frontier = 0;
	return;
}

void Grid::calculateNeighbours () {
	this->sortCells ();
	this->calculateSize ();
	this->populateMatrix ();

	for (auto cell : this->cells) {
		for (int d = (int) Direction::North; d <= (int) Direction::West; d ++) {
			Direction direction = (Direction) d;
			Vector2D offset = DirectionOffset () (direction);

			cell->setNeighbour (direction, this->getCell (cell->getGridPosition () + offset));
		}
	}
}

void Grid::calculateSize () {
	int columns = 0;
	int lastX = INT_MIN;

	auto iterator = this->cells.begin ();

	while (iterator != this->cells.end ()) {
		int x = (int) (*iterator)->getPosition ().getX ();

		if (lastX > x) {
			break;
		}

		lastX = x;
		columns ++;
		iterator ++;
	}

	if (columns == 0) {
		this->size.set (0, 0);
	} else {
		this->size.set (columns, (int) this->cells.size () / columns);
	}

	cout << "Generated grid of size: " << this->size.toString () << endl;
}

Cell* Grid::getCell (int column, int row) {
	if (column < 0 || column >= this->size.getX ()) {
		return nullptr;
	}

	if (row < 0 || row >= this->size.getY ()) {
		return nullptr;
	}

	return this->cellMatrix[column][row];
}

Cell* Grid::getCell (Vector2D position) {
	return this->getCell ((int) position.getX (), (int) position.getY ());
}

// TODO: If necessary, optimize this by keeping a vector of busy inhabitants, 
// from where they remove themselves as they stop being busy
bool Grid::hasBusyInhabitants () {
	for (auto& cell : this->cells) {
		IInhabitant* inhabitant = cell->getInhabitant ();

		if (inhabitant != nullptr && inhabitant->isBusy ()) {
			return true;
		}
	}

	return false;
}

bool Grid::isColumnEmpty (int column) {
	for (int row = 0; row < this->size.getY (); row ++) {
		if (! this->getCell (column, row)->isFree ()) {
			return false;
		}
	}

	return true;
}

void Grid::populateMatrix () {
	int column = 0;
	int row = 0;

	this->cellMatrix = vector<vector<Cell*>> ((int) this->size.getX (), vector<Cell*> ((int) this->size.getY ()));

	for (auto cell : this->cells) {
		this->cellMatrix[column][row] = cell;
		cell->setGridPosition (column, row);

		column ++;

		if (column >= this->size.getX ()) {
			column = 0;
			row ++;
		}
	}
}

void Grid::sortCells () {
	auto comparer = [] (Cell* a, Cell* b) {
		if (a->getPosition ().getY () > b->getPosition ().getY ()) {
			return true;
		} else if (a->getPosition ().getY () == b->getPosition ().getY ()) {
			return (a->getPosition ().getX () < b->getPosition ().getX ());
		}

		return false;
	};

	sort (this->cells.begin (), this->cells.end (), comparer);
}