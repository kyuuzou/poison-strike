/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#define SHUSH

#include "AudioManager.h"
#include <iostream>

using namespace Challenge;
using namespace std;

AudioManager::AudioManager () : mute (false) {
	this->provideService ();
	this->initialize ();

#ifdef SHUSH
	this->toggleMute ();
#endif
}

AudioManager::~AudioManager () {
	Mix_CloseAudio ();
}

type_index AudioManager::getInterfaceType () {
	return typeid (IAudioManager);
}

void AudioManager::initialize () {
	Mix_OpenAudio (22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_VolumeMusic (20);

	this->loadMusic ("Assets/Audio/Music/spells.mp3", "defaultMusic");

	this->loadSound ("Assets/Audio/Sound/advance.wav", "advance");
	this->loadSound ("Assets/Audio/Sound/Click.wav", "click");
	this->loadSound ("Assets/Audio/Sound/explosion1.wav", "explosion1", 15);
	this->loadSound ("Assets/Audio/Sound/explosion2.wav", "explosion2", 40);
	this->loadSound ("Assets/Audio/Sound/gameover.wav", "gameover");
	this->loadSound ("Assets/Audio/Sound/Hit.wav", "hit");
	this->loadSound ("Assets/Audio/Sound/Jump.wav", "jump");
	this->loadSound ("Assets/Audio/Sound/shooting.aiff", "shooting", 10);
}

void AudioManager::loadMusic (string file, string key) {
    Mix_Music* music = Mix_LoadMUS (file.c_str ());
	
	if (music == 0) {
		cerr << "Could not load music: " << Mix_GetError () << endl;
		return;
	}

	this->music[key] = music;
}

void AudioManager::loadSound (string file, string key, int volume) {
	Mix_Chunk* chunk = Mix_LoadWAV (file.c_str ());

	if (chunk == 0) {
		cerr << "Could not load sound effect: " << Mix_GetError () << endl;
		return;
	}

	Mix_VolumeChunk (chunk, volume);

	this->sound[key] = chunk;
}

void AudioManager::playMusic (string id, bool loop) {
	Mix_PlayMusic (this->music[id], loop ? -1 : 0);
}

void AudioManager::playSound (string id, bool loop) {
	Mix_PlayChannel (-1, this->sound[id], loop ? -1 : 0);
}

void AudioManager::toggleMute () {
	this->mute = ! this->mute;

	Mix_Volume (-1, this->mute ? 0 : 128);
	Mix_VolumeMusic (this->mute ? 0 : 20);
}