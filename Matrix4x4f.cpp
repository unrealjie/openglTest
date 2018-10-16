#include <cmath>
#include "Matrix4x4f.h"


CMatrix4x4f::CMatrix4x4f()
{
	MakeIdentity();
}


CMatrix4x4f::CMatrix4x4f(const float mat[DIMENSION][DIMENSION])
{
	SetValue(mat);
}


CMatrix4x4f::CMatrix4x4f(const CMatrix4x4f& mat)
{
	SetValue(mat.m_mat);
}


CMatrix4x4f::~CMatrix4x4f()
{
}


void
CMatrix4x4f::SetValue(const float mat[DIMENSION][DIMENSION])
{
	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			m_mat[i][j] = mat[i][j];
		}
	}
}


void
CMatrix4x4f::GetValue(float mat[DIMENSION][DIMENSION]) const
{
	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			mat[i][j] = m_mat[i][j];
		}
	}
}


void
CMatrix4x4f::SetGLMat(const float mat[16])
{
	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			m_mat[row][col] = mat[col * 4 + row];
		}
	}
}


void
CMatrix4x4f::GetGLMat(float mat[16]) const
{
	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			mat[col * 4 + row] = m_mat[row][col];
		}
	}
}


float*
CMatrix4x4f::operator[](int i)
{
	return m_mat[i];
}


const float*
CMatrix4x4f::operator[](int i) const
{
	return m_mat[i];
}


CMatrix4x4f&
CMatrix4x4f::operator=(const CMatrix4x4f& mat)
{
	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			m_mat[row][col] = mat[row][col];
		}
	}


	return *this;
}


CMatrix4x4f&
CMatrix4x4f::operator+=(const CMatrix4x4f& mat)
{
	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			m_mat[row][col] += mat[row][col];
		}
	}


	return *this;
}


CMatrix4x4f&
CMatrix4x4f::operator-=(const CMatrix4x4f& mat)
{
	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			m_mat[row][col] -= mat[row][col];
		}
	}


	return *this;
}


CMatrix4x4f&
CMatrix4x4f::operator*=(const CMatrix4x4f& mat)
{
	float m[DIMENSION][DIMENSION];

	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			m[row][col] = m_mat[row][X] * mat[X][col] +
			              m_mat[row][Y] * mat[Y][col] +
			              m_mat[row][Z] * mat[Z][col] +
			              m_mat[row][W] * mat[W][col];
		}
	}

	SetValue(m);


	return *this;
}


CMatrix4x4f&
CMatrix4x4f::operator*=(float scalar)
{
	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			m_mat[row][col] *= scalar;
		}
	}


	return *this;
}


CMatrix4x4f&
CMatrix4x4f::operator/=(float scalar)
{
	if (scalar == 0.0f) {
		scalar = 1.0f;
	}

	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			m_mat[row][col] /= scalar;
		}
	}


	return *this;
}


CMatrix4x4f
CMatrix4x4f::operator-() const
{
	CMatrix4x4f mat;

	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			mat[row][col] = - m_mat[row][col];
		}
	}


	return mat;
}


CMatrix4x4f
operator+(const CMatrix4x4f& m1, const CMatrix4x4f& m2)
{
	CMatrix4x4f mat;

	for (int row = 0; row < CMatrix4x4f::DIMENSION; row++) {
		for (int col = 0; col < CMatrix4x4f::DIMENSION; col++) {
			mat[row][col] = m1[row][col] + m2[row][col];
		}
	}

	return mat;
}


CMatrix4x4f
operator-(const CMatrix4x4f& m1, const CMatrix4x4f& m2)
{
	CMatrix4x4f mat;

	for (int row = 0; row < CMatrix4x4f::DIMENSION; row++) {
		for (int col = 0; col < CMatrix4x4f::DIMENSION; col++) {
			mat[row][col] = m1[row][col] - m2[row][col];
		}
	}

	return mat;
}


CMatrix4x4f
operator*(float scalar, const CMatrix4x4f& m)
{
	CMatrix4x4f mat;

	for (int row = 0; row < CMatrix4x4f::DIMENSION; row++) {
		for (int col = 0; col < CMatrix4x4f::DIMENSION; col++) {
			mat[row][col] = scalar * m[row][col];
		}
	}

	return mat;
}


CMatrix4x4f
operator*(const CMatrix4x4f& m, float scalar)
{
	CMatrix4x4f mat;

	for (int row = 0; row < CMatrix4x4f::DIMENSION; row++) {
		for (int col = 0; col < CMatrix4x4f::DIMENSION; col++) {
			mat[row][col] = m[row][col] * scalar;
		}
	}

	return mat;
}


