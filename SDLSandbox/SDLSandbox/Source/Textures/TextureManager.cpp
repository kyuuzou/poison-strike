/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "TextureManager.h"

#include "Atlas.h"
#include "TextureData.h"
#include "../Libraries/TinyXML/tinyxml.h"

#ifdef __APPLE__
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL_image.h>
#endif

using namespace Challenge;
using namespace std;

TextureManager::TextureManager () : renderer (nullptr) {
	this->provideService ();
}

TextureManager::~TextureManager () {
	for (auto iterator : this->atlases) {
		delete iterator.second;
	}
}

Atlas* TextureManager::getAtlas (string atlasID) {
	auto atlasIterator = this->atlases.find (atlasID);

	if (atlasIterator == this->atlases.end ()) {
		return nullptr;
	}

	return atlasIterator->second;
}

void TextureManager::initialize (SDL_Renderer* renderer) {
	this->renderer = renderer;

	this->parseAtlases ();
}

void TextureManager::parseAtlas (string file) {
	cout << "Parsing atlas" << endl;

	TiXmlDocument levelDocument;
    
	if (! levelDocument.LoadFile (file)) {
		cerr << "Could not load file: " << file << endl;
		return;
	}

	TiXmlElement* root = levelDocument.RootElement ();
	
	Atlas* atlas = new Atlas (root->Attribute ("imagePath"), this->renderer);

	for (
		TiXmlElement* child = root->FirstChildElement ();
		child != nullptr;
		child = child->NextSiblingElement ()
	) {
		TextureData* textureData = new TextureData ();
		
		int x, y, width, height;

		child->QueryStringAttribute ("n", &textureData->name);
		child->QueryIntAttribute ("x", &x);
		child->QueryIntAttribute ("y", &y);
		child->QueryIntAttribute ("w", &width);
		child->QueryIntAttribute ("h", &height);

		textureData->position.set (x, y);
		textureData->size.set (width, height);

		atlas->addTextureData (textureData);
	}

	this->atlases[atlas->getImagePath ()] = atlas;
}

void TextureManager::parseAtlases () {
	// TODO: Detect all xml files on the atlas folder, and parse them automatically
	this->parseAtlas ("Assets/Textures/Atlas/atlas.xml");
}

void TextureManager::renderFrame (
	string atlasID,
	string textureID,
	Vector2D position,
	Vector2D size,
	double angle,
	SDL_Color color
) {
	if (atlasID.length () == 0 || textureID.length () == 0) {
		return;
	}

	Atlas* atlas = this->getAtlas (atlasID);

	if (atlas == nullptr) {
		return;
	}
	
	SDL_Texture* texture = atlas->getTexture ();
	TextureData* textureData = atlas->getTextureData (textureID);

	if (textureData == nullptr) {
		return;
	}

	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;

	sourceRectangle.x = (int) textureData->position.getX ();
	sourceRectangle.y = (int) textureData->position.getY ();
	sourceRectangle.w = destinationRectangle.w = (int) textureData->size.getX ();
	sourceRectangle.h = destinationRectangle.h = (int) textureData->size.getY ();

	destinationRectangle.x = (int) position.getX ();
	destinationRectangle.y = (int) position.getY ();
	destinationRectangle.w = (int) size.getX ();
	destinationRectangle.h = (int) size.getY ();

	SDL_SetTextureColorMod (texture, (Uint8) color.r, (Uint8) color.g, (Uint8) color.b);

	SDL_RenderCopyEx (
		this->renderer,
		texture,
		&sourceRectangle,
		&destinationRectangle,
		angle,
		0,
		SDL_FLIP_NONE
	);
}
