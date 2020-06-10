#ifndef __vmath_Header_File__
#define __vmath_Header_File__

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#define ASSIMP_CONVERTION

#ifdef ASSIMP_CONVERTION
#include "assimp/matrix4x4.h"
#include "assimp/quaternion.h"
#endif

namespace math
{

#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923   // pi/2
#endif

#ifndef M_LN2
#define M_LN2      0.693147180559945309417  // ln(2)
#endif

#ifndef M_SQRT2
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#endif

#define DEG2RAD(x) ((x * M_PI) / 180.0)
#define RAD2DEG(x) ((x) * 180.0 / M_PI)
//#define EPSILON (4.37114e-07)

const double epsilon = 4.37114e-05;
#define EPSILON epsilon
    

template<class T>
class vec2;

template<class T>
class vec3;

template<class T>
class vec4;

template<class T>
class mat3;


template<class T>
class mat4;

template<class T>
class quat;


template<class T>
class vec2
{
public:
	union
	{
		/**
		 * First element of vec, alias for X-coordinate.
		 */
		T x;

		/**
		 * First element of vec, alias for S-coordinate.
		 * For textures notation.
		 */
		T s;
	};

	union
	{
		/**
		 * Second element of vec, alias for Y-coordinate.
		 */
		T y;

		/**
		 * Second element of vec, alias for T-coordinate.
		 * For textures notation.
		 */
		T t;
	};

	//----------------[ constructors ]--------------------------
	/**
	 * Creates and sets to (0,0)
	 */
	vec2()
			: x(0), y(0)
	{
	}

	/**
	 * Creates and sets to (x,y)
	 * @param nx initial x-coordinate value
	 * @param ny initial y-coordinate value
	 */
	vec2(T nx, T ny)
			: x(nx), y(ny)
	{
	}

	/**
	 * Copy constructor.
	 * @param src Source of data for new created instance.
	 */
	vec2(const vec2<T>& src)
			: x(src.x), y(src.y)
	{
	}

	/**
	 * Copy casting constructor.
	 * @param src Source of data for new created instance.
	 */
	template<class FromT>
	vec2(const vec2<FromT>& src)
			: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
	{
	}

	//----------------[ access operators ]-------------------
	/**
	 * Copy casting operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	vec2<T>& operator=(const vec2<FromT>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		return *this;
	}

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator=(const vec2<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	/**
	 * Array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, else reference to y 
	 * y coordinate.
	 */
	T& operator[](int n)
	{
		assert(n >= 0 && n <= 1);
		if (0 == n)
			return x;
		else
			return y;
	}

	/**
	 * Constant array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, else reference to y
	 * y coordinate.
	 */
	const T& operator[](int n) const
	{
		assert(n >= 0 && n <= 1);
		if (0 == n)
			return x;
		else
			return y;
	}

