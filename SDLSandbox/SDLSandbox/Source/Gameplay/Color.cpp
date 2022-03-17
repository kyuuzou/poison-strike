/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Color.h"

using namespace Challenge;
using namespace std;

const unordered_map<string, Color> ColorFromString::colorByName = {
	{ "White",		Color::White },
	{ "Blue",		Color::Blue },
	{ "Green",		Color::Green },
	{ "Pink",		Color::Pink },
	{ "Red",		Color::Red },
	{ "Yellow",		Color::Yellow },
	{ "DarkGreen",  Color::DarkGreen },
	{ "DarkGrey",	Color::DarkGrey },
	{ "DarkPurple",	Color::DarkPurple },
	{ "Black",		Color::Black }
};

const map<Color, SDL_Color> ColorFromIdentifier::colorByIdentifier = {
	{ Color::White,		SDL_Color { 255, 255, 255 }},
	{ Color::Blue,		SDL_Color { 100, 100, 255 }},
	{ Color::Green,		SDL_Color { 0,	 255,   0 }},
	{ Color::Pink,		SDL_Color { 255,   0, 255 }},
	{ Color::Red,			SDL_Color { 255,   0,   0 }},
	{ Color::Yellow,		SDL_Color { 255, 255,   0 }},
	{ Color::DarkGreen,	SDL_Color { 0,   180,   0 }},
	{ Color::DarkGrey,	SDL_Color { 50,   50,  50 }},
	{ Color::DarkPurple,	SDL_Color { 100,  50, 200 }},
	{ Color::Black,		SDL_Color { 0,     0,   0 }}
};
