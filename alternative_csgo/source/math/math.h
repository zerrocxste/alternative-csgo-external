#pragma once

#pragma warning (disable: 4244)

#include "../defines.h"

//*****************************Vector*****************************

class Vector;

typedef float vec_t;

class Vector
{
public:

	Vector(void) : x(0.0f), y(0.0f), z(0.0f)
	{

	}

	Vector(float X, float Y, float Z)
		: x(X), y(Y), z(Z)
	{

	}

	Vector(float* p)
	{
		*this = p;
	};

	Vector(const Vector& in)
	{
		x = in.x;
		y = in.y;
		z = in.z;
	};

	~Vector()
	{

	}

	inline Vector& operator= (const Vector& in);
	inline Vector& operator= (float* p);
	inline Vector& operator= (float f);

	inline float& operator[] (int i) const;

	inline bool operator! (void) const;

	inline bool operator== (const Vector& other) const;

	inline bool operator!= (const Vector& other) const;

	inline Vector& operator+= (const Vector& other);
	inline Vector& operator+= (float* p);
	inline Vector& operator+= (float f);

	inline Vector& operator-= (const Vector& other);
	inline Vector& operator-= (float* p);
	inline Vector& operator-= (float f);

	inline Vector& operator*= (const Vector& other);
	inline Vector& operator*= (float* p);
	inline Vector& operator*= (float f);

	inline Vector& operator/= (const Vector& other);
	inline Vector& operator/= (float* p);
	inline Vector& operator/= (float f);

	inline Vector operator+ (const Vector& other) const;
	inline Vector operator+ (float* p) const;
	inline Vector operator+ (float f) const;

	inline Vector operator- (const Vector& other) const;
	inline Vector operator- (float* p) const;
	inline Vector operator- (float f) const;
	inline Vector operator- (void) const;

	inline Vector operator* (const Vector& other) const;
	inline Vector operator* (float* p) const;
	inline Vector operator* (float f) const;

	inline Vector operator/ (const Vector& other) const;
	inline Vector operator/ (float* p) const;
	inline Vector operator/ (float f) const;

	operator float* () { return &x; }
	operator const float* () const { return &x; }

	inline bool IsZero(void) const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	inline bool IsZero2D(void)
	{
		return x == 0.0f && y == 0.0f;
	}

	inline Vector& Clear(void)
	{
		x = y = z = 0;

		return *this;
	}

