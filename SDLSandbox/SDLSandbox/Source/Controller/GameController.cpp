/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "GameController.h"

#include "GameOverState.h"
#include "MainMenuState.h"
#include "../Audio/AudioManager.h"
#include "../Factory/GameObjectFactory.h"
#include "../Input/InputHandler.h"
#include "../Math/RandomGenerator.h"
#include "../Textures/TextureManager.h"

#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
#endif

using namespace Challenge;
using namespace std;

GameController::GameController () :
	inputHandler (nullptr),
	renderer (nullptr),
	running (false),
	stateMachine (nullptr),
	window (nullptr),
	windowSize (640, 480)
{
	this->provideService ();
}

GameController::~GameController () {
	SDL_DestroyWindow (this->window);
	SDL_DestroyRenderer (this->renderer);
	SDL_Quit ();
}

void GameController::changeState (GameState* state) {
	this->stateMachine->changeState (state);
}

type_index GameController::getInterfaceType () {
	return typeid (IGameController);
}

void GameController::handleEvents () {
	this->inputHandler->handleEvents ();
}

bool GameController::initialize (string windowTitle, Vector2D windowSize) {
	if (! this->initializeSDL (windowTitle, windowSize)) {
		return false;
	}

	this->initializeServices ();

	this->stateMachine = new StateMachine ();
	this->stateMachine->changeState (new MainMenuState ());

	this->running = true;

	return true;
}

bool GameController::initializeSDL (string windowTitle, Vector2D windowSize) {
	// Initialize SDL
	if (SDL_Init (SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		cerr << "Could not initialize SDL: " << SDL_GetError () << endl;
		return false;
	}

	// Create window
	this->window = SDL_CreateWindow (
		windowTitle.c_str (),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		(int) windowSize.getX (),
		(int) windowSize.getY (),
		SDL_WINDOW_SHOWN
	);

	this->windowSize = windowSize;

	if (this->window == NULL) {
		cerr << "Could not create window: " << SDL_GetError () << endl;
		return false;
	}

	// Create renderer
	this->renderer = SDL_CreateRenderer (this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (this->renderer == NULL) {
		cerr << "Could not create renderer: " << SDL_GetError () << endl;
		return false;
	}

	cout << "Initialized SDL successfully." << endl;

	return true;
}

void GameController::initializeServices () {
	this->inputHandler = new InputHandler ();

	new RandomGenerator ();

	AudioManager* audioManager = new AudioManager ();
	audioManager->playMusic ("defaultMusic");

	TextureManager* textureManager = new TextureManager ();
	textureManager->initialize (this->renderer);

	new GameObjectFactory ();
}

void GameController::onPressedButton (string buttonIdentifier) {
	this->stateMachine->getCurrentState ()->onPressedButton (buttonIdentifier);
}

void GameController::popState () {
	this->stateMachine->popState ();
}

void GameController::pushState (GameState* state) {
	this->stateMachine->pushState (state);
}

void GameController::quit () {
	this->running = false;
}

void GameController::render () {
	if (SDL_RenderClear (this->renderer) < 0) {
		cerr << "Could not clear rendering target: " << SDL_GetError () << endl;
	}

	this->stateMachine->render ();

	SDL_RenderPresent (this->renderer);
}

void GameController::update () {
	this->stateMachine->update ();
}
