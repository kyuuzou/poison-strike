/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "ISpawner.h"

namespace Challenge {

	class ChopperSpawner : public ISpawner {

		public:
			GameObject* spawn () const override;
	};
}
