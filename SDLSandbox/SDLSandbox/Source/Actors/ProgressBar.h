/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameObject.h"
#include <map>

namespace Challenge {

	class IGameplay;
	class TiledObject;

	class ProgressBar : public GameObject {

		public:
			ProgressBar ();

			virtual void initialize (TiledObject* data) override;
			virtual void render () override;
			virtual void update () override;

		private:
			IGameplay* gameplay;

			// Progress bars save the width they had on instantiation, and consider it to be their full width.
			// They will always progress from 0 width, to this value.
			float initialWidth;

			virtual std::string type () override {
				return "ProgressBar";
			}
	};
}
