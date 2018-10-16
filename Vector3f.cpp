#include <cmath>
#include "Vector3f.h"


CVector3f::CVector3f()
{
	MakeZero();
}


CVector3f::CVector3f(const CVector3f& vec)
{
	SetValue(vec.m_vec);
}


CVector3f::CVector3f(const float vec[DIMENSION])
{
	SetValue(vec);
}


CVector3f::CVector3f(float x, float y, float z)
{
	SetValue(x, y, z);
}


CVector3f::~CVector3f()
{
}


void
CVector3f::SetValue(const float vec[DIMENSION])
{
	SetValue(vec[X], vec[Y], vec[Z]);
}


void
CVector3f::SetValue(float x, float y, float z)
{
	m_vec[X] = x;
	m_vec[Y] = y;
	m_vec[Z] = z;
}


void
CVector3f::GetValue(float vec[DIMENSION]) const
{
	GetValue(vec[X], vec[Y], vec[Z]);
}


void
CVector3f::GetValue(float&x, float& y, float& z) const
{
	x = m_vec[X];
	y = m_vec[Y];
	z = m_vec[Z];
}


CVector3f&
CVector3f::operator=(const CVector3f& vec)
{
	SetValue(vec.m_vec);
	return *this;
}


float&
CVector3f::operator[](int i)
{
	return m_vec[i];
}


float
CVector3f::operator[](int i) const
{
	return m_vec[i];
}


CVector3f&
CVector3f::operator*=(float scalar)
{
	for (int i = 0; i < DIMENSION; i++) {
		m_vec[i] *= scalar;
	}

	return *this;
}


CVector3f&
CVector3f::operator/=(float scalar)
{
	if (scalar == 0.0f) {
		scalar = 1.0f;
	}
	for (int i = 0; i < DIMENSION; i++) {
		m_vec[i] /= scalar;
	}

	return *this;
}


CVector3f&
CVector3f::operator+=(const CVector3f& vec)
{
	for (int i = 0; i < DIMENSION; i++) {
		m_vec[i] += vec[i];
	}

	return *this;
}


CVector3f&
CVector3f::operator-=(const CVector3f& vec)
{
	for (int i = 0; i < DIMENSION; i++) {
		m_vec[i] -= vec[i];
	}

	return *this;
}


CVector3f
CVector3f::operator-() const
{
	CVector3f vec;
	for (int i = 0; i < DIMENSION; i++) {
		vec.m_vec[i] = - m_vec[i];
	}

	return vec;
}


CVector3f
CVector3f::operator+() const
{
	CVector3f vec;
	for (int i = 0; i < DIMENSION; i++) {
		vec.m_vec[i] = + m_vec[i];
	}

	return vec;
}


float
CVector3f::Dot(const CVector3f& vec) const
{
	float dot = 0.0f;
	for (int i = 0; i < DIMENSION; i++) {
		dot += m_vec[i] * vec[i];
	}

	return dot;
}


CVector3f
CVector3f::Cross(const CVector3f& vec) const
{
	CVector3f cross;
	for (int i = 0; i < DIMENSION; i++) {
		cross[i] = m_vec[(i + 1) % DIMENSION] * vec[(i + 2) % DIMENSION] -
		           m_vec[(i + 2) % DIMENSION] * vec[(i + 1) % DIMENSION];
	}

	return cross;
}


float
CVector3f::Length() const
{
	float dot = 0.0f;
	for (int i = 0; i < DIMENSION; i++) {
		dot += m_vec[i] * m_vec[i];
	}

	return (float)sqrt(dot);
}


void
CVector3f::MakeZero()
{
	SetValue(0.0f, 0.0f, 0.0f);
}


void
CVector3f::Negate()
{
	for (int i = 0; i < DIMENSION; i++) {
		m_vec[i] = - m_vec[i];
	}
}


float
CVector3f::Normalize()
{
	float length = Length();

	if (length != 0.0f) {
		for (int i = 0; i < DIMENSION; i++) {
			m_vec[i] /= length;
		}
	}

	return length;
}


float
CVector3f::Angle(const CVector3f& vec) const
{
	CVector3f normal1(m_vec);
	normal1.Normalize();
	CVector3f normal2(vec.m_vec);
	normal2.Normalize();

	float cos = normal1.Dot(normal2);
	float sin = normal1.Cross(normal2).Length();

	return (atan2f(sin, cos) * 180.0f / PI);
}


CVector3f
operator+(const CVector3f& vec1, const CVector3f& vec2)
{
	CVector3f vec;
	for (int i = 0; i < CVector3f::DIMENSION; i++) {
		vec[i] = vec1[i] + vec2[i];
	}

	return vec;
}


CVector3f
operator-(const CVector3f& vec1, const CVector3f& vec2)
{
	CVector3f vec;
	for (int i = 0; i < CVector3f::DIMENSION; i++) {
		vec[i] = vec1[i] - vec2[i];
	}

	return vec;
}


CVector3f
operator*(float scalar, const CVector3f& vec2)
{
	CVector3f vec;
	for (int i = 0; i < CVector3f::DIMENSION; i++) {
		vec[i] = scalar * vec2[i];
	}

	return vec;
}


CVector3f
operator*(const CVector3f& vec1, float scalar)
{
	CVector3f vec;
	for (int i = 0; i < CVector3f::DIMENSION; i++) {
		vec[i] = vec1[i] * scalar;
	}

	return vec;
}


CVector3f
operator/(const CVector3f& vec1, float scalar)
{
	CVector3f vec;
	if (scalar == 0.0f) {
		scalar = 1.0f;
	}
	for (int i = 0; i < CVector3f::DIMENSION; i++) {
		vec[i] = vec1[i] / scalar;
	}

	return vec;
}


bool
operator==(const CVector3f& vec1, const CVector3f& vec2)
{
	bool equal;
	equal = (vec1.m_vec[CVector3f::X] == vec2.m_vec[CVector3f::X]) &&
	        (vec1.m_vec[CVector3f::Y] == vec2.m_vec[CVector3f::Y]) &&
	        (vec1.m_vec[CVector3f::Z] == vec2.m_vec[CVector3f::Z]);

	return equal;
}


bool
operator!=(const CVector3f& vec1, const CVector3f& vec2)
{
	bool notEqual;
	notEqual = (vec1.m_vec[CVector3f::X] != vec2.m_vec[CVector3f::X]) ||
	           (vec1.m_vec[CVector3f::Y] != vec2.m_vec[CVector3f::Y]) ||
	           (vec1.m_vec[CVector3f::Z] != vec2.m_vec[CVector3f::Z]);

	return notEqual;
}
