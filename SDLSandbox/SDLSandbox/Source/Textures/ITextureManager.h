/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Gameplay/Color.h"
#include "../Services/IServiceProvider.h"
#include <string>

namespace Challenge {

	class Vector2D;

	class ITextureManager : public IServiceProvider {

		public:
			ITextureManager () {};
			virtual ~ITextureManager () {};

			// no copy operations
			ITextureManager (const ITextureManager&) = delete;
			ITextureManager& operator=(const ITextureManager&) = delete;

			// no move operations
			ITextureManager (ITextureManager&&) = delete;
			ITextureManager& operator = (ITextureManager&&) = delete;

			/// <summary>
			/// Renders a specific frame, based on its atlas and texture ID. 
			/// </summary>
			/// <param name="atlasID">Atlas identifier.</param>
			/// <param name="textureID">Texture identifier.</param>
			/// <param name="position">Position where it should be rendered.</param>
			/// <param name="size">The size at which it should be rendered.</param>
			/// <param name="angle">The rotation in Z.</param>
			/// <param name="color">What color it should be.</param>
			virtual void renderFrame (
				std::string atlasID,
				std::string textureID,
				Vector2D position,
				Vector2D size,
				double angle,
				SDL_Color color
			) = 0;
	};
}