	//---------------[ vec aritmetic operator ]--------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T> operator+(const vec2<T>& rhs) const
	{
		return vec2<T>(x + rhs.x, y + rhs.y);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T> operator-(const vec2<T>& rhs) const
	{
		return vec2<T>(x - rhs.x, y - rhs.y);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T> operator*(const vec2<T>& rhs) const
	{
		return vec2<T>(x * rhs.x, y * rhs.y);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T> operator/(const vec2<T>& rhs) const
	{
		return vec2<T>(x / rhs.x, y / rhs.y);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator+=(const vec2<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	/**
	 * Substraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator-=(const vec2<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator*=(const vec2<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator/=(const vec2<T>& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	//--------------[ scalar vec operator ]--------------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T> operator+(T rhs) const
	{
		return vec2<T>(x + rhs, y + rhs);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T> operator-(T rhs) const
	{
		return vec2<T>(x - rhs, y - rhs);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T> operator*(T rhs) const
	{
		return vec2<T>(x * rhs, y * rhs);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T> operator/(T rhs) const
	{
		return vec2<T>(x / rhs, y / rhs);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator+=(T rhs)
	{
		x += rhs;
		y += rhs;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator-=(T rhs)
	{
		x -= rhs;
		y -= rhs;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator*=(T rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec2<T>& operator/=(T rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	//--------------[ equality operator ]------------------------
	/**
	 * Equality 
	 operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition | lhs.x - rhs.y | < EPSILON,
	 * same for y-coordinate.
	 */
	bool operator==(const vec2<T>& rhs) const
	{
		return (std::abs(x - rhs.x) < EPSILON) && (std::abs(y - rhs.y) < EPSILON);
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const vec2<T>& rhs) const
	{
		return !(*this == rhs);
	}

	//-------------[ unary operations ]--------------------------
	/**
	 * Unary negate operator
	 * @return negated vec
	 */
	vec2<T> operator-() const
	{
		return vec2<T>(-x, -y);
	}

	//-------------[ size operations ]---------------------------
	/**
	 * Get length of vec.
	 * @return lenght of vec
	 */
	T length() const
	{
		return (T) std::sqrt(x * x + y * y);
	}

	/**
	 * Normalize vec
	 */
	void normalize()
	{
		T s = length();
        
        if( s == 0.0)
            return;
        
        T inv = 1 / s;
		x *= inv;
		y *= inv;
	}

	static vec2<T> normalize(const vec2<T>& from)
	{
		vec2<T> tmp = from;
		tmp.normalize();

		return tmp;
	}

	/**
	 * Return square of length.
	 * @return length ^ 2
	 * @note This method is faster then length(). For comparison
	 * of length of two vec can be used just this value, instead
	 * of more expensive length() method.
	 */
	T lengthSq() const
	{
		return x * x + y * y;
	}

	//--------------[ misc. operations ]-----------------------
	/**
	 * Linear interpolation of two vecs
	 * @param fact Factor of interpolation. For translation from position
	 * of this vec to vec r, values of factor goes from 0.0 to 1.0.
	 * @param r Second vec for interpolation 
	 * @note However values of fact parameter are reasonable only in interval
	 * [0.0 , 1.0], you can pass also values outside of this interval and you
	 * can get result (extrapolation?)
	 */
	vec2<T> lerp(T fact, const vec2<T>& r) const
	{
		return (*this) + (r - (*this)) * fact;
	}

	T dot(const vec2<T>& r) const
	{
		return x * r.x + y * r.y;
	}

	//-------------[ conversion ]-----------------------------
	/**
	 * Conversion to pointer operator
	 * @return Pointer to internally stored (in management of class vec2<T>)
	 * used for passing vec2<T> values to gl*2[fd] functions.
	 */
	operator T*()
	{
		return (T*) this;
	}
	/**
	 * Conversion to pointer operator
	 * @return Constant Pointer to internally stored (in management of class vec2<T>)
	 * used for passing vec2<T> values to gl*2[fd] functions.
	 */
	operator const T*() const
	{
		return (const T*) this;
	}

	//-------------[ output operator ]------------------------
	/**
	 * Output to stream operator
	 * @param lhs Left hand side argument of operator (commonly ostream instance). 
	 * @param rhs Right hand side argument of operator.
	 * @return Left hand side argument - the ostream object passed to operator.
	 */
	friend std::ostream& operator<<(std::ostream& lhs, const vec2<T>& rhs)
	{
		lhs << "[" << rhs.x << "," << rhs.y << "]";
		return lhs;
	}

	/**
	 * Gets string representation.
	 */
	std::string toString() const
	{
		std::ostringstream oss;
		oss << *this;
		return oss.str();
	}
};

//--------------------------------------
// Typedef shortcuts for 2D vec
//-------------------------------------
/// Two dimensional vec of floats
typedef class vec2<float> vec2f;
/// Two dimensional vec of doubles
typedef class vec2<double> vec2d;
/// Two dimensional vec of ints
typedef class vec2<int> vec2i;

/**
 * Class for three dimensional vec.
 * There are four ways of accessing vec components.
 * Let's have <code>vec3f v</code>, you can either:
 * <ul>
 * 	<li>access as position (x,y,z) &mdash; <code>v.x = v.y = v.z = 1;</code></li>
 * 	<li>access as texture coordinate (s,t,u) &mdash; <code>v.s = v.t = v.u = 1;</code></li>
 * 	<li>access as color (r,g,b) &mdash; <code>v.r = v.g = v.b = 1;</code></li>
 * 	<li>access via operator[] &mdash; <code>v[0] = v[1] = v[2] = 1;</code></li>
 * </ul>
 */
template<class T>
class vec3
{
public:
	//T x, y, z;
	union
	{
		/**
		 * First element of vec, alias for X-coordinate.
		 */
		T x;

		/**
		 * First element of vec, alias for S-coordinate.
		 * For textures notation.
		 */
		T s;

		/**
		 * First element of vec, alias for R-coordinate.
		 * For color notation.
		 */
		T r;
	};

	union
	{
		/**
		 * Second element of vec, alias for Y-coordinate.
		 */
		T y;
		/**
		 * Second element of vec, alias for T-coordinate.
		 * For textures notation.
		 */
		T t;
		/**
		 * Second element of vec, alias for G-coordinate.
		 * For color notation.
		 */
		T g;
	};

	union
	{
		/**
		 * Third element of vec, alias for Z-coordinate.
		 */
		T z;

		/**
		 * Third element of vec, alias for U-coordinate.
		 * For textures notation.
		 */
		T u;
		/**
		 * Third element of vec, alias for B-coordinate.
		 * For color notation.
		 */
		T b;
	};

	//----------------[ constructors ]--------------------------
	/**
	 * Creates and sets to (0,0,0)
	 */
	vec3()
			: x(0), y(0), z(0)
	{
	}

	vec3(T f)
		: x(f)
		, y(f)
		, z(f)
	{
	}
	/**
	 * Creates and sets to (x,y,z)
	 * @param nx initial x-coordinate value
	 * @param ny initial y-coordinate value
	 * @param nz initial z-coordinate value
	 */
	vec3(T nx, T ny, T nz)
			: x(nx), y(ny), z(nz)
	{
	}

	/**
	 * Copy constructor.
	 * @param src Source of data for new created vec3 instance.
	 */
	vec3(const vec3<T>& src)
			: x(src.x), y(src.y), z(src.z)
	{
	}

    
    
    T getX()
    {
		std::cout << "test: getX: " << x << std::endl;
        return x;
    }
    
    void setX(T nx)
    {
        x = nx;
    }
	
	void setY(T nx)
	{
		y = nx;
	}
	T getY()
	{
		return y;
	}
	T getZ()
	{
		return z;
	}
	void setZ(T nx)
	{
		z = nx;
	}
    
	/**
	 * Copy casting constructor.
	 * @param src Source of data for new created vec3 instance.
	 */
	template<class FromT>
	vec3(const vec3<FromT>& src)
			: x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), z(static_cast<T>(src.z))
	{
	}

	vec3(const vec4<T> & src):x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), z(static_cast<T>(src.z))
	{

	}

#ifdef ASSIMP_CONVERTION
	vec3(const aiVector3D & src)
	{
		x = src.x;
		y = src.y;
		z = src.z;
	}
#endif
	//----------------[ access operators ]-------------------
	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator=(const vec3<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	/**
	 * Copy casting operator.
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	vec3<T> operator=(const vec3<FromT>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		return *this;
	}

	/**
	 * Array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, n = 1
	 * reference to y, else reference to z 
	 * y coordinate.
	 */
	T & operator[](int n)
	{
		assert(n >= 0 && n <= 2);
		if (0 == n)
			return x;
		else if (1 == n)
			return y;
		else
			return z;
	}

	/**
	 * Constant array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, n = 1
	 * reference to y, else reference to z
	 * y coordinate.
	 */
	const T & operator[](int n) const
	{
		assert(n >= 0 && n <= 2);
		if (0 == n)
			return x;
		else if (1 == n)
			return y;
		else
			return z;
	}

	//---------------[ vec arithmetic operator ]--------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator+(const vec3<T>& rhs) const
	{
		return vec3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator-(const vec3<T>& rhs) const
	{
		return vec3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator*(const vec3<T>& rhs) const
	{
		return vec3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator/(const vec3<T>& rhs) const
	{
		return vec3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T>& operator+=(const vec3<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T>& operator-=(const vec3<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T>& operator*=(const vec3<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T>& operator/=(const vec3<T>& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	vec3<T>& Scale(const vec3<T>& inV)
	{
		x *= inV.x; y *= inV.y; z *= inV.z; return *this;
	}
	/**
	 * Dot product of two vecs.
	 * @param rhs Right hand side argument of binary operator.
	 */
	T dotProduct(const vec3<T>& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	/**
	 * Cross product operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> crossProduct(const vec3<T>& rhs) const
	{
		return vec3<T>(y * rhs.z - rhs.y * z, z * rhs.x - rhs.z * x, x * rhs.y - rhs.x * y);
	}
	static vec3<T> crossProduct(const vec3<T>& lhs, const vec3<T>rhs)
	{
		return vec3<T>(lhs.y * rhs.z - rhs.y * lhs.z, lhs.z * rhs.x - rhs.z * lhs.x, lhs.x * rhs.y - rhs.x * lhs.y);

	}

	//--------------[ scalar vec operator ]--------------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator+(T rhs) const
	{
		return vec3<T>(x + rhs, y + rhs, z + rhs);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator-(T rhs) const
	{
		return vec3<T>(x - rhs, y - rhs, z - rhs);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator*(T rhs) const
	{
		return vec3<T>(x * rhs, y * rhs, z * rhs);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator/(T rhs) const
	{
		return vec3<T>(x / rhs, y / rhs, z / rhs);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T>& operator+=(T rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T>& operator-=(T rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T>& operator*=(T rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T>& operator/=(T rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	//--------------[ Equality operator ]------------------------
	/**
	 * Equality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition | lhs.x - rhs.y | < EPSILON,
	 * same for y-coordinate, and z-coordinate.
	 */
	bool operator==(const vec3<T>& rhs) const
	{
		return std::abs(x - rhs.x) < EPSILON && std::abs(y - rhs.y) < EPSILON && std::abs(z - rhs.z) < EPSILON;
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const vec3<T>& rhs) const
	{
		return !(*this == rhs);
	}

	//-------------[ unary operations ]--------------------------
	/**
	 * Unary negate operator
	 * @return negated vec
	 */
	vec3<T> operator-() const
	{
		return vec3<T>(-x, -y, -z);
	}

	//-------------[ size operations ]---------------------------
	/**
	 * Get length of vec.
	 * @return lenght of vec
	 */
	T length() const
	{
		return (T) std::sqrt(x * x + y * y + z * z);
	}

	/**
	 * Return square of length.
	 * @return length ^ 2
	 * @note This method is faster then length(). For comparison
	 * of length of two vec can be used just this value, instead
	 * of more expensive length() method.
	 */
	T lengthSq() const
	{
		return x * x + y * y + z * z;
	}

	/**
	 * Normalize vec
	 */
	void normalize()
	{
		T s = length();
        if( s == 0.0)
            return;
        
        T inv = 1 / s;
		x *= inv;
		y *= inv;
		z *= inv;
	}

	/**
	 * return normalized vec3 of input vector.
	 */
	static vec3<T> normalize(const vec3<T>& src) {
		vec3<T> tmp = src;
		tmp.normalize();
		return tmp;
	}

	//------------[ other operations ]---------------------------
	/**
	 * Rotate vec around three axis.
	 * @param ax Angle (in degrees) to be rotated around X-axis.
	 * @param ay Angle (in degrees) to be rotated around Y-axis.
	 * @param az Angle (in degrees) to be rotated around Z-axis.
	 */
	void rotate(T ax, T ay, T az)
	{
		T a = cos(DEG2RAD(ax));
		T b = sin(DEG2RAD(ax));
		T c = cos(DEG2RAD(ay));
		T d = sin(DEG2RAD(ay));
		T e = cos(DEG2RAD(az));
		T f = sin(DEG2RAD(az));
		T nx = c * e * x - c * f * y + d * z;
		T ny = (a * f + b * d * e) * x + (a * e - b * d * f) * y - b * c * z;
		T nz = (b * f - a * d * e) * x + (a * d * f + b * e) * y + a * c * z;
		x = nx;
		y = ny;
		z = nz;

	}

	/**
	 * Linear interpolation of two vecs
	 * @param fact Factor of interpolation. For translation from positon
	 * of this vec to vec r, values of factor goes from 0.0 to 1.0.
	 * @param r Second vec for interpolation 
	 * @note However values of fact parameter are reasonable only in interval
	 * [0.0 , 1.0], you can pass also values outside of this interval and you
	 * can get result (extrapolation?)
	 */
	vec3<T> lerp(T fact, const vec3<T>& r) const
	{
		return (*this) + (r - (*this)) * fact;
	}

	static vec3<T> lerp(const vec3<T>& l, const vec3<T>& r, T fact)
	{
		return l + (r - l)*fact;
	}
	//-------------[ conversion ]-----------------------------

	/**
	 * Conversion to pointer operator
	 * @return Pointer to internally stored (in management of class vec3<T>)
	 * used for passing vec3<T> values to gl*3[fd] functions.
	 */
	operator T*()
	{
		return (T*) this;
	}

	/**
	 * Conversion to pointer operator
	 * @return Constant Pointer to internally stored (in management of class vec3<T>)
	 * used for passing vec3<T> values to gl*3[fd] functions.
	 */
	operator const T*() const
	{
		return (const T*) this;
	}

	//-------------[ output operator ]------------------------
	/**
	 * Output to stream operator
	 * @param lhs Left hand side argument of operator (commonly ostream instance). 
	 * @param rhs Right hand side argument of operator.
	 * @return Left hand side argument - the ostream object passed to operator.
	 */
	friend std::ostream& operator<<(std::ostream& lhs, const vec3<T>& rhs)
	{
		lhs << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";
		return lhs;
	}

	/**
	 * Gets string representation.
	 */
	std::string toString() const
	{
		std::ostringstream oss;
		oss << *this;
		return oss.str();
	}

	/**
	* Gets min dim
	*/
	size_t minDim() const {
		if (fabs((double)x) < fabs((double)y) && fabs((double)x) < fabs((double)z)) return 0;
		else if (fabs((double)y) < fabs((double)z))                                 return 1;
		else                                                                        return 2;
	}

	/**
	* Gets max dim
	*/
	size_t maxDim() const {
		if (fabs((double)x) > fabs((double)y) && fabs((double)x) > fabs((double)z)) return 0;
		else if (fabs((double)y) > fabs((double)z))                                 return 1;
		else                                                                        return 2;
	}

	/**
	* create a orthogonal basis from a single direction, assume *this is axis_y
	* make sure *this is a unit vector
	*/
	void createOrthogonalBasis(vec3<T>& axis_x, vec3<T>& axis_z) const {
		switch (minDim()) {
			case (0) : {axis_x[0] = 0, axis_x[1] = -z, axis_x[2] = y; break; }
			case (1) : {axis_x[0] = -z, axis_x[1] = 0, axis_x[2] = x; break; }
			case (2) : {axis_x[0] = -y, axis_x[1] = x, axis_x[2] = 0; break; }
		}
		axis_x.normalize();
		axis_z = axis_x.crossProduct(*this);
		axis_z.normalize();//
	}

public:
	static const vec3<T> Zero;
	static const vec3<T> UnitX;
	static const vec3<T> UnitY;
	static const vec3<T> UnitZ;
};

/// Three dimensional vec of floats
typedef vec3<float> vec3f;
/// Three dimensional vec of doubles
typedef vec3<double> vec3d;
/// Three dimensional vec of ints
typedef vec3<int> vec3i;

/**
 * Class for four dimensional vec.
  * There are four ways of accessing vec components.
 * Let's have <code>vec4f v</code>, you can either:
 * <ul>
 * 	<li>access as position in projective space (x,y,z,w) &mdash; <code>v.x = v.y = v.z = v.w = 1;</code></li>
 * 	<li>access as texture coordinate (s,t,u,v) &mdash; <code>v.s = v.t = v.u = v.v = 1;</code></li>
 * 	<li>access as color (r,g,b,a) &mdash; <code>v.r = v.g = v.b = v.a = 1;</code></li>
 * 	<li>access via operator[] &mdash; <code>v[0] = v[1] = v[2] = v[3] = 1;</code></li>
 * </ul>
 */
template<class T>
class vec4
{
public:

	union
	{
		/**
		 * First element of vec, alias for R-coordinate.
		 * For color notation.
		 */
		T r
		/**
		 * First element of vec, alias for X-coordinate.
		 */;
		T x;
	};

	union
	{
		/**
		 * Second element of vec, alias for G-coordinate.
		 * For color notation.
		 */
		T g;
		/**
		 * Second element of vec, alias for Y-coordinate.
		 */
		T y;
	};

	union
	{
		/**
		 * Third element of vec, alias for B-coordinate.
		 * For color notation.
		 */
		T b;
		/**
		 * Third element of vec, alias for Z-coordinate.
		 */
		T z;
	};

	union
	{
		/**
		 * Fourth element of vec, alias for A-coordinate.
		 * For color notation. This represnt aplha chanell
		 */
		T a;
		/**
		 * First element of vec, alias for W-coordinate.
		 * @note For vecs (such as normals) should be set to 0.0
		 * For vertices should be set to 1.0
		 */
		T w;
	};

	//----------------[ constructors ]--------------------------
	/**
	 * Creates and sets to (0,0,0,0)
	 */
	vec4()
			: x(0), y(0), z(0), w(0)
	{
	}

	/**
	 * Creates and sets to (x,y,z,z)
	 * @param nx initial x-coordinate value (R)
	 * @param ny initial y-coordinate value (G)
	 * @param nz initial z-coordinate value (B)
	 * @param nw initial w-coordinate value (Alpha)
	 */
	vec4(T nx, T ny, T nz, T nw)
			: x(nx), y(ny), z(nz), w(nw)
	{
	}
    
    /**
	 * Creates vec4 from vec3
	 * @param vec3
	 */
    vec4(vec3<T> v, T _w = T(1))
    : x(v.x), y(v.y), z(v.z), w(_w)
	{
	}

	/**
	 * Copy constructor.
	 * @param src Source of data for new created vec4 instance.
	 */
	vec4(const vec4<T>& src)
			: x(src.x), y(src.y), z(src.z), w(src.w)
	{
	}

	/**
	 * Copy casting constructor.
	 * @param src Source of data for new created vec4 instance.
	 */
	template<class FromT>
	vec4(const vec4<FromT>& src)
			: x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), z(static_cast<T>(src.z)), w(static_cast<T>(src.w))
	{
	}

	//----------------[ access operators ]-------------------
	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator=(const vec4<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	/**
	 * Copy casting operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	vec4<T> operator=(const vec4<FromT>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		w = static_cast<T>(rhs.w);
		return *this;
	}

	/**
	 * Array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, n = 1
	 * reference to y coordinate, n = 2 reference to z,  
	 * else reference to w coordinate.
	 */
	T & operator[](int n)
	{
		assert(n >= 0 && n <= 3);
		if (0 == n)
			return x;
		else if (1 == n)
			return y;
		else if (2 == n)
			return z;
		else
			return w;
	}

	/**
	 * Array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, n = 1
	 * reference to y coordinate, n = 2 reference to z,
	 * else reference to w coordinate.
	 */
	const T & operator[](int n) const
	{
		assert(n >= 0 && n <= 3);
		if (0 == n)
			return x;
		else if (1 == n)
			return y;
		else if (2 == n)
			return z;
		else
			return w;
	}

	//---------------[ vec aritmetic operator ]--------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator+(const vec4<T>& rhs) const
	{
		return vec4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator-(const vec4<T>& rhs) const
	{
		return vec4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator*(const vec4<T>& rhs) const
	{
		return vec4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator/(const vec4<T>& rhs) const
	{
		return vec4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T>& operator+=(const vec4<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T>& operator-=(const vec4<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T>& operator*=(const vec4<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T>& operator/=(const vec4<T>& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	//--------------[ equiality operator ]------------------------
	/**
	 * Equality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition | lhs.x - rhs.y | < EPSILON,
	 * same for y-coordinate, z-coordinate, and w-coordinate.
	 */
	bool operator==(const vec4<T>& rhs) const
	{
		return std::abs(x - rhs.x) < EPSILON && std::abs(y - rhs.y) < EPSILON && std::abs(z - rhs.z) < EPSILON
				&& std::abs(w - rhs.w) < EPSILON;
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const vec4<T>& rhs) const
	{
		return !(*this == rhs);
	}

	//-------------[ unary operations ]--------------------------
	/**
	 * Unary negate operator
	 * @return negated vec
	 */
	vec4<T> operator-() const
	{
		return vec4<T>(-x, -y, -z, -w);
	}

	//--------------[ scalar vec operator ]--------------------

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator+(T rhs) const
	{
		return vec4<T>(x + rhs, y + rhs, z + rhs, w + rhs);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator-(T rhs) const
	{
		return vec4<T>(x - rhs, y - rhs, z - rhs, w - rhs);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator*(T rhs) const
	{
		return vec4<T>(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator/(T rhs) const
	{
		return vec4<T>(x / rhs, y / rhs, z / rhs, w / rhs);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T>& operator+=(T rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		w += rhs;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T>& operator-=(T rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		w -= rhs;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T>& operator*=(T rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T>& operator/=(T rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	//-------------[ size operations ]---------------------------
	/**
	 * Get length of vec.
	 * @return lenght of vec
	 */
	T length() const
	{
		return (T) std::sqrt(x * x + y * y + z * z + w * w);
	}

	/**
	 * Normalize vec
	 */
	void normalize()
	{
		T s = length();
        
        if( s == 0.0)
            return;
        
        T inv = 1 / s;
		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;
	}

	/**
	 * Return square of length.
	 * @return length ^ 2
	 * @note This method is faster then length(). For comparison
	 * of length of two vec can be used just this value, instead
	 * of more expensive length() method.
	 */
	T lengthSq() const
	{
		return x * x + y * y + z * z + w * w;
	}

	//--------------[ misc. operations ]-----------------------
	/**
	 * Linear interpolation of two vecs
	 * @param fact Factor of interpolation. For translation from position
	 * of this vec to vec r, values of factor goes from 0.0 to 1.0.
	 * @param r Second vec for interpolation 
	 * @note However values of fact parameter are reasonable only in interval
	 * [0.0 , 1.0], you can pass also values outside of this interval and you
	 * can get result (extrapolation?)
	 */
	vec4<T> lerp(T fact, const vec4<T>& r) const
	{
		return (*this) + (r - (*this)) * fact;
	}

	vec3<T> toVec3() const {
		vec3<T> tmp(x, y, z);
		return tmp;
	}

	//-------------[ conversion ]-----------------------------

	/**
	 * Conversion to pointer operator
	 * @return Pointer to internally stored (in management of class vec4<T>)
	 * used for passing vec4<T> values to gl*4[fd] functions.
	 */
	operator T*()
	{
		return (T*) this;
	}

	/**
	 * Conversion to pointer operator
	 * @return Constant Pointer to internally stored (in management of class vec4<T>)
	 * used for passing vec4<T> values to gl*4[fd] functions.
	 */
	operator const T*() const
	{
		return (const T*) this;
	}

	//-------------[ output operator ]------------------------
	/**
	 * Output to stream operator
	 * @param lhs Left hand side argument of operator (commonly ostream instance). 
	 * @param rhs Right hand side argument of operator.
	 * @return Left hand side argument - the ostream object passed to operator.
	 */
	friend std::ostream& operator<<(std::ostream& lhs, const vec4<T>& rhs)
	{
		lhs << "[" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.w << "]";
		return lhs;
	}

	/**
	 * Gets string representation.
	 */
	std::string toString() const
	{
		std::ostringstream oss;
		oss << *this;
		return oss.str();
	}

};

/// Three dimensional vec of floats
typedef vec4<float> vec4f;
/// Three dimensional vec of doubles
typedef vec4<double> vec4d;
/// Three dimensional vec of ints
typedef vec4<int> vec4i;

#ifndef STRENDER_THIN_MATH
    
/**
 * Class for mat 3x3. 
 * @note Data stored in this mat are in column major order. This arrangement suits OpenGL.
 * If you're using row major mat, consider using fromRowMajorArray as way for construction
 * mat3<T> instance.
 */
template <class T> class mat4;
template<class T>
class mat3
{
public:
	/// Data stored in column major order
	T data[9];

	//--------------------------[ constructors ]-------------------------------
	/**
	 * Creates identity mat
	 */
	mat3()
	{
		for (int i = 0; i < 9; i++)
			data[i] = (i % 4) ? 0 : 1;
	}

    /**
	 * Creates mat3 from mat4 ( extract rotation part )
	 */
	mat3(const mat4<T>& mat)
	{
        data[0] =  mat[0];
        data[1] =  mat[1];
        data[2] =  mat[2];
        
        data[3] =  mat[4];
        data[4] =  mat[5];
        data[5] =  mat[6];
        
        data[6] =  mat[8];
        data[7] =  mat[9];
        data[8] =  mat[10];

	}

	mat3(const T & a0, const T & a1, const T & a2, const T & b0, const T & b1, const T & b2, const T & c0, const T & c1, const T & c2)
	{
		data[0] = a0;
		data[1] = a1;
		data[2] = a2;
		data[3] = b0;
		data[4] = b1;
		data[5] = b2;
		data[6] = c0;
		data[7] = c1;
		data[8] = c2;
	}

	/**
	 * Copy mat values from array (these data must be in column
	 * major order!)
	 */
	mat3(const T * dt)
	{
		std::memcpy(data, dt, sizeof(T) * 9);
	}

	/**
	 * Copy constructor.
	 * @param src Data source for new created instance of mat3
	 */
	mat3(const mat3<T>& src)
	{
		std::memcpy(data, src.data, sizeof(T) * 9);
	}

	/**
	 * Copy casting constructor.
	 * @param src Data source for new created instance of mat3
	 */
	template<class FromT>
	mat3(const mat3<FromT>& src)
	{
		for (int i = 0; i < 9; i++)
		{
			data[i] = static_cast<T>(src.data[i]);
		}
	}

	/**
	 * Resets mat to be identity mat
	 */
	void identity()
	{
		for (int i = 0; i < 9; i++)
			data[i] = (i % 4) ? 0 : 1;
	}

	/**
	 * Creates rotation mat by rotation around axis.
	 * @param xDeg Angle (in degrees) of rotation around axis X.
	 * @param yDeg Angle (in degrees) of rotation around axis Y.
	 * @param zDeg Angle (in degrees) of rotation around axis Z.
	 */
	static mat3<T> createRotationAroundAxis(T xDeg, T yDeg, T zDeg)
	{
		T xRads(DEG2RAD(xDeg));
		T yRads(DEG2RAD(yDeg));
		T zRads(DEG2RAD(zDeg));

		mat3<T> ma, mb, mc;
		float ac = cos(xRads);
		float as = sin(xRads);
		float bc = cos(yRads);
		float bs = sin(yRads);
		float cc = cos(zRads);
		float cs = sin(zRads);

		ma.at(1, 1) = ac;
		ma.at(2, 1) = as;
		ma.at(1, 2) = -as;
		ma.at(2, 2) = ac;

		mb.at(0, 0) = bc;
		mb.at(2, 0) = -bs;
		mb.at(0, 2) = bs;
		mb.at(2, 2) = bc;

		mc.at(0, 0) = cc;
		mc.at(1, 0) = cs;
		mc.at(0, 1) = -cs;
		mc.at(1, 1) = cc;

		mat3<T> ret = ma * mb * mc;
		return ret;
	}

	/**
	 * Creates rotation mat from ODE mat.
	 */
	template<class It>
	static mat3<T> fromOde(const It* mat)
	{
		mat3<T> ret;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ret.at(i, j) = static_cast<T>(mat[j * 4 + i]);
			}
		}
		return ret;
	}

	/**
	 * Creates new mat 3x3 from array that represents such mat 3x3
	 * as array of tightly packed elements in row major order.
	 * @param arr An array of elements for 3x3 mat in row major order.
	 * @return An instance of mat3<T> representing @a arr
	 */
	template<class FromT>
	static mat3<T> fromRowMajorArray(const FromT* arr)
	{
		const T retData[] =
		{ static_cast<T>(arr[0]), static_cast<T>(arr[3]), static_cast<T>(arr[6]), static_cast<T>(arr[1]),
				static_cast<T>(arr[4]), static_cast<T>(arr[7]), static_cast<T>(arr[2]), static_cast<T>(arr[5]),
				static_cast<T>(arr[8]) };

		return retData;
	}

	/**
	 * Creates new mat 3x3 from array that represents such mat 3x3
	 * as array of tightly packed elements in column major order.
	 * @param arr An array of elements for 3x3 mat in column major order.
	 * @return An instance of mat3<T> representing @a arr
	 */
	template<class FromT>
	static mat3<T> fromColumnMajorArray(const FromT* arr)
	{
		const T retData[] =
		{ static_cast<T>(arr[0]), static_cast<T>(arr[1]), static_cast<T>(arr[2]), static_cast<T>(arr[3]),
				static_cast<T>(arr[4]), static_cast<T>(arr[5]), static_cast<T>(arr[6]), static_cast<T>(arr[7]),
				static_cast<T>(arr[8]) };

		return retData;
	}

	//---------------------[ equiality operators ]------------------------------
	/**
	 * Equality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition all elements of mat 
	 * | lhs[i] - rhs[i] | < EPSILON,
	 * same for y-coordinate, z-coordinate, and w-coordinate.
	 */
	bool operator==(const mat3<T>& rhs) const
	{
		for (int i = 0; i < 9; i++)
		{
			if (std::abs(data[i] - rhs.data[i]) >= EPSILON)
				return false;
		}
		return true;
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const mat3<T>& rhs) const
	{
		return !(*this == rhs);
	}

	//---------------------[ access operators ]---------------------------------
	/**
	 * Get reference to element at position (x,y).
	 * @param x Number of column (0..2)
	 * @param y Number of row (0..2)
	 */
	T& at(int x, int y)
	{
		assert(x >= 0 && x < 3);
		assert(y >= 0 && y < 3);
		return data[x * 3 + y];
	}

	/**
	 * Get constant reference to element at position (x,y).
	 * @param x Number of column (0..2)
	 * @param y Number of row (0..2)
	 */
	const T& at(int x, int y) const
	{
		assert(x >= 0 && x < 3);
		assert(y >= 0 && y < 3);
		return data[x * 3 + y];
	}

	/**
	 * Get reference to element at position (i,j), with math mat notation
	 * @param i Number of row (1..3)
	 * @param j Number of column (1..3)
	 */
	T& operator()(int i, int j)
	{
		assert(i >= 1 && i <= 3);
		assert(j >= 1 && j <= 3);
		return data[(j - 1) * 3 + i - 1];
	}

	/**
	 * Get constant reference to element at position (i,j), with math mat notation
	 * @param i Number of row (1..3)
	 * @param j Number of column (1..3)
	 */
	const T& operator()(int i, int j) const
	{
		assert(i >= 1 && i <= 3);
		assert(j >= 1 && j <= 3);
		return data[(j - 1) * 3 + i - 1];
	}

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T>& operator=(const mat3<T>& rhs)
	{
		std::memcpy(data, rhs.data, sizeof(T) * 9);
		return *this;
	}

	/**
	 * Copy casting operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	mat3<T>& operator=(const mat3<FromT>& rhs)
	{
		for (int i = 0; i < 9; i++)
		{
			data[i] = static_cast<T>(rhs.data[i]);
		}
		return *this;
	}

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T>& operator=(const T* rhs)
	{
		std::memcpy(data, rhs, sizeof(T) * 9);
		return *this;
	}

	/*mat3<T> & operator=(const double* m)
	 {
	 for (int i = 0; i < 9; i++) data[i] = (T)m[i];
	 return * this;
	 }*/

	//--------------------[ mat with mat operations ]---------------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T> operator+(const mat3<T>& rhs) const
	{
		mat3<T> ret;
		for (int i = 0; i < 9; i++)
			ret.data[i] = data[i] + rhs.data[i];
		return ret;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T> operator-(const mat3<T>& rhs) const
	{
		mat3<T> ret;
		for (int i = 0; i < 9; i++)
			ret.data[i] = data[i] - rhs.data[i];
		return ret;
	}

	//--------------------[ mat with scalar operations ]---------------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T> operator+(T rhs) const
	{
		mat3<T> ret;
		for (int i = 0; i < 9; i++)
			ret.data[i] = data[i] + rhs;
		return ret;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T> operator-(T rhs) const
	{
		mat3<T> ret;
		for (int i = 0; i < 9; i++)
			ret.data[i] = data[i] - rhs;
		return ret;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T> operator*(T rhs) const
	{
		mat3<T> ret;
		for (int i = 0; i < 9; i++)
			ret.data[i] = data[i] * rhs;
		return ret;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T> operator/(T rhs) const
	{
		mat3<T> ret;
		for (int i = 0; i < 9; i++)
			ret.data[i] = data[i] / rhs;
		return ret;
	}

	//--------------------[ multiply operators ]--------------------------------
	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator*(const vec3<T>& rhs) const
	{
		return vec3<T>(data[0] * rhs.x + data[3] * rhs.y + data[6] * rhs.z,
				data[1] * rhs.x + data[4] * rhs.y + data[7] * rhs.z,
				data[2] * rhs.x + data[5] * rhs.y + data[8] * rhs.z);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat3<T> operator*(mat3<T> rhs) const
	{
		static mat3<T> w;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				T n = 0;
				for (int k = 0; k < 3; k++)
					n += rhs.at(i, k) * at(k, j);
				w.at(i, j) = n;
			}
		}
		return w;

	}
    
	//---------------------------[ misc operations ]----------------------------
	/**
	 * Transpose mat.
	 */
	mat3<T> transpose()
	{
		mat3<T> ret;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ret.at(i, j) = at(j, i);
			}
		}
		return ret;
	}

	/**
	 * Linear interpolation of two matrices
	 * @param fact Factor of interpolation. For translation from positon
	 * of this mat (lhs) to mat rhs, values of factor goes from 0.0 to 1.0.
	 * @param rhs Second mat for interpolation 
	 * @note However values of fact parameter are reasonable only in interval
	 * [0.0 , 1.0], you can pass also values outside of this interval and you
	 * can get result (extrapolation?)
	 */
	mat3<T> lerp(T fact, const mat3<T>& rhs) const
	{
		mat3<T> ret = (*this) + (rhs - (*this)) * fact;
		return ret;
	}

	T det()
	{
		return +at(0, 0) * at(1, 1) * at(2, 2) + at(0, 1) * at(1, 2) * at(2, 0) + at(0, 2) * at(1, 0) * at(2, 1)
				- at(0, 0) * at(1, 2) * at(2, 1) - at(0, 1) * at(1, 0) * at(2, 2) - at(0, 2) * at(1, 1) * at(2, 0);
	}

	/**
	 * Computes inverse mat
	 * @return Inverse mat of this mat.
	 */
	mat3<T> inverse()
	{
		mat3<T> ret;
		ret.at(0, 0) = at(1, 1) * at(2, 2) - at(2, 1) * at(1, 2);
		ret.at(0, 1) = at(2, 1) * at(0, 2) - at(0, 1) * at(2, 2);
		ret.at(0, 2) = at(0, 1) * at(1, 2) - at(1, 1) * at(0, 2);
		ret.at(1, 0) = at(2, 0) * at(1, 2) - at(1, 0) * at(2, 2);
		ret.at(1, 1) = at(0, 0) * at(2, 2) - at(2, 0) * at(0, 2);
		ret.at(1, 2) = at(1, 0) * at(0, 2) - at(0, 0) * at(1, 2);
		ret.at(2, 0) = at(1, 0) * at(2, 1) - at(2, 0) * at(1, 1);
		ret.at(2, 1) = at(2, 0) * at(0, 1) - at(0, 0) * at(2, 1);
		ret.at(2, 2) = at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);
		return ret * (1.0f / det());
	}

	//-------------[ conversion ]-----------------------------

	/**
	 * Conversion to pointer operator
	 * @return Pointer to internally stored (in management of class mat3<T>)
	 * used for passing mat3<T> values to gl*[fd]v functions.
	 */
	operator T*()
	{
		return (T*) data;
	}

	/**
	 * Conversion to pointer operator
	 * @return Constant Pointer to internally stored (in management of class mat3<T>)
	 * used for passing mat3<T> values to gl*[fd]v functions.
	 */
	operator const T*() const
	{
		return (const T*) data;
	}


	static mat3<T> & FromToMatrix(const vec3<T> & from, const vec3<T> & to)
	{
		mat3<T> mtx;
		const T e = from.dotProduct(to);
		const T f = (e < 0) ? -e : e;

		if (f > static_cast<T>(1.0) - static_cast<T>(0.00001))     /* "from" and "to"-vector almost parallel */
		{
			vec3f u, v;     /* temporary storage vectors */
			vec3f x;       /* vector most nearly orthogonal to "from" */

			x.x = (from.x > 0.0) ? from.x : -from.x;
			x.y = (from.y > 0.0) ? from.y : -from.y;
			x.z = (from.z > 0.0) ? from.z : -from.z;

			if (x.x < x.y)
			{
				if (x.x < x.z)
				{
					x.x = static_cast<T>(1.0);
					x.y = x.z = static_cast<T>(0.0);
				}
				else
				{
					x.z = static_cast<T>(1.0);
					x.x = x.y = static_cast<T>(0.0);
				}
			}
			else
			{
				if (x.y < x.z)
				{
					x.y = static_cast<T>(1.0);
					x.x = x.z = static_cast<T>(0.0);
				}
				else
				{
					x.z = static_cast<T>(1.0);
					x.x = x.y = static_cast<T>(0.0);
				}
			}

			u.x = x.x - from.x; u.y = x.y - from.y; u.z = x.z - from.z;
			v.x = x.x - to.x;   v.y = x.y - to.y;   v.z = x.z - to.z;

			const T c1_ = static_cast<T>(2.0) / (u.dotProduct(v));
			const T c2_ = static_cast<T>(2.0) / (v.dotProduct(v));
			const T c3_ = c1_ * c2_  * (u.dotProduct(v));

			for (unsigned int i = 0; i < 3; i++)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					mtx.at(j,i)= -c1_ * u[i] * u[j] - c2_ * v[i] * v[j]
						+ c3_ * v[i] * u[j];
				}
				mtx.at(i, i) += static_cast<T>(1.0);
			}
		}
		else  /* the most common case, unless "from"="to", or "from"=-"to" */
		{
			const vec3<T> v = from.crossProduct(to);
			/* ... use this hand optimized version (9 mults less) */
			const T h = static_cast<T>(1.0) / (static_cast<T>(1.0) + e);      /* optimization by Gottfried Chen */
			const T hvx = h * v.x;
			const T hvz = h * v.z;
			const T hvxy = hvx * v.y;
			const T hvxz = hvx * v.z;
			const T hvyz = hvz * v.y;
			mtx.at(0,0) = e + hvx * v.x;
			mtx.at(1,0) = hvxy - v.z;
			mtx.at(2,0) = hvxz + v.y;

			mtx.at(0,1) = hvxy + v.z;
			mtx.at(1,1) = e + h * v.y * v.y;
			mtx.at(2,1) = hvyz - v.x;

			mtx.at(0,2) = hvxz - v.y;
			mtx.at(1,2) = hvyz + v.x;
			mtx.at(2,2) = e + hvz * v.z;
		}
		return mtx;

	}

	public:
		static const mat3<T> Identity;

	//----------[ output operator ]----------------------------
	/**
	 * Output to stream operator
	 * @param lhs Left hand side argument of operator (commonly ostream instance). 
	 * @param rhs Right hand side argument of operator.
	 * @return Left hand side argument - the ostream object passed to operator.
	 */
	friend std::ostream& operator <<(std::ostream& lhs, const mat3<T>& rhs)
	{
		for (int i = 0; i < 3; i++)
		{
			lhs << "|\t";
			for (int j = 0; j < 3; j++)
			{
				lhs << rhs.at(j, i) << "\t";
			}
			lhs << "|" << std::endl;
		}
		return lhs;
	}

	/**
	 * Gets string representation.
	 */
	std::string toString() const
	{
		std::ostringstream oss;
		oss << *this;
		return oss.str();
	}
};

/// mat 3x3 of floats
typedef mat3<float> mat3f;
/// mat 3x3 of doubles
typedef mat3<double> mat3d;
/// mat 3x3 of int
typedef mat3<int> mat3i;

#endif //STRENDER_THIN_MATH

/**
 * Class for mat 4x4 
 * @note Data stored in this mat are in column major order. This arrangement suits OpenGL.
 * If you're using row major mat, consider using fromRowMajorArray as way for construction
 * mat4<T> instance.
 */
template<class T>
class mat4
{
public:
	/// Data stored in column major order
	T data[16];

	//--------------------------[ constructors ]-------------------------------
	/**
	 *Creates identity mat
	 */
	mat4()
	{
		for (int i = 0; i < 16; i++)
			data[i] = (i % 5) ? 0 : 1;
	}

	/**
	 * Copy mat values from array (these data must be in column
	 * major order!)
	 */
	mat4(const T * dt)
	{
		std::memcpy(data, dt, sizeof(T) * 16);
	}

	/**
	 * Copy constructor.
	 * @param src Data source for new created instance of mat4.
	 */
	mat4(const mat4<T>& src)
	{
#ifdef TRACE_MAT4_COPY_CONST
        std::cerr<<"mat4:[INFO] copy constructor called"<<std::endl;
#endif
		std::memcpy(data, src.data, sizeof(T) * 16);
	}


	mat4(const mat3<T> & src)
	{
		data[0] = src.data[0];
		data[1] = src.data[1];
		data[2] = src.data[2];
		data[3] = static_cast<T>(0.0);

		data[4] = src.data[3];
		data[5] = src.data[4];
		data[6] = src.data[5];
		data[7] = static_cast<T>(0.0);

		data[8] = src.data[6];
		data[9] = src.data[7];
		data[10] = src.data[8];
		data[11] = static_cast<T>(0.0);

		data[12] = static_cast<T>(0.0);
		data[13] = static_cast<T>(0.0);
		data[14] = static_cast<T>(0.0);
		data[15] = static_cast<T>(1.0);

	}

	/**
	 * Copy casting constructor.
	 * @param src Data source for new created instance of mat4.
	 */
	template<class FromT>
	mat4(const mat4<FromT>& src)
	{
		for (int i = 0; i < 16; i++)
		{
			data[i] = static_cast<T>(src.data[i]);
		}
	}

#ifdef ASSIMP_CONVERTION
	mat4(const aiMatrix4x4 & mat)
	{
		mat4<T> mat_4f;
		mat_4f.at(0, 0) = mat.a1; mat_4f.at(1, 0) = mat.a2; mat_4f.at(2, 0) = mat.a3; mat_4f.at(3, 0) = mat.a4;
		mat_4f.at(0, 1) = mat.b1; mat_4f.at(1, 1) = mat.b2; mat_4f.at(2, 1) = mat.b3; mat_4f.at(3, 1) = mat.b4;
		mat_4f.at(0, 2) = mat.c1; mat_4f.at(1, 2) = mat.c2; mat_4f.at(2, 2) = mat.c3; mat_4f.at(3, 2) = mat.c4;
		mat_4f.at(0, 3) = mat.d1; mat_4f.at(1, 3) = mat.d2; mat_4f.at(2, 3) = mat.d3; mat_4f.at(3, 3) = mat.d4;
		*this = mat_4f;

	}
#endif
	/**
	 * Resets mat to be identity mat
	 */
	void identity()
	{
		for (int i = 0; i < 16; i++)
			data[i] = (i % 5) ? 0 : 1;
	}

	/**
	 * Creates rotation mat by rotation around axis.
	 * @param xDeg Angle (in degrees) of rotation around axis X.
	 * @param yDeg Angle (in degrees) of rotation around axis Y.
	 * @param zDeg Angle (in degrees) of rotation around axis Z.
	 */
	static mat4<T> createRotationAroundAxis(T xDeg, T yDeg, T zDeg)
	{
		T xRads(DEG2RAD(xDeg));
		T yRads(DEG2RAD(yDeg));
		T zRads(DEG2RAD(zDeg));

		mat4<T> ma, mb, mc;
		float ac = cos(xRads);
		float as = sin(xRads);
		float bc = cos(yRads);
		float bs = sin(yRads);
		float cc = cos(zRads);
		float cs = sin(zRads);

		ma.at(1, 1) = ac;
		ma.at(2, 1) = as;
		ma.at(1, 2) = -as;
		ma.at(2, 2) = ac;

		mb.at(0, 0) = bc;
		mb.at(2, 0) = -bs;
		mb.at(0, 2) = bs;
		mb.at(2, 2) = bc;

		mc.at(0, 0) = cc;
		mc.at(1, 0) = cs;
		mc.at(0, 1) = -cs;
		mc.at(1, 1) = cc;

		/*std::cout << "RotVec = " << a << "," << b << "," << c << std::endl;
		 std::cout << "Rx = " << std::endl << ma;
		 std::cout << "Ry = " << std::endl << mb;
		 std::cout << "Rz = " << std::endl << mc;*/

		mat4<T> ret = ma * mb * mc;
		//std::cout << "Result = " << std::endl << ma * (mb * mc);

		return ret;
	}

	static mat4<T> createRotationAroundAxis_unity(T xDeg, T yDeg, T zDeg)
	{
		T xRads(DEG2RAD(xDeg));
		T yRads(DEG2RAD(yDeg));
		T zRads(DEG2RAD(zDeg));

		mat4<T> ma, mb, mc;
		float ac = cos(xRads);
		float as = sin(xRads);
		float bc = cos(yRads);
		float bs = sin(yRads);
		float cc = cos(zRads);
		float cs = sin(zRads);

		ma.at(1, 1) = ac;
		ma.at(2, 1) = as;
		ma.at(1, 2) = -as;
		ma.at(2, 2) = ac;

		mb.at(0, 0) = bc;
		mb.at(2, 0) = -bs;
		mb.at(0, 2) = bs;
		mb.at(2, 2) = bc;

		mc.at(0, 0) = cc;
		mc.at(1, 0) = cs;
		mc.at(0, 1) = -cs;
		mc.at(1, 1) = cc;

		/*std::cout << "RotVec = " << a << "," << b << "," << c << std::endl;
		std::cout << "Rx = " << std::endl << ma;
		std::cout << "Ry = " << std::endl << mb;
		std::cout << "Rz = " << std::endl << mc;*/

		//mat4<T> ret = ma * mb * mc;
		//std::cout << "Result = " << std::endl << ma * (mb * mc);
		mat4<T>ret = mb * ma * mc;//unity uses yxz order to represent rotation.
		return ret;
	}


	/// Creates translation mat
	/**
	 * Creates translation mat.
	 * @param x X-direction translation
	 * @param y Y-direction translation
	 * @param z Z-direction translation
	 * @param w for W-coordinate translation (implicitly set to 1)
	 */
	static mat4<T> createTranslation(T x, T y, T z, T w = 1)
	{
		mat4 ret;
		ret.at(3, 0) = x;
		ret.at(3, 1) = y;
		ret.at(3, 2) = z;
		ret.at(3, 3) = w;

		return ret;
	}
	
	static mat4<T> createTranslation(const vec3<T>& v) {
		return createTranslation(v.x, v.y, v.z);
	}

	static mat4<T> createScale(T x, T y, T z) {
		mat4 ret;
		ret.at(0, 0) = x;
		ret.at(1, 1) = y;
		ret.at(2, 2) = z;

		return ret;
	}

	static mat4<T> createScale(const vec3<T>& v) {
		return createScale(v.x, v.y, v.z);
	}
	/**
	 * Creates new view mat to look from specified position @a eyePos to specified position @a centerPos
	 * @param eyePos A position of camera
	 * @param centerPos A position where camera looks-at
	 * @param upDir Direction of up vec
	 * @return Resulting view mat that looks from and at specific position.
	 */
	static mat4<T> createLookAt(const vec3<T>& eyePos, const vec3<T>& centerPos, const vec3<T>& upDir)
	{
        
		vec3<T> forward, side, up;
		mat4<T> m;

		forward = centerPos - eyePos;
		up = upDir;

		forward.normalize();

		// Side = forward x up
		side = forward.crossProduct(up);
		side.normalize();

		// Recompute up as: up = side x forward
		up = side.crossProduct(forward);

		m.at(0, 0) = side.x;
		m.at(1, 0) = side.y;
		m.at(2, 0) = side.z;

		m.at(0, 1) = up.x;
		m.at(1, 1) = up.y;
		m.at(2, 1) = up.z;

		m.at(0, 2) = -forward.x;
		m.at(1, 2) = -forward.y;
		m.at(2, 2) = -forward.z;

		m = m * mat4<T>::createTranslation(-eyePos.x, -eyePos.y, -eyePos.z);
		return m;
#ifdef ZERO___
        vec3<T> x,y,z;
		mat4<T> m0, m1, m;
        
		z = eyePos - centerPos;
		z.normalize();
		x = upDir.crossProduct(z);
		x.normalize();
		y = z.crossProduct(x);
		y.normalize();
		m0[0] = x.x; m0[4] = x.y; m0[8] = x.z; m0[12] = 0.0;
		m0[1] = y.x; m0[5] = y.y; m0[9] = y.z; m0[13] = 0.0;
		m0[2] = z.x; m0[6] = z.y; m0[10] = z.z; m0[14] = 0.0;
		m0[3] = 0.0; m0[7] = 0.0; m0[11] = 0.0; m0[15] = 1.0;
		m1 = mat4<T>::createTranslation(-eyePos.x, -eyePos.y, -eyePos.z);
		m = m0 * m1;
        return m;
#endif
	}


	/**
	 * Creates OpenGL compatible perspective projection according specified frustum parameters.
	 *
	 * @param left Specify the coordinate for the left vertical clipping plane,
	 * @param right Specify the coordinate for the right vertical clipping plane.
	 * @param bottom Specify the coordinate for the bottom horizontal clipping plane,
	 * @param top Specify the coordinate for the top horizontal clipping plane.
	 * @param zNear Specify the distance to the near clipping plane.  Distance must be positive.
	 * @param zFar Specify the distance to the far depth clipping plane.  Distance must be positive.
	 *
	 * @return Projection mat for specified frustum.
	 */
	static mat4<T> createFrustum(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		/*
		 *
      	  2 zNear
        ------------       0              A              0
        right - left

                        2 zNear
            0         ------------        B              0
                      top - bottom

            0              0              C              D

            0              0              -1             0

                                                     A = (right + left) / (right - left)

                                                     B = (top + bottom) / (top - bottom)

                                                    C = - (zFar + zNear) / (zFar - zNear)

                                                    D = - (2 zFar zNear) / (zFar - zNear)
		 *
		 */
		mat4<T> ret;

		const T invWidth = 1.0 / (right - left);
		const T invHeight = 1.0 / (top - bottom);
		const T invDepth = 1.0 / (zFar - zNear);

		const T twoZNear = 2 * zNear;

		ret.at(0,0) = twoZNear * invWidth;
		ret.at(1,1) = twoZNear * invHeight;

		ret.at(2,0) = (right + left) * invWidth;
		ret.at(2,1) = (top + bottom) * invHeight;
		ret.at(2,2) = - (zFar + zNear) * invDepth;
		ret.at(2,3) = -1;

		ret.at(3,2) = - twoZNear * zFar * invDepth;
        ret.at(3,3) = 0.0f;

		return ret;
	}

    /**
	 * Creates OpenGL compatible perspective projection according specified perspective parameters.
	 *
	 * @param T Specify the field of view,
	 * @param aspect aspect ration
	 * @param zNear Specify the distance to the near clipping plane.  Distance must be positive.
	 * @param zFar Specify the distance to the far depth clipping plane.  Distance must be positive.
	 *
	 * @return Projection mat for specified frustum.
	 */
	static mat4<T> createPerspective(T fov,T aspect, T zNear, T zFar)
	{
		/*
		 *
         2 zNear
         ------------       0              A              0
         right - left
         
         2 zNear
         0         ------------        B              0
         top - bottom
         
         0              0              C              D
         
         0              0              -1             0
         
         A = (right + left) / (right - left)
         
         B = (top + bottom) / (top - bottom)
         
         C = - (zFar + zNear) / (zFar - zNear)
         
         D = - (2 zFar zNear) / (zFar - zNear)
		 *
		 */
        
        mat4<T> ret;
        T y = (T)tan(fov * M_PI / 360.0f);
		T x = y * aspect;
		ret[0] = 1.0f / x; ret[4] = 0.0;      ret[8] = 0.0;                               ret[12] = 0.0;
		ret[1] = 0.0;      ret[5] = 1.0f / y; ret[9] = 0.0;                               ret[13] = 0.0;
		ret[2] = 0.0;      ret[6] = 0.0;      ret[10] = -(zFar + zNear) / (zFar - zNear); ret[14] = -(2.0f * zFar * zNear) / (zFar - zNear);
		ret[3] = 0.0;      ret[7] = 0.0;      ret[11] = -1.0;                             ret[15] = 0.0;
        
		return ret;
	}
    
    
	/**
	 * Creates OpenGL compatible orthographic projection mat.
	 * @param left Specify the coordinate for the left vertical clipping plane,
	 * @param right Specify the coordinate for the right vertical clipping plane.
	 * @param bottom Specify the coordinate for the bottom horizontal clipping plane,
	 * @param top Specify the coordinate for the top horizontal clipping plane.
	 * @param zNear Specify the distance to the nearer depth clipping plane.
	 *       This value is negative if the plane is to be behind the viewer,
	 * @param zFar Specify the distance to the farther depth clipping plane.
	 *       This value is negative if the plane is to be behind the viewer.
	 * @return Othrographic projection mat.
	 */
	static mat4<T> createOrtho(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		/*
		   	   2
        ------------       0              0              tx
        right - left

                           2
            0         ------------        0              ty
                      top - bottom

                                          -2
            0              0         ------------        tz
                                      zFar-zNear

            0              0              0              1

       where

                                                    tx = - (right + left) / (right - left)

                                                    ty = - (top + bottom) / (top - bottom)

                                                    tz = - (zFar + zNear) / (zFar - zNear)

		 */

		const T invWidth = 1.0 / (right  - left);
		const T invHeight = 1.0 / (top - bottom);
		const T invDepth = 1.0 / (zFar - zNear);

		mat4<T> ret;

		ret.at(0,0) = 2 * invWidth;
		ret.at(1,1) = 2 * invHeight;
		ret.at(2,2) = -2 * invDepth;

		ret.at(3,0) = -(right + left) * invWidth;
		ret.at(3,1) = -(top + bottom) * invHeight;
		ret.at(3,2) = -(zFar + zNear) * invDepth;

		return ret;
	}

	static mat4<T> FromToMatrix(const vec3<T> & from, const vec3<T> & to)
	{
		return mat4<T>(mat3<T>::FromToMatrix(from, to));
	}
#ifndef STRENDER_THIN_MATH
	/**
	 * Creates new mat 4x4 from array that represents such mat 4x4
	 * as array of tightly packed elements in row major order.
	 * @param arr An array of elements for 4x4 mat in row major order.
	 * @return An instance of mat4<T> representing @a arr
	 */
	template<class FromT>
	static mat4<T> fromRowMajorArray(const FromT* arr)
	{
		const T retData[] =
		{ static_cast<T>(arr[0]), static_cast<T>(arr[4]), static_cast<T>(arr[8]), static_cast<T>(arr[12]),
				static_cast<T>(arr[1]), static_cast<T>(arr[5]), static_cast<T>(arr[9]), static_cast<T>(arr[13]),
				static_cast<T>(arr[2]), static_cast<T>(arr[6]), static_cast<T>(arr[10]), static_cast<T>(arr[14]),
				static_cast<T>(arr[3]), static_cast<T>(arr[7]), static_cast<T>(arr[11]), static_cast<T>(arr[15]) };

		return retData;
	}

	/**
	 * Creates new mat 4x4 from array that represents such mat 4x4
	 * as array of tightly packed elements in column major order.
	 * @param arr An array of elements for 4x4 mat in column major order.
	 * @return An instance of mat4<T> representing @a arr
	 */
	template<class FromT>
	static mat4<T> fromColumnMajorArray(const FromT* arr)
	{
		const T retData[] =
		{ static_cast<T>(arr[0]), static_cast<T>(arr[1]), static_cast<T>(arr[2]), static_cast<T>(arr[3]),
				static_cast<T>(arr[4]), static_cast<T>(arr[5]), static_cast<T>(arr[6]), static_cast<T>(arr[7]),
				static_cast<T>(arr[8]), static_cast<T>(arr[9]), static_cast<T>(arr[10]), static_cast<T>(arr[11]),
				static_cast<T>(arr[12]), static_cast<T>(arr[13]), static_cast<T>(arr[14]), static_cast<T>(arr[15]) };

		return retData;
	}
    
#endif //STRENDER_THIN_MATH

	//---------------------[ Equality operators ]------------------------------
	/**
	 * Equality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition all elements of mat 
	 * | lhs[i] - rhs[i] | < EPSILON,
	 * same for y-coordinate, z-coordinate, and w-coordinate.
	 */
	bool operator==(const mat4<T>& rhs) const
	{
		for (int i = 0; i < 16; i++)
		{
			if (std::abs(data[i] - rhs.data[i]) >= EPSILON
				)
				return false;
		}
		return true;
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const mat4<T>& rhs) const
	{
		return !(*this == rhs);
	}

	//---------------------[ access operators ]---------------------------------
	/**
	 * Get reference to element at postion (x,y).
	 * @param x Number of column (0..3)
	 * @param y Number of row (0..3)
	 */
	T& at(int x, int y)
	{
		assert(x >= 0 && x < 4);
		assert(y >= 0 && y < 4);
		return data[x * 4 + y];
	}

	/**
	 * Get constant reference to element at position (x,y).
	 * @param x Number of column (0..3)
	 * @param y Number of row (0..3)
	 */
	const T& at(int x, int y) const
	{
		assert(x >= 0 && x < 4);
		assert(y >= 0 && y < 4);
		return data[x * 4 + y];
	}

	/**
	 * Get reference to element at position (i,j), with math mat notation
	 * @param i Number of row (1..4)
	 * @param j Number of column (1..4)
	 */
	T& operator()(int i, int j)
	{
		assert(i >= 1 && i <= 4);
		assert(j >= 1 && j <= 4);
		return data[(j - 1) * 4 + i - 1];
	}

	/**
	 * Get constant reference to element at position (i,j), with math mat notation
	 * @param i Number of row (1..4)
	 * @param j Number of column (1..4)
	 */
	const T& operator()(int i, int j) const
	{
		assert(i >= 1 && i <= 4);
		assert(j >= 1 && j <= 4);
		return data[(j - 1) * 4 + i - 1];
	}

	/**
	 * Sets translation part of mat.
	 *
	 * @param v vec of translation to be set.
	 */
	void setTranslation(const vec3<T>& v)
	{
		at(3, 0) = v.x;
		at(3, 1) = v.y;
		at(3, 2) = v.z;
		at(3, 3) = 1;
	}

	vec3<T> getTranslation() const
	{
		return vec3<T>(at(3, 0), at(3, 1), at(3, 2));
	}

	void SetScale(const vec3<T>& v)
	{
		at(0, 0) = v.x;  at(0, 1) = 0;   at(0, 2) = 0;   at(0, 3) =0;
		at(1, 0) = 0;    at(1, 1) = v.y; at(2, 2) = 0;   at(3, 3) = 0;
		at(2, 0) = 0;    at(2, 1) = 0;   at(2, 2) = v.z; at(3, 3) = 0;
		at(3, 0) = 0;    at(3, 1) = 0;   at(2, 2) = 0;   at(3, 3) = 0;

	}
	vec3<T> getScale() const
	{
		vec3<T> vCols[3] = {
			vec3<T>(at(0,0),at(0,1),at(0,2)),
			vec3<T>(at(1,0),at(1,1),at(1,2)),
			vec3<T>(at(2,0),at(2,1),at(2,2))
		};
		vec3<T> scale;
		scale.x = vCols[0].length();
		scale.y = vCols[1].length();
		scale.z = vCols[2].length();
		return scale;
	}
	
	void Decompose(vec3<T> & scale, quat<T> & rotation, vec3<T> & position) const
	{
		const mat4<T> & _this = *this;
		position = _this.getTranslation();

		vec3<T> vCols[3] = {
			vec3<T>(at(0,0),at(0,1),at(0,2)),
			vec3<T>(at(1,0),at(1,1),at(1,2)),
			vec3<T>(at(2,0),at(2,1),at(2,2))
		};

		scale.x = vCols[0].length();
		scale.y = vCols[1].length();
		scale.z = vCols[2].length();

		if (det() < 0)
			scale *= -1;
		if (scale.x) vCols[0] /= scale.x;
		if (scale.y) vCols[1] /= scale.y;
		if (scale.z) vCols[2] /= scale.z;

		mat3<T> m(vCols[0][0], vCols[0][1], vCols[0][2]
				, vCols[1][0], vCols[1][1], vCols[1][2]
				, vCols[2][0], vCols[2][1], vCols[2][2]);
		rotation = quat<T>::frommat(m);

	}

	static mat4<T> Compose(const vec3<T> & scale, const quat<T> & rotation, const vec3<T> & position)
	{

		mat4<T> result;
		mat3<T> m = rotation.rotmat();


		result.at(0, 0) = m.at(0, 0) * scale.x;
		result.at(1, 0) = m.at(1, 0) * scale.x;
		result.at(2, 0) = m.at(2, 0) * scale.x;
		result.at(3, 0) = position.x;

		result.at(0, 1) = m.at(0, 1) * scale.y;
		result.at(1, 1) = m.at(1, 1) * scale.y;
		result.at(2, 1) = m.at(2, 1) * scale.y;
		result.at(3, 1) = position.y;

		result.at(0, 2) = m.at(0, 2) * scale.z;
		result.at(1, 2) = m.at(1, 2) * scale.z;
		result.at(2, 2) = m.at(2, 2) * scale.z;
		result.at(3, 2) = position.z;

		result.at(0, 3) = static_cast<T>(0.0);
		result.at(1, 3) = static_cast<T>(0.0);
		result.at(2, 3) = static_cast<T>(0.0);
		result.at(3, 3) = static_cast<T>(1.0);

		return result;
		
	}

	/**
	 * Sets rotation part (mat 3x3) of mat.
	 *
	 * @param m Rotation part of mat
	 */

#ifndef STRENDER_THIN_MATH
	void setRotation(const mat3<T>& m)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				at(i, j) = m.at(i, j);
			}
		}
	}
#endif //STRENDER_THIN_MATH

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T>& operator=(const mat4<T>& rhs)
	{
#ifdef TRACE_MAT4_COPY_CONST
        std::cerr<<"mat4:[INFO] equal operator called"<<std::endl;
#endif
		std::memcpy(data, rhs.data, sizeof(T) * 16);
		return *this;
	}

	/**
	 * Copy casting operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	mat4<T>& operator=(const mat4<FromT>& rhs)
	{
		for (int i = 0; i < 16; i++)
		{
			data[i] = static_cast<T>(rhs.data[i]);
		}
		return *this;
	}

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T>& operator=(const T* rhs)
	{
		std::memcpy(data, rhs, sizeof(T) * 16);
		return *this;
	}

	/*mat4<T> & operator=(const double* m)
	 {
	 for (int i = 0; i < 16; i++) data[i] = (T)m[i];
	 return * this;
	 }*/

	//--------------------[ mat with mat operations ]---------------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T> operator+(const mat4<T>& rhs) const
	{
		mat4<T> ret;
		for (int i = 0; i < 16; i++)
			ret.data[i] = data[i] + rhs.data[i];
		return ret;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T> operator-(const mat4<T>& rhs) const
	{
		mat4<T> ret;
		for (int i = 0; i < 16; i++)
			ret.data[i] = data[i] - rhs.data[i];
		return ret;
	}

	//--------------------[ mat with scalar operations ]---------------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T> operator+(T rhs) const
	{
		mat4<T> ret;
		for (int i = 0; i < 16; i++)
			ret.data[i] = data[i] + rhs;
		return ret;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T> operator-(T rhs) const
	{
		mat4<T> ret;
		for (int i = 0; i < 16; i++)
			ret.data[i] = data[i] - rhs;
		return ret;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T> operator*(T rhs) const
	{
		mat4<T> ret;
		for (int i = 0; i < 16; i++)
			ret.data[i] = data[i] * rhs;
		return ret;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T> operator/(T rhs) const
	{
		mat4<T> ret;
		for (int i = 0; i < 16; i++)
			ret.data[i] = data[i] / rhs;
		return ret;
	}

	//--------------------[ multiply operators ]--------------------------------
	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec4<T> operator*(const vec4<T>& rhs) const
	{
		return vec4<T>(data[0] * rhs.x + data[4] * rhs.y + data[8] * rhs.z + data[12] * rhs.w,
				data[1] * rhs.x + data[5] * rhs.y + data[9] * rhs.z + data[13] * rhs.w,
				data[2] * rhs.x + data[6] * rhs.y + data[10] * rhs.z + data[14] * rhs.w,
				data[3] * rhs.x + data[7] * rhs.y + data[11] * rhs.z + data[15] * rhs.w);

	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vec3<T> operator*(const vec3<T>& rhs) const
	{
		return vec3<T>(data[0] * rhs.x + data[4] * rhs.y + data[8] * rhs.z,
				data[1] * rhs.x + data[5] * rhs.y + data[9] * rhs.z,
				data[2] * rhs.x + data[6] * rhs.y + data[10] * rhs.z);
		
	}
    
    /**
     * Multiplication operator
     * @param rhs Right hand side argument of binary operator.
     */
    vec3<T> MultiplyPoint(const vec3<T>& rhs) const
    {
        return vec3<T>(data[0] * rhs.x + data[4] * rhs.y + data[8] * rhs.z + data[12] ,
                       data[1] * rhs.x + data[5] * rhs.y + data[9] * rhs.z + data[13] ,
                       data[2] * rhs.x + data[6] * rhs.y + data[10] * rhs.z + data[14]);
    }

    vec3<T> MultiplyVector(const vec3<T>& rhs) const
    {
        return vec3<T>(data[0] * rhs.x + data[4] * rhs.y + data[8] * rhs.z,
                       data[1] * rhs.x + data[5] * rhs.y + data[9] * rhs.z,
                       data[2] * rhs.x + data[6] * rhs.y + data[10] * rhs.z);
    }

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	mat4<T> operator*(mat4<T> rhs) const
	{
		static mat4<T> w;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				T n = 0;
				for (int k = 0; k < 4; k++)
					n += rhs.at(i, k) * at(k, j);
				w.at(i, j) = n;
			}
		}
		return w;

	}

	//---------------------------[ misc operations ]----------------------------

	/**
	 * Computes determinant of mat
	 * @return Determinant of mat
	 * @note This function does 3 * 4 * 6 mul, 3 * 6 add.
	 */
	T det() const
	{

		return +at(3, 0) * at(2, 1) * at(1, 2) * at(0, 3) - at(2, 0) * at(3, 1) * at(1, 2) * at(0, 3)
				- at(3, 0) * at(1, 1) * at(2, 2) * at(0, 3) + at(1, 0) * at(3, 1) * at(2, 2) * at(0, 3)

		+ at(2, 0) * at(1, 1) * at(3, 2) * at(0, 3) - at(1, 0) * at(2, 1) * at(3, 2) * at(0, 3)
				- at(3, 0) * at(2, 1) * at(0, 2) * at(1, 3) + at(2, 0) * at(3, 1) * at(0, 2) * at(1, 3)

		+ at(3, 0) * at(0, 1) * at(2, 2) * at(1, 3) - at(0, 0) * at(3, 1) * at(2, 2) * at(1, 3)
				- at(2, 0) * at(0, 1) * at(3, 2) * at(1, 3) + at(0, 0) * at(2, 1) * at(3, 2) * at(1, 3)

		+ at(3, 0) * at(1, 1) * at(0, 2) * at(2, 3) - at(1, 0) * at(3, 1) * at(0, 2) * at(2, 3)
				- at(3, 0) * at(0, 1) * at(1, 2) * at(2, 3) + at(0, 0) * at(3, 1) * at(1, 2) * at(2, 3)

		+ at(1, 0) * at(0, 1) * at(3, 2) * at(2, 3) - at(0, 0) * at(1, 1) * at(3, 2) * at(2, 3)
				- at(2, 0) * at(1, 1) * at(0, 2) * at(3, 3) + at(1, 0) * at(2, 1) * at(0, 2) * at(3, 3)

		+ at(2, 0) * at(0, 1) * at(1, 2) * at(3, 3) - at(0, 0) * at(2, 1) * at(1, 2) * at(3, 3)
				- at(1, 0) * at(0, 1) * at(2, 2) * at(3, 3) + at(0, 0) * at(1, 1) * at(2, 2) * at(3, 3);

	}

	/**
	 * Computes inverse mat
	 * @return Inverse mat of this mat.
	 * @note This is a little bit time consuming operation
	 * (16 * 6 * 3 mul, 16 * 5 add + det() + mul() functions)
	 */
	mat4<T> inverse() const
	{
		mat4<T> ret;

		ret.at(0, 0) = +at(2, 1) * at(3, 2) * at(1, 3) - at(3, 1) * at(2, 2) * at(1, 3) + at(3, 1) * at(1, 2) * at(2, 3)
				- at(1, 1) * at(3, 2) * at(2, 3) - at(2, 1) * at(1, 2) * at(3, 3) + at(1, 1) * at(2, 2) * at(3, 3);

		ret.at(1, 0) = +at(3, 0) * at(2, 2) * at(1, 3) - at(2, 0) * at(3, 2) * at(1, 3) - at(3, 0) * at(1, 2) * at(2, 3)
				+ at(1, 0) * at(3, 2) * at(2, 3) + at(2, 0) * at(1, 2) * at(3, 3) - at(1, 0) * at(2, 2) * at(3, 3);

		ret.at(2, 0) = +at(2, 0) * at(3, 1) * at(1, 3) - at(3, 0) * at(2, 1) * at(1, 3) + at(3, 0) * at(1, 1) * at(2, 3)
				- at(1, 0) * at(3, 1) * at(2, 3) - at(2, 0) * at(1, 1) * at(3, 3) + at(1, 0) * at(2, 1) * at(3, 3);

		ret.at(3, 0) = +at(3, 0) * at(2, 1) * at(1, 2) - at(2, 0) * at(3, 1) * at(1, 2) - at(3, 0) * at(1, 1) * at(2, 2)
				+ at(1, 0) * at(3, 1) * at(2, 2) + at(2, 0) * at(1, 1) * at(3, 2) - at(1, 0) * at(2, 1) * at(3, 2);

		ret.at(0, 1) = +at(3, 1) * at(2, 2) * at(0, 3) - at(2, 1) * at(3, 2) * at(0, 3) - at(3, 1) * at(0, 2) * at(2, 3)
				+ at(0, 1) * at(3, 2) * at(2, 3) + at(2, 1) * at(0, 2) * at(3, 3) - at(0, 1) * at(2, 2) * at(3, 3);

		ret.at(1, 1) = +at(2, 0) * at(3, 2) * at(0, 3) - at(3, 0) * at(2, 2) * at(0, 3) + at(3, 0) * at(0, 2) * at(2, 3)
				- at(0, 0) * at(3, 2) * at(2, 3) - at(2, 0) * at(0, 2) * at(3, 3) + at(0, 0) * at(2, 2) * at(3, 3);

		ret.at(2, 1) = +at(3, 0) * at(2, 1) * at(0, 3) - at(2, 0) * at(3, 1) * at(0, 3) - at(3, 0) * at(0, 1) * at(2, 3)
				+ at(0, 0) * at(3, 1) * at(2, 3) + at(2, 0) * at(0, 1) * at(3, 3) - at(0, 0) * at(2, 1) * at(3, 3);

		ret.at(3, 1) = +at(2, 0) * at(3, 1) * at(0, 2) - at(3, 0) * at(2, 1) * at(0, 2) + at(3, 0) * at(0, 1) * at(2, 2)
				- at(0, 0) * at(3, 1) * at(2, 2) - at(2, 0) * at(0, 1) * at(3, 2) + at(0, 0) * at(2, 1) * at(3, 2);

		ret.at(0, 2) = +at(1, 1) * at(3, 2) * at(0, 3) - at(3, 1) * at(1, 2) * at(0, 3) + at(3, 1) * at(0, 2) * at(1, 3)
				- at(0, 1) * at(3, 2) * at(1, 3) - at(1, 1) * at(0, 2) * at(3, 3) + at(0, 1) * at(1, 2) * at(3, 3);

		ret.at(1, 2) = +at(3, 0) * at(1, 2) * at(0, 3) - at(1, 0) * at(3, 2) * at(0, 3) - at(3, 0) * at(0, 2) * at(1, 3)
				+ at(0, 0) * at(3, 2) * at(1, 3) + at(1, 0) * at(0, 2) * at(3, 3) - at(0, 0) * at(1, 2) * at(3, 3);

		ret.at(2, 2) = +at(1, 0) * at(3, 1) * at(0, 3) - at(3, 0) * at(1, 1) * at(0, 3) + at(3, 0) * at(0, 1) * at(1, 3)
				- at(0, 0) * at(3, 1) * at(1, 3) - at(1, 0) * at(0, 1) * at(3, 3) + at(0, 0) * at(1, 1) * at(3, 3);

		ret.at(3, 2) = +at(3, 0) * at(1, 1) * at(0, 2) - at(1, 0) * at(3, 1) * at(0, 2) - at(3, 0) * at(0, 1) * at(1, 2)
				+ at(0, 0) * at(3, 1) * at(1, 2) + at(1, 0) * at(0, 1) * at(3, 2) - at(0, 0) * at(1, 1) * at(3, 2);

		ret.at(0, 3) = +at(2, 1) * at(1, 2) * at(0, 3) - at(1, 1) * at(2, 2) * at(0, 3) - at(2, 1) * at(0, 2) * at(1, 3)
				+ at(0, 1) * at(2, 2) * at(1, 3) + at(1, 1) * at(0, 2) * at(2, 3) - at(0, 1) * at(1, 2) * at(2, 3);

		ret.at(1, 3) = +at(1, 0) * at(2, 2) * at(0, 3) - at(2, 0) * at(1, 2) * at(0, 3) + at(2, 0) * at(0, 2) * at(1, 3)
				- at(0, 0) * at(2, 2) * at(1, 3) - at(1, 0) * at(0, 2) * at(2, 3) + at(0, 0) * at(1, 2) * at(2, 3);

		ret.at(2, 3) = +at(2, 0) * at(1, 1) * at(0, 3) - at(1, 0) * at(2, 1) * at(0, 3) - at(2, 0) * at(0, 1) * at(1, 3)
				+ at(0, 0) * at(2, 1) * at(1, 3) + at(1, 0) * at(0, 1) * at(2, 3) - at(0, 0) * at(1, 1) * at(2, 3);

		ret.at(3, 3) = +at(1, 0) * at(2, 1) * at(0, 2) - at(2, 0) * at(1, 1) * at(0, 2) + at(2, 0) * at(0, 1) * at(1, 2)
				- at(0, 0) * at(2, 1) * at(1, 2) - at(1, 0) * at(0, 1) * at(2, 2) + at(0, 0) * at(1, 1) * at(2, 2);

		return ret / det();
	}

	/**
	 * Transpose mat.
	 */
	mat4<T> transpose()
	{
		mat4<T> ret;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ret.at(i, j) = at(j, i);
			}
		}
		return ret;
	}

	/**
	 * Linear interpolation of two matrices
	 * @param fact Factor of interpolation. For translation from positon
	 * of this mat (lhs) to mat rhs, values of factor goes from 0.0 to 1.0.
	 * @param rhs Second mat for interpolation 
	 * @note However values of fact parameter are reasonable only in interval
	 * [0.0 , 1.0], you can pass also values outside of this interval and you
	 * can get result (extrapolation?)
	 */
	mat4<T> lerp(T fact, const mat4<T>& rhs) const
	{
		mat4<T> ret = (*this) + (rhs - (*this)) * fact;
		return ret;
	}
    
	//-------------[ conversion ]-----------------------------
	/**
	 * Conversion to pointer operator
	 * @return Pointer to internally stored (in management of class mat4<T>)
	 * used for passing mat4<T> values to gl*[fd]v functions.
	 */
	operator T*()
	{
		return (T*) data;
	}

	/**
	 * Conversion to pointer operator
	 * @return Constant Pointer to internally stored (in management of class mat4<T>)
	 * used for passing mat4<T> values to gl*[fd]v functions.
	 */
	operator const T*() const
	{
		return (const T*) data;
	}

public:
	static const mat4<T> Identity;
#ifndef STRENDER_THIN_MATH
	//----------[ output operator ]----------------------------
	/**
	 * Output to stream operator
	 * @param lhs Left hand side argument of operator (commonly ostream instance). 
	 * @param rhs Right hand side argument of operator.
	 * @return Left hand side argument - the ostream object passed to operator.
	 */
	friend std::ostream& operator <<(std::ostream& lhs, const mat4<T>& rhs)
	{
		for (int i = 0; i < 4; i++)
		{
			lhs << "|\t";
			for (int j = 0; j < 4; j++)
			{
				lhs << rhs.at(j, i) << "\t";
			}
			lhs << "|" << std::endl;
		}
		return lhs;
	}

	/**
	 * Gets string representation.
	 */
	std::string toString() const
	{
		std::ostringstream oss;
		oss << *this;
		return oss.str();
	}
    
#endif //STRENDER_THIN_MATH

};

/// mat 4x4 of floats
typedef mat4<float> mat4f;
/// mat 4x4 of doubles
typedef mat4<double> mat4d;
/// mat 4x4 of int
typedef mat4<int> mat4i;

/**
 * quat class implementing some quat algebra operations.
 * quat is kind of complex number it consists of its real part (w)
 * and its complex part v. This complex part has three elements, so we
 * can express it as xi + yj + zk . Note that coordinates of (x,y,z) are
 * hold inside v field.
 */
template<class T>
class quat
{
public:
	/**
	 * Real part of quat.
	 */
	T w;
	/**
	 * Imaginary part of quat.
	 */
	vec3<T> v;

	/**
	 * quat constructor, sets quat to (0 + 0i + 0j + 0k).
	 */
	quat()
			: w(0), v(0, 0, 0)
	{
	}

	/**
	 * Copy constructor.
	 */
	quat(const quat<T>& q)
			: w(q.w), v(q.v)
	{
	}

	/**
	 * Copy casting constructor.
	 */
	template<class FromT>
	quat(const quat<FromT>& q)
			: w(static_cast<T>(q.w)), v(q.v)
	{
	}

	/**
	 * Creates quat object from real part w_ and complex part v_.
	 * @param w_ Real part of quat.
	 * @param v_ Complex part of quat (xi + yj + zk).
	 */
	quat(T w_, const vec3<T>& v_)
			: w(w_), v(v_)
	{
	}

	/**
	 * Creates quat object from value (w_ + xi + yj + zk).
	 * @param w_ Real part of quat.
	 * @param x Complex coefficient for i complex constant.
	 * @param y Complex coefficient for j complex constant.
	 * @param z Complex coefficient for k complex constant.
	 */
	quat(T w_, T x, T y, T z)
			: w(w_), v(x, y, z)
	{
	}
	/*quat(T x, T y, T z, T w_)
		: w(w_), v(x, y, z)
	{
	}*/

#ifdef ASSIMP_CONVERTION
	quat(const aiQuaternion & rhs): w(rhs.w), v(rhs.x, rhs.y, rhs.z)
	{
		
		
	}
#endif

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T>& operator=(const quat<T>& rhs)
	{
		v = rhs.v;
		w = rhs.w;
		return *this;
	}
	quat<T> Inverse(const quat<T>& q)
	{
		return Conjugate(q);
	}
	T GetX()
	{
		return v.x;
	}
	void SetX(T t)
	{
		v.x = t;
	}
	quat<T> Conjugate(const quat<T>& q)
	{
		return quat<T>(q.w, -q.v.x, -q.v.y, -q.v.z);
	}
	/**
	 * Copy convert operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	quat<T>& operator=(const quat<FromT>& rhs)
	{
		v = rhs.v;
		w = static_cast<T>(rhs.w);
		return *this;
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T> operator+(const quat<T>& rhs) const
	{
		const quat<T>& lhs = *this;
		return quat<T>(lhs.w + rhs.w, lhs.v + rhs.v);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T> operator*(const quat<T>& rhs) const
	{
		const quat<T>& lhs = *this;
		return quat<T>(lhs.w * rhs.w - lhs.v.x * rhs.v.x - lhs.v.y * rhs.v.y - lhs.v.z * rhs.v.z,
				lhs.w * rhs.v.x + lhs.v.x * rhs.w + lhs.v.y * rhs.v.z - lhs.v.z * rhs.v.y,
				lhs.w * rhs.v.y - lhs.v.x * rhs.v.z + lhs.v.y * rhs.w + lhs.v.z * rhs.v.x,
				lhs.w * rhs.v.z + lhs.v.x * rhs.v.y - lhs.v.y * rhs.v.x + lhs.v.z * rhs.w);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T> operator*(T rhs) const
	{
		return quat<T>(w * rhs, v * rhs);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T> operator-(const quat<T>& rhs) const
	{
		const quat<T>& lhs = *this;
		return quat<T>(lhs.w - rhs.w, lhs.v - rhs.v);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T>& operator+=(const quat<T>& rhs)
	{
		w += rhs.w;
		v += rhs.v;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T>& operator-=(const quat<T>& rhs)
	{
		w -= rhs.w;
		v -= rhs.v;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T>& operator*=(const quat<T>& rhs)
	{
		quat q = (*this) * rhs;
		v = q.v;
		w = q.w;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	quat<T>& operator*=(T rhs)
	{
		w *= rhs;
		v *= rhs;
		return *this;
	}

	/**
	 * Equality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition | lhs - rhs | < EPSILON,
	 * for all quat coordinates.
	 */
	bool operator==(const quat<T>& rhs) const
	{
		const quat<T>& lhs = *this;
		return (std::fabs(lhs.w - rhs.w) < EPSILON) && lhs.v == rhs.v;
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const quat<T>& rhs) const
	{
		return !(*this == rhs);
	}

	//-------------[ unary operations ]--------------------------
	/**
	 * Unary negate operator
	 * @return negated quat
	 */
	quat<T> operator-() const
	{
		return quat<T>(-w, -v);
	}

	/**
	 * Unary conjugate operator
	 * @return conjugated quat
	 */
	quat<T> operator~() const
	{
		return quat<T>(w, -v);
	}

	/**
	 * Get lenght of quat.
	 * @return Length of quat.
	 */
	T length() const
	{
		return (T) std::sqrt(w * w + v.lengthSq());
	}
    /* 
     * Multiplying a quaternion q with a vector v applies the q-rotation to v
     */
    vec3<T> operator* (const vec3<T> &vec) const
    {
        vec3<T> vn(vec);
        vn.normalize();
        
        quat<T> vecQuat, resQuat;
        vecQuat.v.x = vn.x;
        vecQuat.v.y = vn.y;
        vecQuat.v.z = vn.z;
        vecQuat.w = 0.0f;
        quat<T> qq = ~(*this);
        resQuat = vecQuat * qq;
        resQuat = *this * resQuat;
        
        return (vec3<T>(resQuat.v.x, resQuat.v.y, resQuat.v.z));
    }

#ifndef STRENDER_THIN_MATH
	/**
	 * Return square of length.
	 * @return length ^ 2
	 * @note This method is faster then length(). For comparison
	 * of length of two quat can be used just this value, instead
	 * of more expensive length() method.
	 */
	T lengthSq() const
	{
		return w * w + v.lengthSq();
	}

	/**
	 * Normalize quat
	 */
	void normalize()
	{
		T len = length();
        
        if( len == 0.0)
            return;
        
        T inv = 1 / len;
		w *= inv;
		v *= inv;
	}

	/**
	 * Creates quat for eulers angles.
	 * @param x Rotation around x axis (in degrees).
	 * @param y Rotation around y axis (in degrees).
	 * @param z Rotation around z axis (in degrees).
	 * @return quat object representing transformation.
	 */
	 //temp 
	static quat<T>* fromEulerAngles_(T x, T y, T z)
	{
		quat<T> ret = fromAxisRot(vec3<T>(1, 0, 0), x) * fromAxisRot(vec3<T>(0, 1, 0), y)
				* fromAxisRot(vec3<T>(0, 0, 1), z);
		return new quat<T>(ret.w,ret.v.x,ret.v.y,ret.v.z);
	}

	static quat<T> fromEulerAngles(T x, T y, T z)
	{

		quat<T> ret = fromAxisRot(vec3<T>(1, 0, 0), x) * fromAxisRot(vec3<T>(0, 1, 0), y)
			* fromAxisRot(vec3<T>(0, 0, 1), z);
		return ret;
	}
	static quat<T> fromEulerAnglesVector(const vec3<T>& v)
	{
		quat<T> ret = fromAxisRot(vec3<T>(1, 0, 0), v.x) * fromAxisRot(vec3<T>(0, 1, 0), v.y)
			* fromAxisRot(vec3<T>(0, 0, 1), v.z);
		return ret;
	}
	/**
	 * Creates quat as rotation around axis.
	 * @param axis Unit vec expressing axis of rotation.
	 * @param angleDeg Angle of rotation around axis (in degrees).
	 */
	static quat<T> fromAxisRot(vec3<T> axis, float angleDeg)
	{
		double angleRad = DEG2RAD(angleDeg);
		double sa2 = std::sin(angleRad / 2);
		double ca2 = std::cos(angleRad / 2);
		return quat<T>(ca2, axis * sa2);
	}

	/**
	 * Converts quat into rotation mat.
	 * @return Rotation mat expressing this quat.
	 */
	mat3<T> rotmat() const
	{
		mat3<T> ret;

		/*ret.at(0,0) = 1 - 2*v.y*v.y - 2*v.z*v.z;
		 ret.at(1,0) = 2*v.x*v.y - 2*w*v.z;
		 ret.at(2,0) = 2*v.x*v.z - 2*w*v.y;
		 
		 ret.at(0,1) = 2*v.x*v.y + 2*w*v.z;
		 ret.at(1,1) = 1 - 2*v.x*v.x - 2*v.z*v.z;
		 ret.at(2,1) = 2*v.y*v.z - 2*w*v.x;
		 
		 ret.at(0,2) = 2*v.x*v.z - 2*w*v.y;
		 ret.at(1,2) = 2*v.y*v.z + 2*w*v.x;
		 ret.at(2,2) = 1 - 2*v.x*v.x - 2*v.y*v.y;*/

		T xx = v.x * v.x;
		T xy = v.x * v.y;
		T xz = v.x * v.z;
		T xw = v.x * w;

		T yy = v.y * v.y;
		T yz = v.y * v.z;
		T yw = v.y * w;

		T zz = v.z * v.z;
		T zw = v.z * w;

		ret.at(0, 0) = 1 - 2 * (yy + zz);
		ret.at(1, 0) = 2 * (xy - zw);
		ret.at(2, 0) = 2 * (xz + yw);

		ret.at(0, 1) = 2 * (xy + zw);
		ret.at(1, 1) = 1 - 2 * (xx + zz);
		ret.at(2, 1) = 2 * (yz - xw);

		ret.at(0, 2) = 2 * (xz - yw);
		ret.at(1, 2) = 2 * (yz + xw);
		ret.at(2, 2) = 1 - 2 * (xx + yy);

		return ret;
	}
    
#endif //STRENDER_THIN_MATH

	/**
	 * Converts quat into transformation mat.
	 * @note This method performs same operation as rotmat() 
	 * conversion method. But returns mat of 4x4 elements.
	 * @return Transformation mat expressing this quat.
	 */
	mat4<T> transform() const
	{
		mat4<T> ret;

		T xx = v.x * v.x;
		T xy = v.x * v.y;
		T xz = v.x * v.z;
		T xw = v.x * w;

		T yy = v.y * v.y;
		T yz = v.y * v.z;
		T yw = v.y * w;

		T zz = v.z * v.z;
		T zw = v.z * w;

		ret.at(0, 0) = 1 - 2 * (yy + zz);
		ret.at(1, 0) = 2 * (xy - zw);
		ret.at(2, 0) = 2 * (xz + yw);
		ret.at(3, 0) = 0;

		ret.at(0, 1) = 2 * (xy + zw);
		ret.at(1, 1) = 1 - 2 * (xx + zz);
		ret.at(2, 1) = 2 * (yz - xw);
		ret.at(3, 1) = 0;

		ret.at(0, 2) = 2 * (xz - yw);
		ret.at(1, 2) = 2 * (yz + xw);
		ret.at(2, 2) = 1 - 2 * (xx + yy);
		ret.at(3, 2) = 0;

		ret.at(0, 3) = 0;
		ret.at(1, 3) = 0;
		ret.at(2, 3) = 0;
		ret.at(3, 3) = 1;

		return ret;

	}

	template<typename TO_TYPE>
	void toMat4(mat4<TO_TYPE>& ret) const {
		TO_TYPE xx = v.x * v.x;
		TO_TYPE xy = v.x * v.y;
		TO_TYPE xz = v.x * v.z;
		TO_TYPE xw = v.x * w;

		TO_TYPE yy = v.y * v.y;
		TO_TYPE yz = v.y * v.z;
		TO_TYPE yw = v.y * w;

		TO_TYPE zz = v.z * v.z;
		TO_TYPE zw = v.z * w;

		ret.at(0, 0) = 1 - 2 * (yy + zz);
		ret.at(1, 0) = 2 * (xy - zw);
		ret.at(2, 0) = 2 * (xz + yw);
		ret.at(3, 0) = 0;

		ret.at(0, 1) = 2 * (xy + zw);
		ret.at(1, 1) = 1 - 2 * (xx + zz);
		ret.at(2, 1) = 2 * (yz - xw);
		ret.at(3, 1) = 0;

		ret.at(0, 2) = 2 * (xz - yw);
		ret.at(1, 2) = 2 * (yz + xw);
		ret.at(2, 2) = 1 - 2 * (xx + yy);
		ret.at(3, 2) = 0;

		ret.at(0, 3) = 0;
		ret.at(1, 3) = 0;
		ret.at(2, 3) = 0;
		ret.at(3, 3) = 1;
	}

#ifndef STRENDER_THIN_MATH
    /**
     * find the angle of rotation
     */
    void getAxisAngle(vec3<T> *axis, float *angle) const
    {
        float scale = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        axis->x = v.x / scale;
        axis->y = v.y / scale;
        axis->z = v.z / scale;
        *angle = acos(w) * 2.0f;
    }
    vec3<T> toEulerAngles() const 
    {
        float yaw = (float)(atan2f(2.f * ((v.x * v.y) + (w * v.z)) , ((w * w) + (v.x * v.x) - (v.y * v.y) - (v.z * v.z))));
        float pitch = (float)(asin(-2.f * ((v.x * v.z) - (w * v.y))));
        float roll = (float)(atan2f(2 * ((w * v.x) + (v.y * v.z)) , ((w * w) - (v.x * v.x) - (v.y * v.y) + (v.z * v.z))));
        return vec3<T>(yaw * 180.f / M_PI, pitch* 180.f / M_PI, roll* 180.f / M_PI);
    }

	/**
	 * Linear interpolation of two quats
	 * @param fact Factor of interpolation. For translation from position
	 * of this vec to quat rhs, values of factor goes from 0.0 to 1.0.
	 * @param rhs Second quat for interpolation 
	 * @note However values of fact parameter are reasonable only in interval
	 * [0.0 , 1.0], you can pass also values outside of this interval and you
	 * can get result (extrapolation?)
	 */
	quat<T> lerp(T fact, const quat<T>& rhs) const
	{
		return quat<T>((1 - fact) * w + fact * rhs.w, v.lerp(fact, rhs.v));
	}

	/**
	 * Provides output to standard output stream.
	 */
	friend std::ostream& operator <<(std::ostream& oss, const quat<T>& q)
	{
		oss << "Re: " << q.w << " Im: " << q.v;
		return oss;
	}

	/**
	 * Gets string representation.
	 */
	std::string toString() const
	{
		std::ostringstream oss;
		oss << *this;
		return oss.str();
	}
#endif //STRENDER_THIN_MATH
    
	/**
	 * Creates quat from transform mat.
	 *
	 * @param m Transform mat used to compute quat.
	 * @return quat representing rotation of mat m.
	 */
    // 2011-07-02: Davide Bacchet: changed formula to fix degenerate cases
	 static quat<T> frommat(const mat4<T>& m)
	 {
		quat<T> q;

		T tr, s;
		tr = m(1, 1) + m(2, 2) + m(3, 3);
		if (tr >= epsilon)
		{
			s = 0.5 / (T) sqrt(tr + 1.0);
			q.w = 0.25 / s;
			q.v.x = (m(3, 2) - m(2, 3)) * s;
			q.v.y = (m(1, 3) - m(3, 1)) * s;
			q.v.z = (m(2, 1) - m(1, 2)) * s;
		}
		else
		{
			T d0 = m(1, 1);
			T d1 = m(2, 2);
			T d2 = m(3, 3);

			char bigIdx = (d0 > d1) ? ((d0 > d2) ? 0 : 2):((d1 > d2) ? 1 : 2);

			if (bigIdx == 0)
			{
				s = 2.0 * (T) sqrt(1.0 + m(1, 1) - m(2, 2) - m(3, 3));
				q.w = (m(3, 2) - m(2, 3)) / s;
				q.v.x = 0.25 * s;
				q.v.y = (m(1, 2) + m(2, 1)) / s;
				q.v.z = (m(1, 3) + m(3, 1)) / s;
			}
			else if (bigIdx == 1)
			{
				s = 2.0 * (T) sqrt(1.0 + m(2, 2) - m(1, 1) - m(3, 3));
				q.w = (m(1, 3) - m(3, 1)) / s;
				q.v.x = (m(1, 2) + m(2, 1)) / s;
				q.v.y = 0.25 * s;
				q.v.z = (m(2, 3) + m(3, 2)) / s;
			}
			else
			{
				s = 2.0 * (T) sqrt(1.0 + m(3, 3) - m(1, 1) - m(2, 2));
				q.w = (m(2, 1) - m(1, 2)) / s;
				q.v.x = (m(1, 3) + m(3, 1)) / s;
				q.v.y = (m(2, 3) + m(3, 2)) / s;
				q.v.z = 0.25 * s;
			}
		}

		return q;
	}

#ifndef STRENDER_THIN_MATH
	/**
	 * Creates quat from rotation mat.
	 *
	 * @param m Rotation mat used to compute quat.
	 * @return quat representing rotation of mat m.
	 */

     // 2011-07-02: Davide Bacchet: changed formula to fix degenerate cases
	 static quat<T> frommat(const mat3<T>& m)
	 {
		quat<T> q;

		T tr, s;
		tr = m(1, 1) + m(2, 2) + m(3, 3);
		if (tr >= epsilon)
		{
			s = 0.5 / (T) sqrt(tr + 1.0);
			q.w = 0.25 / s;
			q.v.x = (m(3, 2) - m(2, 3)) * s;
			q.v.y = (m(1, 3) - m(3, 1)) * s;
			q.v.z = (m(2, 1) - m(1, 2)) * s;
		}
		else
		{
			T d0 = m(1, 1);
			T d1 = m(2, 2);
			T d2 = m(3, 3);

			char bigIdx = (d0 > d1) ? ((d0 > d2) ? 0 : 2):((d1 > d2) ? 1 : 2);

			if (bigIdx == 0)
			{
				s = 2.0 * (T) sqrt(1.0 + m(1, 1) - m(2, 2) - m(3, 3));
				q.w = (m(3, 2) - m(2, 3)) / s;
				q.v.x = 0.25 * s;
				q.v.y = (m(1, 2) + m(2, 1)) / s;
				q.v.z = (m(1, 3) + m(3, 1)) / s;
			}
			else if (bigIdx == 1)
			{
				s = 2.0 * (T) sqrt(1.0 + m(2, 2) - m(1, 1) - m(3, 3));
				q.w = (m(1, 3) - m(3, 1)) / s;
				q.v.x = (m(1, 2) + m(2, 1)) / s;
				q.v.y = 0.25 * s;
				q.v.z = (m(2, 3) + m(3, 2)) / s;
			}
			else
			{
				s = 2.0 * (T) sqrt(1.0 + m(3, 3) - m(1, 1) - m(2, 2));
				q.w = (m(2, 1) - m(1, 2)) / s;
				q.v.x = (m(1, 3) + m(3, 1)) / s;
				q.v.y = (m(2, 3) + m(3, 2)) / s;
				q.v.z = 0.25 * s;
			}
		}

		return q;
	}

	/**
	 * Computes spherical interpolation between quats (this, q2)
	 * using coefficient of interpolation r (in [0, 1]).
	 *
	 * @param r The ratio of interpolation form this (r = 0) to q2 (r = 1).
	 * @param q2 Second quat for interpolation.
	 * @return Result of interpolation.
	 */
	quat<T> slerp(T r, const quat<T>& q2) const
	{
		quat<T> ret;
		T cosTheta = w * q2.w + v.x * q2.v.x + v.y * q2.v.y + v.z * q2.v.z;
		T theta = (T) acos(cosTheta);
		if (fabs(theta) < epsilon)
		{
			ret = *this;
		}
		else
		{
			T sinTheta = (T) sqrt(1.0 - cosTheta * cosTheta);
			if (fabs(sinTheta) < epsilon)
			{
				ret.w = 0.5 * w + 0.5 * q2.w;
				ret.v = v.lerp(0.5, q2.v);
			}
			else
			{
				T rA = (T) sin((1.0 - r) * theta) / sinTheta;
				T rB = (T) sin(r * theta) / sinTheta;

				ret.w = w * rA + q2.w * rB;
				ret.v.x = v.x * rA + q2.v.x * rB;
				ret.v.y = v.y * rA + q2.v.y * rB;
				ret.v.z = v.z * rA + q2.v.z * rB;
			}
		}
		return ret;
	}
    
#endif //STRENDER_THIN_MATH

};

typedef quat<float> Quatf;
typedef quat<double> Quatd;
    
}

#endif // __vmath_Header_File__

