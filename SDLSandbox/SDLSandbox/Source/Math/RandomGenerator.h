/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "IRandomGenerator.h"
#include <random>

namespace Challenge {
	
	class RandomGenerator : public IRandomGenerator {

		public:
			RandomGenerator();
			~RandomGenerator();

			/// <summary>
			/// Returns the type of interface which will be used to communicate with this kind of service.
			/// </summary>
			std::type_index getInterfaceType ();

			/// <summary>
			/// Returns a random number between minimum and maximum (inclusive).
			/// </summary>
			int getRandom (int minimum, int maximum);

		private:
			std::random_device device;

			// Mersenne Twister engine
			std::mt19937 engine;

			std::uniform_int_distribution<int> distribution { 0, 100 };
	};
}
