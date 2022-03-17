/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Gameplay/Color.h"

namespace Challenge {

	class Cell;

	class IInhabitant {
		
		public:
			IInhabitant () {};
			virtual ~IInhabitant () {};

			// no copy operations
			IInhabitant (const IInhabitant&) = delete;
			IInhabitant& operator=(const IInhabitant&) = delete;

			// no move operations
			IInhabitant (IInhabitant&&) = delete;
			IInhabitant& operator = (IInhabitant&&) = delete;

			/// <summary>
			/// Schedules this game object for disposal.
			/// </summary>
			virtual void die () = 0;

			/// <summary>
			/// Returns this game object's color identifier.
			/// </summary>
			virtual Color getColor () = 0;

			virtual Cell* getCurrentCell () = 0;

			/// <summary>
			/// Whether this game object is currently busy.
			/// The definition of "busy" may change depending on the type of inhabitant.
			/// </summary>
			virtual bool isBusy () = 0;

			/// <summary>
			/// Whether this game object is scheduled for disposal.
			/// </summary>
			virtual bool isDead () = 0;

			virtual void setCurrentCell (Cell* cell) = 0;
	};
}
