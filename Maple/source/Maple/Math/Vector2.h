#pragma once

#include <imgui.h>

namespace Maple
{
	template<typename Ty = float>
	struct Vector2
	{
		union
		{
			struct { Ty x, y; };
			Ty m[2];
		};

		Vector2(Ty p_x = 0, Ty p_y = 0)
			:x(p_x), y(p_y)
		{
		}

		Vector2(const ImVec2& vec)
			:x(vec.x), y(vec.y)
		{
		}

		const Ty& operator[](size_t index) const { return m[index]; }
		Ty& operator[](size_t index) { return m[index]; }

		const Vector2<Ty>& operator+=(const Vector2<Ty>& v)
		{
			x += v.x;
			y += v.y;

			return *this;
		}

		const Vector2<Ty>& operator-=(const Vector2<Ty>& v)
		{
			x -= v.x;
			y -= v.y;

			return *this;
		}

		const Vector2<Ty>& operator*=(const Vector2<Ty>& v)
		{
			x *= v.x;
			y *= v.y;

			return *this;
		}

		const Vector2<Ty>& operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;

			return *this;
		}
		
		const Vector2<Ty>& operator/=(const Vector2<Ty>& v)
		{
			x /= v.x;
			y /= v.y;

			return *this;
		}

		const Vector2<Ty>& operator/=(const float scalar)
		{
			x /= scalar;
			y /= scalar;

			return *this;
		}

		Vector2<Ty> operator+(const Vector2<Ty>& v)
		{
			Vector2<Ty> ret = *this;
			return ret += v;
		}
		
		Vector2<Ty> operator-(const Vector2<Ty>& v)
		{
			Vector2<Ty> ret = *this;
			return ret -= v;
		}

		Vector2<Ty> operator*(const Vector2<Ty>& v)
		{
			Vector2<Ty> ret = *this;
			return ret *= v;
		}
		
		Vector2<Ty> operator*(const float scalar)
		{
			Vector2<Ty> ret = *this;
			return ret *= scalar;
		}
		
		friend Vector2<Ty> operator*(const float scalar, const Vector2<Ty>& v)
			{ return v * scalar; }


		Vector2<Ty> operator/(const Vector2<Ty>& v)
		{
			Vector2<Ty> ret = *this;
			return ret /= v;
		}

		Vector2<Ty> operator/(const float scalar)
		{
			Vector2<Ty> ret = *this;
			return ret /= scalar;
		}

		friend Vector2<Ty> operator/(const float scalar, const Vector2<Ty>& v)
		{
			return Vector2<Ty>(scalar / v.x, scalar / v.y);
		}

		operator ImVec2() const { return ImVec2((float)x, (float)y); }
	};

	using Vector2i = Vector2<int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}