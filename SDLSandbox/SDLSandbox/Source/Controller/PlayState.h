/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameState.h"
#include <vector>

namespace Challenge {

	class Gameplay;

		class PlayState : public GameState {

			public:
				PlayState ();

				virtual std::string getStateFile () const override;
				virtual std::string getStateID () const override;
				virtual bool onEnter () override;
				virtual bool onExit () override;
				virtual void render () override;
				virtual void update () override;

			protected:
				/// <summary>
				/// Spawns all the parsed game objects and passes all the cells to the current Gameplay instance.
				/// </summary>
				virtual void spawnObjects () override;

			private:
				static const std::string file;
				static const std::string id;

				Gameplay* gameplay;

				/// <summary>
				/// Schedules a column increase.
				/// </summary>
				static void onPressedAdvance ();

				/// <summary>
				/// Toggles whether the sounds and music are muted.
				/// </summary>
				static void onPressedMute ();

				/// <summary>
				/// Switches to the paused state.
				/// </summary>
				static void onPressedPause ();
	};
}
