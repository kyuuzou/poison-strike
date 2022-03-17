/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "IInputHandler.h"
#include "../Math/Vector2D.h"
#include <vector>

union SDL_Event;

namespace Challenge {

	class InputHandler : public IInputHandler {

		public:
			InputHandler ();

			/// <summary>
			/// Returns the type of interface which will be used to communicate with this kind of service.
			/// </summary>
			virtual std::type_index getInterfaceType () override;

			/// <summary>
			/// Returns whether the provided button is currently pressed down.
			/// </summary>
			virtual bool getMouseButtonState (MouseButton button) override;

			/// <summary>
			/// Returns the mouse cursor position in world space.
			/// </summary>
			virtual Vector2D getMousePosition () override;

			/// <summary>
			/// Handles SDL events.
			/// </summary>
			void handleEvents () override;

			/// <summary>
			/// Handles a mouse down event, registering the button status.
			/// </summary>
			void onMouseButtonDown (SDL_Event& event);

			/// <summary>
			/// Handles a mouse up event, registering the button status.
			/// </summary>
			void onMouseButtonUp (SDL_Event& event);

			/// <summary>
			/// Handles a mouse move event, registering the mouse position.
			/// </summary>
			void onMouseMove (SDL_Event& event);

			/// <summary>
			/// Resets input, setting all button states to false.
			/// </summary>
			virtual void reset () override;

			/// <summary>
			/// Returns whether the left mouse button was down at some point during this frame.
			/// This is used to trigger animations even if input is reset before animation has a chance to play.
			/// </summary>
			virtual bool wasMouseDown () override;

		private:
			std::vector<bool> mouseButtonStates;
			Vector2D mousePosition;
			bool mouseDownThisFrame;
	};
}