CVector3f
operator*(const CVector3f& v, const CMatrix4x4f& m)
{
	CVector3f vec;
	vec.MakeZero();

	for (int col = 0; col < CVector3f::DIMENSION; col++) {
		for (int row = 0; row < CVector3f::DIMENSION; row++) {
			vec[col] += v[row] * m[row][col];
		}
		vec[col] += m[CMatrix4x4f::W][col];
	}

	return vec;
}


CVector3f
operator*(const CMatrix4x4f& m, const CVector3f& v)
{
	CVector3f vec;
	vec.MakeZero();

	for (int row = 0; row < CVector3f::DIMENSION; row++) {
		for (int col = 0; col < CVector3f::DIMENSION; col++) {
			vec[row] += m[row][col] * v[col];
		}
		vec[row] += m[row][CMatrix4x4f::W];
	}

	return vec;
}


CMatrix4x4f
operator*(const CMatrix4x4f& m1, const CMatrix4x4f& m2)
{
	CMatrix4x4f mat;

	for (int row = 0; row < CMatrix4x4f::DIMENSION; row++) {
		for (int col = 0; col < CMatrix4x4f::DIMENSION; col++) {
			mat[row][col] = m1[row][CMatrix4x4f::X] * m2[CMatrix4x4f::X][col] +
			                m1[row][CMatrix4x4f::Y] * m2[CMatrix4x4f::Y][col] +
			                m1[row][CMatrix4x4f::Z] * m2[CMatrix4x4f::Z][col] +
			                m1[row][CMatrix4x4f::W] * m2[CMatrix4x4f::W][col];
		}
	}

	return mat;
}


bool
operator==(const CMatrix4x4f& m1, const CMatrix4x4f& m2)
{
	for (int row = 0; row < CMatrix4x4f::DIMENSION; row++) {
		for (int col = 0; col < CMatrix4x4f::DIMENSION; col++) {
			if (m1[row][col] != m2[row][col]) {
				return false;
			}
		}
	}

	return true;
}


bool
operator!=(const CMatrix4x4f& m1, const CMatrix4x4f& m2)
{
	return !(m1 == m2);
}


void
CMatrix4x4f::MakeIdentity()
{
	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			m_mat[i][j] = ((i == j) ? 1.0f : 0.0f);
		}
	}
}


void
CMatrix4x4f::MakeZero()
{
	for (int i = 0; i < DIMENSION; i++) {
		for (int j = 0; j < DIMENSION; j++) {
			m_mat[i][j] = 0.0f;
		}
	}
}


void
CMatrix4x4f::Transpose()
{
	float mat[DIMENSION][DIMENSION];
	for (int row = 0; row < DIMENSION; row++) {
		for (int col = 0; col < DIMENSION; col++) {
			mat[row][col] = m_mat[col][row];
		}
	}
	SetValue(mat);
}


bool
CMatrix4x4f::Inverse()
{
	CMatrix4x4f cofactorMat;
	float det;
	int row;
	int col;

	for (row = 0; row < DIMENSION; row++) {
		for (col = 0; col < DIMENSION; col++) {
			cofactorMat[row][col] = Cofactor(col, row);
		}
	}

	det = Det();

	if (det == 0.0f) {
		return false;
	}

	for (row = 0; row < DIMENSION; row++) {
		for (col = 0; col < DIMENSION; col++) {
			m_mat[row][col] = cofactorMat[row][col] / det;
		}
	}

	return true;
}


void
CMatrix4x4f::MakeOrthonormal(const CVector3f& i, const CVector3f& j, const CVector3f& k)
{
	MakeIdentity();
	m_mat[X][X] = i[X];
	m_mat[Y][X] = i[Y];
	m_mat[Z][X] = i[Z];
	m_mat[X][Y] = j[X];
	m_mat[Y][Y] = j[Y];
	m_mat[Z][Y] = j[Z];
	m_mat[X][Z] = k[X];
	m_mat[Y][Z] = k[Y];
	m_mat[Z][Z] = k[Z];
}


