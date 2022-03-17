/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Services/IServiceProvider.h"
#include <string>

namespace Challenge {

	class GameState;

	class IGameController : public IServiceProvider {

		public:
			IGameController () {};
			virtual ~IGameController () {};

			// no copy operations
			IGameController (const IGameController&) = delete;
			IGameController& operator=(const IGameController&) = delete;

			// no move operations
			IGameController (IGameController&&) = delete;
			IGameController& operator = (IGameController&&) = delete;

			/// <summary>
			/// Switches to a new game state, scheduling all currently instantiated states for disposal.
			/// </summary>
			virtual void changeState (GameState* state) = 0;

			/// <summary>
			/// Tells the current game state to handle a button click.
			/// </summary>
			/// <param name="buttonIdentifier">The identifier of the clicked button.</param>
			virtual void onPressedButton (std::string buttonIdentifier) = 0;

			/// <summary>
			/// Returns to the previous state, scheduling the current state for disposal.
			/// </summary>
			virtual void popState () = 0;

			/// <summary>
			/// Switches to a new state, without disposing the last one.
			/// </summary>
			virtual void pushState (GameState* state) = 0;

			/// <summary>
			/// Quits the application at the end of the current frame.
			/// </summary>
			virtual void quit () = 0;
	};
}
