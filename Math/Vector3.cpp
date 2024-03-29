#include "Vector3.h"
#include "Matrix3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
using namespace Matrix::Math;

const Vector3 Vector3::ms_Up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ms_Right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::ms_Front = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::ms_Zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::ms_One = Vector3(1.0f, 1.0f, 1.0f);
/*----------------------------------------------------------------*/
Vector3::Vector3(void)
{
	x = 0;
	y = 0;
	z = 0;
}
/*----------------------------------------------------------------*/
Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
/*----------------------------------------------------------------*/

inline float Vector3::AngleWith(Vector3& v)
{
	return (float)acos(((*this).Dot(v)) / (this->GetLength() * v.GetLength()));
}

/*----------------------------------------------------------------*/

inline void Vector3::Create(const Vector3& v1, const Vector3& v2)
{

	x = v2.x - v1.x;
	y = v2.y - v1.y;
	z = v2.z - v1.z;
}
/*----------------------------------------------------------------*/
void Vector3::operator+=(const Vector3& v)
{

	x += v.x;
	y += v.y;
	z += v.z;
}
/*----------------------------------------------------------------*/

Vector3 Vector3::operator+(const Vector3& v) const
{

	return Vector3(x + v.x, y + v.y, z + v.z);
}
/*----------------------------------------------------------------*/

void Vector3::operator-=(const Vector3& v)
{

	x -= v.x;
	y -= v.y;
	z -= v.z;
}
/*----------------------------------------------------------------*/

Vector3 Vector3::operator-(const Vector3& v) const
{

	return Vector3(x - v.x, y - v.y, z - v.z);
}
Vector3 Vector3::operator/(const Vector3& v) const
{

	return Vector3(x / v.x, y / v.y, z / v.z);
}
void Vector3::operator/=(const Vector3& v)
{

	x /= v.x;
	y /= v.y;
	z /= v.z;
}
Vector3 Vector3::operator*(const Vector3& v) const
{

	return Vector3(x * v.x, y * v.y, z * v.z);
}
void Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y, z *= v.z;
}
/*----------------------------------------------------------------*/

void Vector3::operator*=(float f)
{

	x *= f;
	y *= f;
	z *= f;
}
/*----------------------------------------------------------------*/

void Vector3::operator/=(float f)
{

	x /= f;
	y /= f;
	z /= f;
}
/*----------------------------------------------------------------*/

Vector3 Vector3::operator*(float f) const
{

	return Vector3(x * f, y * f, z * f);
}
/*----------------------------------------------------------------*/

Vector3 Vector3::operator/(float f) const
{

	return Vector3(x / f, y / f, z / f);
}
/*----------------------------------------------------------------*/

void Vector3::operator+=(float f)
{
	x += f;
	y += f;
	z += f;
}
/*----------------------------------------------------------------*/

void Vector3::operator-=(float f)
{

	x -= f;
	y -= f;
	z -= f;
}
/*----------------------------------------------------------------*/

Vector3 Vector3::operator+(float f) const
{
	return Vector3(x + f, y + f, z + f);
}
/*----------------------------------------------------------------*/

