/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Math/Vector2D.h"
#include <string>

namespace Challenge {

	struct TextureData {
		std::string name;

		Vector2D position;
		Vector2D size;
	};
}