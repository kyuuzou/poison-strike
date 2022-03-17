/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Services/IServiceProvider.h"
#include <random>

namespace Challenge {

	class IRandomGenerator : public IServiceProvider {

		public:
			IRandomGenerator () {};
			virtual ~IRandomGenerator () {};

			// no copy operations
			IRandomGenerator (const IRandomGenerator&) = delete;
			IRandomGenerator& operator=(const IRandomGenerator&) = delete;

			// no move operations
			IRandomGenerator (IRandomGenerator&&) = delete;
			IRandomGenerator& operator = (IRandomGenerator&&) = delete;

			/// <summary>
			/// Returns a random number between minimum and maximum (inclusive).
			/// </summary>
			virtual int getRandom (int minimum, int maximum) = 0;
	};
}