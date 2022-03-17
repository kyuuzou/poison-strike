/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Services/IServiceProvider.h"
#include <string>
#include <unordered_map>

namespace Challenge {

	class GameObject;
	class TiledTileset;
	class TiledObject;

	class IGameObjectFactory : public IServiceProvider {

		public:
			IGameObjectFactory () {};
			virtual ~IGameObjectFactory () {};

			// no copy operations
			IGameObjectFactory (const IGameObjectFactory&) = delete;
			IGameObjectFactory& operator=(const IGameObjectFactory&) = delete;

			// no move operations
			IGameObjectFactory (IGameObjectFactory&&) = delete;
			IGameObjectFactory& operator = (IGameObjectFactory&&) = delete;

			/// <summary>
			/// Spawns a game object based on a parsed Tiled object.
			/// </summary>
			virtual GameObject* spawn (TiledObject* object) = 0;
	};
}
