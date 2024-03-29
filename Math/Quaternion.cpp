#include "CMathInterface.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix3.h"
using namespace Matrix::Math;
/*----------------------------------------------------------------*/
Quaternion::Quaternion(void)
{
	w = 1.0f, x = 0.0f, y = 0.0f, z = 0.0f;
}
/*----------------------------------------------------------------*/
Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	w = _w;
	x = _x;
	y = _y;
	z = _z;
}
/*----------------------------------------------------------------*/
void Quaternion::Set(float _w, float _x, float _y, float _z)
{
	w = _w;
	x = _x;
	y = _y;
	z = _z;
}
/*----------------------------------------------------------------*/
void Quaternion::CreateEuler(float fRoll, float fPitch, float fYaw)
{
	float cX, cY, cZ, sX, sY, sZ, cXcZ, sXsZ, cXsZ, sXcZ;

	fPitch *= 0.5f;
	fYaw *= 0.5f;
	fRoll *= 0.5f;

	cX = COS(fPitch);
	cY = COS(fYaw);
	cZ = COS(fRoll);

	sX = SIN(fPitch);
	sY = SIN(fYaw);
	sZ = SIN(fRoll);

	cXcZ = cX * cZ;
	sXsZ = sX * sZ;
	cXsZ = cX * sZ;
	sXcZ = sX * cZ;

	w = cXcZ * cY + sXsZ * sY;
	x = sXcZ * cY + cXsZ * sY;
	y = cXcZ * sY - sXsZ * cY;
	z = cXsZ * cY - sXcZ * sY;

} // MakeFromEuler
/*----------------------------------------------------------------*/
void Quaternion::Normalize(void)
{

	float m = SQRT(x * x + y * y + z * z + w * w);
	float Invm = 1.0f / m;
	x *= Invm;
	y *= Invm;
	z *= Invm;
	w *= Invm;
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::GetConjugate() const
{

	return Quaternion(w, -x, -y, -z);
}
/*----------------------------------------------------------------*/
void Quaternion::GetEulers(float& fRoll, float& fPitch, float& fYaw) const
{

	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = x + x;
	y2 = y + y;
	z2 = z + z;

	xx = x * x2;
	xy = x * y2;
	xz = x * z2;

	yy = y * y2;
	yz = y * z2;
	zz = z * z2;

	wx = w * x2;
	wy = w * y2;
	wz = w * z2;

	float _00 = 1.0f - (yy + zz); //
	float _01 = xy + wz;          //

	float _10 = xy - wz;          //
	float _11 = 1.0f - (xx + zz); //

	float _20 = xz + wy;          //
	float _21 = yz - wx;          //
	float _22 = 1.0f - (xx + yy); //

	if (_21 > 1.0f)
		fPitch = -PI2;
	else if (_21 < -1.0f)
		fPitch = PI2;
	else
		fPitch = ASIN(-_21);

	if (fabs(_21) > REAL_1)
	{
		fYaw = 0;
		fRoll = ATAN2(-_10, _00);
	}
	else
	{
		fRoll = ATAN2(_01, _11);
		fYaw = ATAN2(_20, _22);
	}

} // EulerFromQuat
/*----------------------------------------------------------------*/
void Quaternion::GetMatrix(Matrix3& Mat) const
{
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = x + x;
	y2 = y + y;
	z2 = z + z;

	xx = x * x2;
	xy = x * y2;
	xz = x * z2;

	yy = y * y2;
	yz = y * z2;
	zz = z * z2;

	wx = w * x2;
	wy = w * y2;
	wz = w * z2;

	Mat._00 = 1.0f - (yy + zz);
	Mat._01 = xy + wz;
	Mat._02 = xz - wy;

	Mat._10 = xy - wz;
	Mat._11 = 1.0f - (xx + zz);
	Mat._12 = yz + wx;

	Mat._20 = xz + wy;
	Mat._21 = yz - wx;
	Mat._22 = 1.0f - (xx + yy);
} // GetMatrix
/*----------------------------------------------------------------*/
float Quaternion::GetLength(void) const
{

	return SQRT(x * x + y * y + z * z + w * w);
}
/*----------------------------------------------------------------*/
void Quaternion::operator/=(float f)
{

	w /= f;
	x /= f;
	y /= f;
	z /= f;
}

/*----------------------------------------------------------------*/
Quaternion Quaternion::operator/(float f) const
{

	return Quaternion(w / f, x / f, y / f, z / f);
}
/*----------------------------------------------------------------*/

void Quaternion::operator*=(float f)
{
	w *= f;
	x *= f;
	y *= f;
	z *= f;
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::operator*(float f) const
{

	return Quaternion(w * f, x * f, y * f, z * f);
}
/*----------------------------------------------------------------*/

void Quaternion::operator+=(const Quaternion& q)
{

	w += q.w;
	x += q.x;
	y += q.y;
	z += q.z;
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::operator+(const Quaternion& q) const
{

	return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}
/*----------------------------------------------------------------*/
void Quaternion::operator-=(const Quaternion& q)
{

	w -= q.w;
	x -= q.x;
	y -= q.y;
	z -= q.z;
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::operator-(const Quaternion& q) const
{

	return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}
/*----------------------------------------------------------------*/
void Quaternion::operator*=(const Quaternion& q)
{

	w = w * q.w - x * q.x - y * q.y - z * q.z;
	x = w * q.x + x * q.w + z * q.y - y * q.z;
	y = w * q.y + y * q.w + x * q.z - z * q.x;
	z = w * q.z + z * q.w + y * q.x - x * q.y;
}
/*----------------------------------------------------------------*/

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	Quaternion qResult;

	qResult.w = w * q.w - x * q.x - y * q.y - z * q.z;
	qResult.x = w * q.x + x * q.w + z * q.y - y * q.z;
	qResult.y = w * q.y + y * q.w + x * q.z - z * q.x;
	qResult.z = w * q.z + z * q.w + y * q.x - x * q.y;

	return qResult;
}
/*----------------------------------------------------------------*/
Vector3 Quaternion::operator*(const Vector3& v) const
{
	// nVidia SDK implementation
	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = qvec.Cross(v);
	uuv = qvec.Cross(uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;
}
/*----------------------------------------------------------------*/
bool Quaternion::operator==(const Quaternion& q) const
{
	for (unsigned int i = 0; i < 4; i++)
	{
		if (ABS(m[i] - q.m[i]) > EPSILON_E4)
		{
			return false;
		}
	}
	return true;
}
/*----------------------------------------------------------------*/
void Quaternion::Rotate(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion m1 = q1;
	Quaternion m2 = q2;
	m1.Normalize();
	m2.Normalize();
	Quaternion t = (~m1) * m2 * m1;
	w = t.w;
	x = t.x;
	y = t.y;
	z = t.z;
}
/*----------------------------------------------------------------*/
Vector3 Quaternion::Rotate(const Vector3& v) const
{
	Quaternion t(w, x, y, z);
	t.Normalize();
	Quaternion r = (~t) * v * t;
	return Vector3(r.x, r.y, r.z);
}
/*----------------------------------------------------------------*/
float Quaternion::Dot(const Quaternion& q) const
{

	return (w * q.w + x * q.x + y * q.y + z * q.z);
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::operator~(void) const
{
	return Quaternion(w, -x, -y, -z);
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::GetInverse() const
{
	return (GetConjugate() / GetLength());
}
/*----------------------------------------------------------------*/
void Quaternion::CreateAxisAngle(const Vector3& Axis, float fAngle)
{
	float fTemp = fAngle / 2.0f;
	float Sin = SIN(fTemp);
	float Cos = COS(fTemp);

	Vector3 N = Axis;
	N.Normalize();

	w = Cos;
	x = Sin * N.x;
	y = Sin * N.y;
	z = Sin * N.z;
}
/*----------------------------------------------------------------*/
void Quaternion::GetAxisAngle(Vector3& Axis, float& fAngle) const
{

	Quaternion QTemp = *this;
	float fHalfAngle = ACOS(QTemp.w);

	fAngle = fHalfAngle * 2.0f;

	float SinHalfAngle = 1.0f - QTemp.w * QTemp.w;

	float InvSinHalfAngle = 1.0f / SinHalfAngle;
	Axis.x = QTemp.x * InvSinHalfAngle;
	Axis.y = QTemp.y * InvSinHalfAngle;
	Axis.z = QTemp.z * InvSinHalfAngle;
}
/*----------------------------------------------------------------*/
void Quaternion::Slerp(float t, const Quaternion& q1, const Quaternion& q2)
{
	if (t <= 0)
	{
		(*this) = q1;
		return;
	}
	if (t >= 1)
	{
		(*this) = q2;
		return;
	}

	Quaternion q1Temp, q2Temp;
	q1Temp = q1;
	q2Temp = q2;
	q1Temp.Normalize();
	q2Temp.Normalize();
	float fCos = q1Temp.Dot(q2Temp);
	if (fCos < 0.0f)
	{
		q1Temp *= -1.0f;
		fCos = -fCos;
	}
	float k1, k2;
	if (fCos > REAL_1)
	{
		k1 = 1.0f - t;
		k2 = t;
	}
	else
	{
		float fSin = SQRT(1.0f - fCos * fCos);
		float fAngle = ATAN2(fSin, fCos);
		float fInvSin = 1.0f / fSin;
		k1 = SIN((1.0f - t) * fAngle) * fInvSin;
		k2 = SIN(t * fAngle) * fInvSin;
	}
	w = k1 * q1Temp.w + k2 * q2Temp.w;
	x = k1 * q1Temp.x + k2 * q2Temp.x;
	y = k1 * q1Temp.y + k2 * q2Temp.y;
	z = k1 * q1Temp.z + k2 * q2Temp.z;
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::Pow(float exp) const
{
	if (ABS(w) > REAL_1)
		return *this;

	float alpha = ACOS(w);
	float newAlpha = alpha * exp;

	float mult = SIN(newAlpha) / SIN(alpha);
	return Quaternion(COS(newAlpha), x * mult, y * mult, z * mult);
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::Ln() const
{
	if (ABS(w) > REAL_1)
		return Quaternion(x, y, z, 0.0f);
	;
	float alpha = ACOS(w);

	float Sin = SIN(alpha);
	float temp = alpha / Sin;
	return Quaternion(0.0f, temp * x, temp * y, temp * z);
}
/*----------------------------------------------------------------*/
Quaternion Quaternion::Exp() const
{
	float alpha = GetLength();
	float Sin = SIN(alpha);
	if (ABS(Sin) > EPSILON_E4)
	{
		float temp = Sin / alpha;
		return Quaternion(COS(alpha), x * temp, y * temp, z * temp);
	}
	else
	{
		return Quaternion(COS(alpha), x, y, z);
	}
}
/*----------------------------------------------------------------*/
void Quaternion::SlerpSValueOf(const Quaternion& q1, const Quaternion& q2, const Quaternion& q3)
{
	Quaternion q2Inv = q2.GetInverse();
	Quaternion K1 = q1 * q2;
	Quaternion K2 = q3 * q2;

	Quaternion K3 = (K1.Ln() + K2.Ln()) * (-0.25f);
	*this = q2 * K3.Exp();
}
/*----------------------------------------------------------------*/
void Quaternion::Slerp(float t, const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2)
{
	float fSlerpT = 2.0f * t * (1.0f - t);
	Quaternion SlerpP;
	SlerpP.Slerp(t, q1, q2);
	Quaternion SlerpQ;
	SlerpQ.Slerp(t, s1, s2);
	Slerp(fSlerpT, SlerpP, SlerpQ);
}
/*----------------------------------------------------------------*/
void Quaternion::TriangleSlerp(float t1, float t2, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3)
{
	*this = q1.Pow(t1) + q2.Pow(t2) + q3.Pow(1.0f - t1 - t2);
}