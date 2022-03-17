/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameObject.h"

namespace Challenge {

	class IGameController;
	class IInputHandler;

	class MenuButton : public GameObject {

		public:
			MenuButton ();

			virtual void initialize (TiledObject* data) override;
			virtual void render () override;
			virtual void update () override;

		private:
			std::string callback;
			bool pressed;

			IGameController* gameController;
			IInputHandler* inputHandler;

			/// <summary>
			/// Handles a click within the bounds of this game object, invoking this button's callback.
			/// </summary>
			void onPressed ();

			virtual std::string type () override {
				return "MenuButton";
			}
		};
}
