/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <math.h>
#include <string>

namespace Challenge {

	class Vector2D {

		public:
			Vector2D () : x (0), y (0) {

			}

			Vector2D (float x, float y) : x (x), y (y) {
		
			}

			Vector2D (double x, double y) {
				this->x = (float) x;
				this->y = (float) y;
			}

			Vector2D (int x, int y) {
				this->x = (float) x;
				this->y = (float) y;
			}

			float getX () { return this->x; }
			float getY () { return this->y; }


			/// <summary>
			/// Returns this vector's hypotenuse.
			/// </summary>
			/// <returns></returns>
			float length () {
				return sqrtf (this->x * this->x + this->y * this->y);
			}

			/// <summary>
			/// Converts this vector into a unit vector.
			/// </summary>
			void normalize () {
				float length = this->length ();

				if (length > 0) {
					(*this) /= length;
				}
			}
		
			void set (float x, float y) {
				this->x = x;
				this->y = y;
			}

			void set (int x, int y) {
				this->set ((float) x, (float) y);
			}

			void set (Vector2D vector) {
				this->x = vector.getX ();
				this->y = vector.getY ();
			}

			void setX (float x) { this->x = x; }
			void setX (int x) { this->x = (float) x; }
			void setY (float y) { this->y = y; }
			void setY (int y) { this->y = (float) y; }

			std::string toString () {
				return std::to_string (this->getX ()) + " " + std::to_string (this->getY ());
			}

			Vector2D operator + (const Vector2D& v) const {
				return Vector2D (this->x + v.x, this->y + v.y);
			}

			friend Vector2D& operator += (Vector2D& a, const Vector2D& b) {
				a.x += b.x;
				a.y += b.y;

				return a;
			}

			Vector2D operator * (float number) {
				return Vector2D (this->x * number, this->y * number);
			}

			Vector2D& operator *= (float number) {
				this->x *= number;
				this->y *= number;

				return *this;
			}

			Vector2D operator - (const Vector2D& v) const {
				return Vector2D (this->x - v.x, this->y - v.y);
			}

			friend Vector2D& operator -= (Vector2D& a, const Vector2D& b) {
				a.x -= b.x;
				a.y -= b.y;

				return a;
			}

			Vector2D operator / (float number) {
				return Vector2D (this->x / number, this->y / number);
			}

			Vector2D& operator /= (float number) {
				this->x /= number;
				this->y /= number;

				return *this;
			}

			/// <summary>
			/// Returns the axis associated with the provided index.
			/// </summary>
			/// <returns>Pointer to axis, or nullptr if index is invalid.</returns>
			float* operator[] (const int index) {
				switch (index) {
					case 0:
						return &this->x;
						break;

					case 1:
						return &this->y;
						break;

					default:
						return nullptr;
				}
			}

		private:
			float x;
			float y;
	};
}
