/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "TiledState.h"

class TiXmlElement;

namespace Challenge {

	class TiledTileData;

	class TiledParser {

		public:
			TiledParser ();

			/// <summary>
			/// Parses an uncompressed Tiled file, and stores its contents on a TiledState.
			/// </summary>
			/// <param name="file">Uncompressed Tiled file.</param>
			/// <returns>The parsed state.</returns>
			std::unique_ptr<TiledState> parse (std::string file);

		private:
			static int currentLayerIndex;

			/// <summary>
			/// The parser function for each kind of element.
			/// </summary>
			std::unordered_map<std::string, std::function<void(TiXmlElement*, TiledState* state)>> elementParsers;

			/// <summary>
			/// Parses a object layer, and tells the factory to spawn its elements.
			/// </summary>
			/// <param name="element">The root element of a object layer.</param>
			/// <param name="state">The game state to which the spawned elements will be added.</param>
			/// <returns></returns>
			static void parseObjectLayer (TiXmlElement* element, TiledState* state);

			/// <summary>
			/// Parses an element with custom properties, defined on Tiled.
			/// </summary>
			/// <param name="element">The root element of a properties list.</param>
			/// <returns>The custom properties.</returns>
			static std::unordered_map<std::string, std::string> parsePropertiesElement (TiXmlElement* element);

			/// <summary>
			/// Parses an element with tile data, defined on Tiled.
			/// </summary>
			/// <param name="element">The root element of data about a tile.</param>
			/// <returns>The parsed tile data.</returns>
			static TiledTileData* parseTileData (TiXmlElement* element);

			/// <summary>
			/// Parses a tileset and adds it to the factory.
			/// </summary>
			/// <param name="element">The root element of a tileset.</param>
			/// <param name="state">The game state to which the spawned tileset will be added.</param>
			static void parseTileset (TiXmlElement* element, TiledState* state);

			/// <summary>
			/// Prints indeterminate number of arguments to the console, separated by spaces.
			/// </summary>
			template<typename T, typename... Tail>
			static void printToConsole (T head, Tail... tail);

			/// <summary>
			/// Adds a new line after printing indeterminate amount of arguments.
			/// </summary>
			static void printToConsole ();
	};
}
