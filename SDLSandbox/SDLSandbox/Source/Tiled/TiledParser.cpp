/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

//#define VERBOSE

#include "TiledParser.h"

#include "TiledObject.h"
#include "TiledTileset.h"
#include "../Libraries/TinyXML/tinyxml.h"
#include "../Services/ServiceLocator.h"

using namespace Challenge;
using namespace std;

int TiledParser::currentLayerIndex;

TiledParser::TiledParser () : elementParsers () {
	// Map the parser function for each kind of element
	this->elementParsers["objectgroup"] = &TiledParser::parseObjectLayer;
	this->elementParsers["tileset"] = &TiledParser::parseTileset;
}
	
unique_ptr<TiledState> TiledParser::parse (string file) {
	TiXmlDocument levelDocument;
	
	if (! levelDocument.LoadFile (file)) {
		cerr << "Could not load file: " << file << endl;
		return nullptr;
	}

	TiledParser::currentLayerIndex = 0;

    unique_ptr<TiledState> state = make_unique<TiledState> ();
	TiXmlElement* root = levelDocument.RootElement ();

	for (
		TiXmlElement* element = root->FirstChildElement ();
		element != nullptr;
		element = element->NextSiblingElement ()
	) {
		// Checks if there's a parser for this type of element
		auto parserIterator = this->elementParsers.find (element->Value ());

		if (parserIterator == this->elementParsers.end ()) {
			cerr << "Could not parse element, type not supported: " << element->Value () << endl;
			continue;
		}

		this->elementParsers[element->Value ()] (element, state.get ());
	}
	
	return state;
}

void TiledParser::parseObjectLayer (TiXmlElement* element, TiledState* state) {
	for (
		TiXmlElement* objectElement = element->FirstChildElement ();
		objectElement != nullptr;
		objectElement = objectElement->NextSiblingElement ()
	) {
		int id, gid, layer, x, y, width, height;
		string type;

		objectElement->QueryStringAttribute ("type", &type);

		if (type.length () == 0) {
			cerr << "Could not parse object: Empty type." << endl;
			continue;
		}

		layer = TiledParser::currentLayerIndex;

		objectElement->QueryIntAttribute ("id", &id);
		objectElement->QueryIntAttribute ("gid", &gid);
		objectElement->QueryIntAttribute ("x", &x);
		objectElement->QueryIntAttribute ("y", &y);
		objectElement->QueryIntAttribute ("width", &width);
		objectElement->QueryIntAttribute ("height", &height);

		// Because Tiled sets the sprite pivot to the bottom left corner
		y -= height;

		TiledParser::printToConsole (
			"[Object]",
			"\nid:", id,
			"\ngid:", gid,
			"\ntype:", type,
			"\nx:", x,
			"\ny:", y,
			"\nwidth:", width,
			"\nheight:", height
		);

		TiledObject* object = new TiledObject (id, gid, layer, Vector2D (x, y), Vector2D (width, height), type);
		
		auto properties = TiledParser::parsePropertiesElement (objectElement->FirstChildElement ());

		for (auto property : properties) {
			object->setProperty (property.first, property.second);
		}

		state->addObject (object);
	}

	TiledParser::currentLayerIndex ++;
}
		
unordered_map<string, string> TiledParser::parsePropertiesElement (TiXmlElement* element) {
	unordered_map<string, string> properties;

	TiledParser::printToConsole ("[Properties]");

	for (
		TiXmlElement* sibling = element;
		sibling != nullptr;
		sibling = sibling->NextSiblingElement ()
	) {
		for (
			TiXmlElement* property = sibling->FirstChildElement ();
			property != nullptr;
			property = property->NextSiblingElement ()
		) {
			if (property->Value () == string ("property")) {
				properties[property->Attribute ("name")] = property->Attribute ("value");

				TiledParser::printToConsole (property->Attribute ("name"), ":", property->Attribute ("value"));
			}
		}
	}

	return properties;
}

TiledTileData* TiledParser::parseTileData (TiXmlElement* element) {
	int gid;
	element->QueryIntAttribute ("id", &gid);

	TiledTileData* tileData = new TiledTileData (gid);

	for (
		TiXmlElement* child = element->FirstChildElement ();
		child != nullptr;
		child = child->NextSiblingElement ()
	) {
		if (child->Value () == string ("properties")) {
			auto properties = TiledParser::parsePropertiesElement (child);

			for (auto property : properties) {
				tileData->setProperty (property.first, property.second);
			}
		}
	}

	return tileData;
}

void TiledParser::parseTileset (TiXmlElement* element, TiledState* state) {
	int firstGid;

	element->QueryIntAttribute ("firstgid", &firstGid);

	TiledTileset* tileset = new TiledTileset (firstGid);

	for (
		TiXmlElement* child = element->FirstChildElement ();
		child != nullptr;
		child = child->NextSiblingElement ()
	) {
		TiledTileData* tileData = TiledParser::parseTileData (child);
		tileset->addTile (tileData);
	}

	TiledParser::printToConsole (
		"[TiledTileset]",
		"\nfirstGid:", tileset->getFirstGid ()
	);

	state->addTileset (tileset);
}

// Disables the "unreferenced formal parameter" warning for when VERBOSE is not defined
#pragma warning (push)
#pragma warning (disable : 4100)
template<typename T, typename... Tail>
void TiledParser::printToConsole (T head, Tail... tail) {
#ifdef VERBOSE
	cout << head << " ";

	TiledParser::printToConsole (tail...);
#endif
}
	
void TiledParser::printToConsole() {
#ifdef VERBOSE
	cout << "\n" << endl;
#endif
}

#pragma warning (pop)
