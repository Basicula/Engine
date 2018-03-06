#include "vector2.h"

namespace Engine {

	namespace Math {

		Vector2::Vector2()
		{
			x = 0.0f;
			y = 0.0f;
		}

		Vector2::Vector2(const float& _x, const float& _y)
		{
			x = _x;
			y = _y;
		}

		Vector2& Vector2::add(const Vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2& Vector2::multiply(const Vector2& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		Vector2& Vector2::substract(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2& Vector2::divide(const Vector2& other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}


		Vector2 operator+(Vector2 left, const Vector2& rigth)
		{
			return left.add(rigth);
		}

		Vector2 operator-(Vector2 left, const Vector2& rigth)
		{
			return left.substract(rigth);
		}

		Vector2 operator*(Vector2 left, const Vector2& rigth)
		{
			return left.multiply(rigth);
		}

		Vector2 operator/(Vector2 left, const Vector2& rigth)
		{
			return left.divide(rigth);
		}

		Vector2& Vector2::operator+=(const Vector2& rigth)
		{
			return add(rigth);
		}

		Vector2& Vector2::operator-=(const Vector2& rigth)
		{
			return substract(rigth);
		}

		Vector2& Vector2::operator/=(const Vector2& rigth)
		{
			return divide(rigth);
		}

		Vector2& Vector2::operator*=(const Vector2& rigth)
		{
			return multiply(rigth);
		}

		bool Vector2::operator==(const Vector2& other)
		{
			return x == other.x && y == other.y;
		}

		bool Vector2::operator!=(const Vector2& other)
		{
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
		{
			stream <<"("<< vector.x << ", " << vector.y<<")";
			return stream;
		}

	}
}