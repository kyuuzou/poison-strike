/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "ITextureManager.h"
#include "../Math/Vector2D.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

struct SDL_Renderer;

namespace Challenge {

	class Atlas;

	class TextureManager : public ITextureManager {

		public:
			TextureManager ();
			~TextureManager ();

			/// <summary>
			/// Returns the type of interface which will be used to communicate with this kind of service.
			/// </summary>
			virtual std::type_index getInterfaceType () override {
				return typeid (ITextureManager);
			}

			/// <summary>
			/// Parses all the atlases.
			/// </summary>
			void initialize (SDL_Renderer* renderer);

			/// <summary>
			/// Renders a specific frame, based on its atlas and texture ID. 
			/// </summary>
			/// <param name="atlasID">Atlas identifier.</param>
			/// <param name="textureID">Texture identifier.</param>
			/// <param name="position">Position where it should be rendered.</param>
			/// <param name="size">The size at which it should be rendered.</param>
			/// <param name="angle">The rotation in Z.</param>
			/// <param name="color">What color it should be.</param>
			void renderFrame (
				std::string atlasID,
				std::string textureID,
				Vector2D position,
				Vector2D size,
				double angle,
				SDL_Color color
			) override;

		private:
			SDL_Renderer* renderer;
			std::unordered_map<std::string, Atlas*> atlases;

			/// <summary>
			/// Returns the atlas identified by the atlas ID.
			/// </summary>
			Atlas* getAtlas (std::string atlasID);

			/// <summary>
			/// Parses the atlas at the provided path.
			/// </summary>
			void parseAtlas (std::string path);

			/// <summary>
			/// Parses all the atlases.
			/// </summary>
			void parseAtlases ();
	};
}
