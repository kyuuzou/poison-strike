/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameObject.h"
#include "Decoration.h"
#include <map>

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

namespace Challenge {

	class IAudioManager;
	class IInputHandler;
	class TiledObject;

	class Chopper : public GameObject {

		public:
			Chopper ();

			virtual void initialize (TiledObject* data) override;
			virtual void render () override;
			virtual void update () override;

		private:
			IAudioManager* audioManager;
			Vector2D initialPosition;
			IInputHandler* inputHandler;
			bool shooting;
			Decoration shootingFlare;
			Uint32 shootingStart;

			/// <summary>
			/// Initializes the gun flare with hard-coded values.
			/// </summary>
			void initializeFlare ();

			/// <summary>
			/// Keeps the gun flare positioned roughly at the front of the chopper, matching the chopper rotation.
			/// </summary>
			void updateFlare ();

			/// <summary>
			/// Checks whether or not the chopper should be currently shooting, plays the appropriate sounds and
			/// shows/hides the gun flare.
			/// </summary>
			void updateShooting ();

			virtual std::string type () override {
				return "Chopper";
			}
	};
}
