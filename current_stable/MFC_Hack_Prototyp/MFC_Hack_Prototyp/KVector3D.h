#pragma once

#include <math.h>


class K_Vector3D
{
public:

	// Variablen
	float x;
	float y;
	float z;


	// Konstruktoren
	K_Vector3D()																			{ }
	K_Vector3D(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z)		{ }

	// Zuweisungsoperatoren
	K_Vector3D& operator = (const K_Vector3D& v)	{ x = v.x; y = v.y; z = v.z; return *this; }
	K_Vector3D& operator += (const K_Vector3D& v)	{ x += v.x; y += v.y; z += v.z; return *this; }
	K_Vector3D& operator -= (const K_Vector3D& v)	{ x -= v.x; y -= v.y; z -= v.z; return *this; }
	K_Vector3D& operator *= (const K_Vector3D& v)	{ x *= v.x; y *= v.y; z *= v.z; return *this; }
	K_Vector3D& operator *= (const float f)			{ x *= f; y *= f; z *= f; return *this; }
	K_Vector3D& operator /= (const K_Vector3D& v)	{ x /= v.x; y /= v.y; z /= v.z; return *this; }
	K_Vector3D& operator /= (const float f)			{ x /= f; y /= f; z /= f; return *this; }

	float GetLaenge()						{ return sqrtf(x * x + y * y + z * z); }
	float GetLaenge(const K_Vector3D& v)	{ return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
	float GetKreuzProdukt(K_Vector3D v)		{ return (x * v.x + y * v.y + z * v.z); }

	//K_Vector3D SubVectorDist(K_Vector3D &playerFrom, K_Vector3D &playerTo);
	K_Vector3D SubVectorDist(K_Vector3D &pkPlayer);


	// Vergleichsoperatoren
	/*
	bool operator == (const K_Vector3D& a, const K_Vector3D& b) { if (a.x != b.x) return False; if (a.y != b.y) return False; return a.z == b.z; }
	bool operator != (const K_Vector3D& a, const K_Vector3D& b) { if (a.x != b.x) return True; if (a.y != b.y) return True; return a.z != b.z; }
	*/
};



/*
// Arithmetische Operatoren
inline K_Vector3D operator + (const K_Vector3D& a, const K_Vector3D& b)		{ return K_Vector3D(a.x + b.x, a.y + b.y, a.z + b.z); }
inline K_Vector3D operator - (const K_Vector3D& a, const K_Vector3D& b)		{ return K_Vector3D(a.x - b.x, a.y - b.y, a.z - b.z); }
inline K_Vector3D operator - (const K_Vector3D& v)							{ return K_Vector3D(-v.x, -v.y, -v.z); }
inline K_Vector3D operator * (const K_Vector3D& a, const K_Vector3D& b)		{ return K_Vector3D(a.x * b.x, a.y * b.y, a.z * b.z); }
inline K_Vector3D operator * (const K_Vector3D& v, const float f)			{ return K_Vector3D(v.x * f, v.y * f, v.z * f); }
inline K_Vector3D operator * (const float f, const K_Vector3D& v)			{ return K_Vector3D(v.x * f, v.y * f, v.z * f); }
inline K_Vector3D operator / (const K_Vector3D& a, const K_Vector3D& b)		{ return K_Vector3D(a.x / b.x, a.y / b.y, a.z / b.z); }
inline K_Vector3D operator / (const K_Vector3D& v, const float f)			{ return K_Vector3D(v.x / f, v.y / f, v.z / f); }

*/



