/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "IAudioManager.h"

#include <map>

#ifdef __APPLE__
    #include <SDL2_mixer/SDL_mixer.h>
#else
    #include <SDL_mixer.h>
#endif

namespace Challenge {

	class AudioManager : public IAudioManager {

		public:
			AudioManager ();
			~AudioManager ();

			/// <summary>
			/// Returns the type of interface which will be used to communicate with this kind of service.
			/// </summary>
			std::type_index getInterfaceType ();

			/// <summary>
			/// Plays the music associated with the provided id.
			/// </summary>
			/// <param name="id">Music identifier.</param>
			/// <param name="loop">Whether the music should keep looping forever.</param>
			void playMusic (std::string id, bool loop = true);

			/// <summary>
			/// Plays the sound associated with the provided id.
			/// </summary>
			/// <param name="id">Sound identifier.</param>
			/// <param name="loop">Whether the sound should keep looping forever.</param>
			void playSound (std::string id, bool loop = false);

		private:
			bool mute;
			std::map<std::string, Mix_Chunk*> sound;
			std::map<std::string, Mix_Music*> music;

			/// <summary>
			/// Loads all the music tracks and sounds.
			/// </summary>
			void initialize ();

			/// <summary>
			/// Loads a music file, and associates it with the provided key.
			/// </summary>
			/// <param name="file">The file.</param>
			/// <param name="key">The key which will identify this music.</param>
			void loadMusic (std::string file, std::string key);

			/// <summary>
			/// Loads a sound file, and associates it with the provided key.
			/// </summary>
			/// <param name="file">The file.</param>
			/// <param name="key">The key which will identify this sound.</param>
			/// <param name="volume">The base volume the sound should be loaded with.</param>
			void loadSound (std::string file, std::string key, int volume = 30);

			/// <summary>
			/// Toggles whether the sound and music are muted.
			/// </summary>
			void toggleMute ();
	};
}
