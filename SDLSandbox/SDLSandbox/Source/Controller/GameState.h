/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "../Tiled/TiledState.h"

namespace Challenge {

	class GameObject;

	class GameState {

		public:
			GameState ();
			virtual ~GameState ();

			// no copy operations
			GameState (const GameState&) = delete;
			GameState& operator=(const GameState&) = delete;

			// no move operations
			GameState (GameState&&) = delete;
			GameState& operator = (GameState&&) = delete;

			/// <summary>
			/// Adds a new game object to this game state.
			/// </summary>
			void addGameObject (GameObject* gameObject);

			/// <summary>
			/// Returns the name of a Tiled TMX file, that represents a game state.
			/// </summary>
			virtual std::string getStateFile () const = 0;

			/// <summary>
			/// Returns an identifier for this state.
			/// </summary>
			virtual std::string getStateID () const = 0;

			/// <summary>
			/// Parses the state file, and spawns the parsed game objects.
			/// </summary>
			virtual bool onEnter ();

			/// <summary>
			/// Cleans up any loose ends before leaving the state.
			/// </summary>
			virtual bool onExit ();

			/// <summary>
			/// Checks if there is a callback for the button identified by the provided key, and if so, invokes it.
			/// </summary>
			/// <param name="key">Button identifier.</param>
			virtual void onPressedButton (std::string key);

			/// <summary>
			/// Renders this state's game objects.
			/// </summary>
			virtual void render ();

			/// <summary>
			/// Updates this state's game objects.
			/// </summary>
			virtual void update ();

		protected:
			/// <summary>
			/// Adds a callback for a button identified by the provided key.
			/// </summary>
			/// <param name="key">Button identifier.</param>
			/// <param name="callback">Callback for the button.</param>
			void addCallback (std::string key, std::function<void ()> callback);

			/// <summary>
			/// Returns all game objects of the provided type.
			/// </summary>
			std::vector<GameObject*> getGameObjects (std::string type);

			/// <summary>
			/// Spawns all the parsed game objects.
			/// </summary>
			virtual void spawnObjects ();

		private:
			std::unordered_map<std::string, std::function<void ()>> callbacks;
			std::map<int, std::vector<GameObject*>> gameObjectsByLayer;
			std::unordered_map<std::string, std::vector<GameObject*>> gameObjectsByType;
			std::unique_ptr<TiledState> stateData;

			/// <summary>
			/// Removes game object from its rendering layer.
			/// </summary>
			void removeObjectFromLayer (GameObject* gameObject);
	};
}