	inline Vector& Init(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline Vector& Init(float* p)
	{
		*this = p;

		return *this;
	}

	inline Vector& Negate(void)
	{
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}

	inline float Dot(const Vector& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	inline float Dot2D(const Vector& other)
	{
		return x * other.x + y * other.y;
	}

	inline float Length(void)
	{
		float Length = 0;

		Length = sqrt(LengthSqr());

		return Length;
	}

	inline float Length2D(void)
	{
		float Length = 0;

		Length = sqrt(LengthSqr2D());

		return Length;
	}

	inline float LengthSqr(void)
	{
		return x * x + y * y + z * z;
	}

	inline float LengthSqr2D(void)
	{
		return x * x + y * y;
	}

	inline float Distance(Vector& ToVector)
	{
		return (ToVector - *this).Length();
	}

	inline float Distance2D(Vector& ToVector)
	{
		return (ToVector - *this).Length2D();
	}

	inline float Normalize(void)
	{
		float RecipLength, VectorLength;

		VectorLength = Length();

		if (VectorLength != 0)
		{
			RecipLength = 1 / VectorLength;

			x *= RecipLength;
			y *= RecipLength;
			z *= RecipLength;
		}

		return VectorLength;
	}

	inline Vector Normalized(void)
	{
		float flLen = Length();
		if (flLen == 0) return Vector(0, 0, 1);
		flLen = 1 / flLen;
		return Vector(x * flLen, y * flLen, z * flLen);
	}

	inline float Normalize2D(void)
	{
		float Length = LengthSqr2D();
		float RecipLength;

		if (Length != 0)
		{
			RecipLength = 1 / Length;

			x *= RecipLength;
			y *= RecipLength;
		}

		return Length;
	}

	inline float AngleBetween(Vector& other)
	{
		other.Normalize();
		Normalize();

		return acos(Dot(other)) * static_cast<float>(180.0 / M_PI_F);
	}

	Vector& CrossProduct(const Vector& a, const Vector& b)
	{
		x = (a.y * b.z) - (a.z * b.y);
		y = (a.z * b.x) - (a.x * b.z);
		z = (a.x * b.y) - (a.y * b.x);

		return *this;
	}

	void VectorVectors(Vector& Right, Vector& Up)
	{
		Vector tmp;

		if (x == 0 && y == 0)
		{
			Right[0] = 1;
			Right[1] = 0;
			Right[2] = 0;
			Up[0] = -z;
			Up[1] = 0;
			Up[2] = 0;
			return;
		}

		tmp[0] = 0; tmp[1] = 0; tmp[2] = 1.0;
		CrossProduct(tmp, Right);
		Right.Normalize();
		Right.CrossProduct(*this, Up);
		Up.Normalize();
	}

	inline bool IsValid()
	{
		return isfinite(x) && isfinite(y) && isfinite(z);
	}

public:

	float x, y, z;
};

inline Vector& Vector::operator= (const Vector& in)
{
	x = in.x;
	y = in.y;
	z = in.z;

	return *this;
}

inline Vector& Vector::operator= (float* p)
{
	if (p)
	{
		x = p[0]; y = p[1]; z = p[2];
	}
	else
	{
		x = y = z = 0;
	}

	return *this;
}

inline Vector& Vector::operator= (float f)
{
	x = y = z = f;

	return *this;
}

inline float& Vector::operator[] (int i) const
{
	if (i >= 0 && i < 3)
	{
		return ((float*)this)[i];
	}

	return ((float*)this)[0];
}

inline bool Vector::operator! (void) const
{
	return IsZero();
}

inline bool Vector::operator== (const Vector& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

inline bool Vector::operator!= (const Vector& other) const
{
	return x != other.x || y != other.y || z != other.z;
}

inline Vector& Vector::operator+= (const Vector& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

inline Vector& Vector::operator+= (float* p)
{
	x += p[0];
	y += p[1];
	z += p[2];

	return *this;
}

inline Vector& Vector::operator+= (float f)
{
	x += f;
	y += f;
	z += f;

	return *this;
}

inline Vector& Vector::operator-= (const Vector& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

inline Vector& Vector::operator-= (float* p)
{
	x -= p[0];
	y -= p[1];
	z -= p[2];

	return *this;
}
inline Vector& Vector::operator-= (float f)
{
	x -= f;
	y -= f;
	z -= f;

	return *this;
}

inline Vector& Vector::operator*= (const Vector& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

inline Vector& Vector::operator*= (float* p)
{
	x *= p[0];
	y *= p[1];
	z *= p[2];

	return *this;
}

inline Vector& Vector::operator*= (float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

inline Vector& Vector::operator/= (const Vector& other)
{
	if (other.x != 0 && other.y != 0 && other.z != 0)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
	}

	return *this;
}

inline Vector& Vector::operator/= (float* p)
{
	if (p[0] != 0 && p[1] != 0 && p[2] != 0)
	{
		x /= p[0];
		y /= p[1];
		z /= p[2];
	}

	return *this;
}

inline Vector& Vector::operator/= (float f)
{
	if (f != 0)
	{
		x /= f;
		y /= f;
		z /= f;
	}

	return *this;
}

inline Vector Vector::operator+ (const Vector& other) const
{
	return Vector(x + other.x, y + other.y, z + other.z);
}

inline Vector Vector::operator+ (float* p) const
{
	return Vector(x + p[0], y + p[1], z + p[2]);
}

inline Vector Vector::operator+ (float f) const
{
	return Vector(x + f, y + f, z + f);
}

inline Vector  Vector::operator- (const Vector& other) const
{
	return Vector(x - other.x, y - other.y, z - other.z);
}

inline Vector  Vector::operator- (float* p) const
{
	return Vector(x - p[0], y - p[1], z - p[2]);
}

inline Vector  Vector::operator- (float f) const
{
	return Vector(x - f, y - f, z - f);
}

inline Vector Vector::operator- (void) const
{
	return Vector(-x, -y, -z);
}

inline Vector Vector::operator* (const Vector& other) const
{
	return Vector(x * other.x, y * other.y, z * other.z);
}

inline Vector Vector::operator* (float* p) const
{
	return Vector(x * p[0], y * p[1], z * p[2]);
}

inline Vector Vector::operator* (float f) const
{
	return Vector(x * f, y * f, z * f);
}

inline Vector Vector::operator/ (const Vector& other) const
{
	if (other.x != 0 && other.y != 0 && other.z != 0)
	{
		return Vector(x / other.x, y / other.y, z / other.z);
	}

	return *this;
}

inline Vector Vector::operator/ (float* p) const
{
	if (p[0] != 0 && p[1] != 0 && p[2] != 0)
	{
		return Vector(x / p[0], y / p[1], z / p[2]);
	}

	return *this;
}

inline Vector Vector::operator/ (float f) const
{
	if (f != 0)
	{
		return Vector(x / f, y / f, z / f);
	}

	return *this;
}


//*****************************QAngle*****************************


class QAngle;

class QAngle
{
public:

	QAngle(void) : x(0.0f), y(0.0f), z(0.0f)
	{

	}

	QAngle(float X, float Y, float Z)
		: x(X), y(Y), z(Z)
	{

	}

	QAngle(float* p)
	{
		*this = p;
	};

	QAngle(QAngle& in)
	{
		*this = in;
	};

	~QAngle()
	{

	}

	inline QAngle& operator= (const QAngle& in);
	inline QAngle& operator= (float* p);
	inline QAngle& operator= (float f);
	inline QAngle& operator= (Vector v);

	inline float& operator[] (int i) const;

	inline bool operator! (void) const;

	inline bool operator== (const QAngle& other) const;

	inline bool operator!= (const QAngle& other) const;

	inline QAngle& operator+= (const QAngle& other);
	inline QAngle& operator+= (float* p);
	inline QAngle& operator+= (float f);

	inline QAngle& operator-= (const QAngle& other);
	inline QAngle& operator-= (float* p);
	inline QAngle& operator-= (float f);

	inline QAngle& operator*= (const QAngle& other);
	inline QAngle& operator*= (float* p);
	inline QAngle& operator*= (float f);

	inline QAngle& operator/= (const QAngle& other);
	inline QAngle& operator/= (float* p);
	inline QAngle& operator/= (float f);

	inline QAngle operator+ (const QAngle& other) const;
	inline QAngle operator+ (float* p) const;
	inline QAngle operator+ (float f) const;

	inline QAngle operator- (const QAngle& other) const;
	inline QAngle operator- (float* p) const;
	inline QAngle operator- (float f) const;
	inline QAngle operator- (void) const;

	inline QAngle operator* (const QAngle& other) const;
	inline QAngle operator* (float* p) const;
	inline QAngle operator* (float f) const;

	inline QAngle operator/ (const QAngle& other) const;
	inline QAngle operator/ (float* p) const;
	inline QAngle operator/ (float f) const;

	operator float* () { return &x; }
	operator const float* () const { return &x; }

	inline bool IsZero(void) const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	inline bool IsZero2D(void)
	{
		return x == 0.0f && y == 0.0f;
	}

	inline QAngle& Clear(void)
	{
		x = y = z = 0;

		return *this;
	}

	inline QAngle& Init(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;

		return *this;
	}

	inline QAngle& Init(float* p)
	{
		*this = p;

		return *this;
	}

	inline QAngle& Negate(void)
	{
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}

	QAngle& Normalize(void)
	{
		float* Pointer = (float*)this;

		for (int i = 0; i < 3; i++)
		{
			if (Pointer[i] > 180)
			{
				Pointer[i] -= 360;
			}
			else if (Pointer[i] < -180)
			{
				Pointer[i] += 360;
			}
		}

		return *this;
	}

	QAngle Delta360(QAngle& other)
	{
		QAngle OutDifference;

		OutDifference = other - *this;

		for (int i = 0; i < 3; i++)
		{
			if (OutDifference[i] < 0)
			{
				OutDifference[i] = -OutDifference[i];

				if (OutDifference[i] > 180)
				{
					OutDifference[i] = 360 - OutDifference[i];
				}
			}
		}

		return OutDifference;
	}

	bool IsWithinFOV(QAngle& AngIn, float fovX, float fovY)
	{
		QAngle AngleDifference = Delta360(AngIn);

		return AngleDifference.x <= fovX && AngleDifference.y <= fovY;
	}

	void AngleVectors(Vector* Forward, Vector* Right, Vector* Up)
	{
		float sp, sy, sr, cp, cy, cr, radx, rady, radz;

		radx = x * (M_PI * 2 / 360);
		rady = y * (M_PI * 2 / 360);
		radz = z * (M_PI * 2 / 360);

		sp = sin(radx);
		sy = sin(rady);
		sr = sin(radz);

		cp = cos(radx);
		cy = cos(rady);
		cr = cos(radz);

		if (Forward)
		{
			Forward->x = cp * cy;
			Forward->y = cp * sy;
			Forward->z = -sp;
		}

		if (Right)
		{
			Right->x = -1 * sr * sp * cy + -1 * cr * -sy;
			Right->y = -1 * sr * sp * sy + -1 * cr * cy;
			Right->z = -1 * sr * cp;
		}

		if (Up)
		{
			Up->x = cr * sp * cy + -sr * -sy;
			Up->y = cr * sp * sy + -sr * cy;
			Up->z = cr * cp;
		}
	}

	void AngleVectorsTranspose(Vector* Forward, Vector* Right, Vector* Up)
	{
		float sp, sy, sr, cp, cy, cr, radx, rady, radz;

		radx = x * (M_PI * 2 / 360);
		rady = y * (M_PI * 2 / 360);
		radz = z * (M_PI * 2 / 360);

		sp = sin(radx);
		sy = sin(rady);
		sr = sin(radz);

		cp = cos(radx);
		cy = cos(rady);
		cr = cos(radz);

		if (Forward)
		{
			Forward->x = cp * cy;
			Forward->y = sr * sp * cy + cr * -sy;
			Forward->z = cr * sp * cy + -sr * -sy;
		}

		if (Right)
		{
			Right->x = cp * sy;
			Right->y = sr * sp * sy + cr * cy;
			Right->z = cr * sp * sy + -sr * cy;
		}

		if (Up)
		{
			Up->x = -sp;
			Up->y = sr * cp;
			Up->z = cr * cp;
		}
	}

	inline bool IsValid()
	{
		return isfinite(x) && isfinite(y) && isfinite(z);
	}

public:

	float x, y, z;
};

inline QAngle& QAngle::operator= (const QAngle& in)
{
	x = in.x;
	y = in.y;
	z = in.z;

	return *this;
}

inline QAngle& QAngle::operator= (float* p)
{
	if (p)
	{
		x = p[0]; y = p[1]; z = p[2];
	}
	else
	{
		x = y = z = 0;
	}

	return *this;
}

inline QAngle& QAngle::operator= (float f)
{
	x = y = z = f;

	return *this;
}

inline QAngle& QAngle::operator= (Vector v)
{
	x = v[0]; y = v[1]; z = v[2];

	return *this;
}

inline float& QAngle::operator[] (int i) const
{
	if (i >= 0 && i < 3)
	{
		return ((float*)this)[i];
	}

	return ((float*)this)[0];
}

inline bool QAngle::operator! (void) const
{
	return IsZero();
}

inline bool QAngle::operator== (const QAngle& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

inline bool QAngle::operator!= (const QAngle& other) const
{
	return x != other.x || y != other.y || z != other.z;
}

inline QAngle& QAngle::operator+= (const QAngle& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

inline QAngle& QAngle::operator+= (float* p)
{
	x += p[0];
	y += p[1];
	z += p[2];

	return *this;
}

inline QAngle& QAngle::operator+= (float f)
{
	x += f;
	y += f;
	z += f;

	return *this;
}

inline QAngle& QAngle::operator-= (const QAngle& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

inline QAngle& QAngle::operator-= (float* p)
{
	x -= p[0];
	y -= p[1];
	z -= p[2];

	return *this;
}
inline QAngle& QAngle::operator-= (float f)
{
	x -= f;
	y -= f;
	z -= f;

	return *this;
}

inline QAngle& QAngle::operator*= (const QAngle& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

inline QAngle& QAngle::operator*= (float* p)
{
	x *= p[0];
	y *= p[1];
	z *= p[2];

	return *this;
}

inline QAngle& QAngle::operator*= (float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

inline QAngle& QAngle::operator/= (const QAngle& other)
{
	if (other.x != 0 && other.y != 0 && other.z != 0)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
	}

	return *this;
}

inline QAngle& QAngle::operator/= (float* p)
{
	if (p[0] != 0 && p[1] != 0 && p[2] != 0)
	{
		x /= p[0];
		y /= p[1];
		z /= p[2];
	}

	return *this;
}

inline QAngle& QAngle::operator/= (float f)
{
	if (f != 0)
	{
		x /= f;
		y /= f;
		z /= f;
	}

	return *this;
}

inline QAngle QAngle::operator+ (const QAngle& other) const
{
	return QAngle(x + other.x, y + other.y, z + other.z);
}

inline QAngle QAngle::operator+ (float* p) const
{
	return QAngle(x + p[0], y + p[1], z + p[2]);
}

inline QAngle QAngle::operator+ (float f) const
{
	return QAngle(x + f, y + f, z + f);
}

inline QAngle  QAngle::operator- (const QAngle& other) const
{
	return QAngle(x - other.x, y - other.y, z - other.z);
}

inline QAngle  QAngle::operator- (float* p) const
{
	return QAngle(x - p[0], y - p[1], z - p[2]);
}

inline QAngle  QAngle::operator- (float f) const
{
	return QAngle(x - f, y - f, z - f);
}

inline QAngle QAngle::operator- (void) const
{
	return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator* (const QAngle& other) const
{
	return QAngle(x * other.x, y * other.y, z * other.z);
}

inline QAngle QAngle::operator* (float* p) const
{
	return QAngle(x * p[0], y * p[1], z * p[2]);
}

inline QAngle QAngle::operator* (float f) const
{
	return QAngle(x * f, y * f, z * f);
}

inline QAngle QAngle::operator/ (const QAngle& other) const
{
	if (other.x != 0 && other.y != 0 && other.z != 0)
	{
		return QAngle(x / other.x, y / other.y, z / other.z);
	}

	return QAngle(0, 0, 0);
}

inline QAngle QAngle::operator/ (float* p) const
{
	if (p[0] != 0 && p[1] != 0 && p[2] != 0)
	{
		return QAngle(x / p[0], y / p[1], z / p[2]);
	}

	return QAngle(0, 0, 0);
}

inline QAngle QAngle::operator/ (float f) const
{
	if (f != 0)
	{
		return QAngle(x / f, y / f, z / f);
	}

	return QAngle(0, 0, 0);
}

inline QAngle operator*(float fl, const QAngle& v) { return v * fl; };

