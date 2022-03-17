/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Math/Vector2D.h"
#include <vector>

namespace Challenge {
	
	class Cell;
	
	class Grid {

		public:
			Grid ();
			~Grid ();

			/// <summary>
			/// Adds a cell to the grid.
			/// </summary>
			void addCell (Cell* cell);

			/// <summary>
			/// Calculates the index of the first populated column from the left.
			/// </summary>
			void calculateFrontier ();

			/// <summary>
			/// Calculates the neighbours in every direction for each cell.
			/// </summary>
			void calculateNeighbours ();

			/// <summary>
			/// Returns the cell at the given position.
			/// </summary>
			Cell* getCell (int column, int row);

			/// <summary>
			/// Returns the cell at the given position.
			/// </summary>
			Cell* getCell (Vector2D position);
			
			/// <summary>
			/// Returns the index of the first populated column from the left.
			/// </summary>
			inline int getFrontier () {
				return this->frontier;
			}

			/// <summary>
			/// Returns the grid size in rows and columns.
			/// </summary>
			inline Vector2D& getSize () {
				return this->size;
			}

			/// <summary>
			/// Whether any of the grid inhabitants is busy.
			/// The definition of "busy" may vary depending on the kind of inhabitant.
			/// </summary>
			bool hasBusyInhabitants ();

			/// <summary>
			/// Returns whether all the cells on the provided column is empty.
			/// </summary>
			/// <param name="">Index of the column.</param>
			bool isColumnEmpty (int column);

		private:
			std::vector<Cell*> cells;
			std::vector<std::vector<Cell*>> cellMatrix;

			// Corresponds to the index of the leftmost populated column.
			int frontier;

			Vector2D size;

			/// <summary>
			/// Calculates the size of the grid in rows and columns.
			/// </summary>
			void calculateSize ();

			/// <summary>
			/// Inserts the sorted cells in a matrix, based on the calculated grid size.
			/// </summary>
			void populateMatrix ();

			/// <summary>
			/// Sorts the cell list, so they're ordered from bottom to top, and left to right.
			/// </summary>
			void sortCells ();
	};
}
