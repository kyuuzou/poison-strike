/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Math/Vector2D.h"
#include <map>

namespace Challenge {

	enum class Direction { North, East, South, West};

	class DirectionOffset {

		public:
			/// <summary>
			/// Returns a vector in 2D space corresponding to the provided direction.
			/// </summary>
			Vector2D operator () (Direction direction) {
				auto iterator = DirectionOffset::offsetPerDirection.find (direction);

				if (iterator != DirectionOffset::offsetPerDirection.end ()) {
					return iterator->second;
				}

				return Vector2D (0, 0);
			}

		private:
			static const std::map<Direction, Vector2D> offsetPerDirection;
	};
}
