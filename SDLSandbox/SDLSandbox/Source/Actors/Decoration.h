/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameObject.h"
#include <map>

namespace Challenge {

	class TiledObject;

	class Decoration : public GameObject {

		public:
			Decoration ();

			virtual void initialize (TiledObject* data) override;
			virtual void render () override;
			virtual void update () override;

		private:

			virtual std::string type () override {
				return "Decoration";
			}
	};
}
