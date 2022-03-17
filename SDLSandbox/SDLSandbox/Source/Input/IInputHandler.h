/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Services/IServiceProvider.h"

namespace Challenge {

	enum class MouseButton {
		Left = 0,
		Middle = 1,
		Right = 2
	};

	class Vector2D;

	class IInputHandler : public IServiceProvider {

		public:
			IInputHandler () {};
			virtual ~IInputHandler () {};

			// no copy operations
			IInputHandler (const IInputHandler&) = delete;
			IInputHandler& operator=(const IInputHandler&) = delete;

			// no move operations
			IInputHandler (IInputHandler&&) = delete;
			IInputHandler& operator = (IInputHandler&&) = delete;

			/// <summary>
			/// Returns whether the provided button is currently pressed down.
			/// </summary>
			virtual bool getMouseButtonState (MouseButton button) = 0;

			/// <summary>
			/// Returns the mouse cursor position in world space.
			/// </summary>
			virtual Vector2D getMousePosition () = 0;

			/// <summary>
			/// Handles SDL events.
			/// </summary>
			virtual void handleEvents () = 0;

			/// <summary>
			/// Resets input, setting all button states to false.
			/// </summary>
			virtual void reset () = 0;

			/// <summary>
			/// Returns whether the left mouse button was down at some point during this frame.
			/// This is used to trigger animations even if input is reset before animation has a chance to play.
			/// </summary>
			virtual bool wasMouseDown () = 0;
	};
}