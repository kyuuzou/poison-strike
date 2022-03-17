/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <map>
#include <string>
#include <unordered_map>

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

namespace Challenge {

	enum class Color { White, Blue, Green, Pink, Red, Yellow, DarkGreen, DarkGrey, DarkPurple, Black };

	class ColorFromString {

		public:
			/// <summary>
			/// Returns a specific Color based on a parsed color name.
			/// </summary>
			Color operator () (std::string colorName) {
				auto iterator = ColorFromString::colorByName.find (colorName);

				if (iterator != ColorFromString::colorByName.end ()) {
					return iterator->second;
				}

				return Color::White;
			}

		private:
			static const std::unordered_map<std::string, Color> colorByName;
	};


	class ColorFromIdentifier {

		public:
			/// <summary>
			/// Returns an SDL color based on a color identifier.
			/// </summary>
			SDL_Color operator () (Color identifier) {
				auto iterator = ColorFromIdentifier::colorByIdentifier.find (identifier);

				if (iterator != ColorFromIdentifier::colorByIdentifier.end ()) {
					return iterator->second;
				}

				return ColorFromIdentifier::colorByIdentifier.at (Color::White);
			}

		private:
			static const std::map<Color, SDL_Color> colorByIdentifier;
	};
}