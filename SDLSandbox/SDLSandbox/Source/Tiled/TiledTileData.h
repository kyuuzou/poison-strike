/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <string>
#include <unordered_map>

namespace Challenge {

	class TiledTileData {

		public:
			TiledTileData (int gid);

			TiledTileData (const TiledTileData& data);

			/// <summary>
			/// Returns this data's global id.
			/// </summary>
			int getGid ();

			/// <summary>
			/// Returns a property, after converting it to int.
			/// </summary>
			/// <param name="key">Key that identifies the property.</param>
			/// <returns>The property value, or the default value if the property is invalid.</returns>
			int getIntProperty (std::string key, int defaultValue);

			/// <summary>
			/// Returns a property identified by the provided key.
			/// </summary>
			std::string getProperty (std::string key);

			/// <summary>
			/// Sets a property value, identified by the provided key.
			/// </summary>
			void setProperty (std::string key, std::string value);

		private:
			int gid;

			/// <summary>
			/// Custom properties defined on Tiled.
			/// </summary>
			std::unordered_map<std::string, std::string> properties;
	};
}