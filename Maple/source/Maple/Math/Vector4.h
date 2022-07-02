#pragma once

namespace Maple
{
	template<typename Ty = float>
	struct Vector4
	{
		union
		{
			struct { Ty x, y, z, w; };
            struct { Ty r, g, b, a; };
            struct { Ty h, s, v, a; };
			Ty m[4];
		};

		Vector4(Ty p_x = 0, Ty p_y = 0, Ty p_z = 0, Ty p_w = 0)
			:x(p_x), y(p_y), z(p_z), w(p_w)
		{
		}

		const Ty& operator[](size_t index) const { return m[index]; }
		Ty& operator[](size_t index) { return m[index]; }

		const Vector4<Ty>& operator+=(const Vector4<Ty>& v)
		{
			x += v.x;
			y += v.y;
            z += v.z;
            w += v.w;

			return *this;
		}

		const Vector4<Ty>& operator-=(const Vector4<Ty>& v)
		{
			x -= v.x;
			y -= v.y;
            z -= v.z;
            w -= v.w;

			return *this;
		}

		const Vector4<Ty>& operator*=(const Vector4<Ty>& v)
		{
			x *= v.x;
			y *= v.y;
            z *= v.z;
            w *= v.w;

			return *this;
		}

		const Vector4<Ty>& operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
            z *= scalar;
            w *= scalar;

			return *this;
		}
		
		const Vector4<Ty>& operator/=(const Vector4<Ty>& v)
		{
			x /= v.x;
			y /= v.y;
            z /= v.z;
            w /= v.w;

			return *this;
		}

		const Vector4<Ty>& operator/=(const float scalar)
		{
			x /= scalar;
			y /= scalar;
            z /= scalar;
            w /= scalar;

			return *this;
		}

		Vector4<Ty> operator+(const Vector4<Ty>& v)
		{
			Vector4<Ty> ret = *this;
			return ret += v;
		}
		
		Vector4<Ty> operator-(const Vector4<Ty>& v)
		{
			Vector4<Ty> ret = *this;
			return ret -= v;
		}

		Vector4<Ty> operator*(const Vector4<Ty>& v)
		{
			Vector4<Ty> ret = *this;
			return ret *= v;
		}
		
		Vector4<Ty> operator*(const float scalar)
		{
			Vector4<Ty> ret = *this;
			return ret *= scalar;
		}
		
		friend Vector4<Ty> operator*(const float scalar, const Vector4<Ty>& v)
			{ return v * scalar; }


		Vector4<Ty> operator/(const Vector4<Ty>& v)
		{
			Vector4<Ty> ret = *this;
			return ret /= v;
		}

		Vector4<Ty> operator/(const float scalar)
		{
			Vector4<Ty> ret = *this;
			return ret /= scalar;
		}

		friend Vector4<Ty> operator/(const float scalar, const Vector4<Ty>& v)
		{
			return Vector4<Ty>(scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
		}
	};

	using Vector4i = Vector4<int>;
	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;

    template<typename Ty>
    using Color4   = Vector4<Ty>;

    using Color4i  = Vector4<int>;
    using Color4f  = Vector4<float>;
    using Color4d  = Vector4<double>;
}