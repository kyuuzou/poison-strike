/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <vector>

namespace Challenge {

	class GameState;

	class StateMachine {

		public:

			/// <summary>
			/// Switches to a new game state, scheduling all currently instantiated states for disposal.
			/// </summary>
			void changeState (GameState* state);

			/// <summary>
			/// Returns the current game state.
			/// </summary>
			inline GameState* getCurrentState () {
				return this->gameStates.back ();
			}

			/// <summary>
			/// Returns to the previous state, scheduling the current state for disposal.
			/// </summary>
			void popState ();

			/// <summary>
			/// Switches to a new state, without disposing the last one.
			/// </summary>
			void pushState (GameState* state);

			/// <summary>
			/// Renders the current game state.
			/// </summary>
			void render ();

			/// <summary>
			/// Updates the current game state.
			/// </summary>
			void update ();

		private:
			std::vector<GameState*> gameStates;
			std::vector<GameState*> disposableStates;

			/// <summary>
			/// Schedules the provided state for disposal.
			/// </summary>
			void scheduleDisposal (GameState* state);
	};
}
