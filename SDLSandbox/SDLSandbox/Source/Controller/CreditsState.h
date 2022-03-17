/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameState.h"
#include <vector>

namespace Challenge {

	class GameObject;

	class CreditsState : public GameState {

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
	};
}
