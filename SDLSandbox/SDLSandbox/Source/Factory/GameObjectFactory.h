/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "IGameObjectFactory.h"
#include "../Tiled/TiledTileset.h"

#include <map>
#include <string>
#include <typeindex>
#include <vector>

namespace Challenge {

	class ISpawner;
	class GameObject;

	class GameObjectFactory : public IGameObjectFactory {

		public:
			GameObjectFactory ();

			/// <summary>
			/// Returns the type of interface which will be used to communicate with this kind of service.
			/// </summary>
			virtual std::type_index getInterfaceType () override;

			/// <summary>
			/// Spawns a game object based on a parsed Tiled object.
			/// </summary>
			virtual GameObject* spawn (TiledObject* object) override;

		private:
			std::map<std::string, ISpawner*> spawners;
			std::vector<TiledTileset*> tilesets;

			/// <summary>
			/// Creates a game object, based on its type and properties.
			/// </summary>
			/// <param name="object">The object data.</param>
			/// <returns>The game object.</returns>
			GameObject* createGameObject (std::string type);

			/// <summary>
			/// Registers all the game object spawners.
			/// </summary>
			void initialize ();

			/// <summary>
			/// Registers a specific spawner for the provided type of game object.
			/// </summary>
			/// <param name="type">Type of game object.</param>
			/// <param name="Spawner">Spawner class.</param>
			/// <returns>Whether the spawner was registered successfully.</returns>
			bool registerSpawner (std::string type, ISpawner* spawner);
	};
}