Vector3 Vector3::operator-(float f) const
{

	return Vector3(x - f, y - f, z - f);
}
/*----------------------------------------------------------------*/
float Vector3::Dot(const Vector3& v) const
{

	return (v.x * x + v.y * y + v.z * z);
}
Vector3 Matrix::Math::Vector3::Cross(const Vector3& v)
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
/*----------------------------------------------------------------*/
bool Vector3::operator==(const Vector3& v) const
{
	for (unsigned int i = 0; i < 3; i++)
	{
		if (ABS(m[i] - v.m[i]) > EPSILON_E4)
		{
			return false;
		}
	}
	return true;
	// 	return (ABS(x-v.x) < EPSILON_E4 &&
	// 			ABS(y-v.y) < EPSILON_E4 &&
	// 			ABS(z-v.z) < EPSILON_E4 );
}
/*----------------------------------------------------------------*/
Quaternion Vector3::operator*(const Quaternion& q) const
{

	return Quaternion(q.w * x + q.z * y - q.y * z,
		q.w * y + q.x * z - q.z * x,
		q.w * z + q.y * x - q.x * y,
		-(q.x * x + q.y * y + q.z * z));
}
/*----------------------------------------------------------------*/
Vector3 Vector3::operator*(const Matrix3& m) const
{
	Vector3 vcResult;

#ifdef MX_SSE
	{
		VectorRegister _v = MakeVectorRegister(x, y, z, 0.0f);
		VectorRegister _m0 = MakeVectorRegister(m._00, m._01, m._02, 0.0f);
		VectorRegister _m1 = MakeVectorRegister(m._10, m._11, m._12, 0.0f);
		VectorRegister _m2 = MakeVectorRegister(m._20, m._21, m._22, 0.0f);

		// Splat x,y,z and w
		VectorRegister VTempX = VectorReplicate(_v, 0);
		VectorRegister VTempY = VectorReplicate(_v, 1);
		VectorRegister VTempZ = VectorReplicate(_v, 2);

		// Mul by the matrix
		VTempX = VectorMultiply(VTempX, _m0);
		VTempY = VectorMultiply(VTempY, _m1);
		VTempZ = VectorMultiply(VTempZ, _m2);
		// Add them all together
		VTempX = VectorAdd(VTempX, VTempY);

		VTempX = VectorAdd(VTempX, VTempZ);
		VectorStoreFloat3(VTempX, &vcResult);
	}
#else
	{
		vcResult.x = x * m._00 + y * m._10 + z * m._20;
		vcResult.y = x * m._01 + y * m._11 + z * m._21;
		vcResult.z = x * m._02 + y * m._12 + z * m._22;
	}
#endif

	return vcResult;
}
/*----------------------------------------------------------------*/
bool Vector3::IsParallel(const Vector3& Vector) const
{
	float t0, t1;
	bool temp = 0;
	t0 = x * Vector.y;
	t1 = y * Vector.x;

	if (ABS(t0 - t1) > EPSILON_E4)
		temp = 1;

	t0 = y * Vector.z;
	t1 = z * Vector.y;

	if (ABS(t0 - t1) > EPSILON_E4 && temp)
		return 1;
	else
		return 0;
}
/*----------------------------------------------------------------*/
Vector3 Vector3::operator*(const Matrix4x4& m) const
{
	Vector3 vcResult;

#ifdef MX_SSE
	{
		VectorRegister _v = MakeVectorRegister(x, y, z, 1.0f);
		VectorRegister _m0 = VectorLoad(&m.m[0]);
		VectorRegister _m1 = VectorLoad(&m.m[4]);
		VectorRegister _m2 = VectorLoad(&m.m[8]);
		VectorRegister _m3 = VectorLoad(&m.m[12]);
		// Splat x,y,z and w
		VectorRegister VTempX = VectorReplicate(_v, 0);
		VectorRegister VTempY = VectorReplicate(_v, 1);
		VectorRegister VTempZ = VectorReplicate(_v, 2);
		VectorRegister VTempW = VectorReplicate(_v, 3);
		// Mul by the matrix
		VTempX = VectorMultiply(VTempX, _m0);
		VTempY = VectorMultiply(VTempY, _m1);
		VTempZ = VectorMultiply(VTempZ, _m2);
		VTempW = VectorMultiply(VTempW, _m3);
		// Add them all together
		VTempX = VectorAdd(VTempX, VTempY);
		VTempZ = VectorAdd(VTempZ, VTempW);
		VTempX = VectorAdd(VTempX, VTempZ);

		VectorRegister _div_w = VectorSetFloat1(VectorGetComponent(VTempX, 3));
		VectorRegister _l = VectorDivide(VTempX, _div_w);
		VectorStoreFloat3(_l, &vcResult);
	}
#else
	{
		vcResult.x = x * m._00 + y * m._10 + z * m._20 + m._30;
		vcResult.y = x * m._01 + y * m._11 + z * m._21 + m._31;
		vcResult.z = x * m._02 + y * m._12 + z * m._22 + m._32;
		float w = x * m._03 + y * m._13 + z * m._23 + m._33;

		vcResult.x = vcResult.x / w;
		vcResult.y = vcResult.y / w;
		vcResult.z = vcResult.z / w;
	}
#endif
	return vcResult;
}
Vector3 Vector3::ReflectDir(const Vector3& N) const
{
	return N * Dot(N) * 2 + *this;
}
