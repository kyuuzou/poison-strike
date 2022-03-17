/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "TiledTileData.h"
#include "../Math/Vector2D.h"
#include <iostream>

namespace Challenge {

	class TiledTileset {

		public:
			TiledTileset (int firstGid);

			/// <summary>
			/// Adds parsed tile data to this tileset.
			/// </summary>
			void addTile (TiledTileData* tileData);

			/// <summary>
			/// Returns the tile data identified by the provided global id.
			/// </summary>
			TiledTileData* getData (int gid);

			/// <summary>
			/// Returns the first global id contained by this tileset.
			/// </summary>
			int getFirstGid ();

		private:
			/// <summary>
			/// The first id on this tileset. Tiles must figure out what tileset
			/// they should be getting their info from, based on their id.
			/// </summary>
			int firstGid;

			std::unordered_map <int, TiledTileData*> tiles;
	};
}
