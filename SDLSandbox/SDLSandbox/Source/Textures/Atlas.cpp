/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Atlas.h"

#include "TextureData.h"
#include <iostream>

#ifdef __APPLE__
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL_image.h>
#endif

using namespace Challenge;
using namespace std;

Atlas::Atlas (string imagePath, SDL_Renderer* renderer) : imagePath (imagePath), texture (nullptr) {
	this->loadTexture (renderer);
}

Atlas::~Atlas () {
	for (auto data : this->textureData) {
		delete data.second;
	}
}

void Atlas::addTextureData (TextureData* textureData) {
	this->textureData[textureData->name] = textureData;
}

TextureData* Atlas::getTextureData (string name) {
	auto iterator = this->textureData.find (name);

	if (iterator == this->textureData.end ()) {
		return nullptr;
	}

	return iterator->second;
}

bool Atlas::loadTexture (SDL_Renderer* renderer) {
	string path = "Assets/Textures/Atlas/" + this->imagePath;
	SDL_Surface* temporarySurface = IMG_Load (path.c_str ());

	if (temporarySurface == NULL) {
		cerr << "Could not load surface: " << SDL_GetError () << endl;
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface (renderer, temporarySurface);
	SDL_FreeSurface (temporarySurface);

	if (texture == NULL) {
		cerr << "Could not create texture: " << SDL_GetError () << endl;
		return false;
	}

	this->texture = texture;

	return true;
}

