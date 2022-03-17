/* 
 * Miniclip Challenge: Poison Strike
 * @author Nelson Rodrigues
 */

#include "Controller/GameController.h"

#ifdef __APPLE__
    #include <SDL2/SDL.h>
	#include <mach-o/dyld.h>
	#include <unistd.h>
#else
    #include <SDL.h>
#endif

const int framerate = 60;
constexpr int deltaTime = 1000 / framerate;

using namespace Challenge;

// Disables the "unreferenced formal parameter" warning for argc and args
#pragma warning (push)
#pragma warning (disable : 4100)

int main (int argc, char* args[]) {
#if __APPLE__
	// Sets working directory to the same folder as the executable
	// TODO: Automate bundle creation so this becomes unnecessary
	char executablePath[1024];
	uint32_t size = sizeof (executablePath);

	if (_NSGetExecutablePath (executablePath, &size) == 0) {
        std::string surplus = "/Challenge";
        std::string path = std::string (executablePath);
		path.replace (path.length () - surplus.length(), surplus.length (), "");
		chdir (path.c_str ());
	}
#endif

	GameController* gameController = new GameController ();

	if (! gameController->initialize ("Challenge!", Vector2D (640, 480))) {
		return -1;
	}

	Uint32 frameStart, frameElapsed;

	while (gameController->isRunning ()) {
		frameStart = SDL_GetTicks ();

		gameController->handleEvents ();
		gameController->render ();
		gameController->update ();

		// Cap the framerate
		frameElapsed = SDL_GetTicks() - frameStart;

		if (frameElapsed < deltaTime) {
			SDL_Delay ((int) (deltaTime - frameElapsed));
		}
	}

	delete gameController;

	return 0;
}

#pragma warning (pop)
