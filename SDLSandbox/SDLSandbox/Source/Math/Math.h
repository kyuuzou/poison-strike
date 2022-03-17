/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <algorithm>

namespace Challenge {

	class Math {

		public:

			/// <summary>
			/// Moves the provided value towards the destination, at a given speed.
			/// </summary>
			/// <param name="value">Current value.</param>
			/// <param name="origin">Where the value came from.</param>
			/// <param name="destination">Where the value is going.</param>
			/// <param name="speed">Speed at which the value should change.</param>
			/// <returns>The new value.</returns>
			static float moveTowards (float value, float origin, float destination, float speed) {
                float totalDistance = std::abs (destination - origin);
                float currentDistance = std::abs (destination - value);
				float delta = 1.0f - (currentDistance / totalDistance);

				delta = std::min (delta + speed, 1.0f);

				return origin + delta * (destination - origin);
			}
	};
}