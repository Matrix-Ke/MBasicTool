#pragma once
#include "Vector3.h"
#include "Matrix3.h"
#include "Quaternion.h"
#include "Vector4.h"




namespace Matrix
{
	namespace Math
	{
		bool MATRIX_MATH_API IsUniformScale(float fScale);
		bool MATRIX_MATH_API IsZeroTranslate(const Vector3& Translate);
		bool MATRIX_MATH_API IsIdentityRotate(const Matrix3& Rotate);
		bool MATRIX_MATH_API IsIdentityRotate(const Quaternion& Rotate);

		// 	template< typename T>
		// 	T LineInterpolation (T t1, T t2, float t)
		// 	{
		// 		return t1 + (t2 - t1) * t;
		// 	}
		// 	Quaternion LineInterpolation (Quaternion t1, Quaternion t2, float t)
		// 	{
		// 		float fCos = t2.Dot(t1);
		// 		if(fCos < 0.0f)
		// 		{
		// 			t1 *= -1.0f;
		// 		}
		// 		return t1 + (t2 - t1) * t;
		// 	}
		float MATRIX_MATH_API LineInterpolation(float t1, float t2, float t);

		Vector3 MATRIX_MATH_API LineInterpolation(const Vector3& t1, const Vector3& t2, float t);

		Quaternion MATRIX_MATH_API LineInterpolation(const Quaternion& t1, const Quaternion& t2, float t);

		Vector4 MATRIX_MATH_API LineInterpolation(const Vector4& t1, const Vector4& t2, float t);

		float getMaxElement(float x, float y, float z);
	}
}
