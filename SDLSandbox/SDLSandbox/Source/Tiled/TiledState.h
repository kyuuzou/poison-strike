/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace Challenge {

	class TiledObject;
	class TiledTileset;

	class TiledState {

		public:
			TiledState();
			~TiledState();

			/// <summary>
			/// Adds a parsed Tiled object.
			/// </summary>
			void addObject (TiledObject* object);

			/// <summary>
			/// Adds a parsed Tiled tileset.
			/// </summary>
			void addTileset (TiledTileset* tileset);

			/// <summary>
			/// Returns this state's spawned Tiled's objects.
			/// </summary>
			std::vector<TiledObject*>& getObjects () {
				return this->objects;
			}

		private:
			std::vector<TiledObject*> objects;
			std::vector<TiledTileset*> tilesets;

			/// <summary>
			/// Finds the appropriate tileset for the provided global id.
			/// </summary>
			/// <param name="gid">The global id.</param>
			/// <returns>The tileset.</returns>
			TiledTileset* findTileset (int gid);
	};
}
