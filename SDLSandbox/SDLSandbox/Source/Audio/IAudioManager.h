/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Services/IServiceProvider.h"
#include <string>

namespace Challenge {

	class IAudioManager : public IServiceProvider {

		public:
			IAudioManager () {};
			virtual ~IAudioManager () {};

			// no copy operations
			IAudioManager (const IAudioManager&) = delete;
			IAudioManager& operator=(const IAudioManager&) = delete;

			// no move operations
			IAudioManager (IAudioManager&&) = delete;
			IAudioManager& operator = (IAudioManager&&) = delete;

			/// <summary>
			/// Loads a music file, and associates it with the provided key.
			/// </summary>
			/// <param name="file">The file.</param>
			/// <param name="key">The key which will identify this music.</param>
			virtual void playMusic (std::string id, bool loop = true) = 0;

			/// <summary>
			/// Loads a sound file, and associates it with the provided key.
			/// </summary>
			/// <param name="file">The file.</param>
			/// <param name="key">The key which will identify this sound.</param>
			/// <param name="volume">The base volume the sound should be loaded with.</param>
			virtual void playSound (std::string id, bool loop = false) = 0;

			/// <summary>
			/// Toggles whether the sound and music are muted.
			/// </summary>
			virtual void toggleMute () = 0;
	};
}
