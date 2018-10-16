#ifndef _MATRIX4X4F_H_
#define _MATRIX4X4F_H_


#include "Vector3f.h"


#ifndef PI
#define PI  3.14159265358979323846f
#endif


class CMatrix4x4f
{
public:
	enum {
		X = 0,
		Y = 1,
		Z = 2,
		W = 3,
		DIMENSION = 4
	};

private:
	float m_mat[DIMENSION][DIMENSION];

public:
	CMatrix4x4f();
	CMatrix4x4f(const float mat[DIMENSION][DIMENSION]);
	CMatrix4x4f(const CMatrix4x4f& mat);
	virtual ~CMatrix4x4f();

	void SetValue(const float mat[DIMENSION][DIMENSION]);
	void GetValue(float mat[DIMENSION][DIMENSION]) const;

	void SetGLMat(const float mat[16]);
	void GetGLMat(float mat[16]) const;

	void MakeIdentity();
	void MakeZero();

	void Transpose();
	bool Inverse();

	void MakeOrthonormal(const CVector3f& i, const CVector3f& j, const CVector3f& k);

	void MakeRotation(const CVector3f& axis, float angle);
	void MakeTranslation(const CVector3f& trans);
	void MakeScale(const CVector3f& scale);

	void MakePerspective(float l, float r, float b, float t, float n, float f);
	void MakeOrthographic(float l, float r, float b, float t, float n, float f);

	float Det() const;
	float Cofactor(int i, int j) const;

	float* operator[](int i);
	const float* operator[](int i) const;

	CMatrix4x4f& operator=(const CMatrix4x4f& mat);

	CMatrix4x4f& operator+=(const CMatrix4x4f& mat);
	CMatrix4x4f& operator-=(const CMatrix4x4f& mat);
	CMatrix4x4f& operator*=(const CMatrix4x4f& mat);
	CMatrix4x4f& operator*=(float scalar);
	CMatrix4x4f& operator/=(float scalar);

	CMatrix4x4f operator-() const;

	friend CMatrix4x4f operator+(const CMatrix4x4f& m1,
	                              const CMatrix4x4f& m2);
	friend CMatrix4x4f operator-(const CMatrix4x4f& m1,
	                              const CMatrix4x4f& m2);
	friend CMatrix4x4f operator*(const CMatrix4x4f& m1,
	                              const CMatrix4x4f& m2);
	friend CMatrix4x4f operator*(float scalar,
	                              const CMatrix4x4f& m);
	friend CMatrix4x4f operator*(const CMatrix4x4f& m,
	                              float scalar);
	friend CVector3f operator*(const CVector3f& v, const CMatrix4x4f& m);
	friend CVector3f operator*(const CMatrix4x4f& m, const CVector3f& v);

	friend bool operator==(const CMatrix4x4f& m1, const CMatrix4x4f& m2);
	friend bool operator!=(const CMatrix4x4f& m1, const CMatrix4x4f& m2);

private:
	float Det(const float mat[DIMENSION][DIMENSION], int dimension) const;
	float Cofactor(const float mat[DIMENSION][DIMENSION], int dimension, int i, int j) const;
};


#endif // _MATRIX4X4F_H_
