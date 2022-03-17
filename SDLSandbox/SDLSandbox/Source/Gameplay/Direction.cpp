/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#include "Direction.h"

using namespace Challenge;

const std::map<Direction, Vector2D> DirectionOffset::offsetPerDirection = {
	{ Direction::North, Vector2D (0, 1) },
	{ Direction::East,  Vector2D (1, 0) },
	{ Direction::South, Vector2D (0, -1) },
	{ Direction::West,  Vector2D (-1, 0) }
};
