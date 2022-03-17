/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Math/Vector2D.h"
#include <string>
#include <unordered_map>

namespace Challenge {

	class TiledTileData;

	class TiledObject {

		public:
			TiledObject ();
			TiledObject (const TiledObject& object);
			TiledObject (int layer, Vector2D position, Vector2D size);
			TiledObject (int id, int gid, int layer, Vector2D position, Vector2D size, std::string type);

			~TiledObject ();

			/// <summary>
			/// Returns this object's parsed tile data.
			/// </summary>
			TiledTileData* getData ();

			/// <summary>
			/// Returns this object's id.
			/// </summary>
			int getId ();

			/// <summary>
			/// Returns this object's global id.
			/// The global id is used to identify what tileset this object should be getting its data from.
			/// </summary>
			int getGid ();

			/// <summary>
			/// Returns this object's rendering layer index.
			/// </summary>
			int getLayer ();

			/// <summary>
			/// Returns this object's position in world space.
			/// </summary>
			Vector2D getPosition ();

			/// <summary>
			/// Returns the property identified by the provided key.
			/// </summary>
			/// <returns>The property, or an empty string if no property is found.</returns>
			std::string getProperty (std::string key);

			/// <summary>
			/// Returns this object's size in world space.
			/// </summary>
			Vector2D getSize ();

			/// <summary>
			/// Return this object's type.
			/// </summary>
			std::string getType ();

			/// <summary>
			/// Sets this object's parsed tile data.
			/// </summary>
			void setData (TiledTileData* data);

			/// <summary>
			/// Sets this object's rendering layer.
			/// </summary>
			void setLayer (int layer);

			/// <summary>
			/// Sets this object's position in world space.
			/// </summary>
			void setPosition (Vector2D position);

			/// <summary>
			/// Sets a property value for the given key.
			/// </summary>
			void setProperty (std::string key, std::string value);

			/// <summary>
			/// Sets this object's size in world space.
			/// </summary>
			void setSize (Vector2D size);

		private:
			int id;
			TiledTileData* data;
			int gid;
			int layer;

			Vector2D position;

			/// <summary>
			/// Custom properties defined on Tiled.
			/// </summary>
			std::unordered_map<std::string, std::string> properties;

			Vector2D size;
			std::string type;
	};
}