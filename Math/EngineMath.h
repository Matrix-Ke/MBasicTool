#pragma once
#include "CMathInterface.h"

namespace Matrix
{
	namespace Math
	{
		class Vector3;
		class Vector4;
		class Matrix3;
		class  Quat;

		class MATRIX_MATH_API VSMathInstance
		{
		public:
			VSMathInstance();
			~VSMathInstance();
			float GetFastSin(unsigned int i);
			float GetFastCos(unsigned int i);
			unsigned int CRC32Compute(const void* pData, unsigned int uiDataSize);

			static VSMathInstance& GetMathInstance()
			{
				static VSMathInstance g_MathInitial;
				return g_MathInitial;
			}
		protected:
			void VSInitCRCTable();
			float FastSin[361];
			float FastCos[361];
			unsigned int CRCTable[256];
		};

		bool MATRIX_MATH_API VSInitMath();

		inline unsigned int GetTypeHash(const TCHAR* A)
		{
			return VSMathInstance::GetMathInstance().CRC32Compute(A, (unsigned int)_tcslen(A));
		}


		bool MATRIX_MATH_API IsUniformScale(float fScale);
		bool MATRIX_MATH_API IsZeroTranslate(const Vector3& Translate);
		bool MATRIX_MATH_API IsIdentityRotate(const Matrix3& Rotate);
		bool MATRIX_MATH_API IsIdentityRotate(const Quat& Rotate);


		float MATRIX_MATH_API LineInterpolation(float t1, float t2, float t);
		Vector3 MATRIX_MATH_API LineInterpolation(const Vector3& t1, const Vector3& t2, float t);
		Quat MATRIX_MATH_API LineInterpolation(const Quat& t1, const Quat& t2, float t);
		Vector4 MATRIX_MATH_API LineInterpolation(const Vector4& t1, const Vector4& t2, float t);


	}
}
