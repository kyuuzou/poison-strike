/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "Grid.h"
#include "IGameplay.h"
#include "Direction.h"
#include <vector>

namespace Challenge {

	class IAudioManager;
	class Box;
	class Cell;
	class GameObject;
	class GameState;

	class Gameplay : public IGameplay {

		public:
			Gameplay (GameState* state);
			~Gameplay ();

			/// <summary>
			/// Collapses the columns towards the right, making sure there's no empty columns in between.
			/// </summary>
			void collapseColumns ();

			/// <summary>
			/// Drops all the boxes vertically, making sure there's no empty rows in between.
			/// </summary>
			void dropInhabitants ();

			/// <summary>
			/// Returns the type of interface which will be used to communicate with this kind of service.
			/// </summary>
			virtual std::type_index getInterfaceType () override;

			/// <summary>
			/// Increases columns by one.
			/// </summary>
			void increaseColumns ();

			/// <summary>
			/// Associates the spawned cells with a Grid instance.
			/// </summary>
			void onSpawnedCells (std::vector<GameObject*> gameObjects);

			/// <summary>
			/// Schedules a column increase for when there are no moving boxes.
			/// </summary>
			virtual void scheduleColumnIncrease () override;

			/// <summary>
			/// Controls game flow.
			/// </summary>
			void update ();

		private:
			IAudioManager* audioManager;
			Grid grid;
			bool scheduledColumnIncrease;
			GameState* state;

			/// <summary>
			/// Creates the grid's cells, and spawns its inhabitants.
			/// </summary>
			/// <param name=""></param>
			void initializeGrid (std::vector<GameObject*> cells);

			/// <summary>
			/// Spawns a Box on the provided cell.
			/// </summary>
			Box* spawnBox (Cell* cell);
	};
}