#pragma once

namespace Maple
{
	template<typename Ty = float>
	struct Vector3
	{
		union
		{
			struct { Ty x, y, z; };
            struct { Ty r, g, b; };
			struct { Ty h, s, v; };
			Ty m[3];
		};

		Vector3(Ty p_x = 0, Ty p_y = 0, Ty p_z = 0)
			:x(p_x), y(p_y), z(p_z)
		{
		}

		const Ty& operator[](size_t index) const { return m[index]; }
		Ty& operator[](size_t index) { return m[index]; }

		const Vector3<Ty>& operator+=(const Vector3<Ty>& v)
		{
			x += v.x;
			y += v.y;
            z += v.z;

			return *this;
		}

		const Vector3<Ty>& operator-=(const Vector3<Ty>& v)
		{
			x -= v.x;
			y -= v.y;
            z -= v.z;

			return *this;
		}

		const Vector3<Ty>& operator*=(const Vector3<Ty>& v)
		{
			x *= v.x;
			y *= v.y;
            z *= v.z;

			return *this;
		}

		const Vector3<Ty>& operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
            z *= scalar;

			return *this;
		}
		
		const Vector3<Ty>& operator/=(const Vector3<Ty>& v)
		{
			x /= v.x;
			y /= v.y;
            z /= v.z;

			return *this;
		}

		const Vector3<Ty>& operator/=(const float scalar)
		{
			x /= scalar;
			y /= scalar;
            z /= scalar;

			return *this;
		}

		Vector3<Ty> operator+(const Vector3<Ty>& v)
		{
			Vector3<Ty> ret = *this;
			return ret += v;
		}
		
		Vector3<Ty> operator-(const Vector3<Ty>& v)
		{
			Vector3<Ty> ret = *this;
			return ret -= v;
		}

		Vector3<Ty> operator*(const Vector3<Ty>& v)
		{
			Vector3<Ty> ret = *this;
			return ret *= v;
		}
		
		Vector3<Ty> operator*(const float scalar)
		{
			Vector3<Ty> ret = *this;
			return ret *= scalar;
		}
		
		friend Vector3<Ty> operator*(const float scalar, const Vector3<Ty>& v)
			{ return v * scalar; }


		Vector3<Ty> operator/(const Vector3<Ty>& v)
		{
			Vector3<Ty> ret = *this;
			return ret /= v;
		}

		Vector3<Ty> operator/(const float scalar)
		{
			Vector3<Ty> ret = *this;
			return ret /= scalar;
		}

		friend Vector3<Ty> operator/(const float scalar, const Vector3<Ty>& v)
		{
			return Vector3<Ty>(scalar / v.x, scalar / v.y, scalar / v.z);
		}
	};

	using Vector3i = Vector3<int>;
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;

    template<typename Ty>
    using Color3   = Vector3<Ty>;

    using Color3i  = Vector3<int>;
    using Color3f  = Vector3<float>;
    using Color3d  = Vector3<double>;
}