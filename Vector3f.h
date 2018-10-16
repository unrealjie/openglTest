#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_


#ifndef PI
#define PI  3.14159265358979323846f
#endif


class CVector3f
{
public:
	enum {
		X = 0,
		Y = 1,
		Z = 2,
		DIMENSION = 3
	};

private:
	float m_vec[DIMENSION];

public:
	CVector3f();
	CVector3f(const CVector3f& vec);
	CVector3f(const float vec[DIMENSION]);
	CVector3f(float x, float y, float z);
	virtual ~CVector3f();

	void SetValue(const float vec[DIMENSION]);
	void SetValue(float x, float y, float z);

	void GetValue(float vec[DIMENSION]) const;
	void GetValue(float& x, float& y, float& z) const;

	float& operator[](int i);
	float operator[](int i) const;

	CVector3f& operator=(const CVector3f& vec);

	CVector3f& operator*=(float scalar);
	CVector3f& operator/=(float scalar);

	CVector3f& operator+=(const CVector3f& vec);
	CVector3f& operator-=(const CVector3f& vec);

	CVector3f operator-() const;
	CVector3f operator+() const;

	float Dot(const CVector3f& vec) const;
	CVector3f Cross(const CVector3f& vec) const;

	float Length() const;

	void MakeZero();

	void Negate();

	float Normalize();

	float Angle(const CVector3f& vec) const;

	friend CVector3f operator+(const CVector3f& vec1, const CVector3f& vec2);
	friend CVector3f operator-(const CVector3f& vec1, const CVector3f& vec2);

	friend CVector3f operator*(float scalar, const CVector3f& vec2);
	friend CVector3f operator*(const CVector3f& vec1, float scalar);
	friend CVector3f operator/(const CVector3f& vec1, float scalar);

	friend bool operator==(const CVector3f& vec1, const CVector3f& vec2);
	friend bool operator!=(const CVector3f& vec1, const CVector3f& vec2);
};


#endif // _VECTOR3F_H_
