/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameState.h"
#include <vector>

namespace Challenge {

	class GameObject;

	class GameOverState : public GameState {

		public:
			virtual std::string getStateFile () const override;
			virtual std::string getStateID () const override;
			virtual bool onEnter () override;
			virtual bool onExit () override;
			virtual void render () override;
			virtual void update () override;

		private:
			static const std::string file;
			static const std::string id;

			/// <summary>
			/// Switches to the main menu state.
			/// </summary>
			static void onPressedMainMenu ();

			/// <summary>
			/// Toggles whether the sounds and music are muted.
			/// </summary>
			static void onPressedMute ();

			/// <summary>
			/// Restarts the game level.
			/// </summary>
			static void onPressedRetry ();
	};
}
