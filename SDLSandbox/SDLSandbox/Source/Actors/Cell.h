/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameObject.h"
#include "IInhabitant.h"
#include "../Gameplay/Direction.h"
#include <map>

namespace Challenge {

	class Cell : public GameObject {

		public:
			Cell ();

			/// <summary>
			/// Returns the position of this cell in grid coordinates.
			/// </summary>
			inline Vector2D& getGridPosition () {
				return this->gridPosition;
			}

			/// <summary>
			/// Returns the current inhabitant, if any.
			/// </summary>
			IInhabitant* getInhabitant ();

			/// <summary>
			/// Returns the adjacent grid cell in the provided direction.
			/// </summary>
			/// <param name="direction">Direction to search for a neighbour.</param>
			/// <returns>Adjacent cell.</returns>
			Cell* getNeighbour (Direction direction);

			virtual void initialize (TiledObject* data) override;

			/// <summary>
			/// Whether this cell is supposed to be populated.
			/// This is only used for the initial populating of the grid, and corresponds to a property set on Tiled.
			/// </summary>
			inline bool isActive () {
				return this->active;
			}

			/// <summary>
			/// Whether this cell is currently available.
			/// Dead inhabitants don't count.
			/// </summary>
			/// <returns></returns>
			bool isFree () {
				return this->inhabitant == nullptr || this->inhabitant->isDead ();
			}

			virtual void render () override;

			/// <summary>
			/// Sets the current position in grid coordinates.
			/// </summary>
			void setGridPosition (int column, int row);

			/// <summary>
			/// Sets the current inhabitant.
			/// </summary>
			void setInhabitant (IInhabitant* inhabitant);

			/// <summary>
			/// Sets a neighbour cell for a given direction.
			/// </summary>
			void setNeighbour (Direction direction, Cell* cell);

			virtual void update () override;

		private:
			bool active;
			Vector2D gridPosition;
			IInhabitant* inhabitant;
			std::map<Direction, Cell*> neighbours;

			virtual std::string type () override {
				return "Cell";
			}
	};
}
