/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Services/IServiceProvider.h"

namespace Challenge {

	class IGameplay : public IServiceProvider {

		public:
			IGameplay () {};
			virtual ~IGameplay () {};

			// no copy operations
			IGameplay (const IGameplay&) = delete;
			IGameplay& operator=(const IGameplay&) = delete;

			// no move operations
			IGameplay (IGameplay&&) = delete;
			IGameplay& operator = (IGameplay&&) = delete;

			/// <summary>
			/// Schedules a column increase for when there are no moving boxes.
			/// </summary>
			virtual void scheduleColumnIncrease () = 0;
	};
}