/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <string>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;

namespace Challenge {

	struct TextureData;

	class Atlas {

		public:
			Atlas (std::string imagePath, SDL_Renderer* renderer);
			~Atlas();

			/// <summary>
			/// Adds data about a parsed TexturePacker texture.
			/// </summary>
			void addTextureData (TextureData* textureData);

			/// <summary>
			/// Returns the imagePath where the atlas texture is located.
			/// </summary>
			inline std::string getImagePath () {
				return this->imagePath;
			}

			/// <summary>
			/// Returns the atlas' SDL texture.
			/// </summary>
			SDL_Texture* getTexture () {
				return this->texture;
			}

			/// <summary>
			/// Returns the parsed TexturePacker texture data associated with the provided name.
			/// </summary>
			TextureData* getTextureData (std::string name);

		private:
			std::string imagePath;
			SDL_Texture* texture;
			std::unordered_map<std::string, TextureData*> textureData;

			/// <summary>
			/// Load this atlas' SDL texture.
			/// </summary>
			bool loadTexture (SDL_Renderer* renderer);
	};
}
