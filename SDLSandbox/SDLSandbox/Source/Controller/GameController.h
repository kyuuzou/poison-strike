/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "IGameController.h"
#include "StateMachine.h"
#include "../Input/IInputHandler.h"
#include "../Math/Vector2D.h"

#include <iostream>
#include <string>
#include <vector>

struct SDL_Renderer;
struct SDL_Window;

namespace Challenge {

	class GameController : public IGameController {

		public:
			GameController ();
			~GameController ();

			/// <summary>
			/// Switches to a new game state, scheduling all currently instantiated states for disposal.
			/// </summary>
			void changeState (GameState* state) override;

			/// <summary>
			/// Returns the type of interface which will be used to communicate with this kind of service.
			/// </summary>
			virtual std::type_index getInterfaceType () override;

			/// <summary>
			/// Updates the input handler, handling sdl events.
			/// </summary>
			void handleEvents ();

			/// <summary>
			/// Initializes SDL, the services, and the state machine.
			/// </summary>
			/// <param name="windowTitle">Title for the game window.</param>
			/// <param name="windowSize">Size of the game window.</param>
			bool initialize (std::string windowTitle, Vector2D windowSize);
		
			/// <summary>
			/// Whether the game is still meant to be running.
			/// The game controller should be disposed if it has stopped running.
			/// </summary>
			inline bool isRunning () { return this->running; }

			/// <summary>
			/// Tells the current game state to handle a button click.
			/// </summary>
			/// <param name="buttonIdentifier">The identifier of the clicked button.</param>
			virtual void onPressedButton (std::string buttonIdentifier) override;

			/// <summary>
			/// Returns to the previous state, scheduling the current state for disposal.
			/// </summary>
			virtual void popState () override;

			/// <summary>
			/// Switches to a new state, without disposing the last one.
			/// </summary>
			virtual void pushState (GameState* state) override;

			/// <summary>
			/// Quits the application at the end of the current frame.
			/// </summary>
			virtual void quit () override;

			/// <summary>
			/// Renders the current game state.
			/// </summary>
			void render ();

			/// <summary>
			/// Updates the current game state.
			/// </summary>
			void update ();

		private:
			SDL_Renderer* renderer;
			bool running;
			SDL_Window* window;
			Vector2D windowSize;

			IInputHandler* inputHandler;
			StateMachine* stateMachine;

			/// <summary>
			/// Initializes SDL, creating a game window and renderer.
			/// </summary>
			/// <param name="windowTitle">Title for the game window.</param>
			/// <param name="windowSize">Size of the game window.</param>
			/// <returns>Whether SDL was initialized successfully.</returns>
			bool initializeSDL (std::string windowTitle, Vector2D windowSize);

			/// <summary>
			/// Initializes services, specifically:
			/// an InputHandler, an AudioManager, a RandomGenerator, a TextureManager and a GameObjectFactory.
			/// </summary>
			void initializeServices ();
	};
}