void
CMatrix4x4f::MakeRotation(const CVector3f& axis, float angle)
{
	MakeIdentity();

	CVector3f u;

	CMatrix4x4f I;
	I.MakeIdentity();

	u = axis;
	u.Normalize();;
	CMatrix4x4f uuT;
	uuT.MakeIdentity();
	for (int i = 0; i < (DIMENSION - 1); i++) {
		for (int j = 0; j < (DIMENSION - 1); j++) {
			uuT[i][j] = u[i] * u[j];
		}
	}

	CMatrix4x4f S;
	S.MakeIdentity();
	S[X][X] = 0.0f;
	S[X][Y] = -u[Z];
	S[X][Z] = u[Y];
	S[Y][X] = u[Z];
	S[Y][Y] = 0.0f;
	S[Y][Z] = -u[X];
	S[Z][X] = -u[Y];
	S[Z][Y] = u[X];
	S[Z][Z] = 0.0f;

	CMatrix4x4f M2;
	M2 = I - uuT;
	M2 *= cosf(angle * PI / 180.0f);
	M2[W][W] = 1.0f;
  
	CMatrix4x4f M3;
	M3 = sinf(angle * PI / 180.0f) * S;
	M3[W][W] = 1.0f;

	CMatrix4x4f M;
	M.MakeZero();
	M += uuT;
	M += M2;
	M += M3;
	M[W][W] = 1.0f;

	M.GetValue(m_mat);
}


void
CMatrix4x4f::MakeTranslation(const CVector3f& trans)
{
	MakeIdentity();
	m_mat[X][W] = trans[X];
	m_mat[Y][W] = trans[Y];
	m_mat[Z][W] = trans[Z];
}


void
CMatrix4x4f::MakeScale(const CVector3f& scale)
{
	MakeIdentity();
	m_mat[X][X] = scale[X];
	m_mat[Y][Y] = scale[Y];
	m_mat[Z][Z] = scale[Z];
}


void
CMatrix4x4f::MakePerspective(float l, float r, float b, float t, float n, float f)
{

	m_mat[X][X] = 2.0f * n / (r - l);
	m_mat[X][Y] = 0.0f;
	m_mat[X][Z] = (r + l) / (r - l);
	m_mat[X][W] = 0.0f;

	m_mat[Y][X] = 0.0f;
	m_mat[Y][Y] = 2.0f * n / (t - b);
	m_mat[Y][Z] = (t + b) / (t - b);
	m_mat[Y][W] = 0.0f;

	m_mat[Z][X] = 0.0f;
	m_mat[Z][Y] = 0.0f;
	m_mat[Z][Z] = -(f + n) / (f - n);
	m_mat[Z][W] = -2.0f * f * n / (f - n);

	m_mat[W][X] = 0.0f;
	m_mat[W][Y] = 0.0f;
	m_mat[W][Z] = -1.0f;
	m_mat[W][W] = 0.0f;
}


void
CMatrix4x4f::MakeOrthographic(float l, float r, float b, float t, float n, float f)
{
	m_mat[X][X] = 2.0f / (r - l);
	m_mat[X][Y] = 0.0f;
	m_mat[X][Z] = 0.0f;
	m_mat[X][W] = - (r + l) / (r - l);

	m_mat[Y][X] = 0.0f;
	m_mat[Y][Y] = 2.0f / (t - b);
	m_mat[Y][Z] = 0.0f;
	m_mat[Y][W] = - (t + b) / (t - b);

	m_mat[Z][X] = 0.0f;
	m_mat[Z][Y] = 0.0f;
	m_mat[Z][Z] = - 2.0f / (f - n);
	m_mat[Z][W] = - (f + n) / (f - n);

	m_mat[W][X] = 0.0f;
	m_mat[W][Y] = 0.0f;
	m_mat[W][Z] = 0.0f;
	m_mat[W][W] = 1.0f;
}


float
CMatrix4x4f::Det() const
{
	return Det(m_mat, DIMENSION);
}


float
CMatrix4x4f::Cofactor(int i, int j) const
{
	return Cofactor(m_mat, DIMENSION, i, j);
}


float
CMatrix4x4f::Det(const float mat[DIMENSION][DIMENSION] ,int dimension) const
{
	float det;

	if (dimension == 1) {
		det = mat[0][0];
	}
	else {
		det = 0.0f;
		for (int j = 0; j < dimension; j++) {
			det += mat[0][j] * Cofactor(mat, dimension, 0, j);
		}
	}

	return det;
}


float
CMatrix4x4f::Cofactor(const float mat[DIMENSION][DIMENSION], int dimension, int i, int j) const
{
	float cofactor = 0.0f;
	float m[DIMENSION][DIMENSION];

	for (int k = 0; k < dimension; k++) {
		for (int l = 0; l < dimension; l++) {
			if (k < i && l < j) {
				m[k][l] = mat[k][l];
			}
			else if (k < i && l > j) {
				m[k][l - 1] = mat[k][l];
			}
			else if (k > i && l < j) {
				m[k - 1][l] = mat[k][l];
			}
			else if (k > i && l > j) {
				m[k - 1][l - 1] = mat[k][l];
			}
		}
	}

	cofactor = (float)pow(-1.0, i + j) * Det(m, dimension - 1);

	return cofactor;
}
