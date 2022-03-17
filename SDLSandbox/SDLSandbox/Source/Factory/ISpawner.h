/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

namespace Challenge {

	class GameObject;

	class ISpawner {

		public:
			ISpawner () {};
			virtual ~ISpawner () {};

			// no copy operations
			ISpawner (const ISpawner&) = delete;
			ISpawner& operator=(const ISpawner&) = delete;

			// no move operations
			ISpawner (ISpawner&&) = delete;
			ISpawner& operator = (ISpawner&&) = delete;

			/// <summary>
			/// Spawns a game object.
			/// This method is invoked by the game object factory when attempting to create a game object of a 
			/// specific type.
			/// </summary>
			virtual GameObject* spawn () const = 0;
	};
}
