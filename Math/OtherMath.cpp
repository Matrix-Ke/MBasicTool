#include "OtherMath.h"


using namespace Matrix::Math;

bool IsUniformScale(float fScale)
{
	if (ABS(fScale - 1.0f) < EPSILON_E4)
	{
		return true;
	}
	return false;
}
bool IsZeroTranslate(const Vector3& Translate)
{
	if (Translate.GetSqrLength() < EPSILON_E4)
	{
		return true;
	}
	return false;
}
bool IsIdentityRotate(const Matrix3& Rotate)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			if (i != j)
			{
				if (ABS(Rotate.M[i][j]) > EPSILON_E4)
				{
					return false;
				}
			}
			else
			{
				if (ABS(Rotate.M[i][j] - 1.0f) > EPSILON_E4)
				{
					return false;
				}
			}

		}
	}
	return true;
}
bool IsIdentityRotate(const Quaternion& Rotate)
{
	Vector3 R(Rotate.x, Rotate.y, Rotate.z);
	if (R.GetSqrLength() < EPSILON_E4)
	{
		return true;
	}
	return false;
}
float LineInterpolation(float t1, float t2, float t)
{
	return t1 + (t2 - t1) * t;
}
Vector3 LineInterpolation(const Vector3& t1, const Vector3& t2, float t)
{
	return t1 + (t2 - t1) * t;
}
Quaternion LineInterpolation(const Quaternion& t1, const Quaternion& t2, float t)
{
	float fCos = t2.Dot(t1);
	Quaternion Temp = t1;
	if (fCos < 0.0f)
	{
		Temp = t1 * (-1.0f);
	}
	return Temp + (t2 - Temp) * t;
}
Vector4 LineInterpolation(const Vector4& t1, const Vector4& t2, float t)
{
	return t1 + (t2 - t1) * t;
}

