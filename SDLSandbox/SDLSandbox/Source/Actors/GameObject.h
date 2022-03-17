/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "../Gameplay/Color.h"
#include "../Math/Vector2D.h"
#include <memory>
#include <string>
#include <vector>

namespace Challenge {

	class GameObjectData;
	class ITextureManager;
	class TiledObject;

	class GameObject {

		public:
			virtual ~GameObject ();

			// no copy operations
			GameObject (const GameObject&) = delete;
			GameObject& operator=(const GameObject&) = delete;

			// no move operations
			GameObject (GameObject&&) = delete;
			GameObject& operator = (GameObject&&) = delete;

			/// <summary>
			/// Checks whether the provided position is within the bounds of this game object.
			/// </summary>
			bool contains (Vector2D position);

			/// <summary>
			/// Schedules this game object for disposal.
			/// </summary>
			virtual void die ();

			/// <summary>
			/// Returns this game object's color identifier.
			/// </summary>
			virtual Color getColor ();

			/// <summary>
			/// Returns the actual underlying color of this game object.
			/// Elements with different shades of purple have different values, but are still all grouped under the
			/// color identifier "Purple".
			/// </summary>
			SDL_Color getColorValue ();

			/// <summary>
			/// Returns the rendering layer.
			/// Layers are rendered in ascending order according to this value.
			/// </summary>
			inline int getLayer () {
				return this->layer;
			}

			/// <summary>
			/// Returns this object's position in world coordinates.
			/// </summary>
			Vector2D& getPosition ();

			/// <summary>
			/// Returns this object's size, in world space.
			/// </summary>
			Vector2D& getSize ();

			/// <summary>
			/// Initialize this game object according to a parsed Tiled object.
			/// </summary>
			virtual void initialize (TiledObject* data) = 0;

			/// <summary>
			/// Whether this game object is scheduled for disposal.
			/// </summary>
			virtual bool isDead ();

			/// <summary>
			/// Checks if this game object's bounds overlap a second game object.
			/// </summary>
			bool overlaps (GameObject* otherObject);

			/// <summary>
			/// Tells the texture manager to render this game object.
			/// </summary>
			virtual void render ();

			/// <summary>
			/// Sets this game object's rotation angle in the Z coordinate, in world space.
			/// </summary>
			void setRotation (double rotation);

			void setColor (Color identifier);

			void setPosition (Vector2D position);

			/// <summary>
			/// Returns this game object's underlying type name.
			/// </summary>
			virtual std::string type () = 0;

			virtual void update () = 0;
		
		protected:
			GameObject ();

			Vector2D acceleration;
			int animationSpeed;
			int currentFrame;
			bool dead;
			std::vector<std::string> frames;
			int layer;
			Vector2D position;
			double rotation;
			Vector2D size;
			Vector2D velocity;
			bool visible;

			// While the actual color may be any value, the identifier helps grouping up objects. This way,
			// objects with different shades of purple all share a color identifier: Purple.
			Color color;
			SDL_Color colorValue;

			std::string atlasID;
			std::string textureID;

		private:
			ITextureManager* textureManager;
	};
}
