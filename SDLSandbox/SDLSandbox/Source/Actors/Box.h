/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "GameObject.h"
#include "IInhabitant.h"
#include "../Tiled/TiledObject.h"
#include <vector>

namespace Challenge {

	class IAudioManager;
	class Cell;
	class Grid;
	class IInputHandler;

	class Box : public GameObject, public IInhabitant {

		public:
			Box ();
			Box (Grid* grid);

			/// <summary>
			/// Schedules this game object for disposal.
			/// </summary>
			virtual void die () override;

			virtual Color getColor () override;

			virtual Cell* getCurrentCell () override;

			/// <summary>
			/// Checks if this box has been pressed.
			/// </summary>
			void handleInput ();

			/// <summary>
			/// Initializes this game object with a random color and texture.
			/// </summary>
			void initialize ();

			/// <summary>
			/// Initializes this game object according to a parsed Tiled object.
			/// </summary>
			virtual void initialize (TiledObject* data) override;
			
			/// <summary>
			/// Whether this game object is currently busy.
			/// Boxes are considered busy if they are moving, and they do not accept input until they stop moving.
			/// </summary>
			inline virtual bool isBusy () override {
				return this->busy;
			}

			/// <summary>
			/// Whether this object is scheduled for disposal.
			/// </summary>
			virtual bool isDead () override;

			/// <summary>
			/// Schedules contiguous group of boxes of the same colour for disposal, if there are more than one.
			/// </summary>
			/// <returns>Whether a group was actually disposed.</returns>
			bool killGroup ();

			/// <summary>
			/// Randomizes this game object's color.
			/// </summary>
			void randomizeColor ();

			/// <summary>
			/// Randomizes this game object's texture.
			/// </summary>
			void randomizeTexture ();

			virtual void render () override;

			/// <summary>
			/// Sets the current cell.
			/// The box doesn't immediately move to the target, instead it progresses towards the target over time.
			/// </summary>
			virtual void setCurrentCell (Cell* cell) override;

			virtual void update () override;

		private:
			static TiledObject defaultData;

			static class StaticConstructor {
				public:
					StaticConstructor ();
			} DefaultDataInitializer;

			static const std::vector<std::string> textureNames;

			IAudioManager* audioManager;
			Grid* grid;
			IInputHandler* inputHandler;
			Cell* currentCell;
			Cell* lastCell;
			bool busy;
			bool pressed;

			/// <summary>
			/// Moves box towards the current target.
			/// </summary>
			/// <returns>Whether the box actually moved.</returns>
			bool moveTowardsTarget ();

			/// <summary>
			/// Handles a click within the bounds of this game object.
			/// On boxes associated with a grid, this will check if the box is part of a group of contiguous boxes
			/// of the same colour, and scheduled the disposal of the group.
			/// On boxes not associated with a grid, this will schedule the disposal of the box.
			/// </summary>
			void onPressed ();

			virtual std::string type () override {
				return "Box";
			}
	};
}
