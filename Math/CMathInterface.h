#pragma once
#include <math.h>
#include <tchar.h>
#include <stdlib.h>
#ifndef USE_STL_TYPE_TRAIT
#define USE_STL_TYPE_TRAIT
#endif //USE_STL_TYPE_TRAIT
#ifndef USE_MATRIX_NEW
#define USE_MATRIX_NEW
#endif // !USE_MATRIX_NEW

#include "Platform/PlatformMacro.h"
#include "Platform/Core.h"

#ifdef Math_EXPORTS
#define MATRIX_MATH_API __declspec(dllexport)
#else
#define MATRIX_MATH_API __declspec(dllimport)
#endif

namespace Matrix
{
	namespace Math
	{
		// Trigonometric functions  三角函数
#define SIN(x) sinf(x)
#define COS(x) cosf(x)
#define TAN(x) tanf(x)
#define ASIN(x) asinf(x)
#define ACOS(x) acosf(x)
#define ATAN(x) atanf(x)
#define ATAN2(y, x) atan2f(y, x)

//指数函数 Exponential and logarithmic functions
#define SQRT(x) sqrtf(x)
#define POW(x, y) powf(x, y)
#define EXP(x) expf(x)
#define EXP2(x) exp2(x)
#define LOG(x) log(x)
#define LOG2(x) log(x) * 1.4426950f

//舍入舍出函数  Rounding and remainder functions
#define CEIL(x) ceil(x)
#define FLOOR(x) floor(x)
#define FMOD(x, y) fmodf(x, y) // Breaks x into an integral and a fractional part.

//其他工具函数 of x: |x|.
#define FABS(x) fabsf(x)
#define IABS(x) abs(x)
#define LABS(x) labs(x)
#define LLABS(x) llabs(x)


// Macro constants  浮点数精确度宏定义
#define EPSILON_E3 (float)(1E-3)
#define EPSILON_E4 (float)(1E-4)
#define EPSILON_E5 (float)(1E-5)
#define EPSILON_E6 (float)(1E-6)
#define EPSILON_E8 (float)(1E-8)

//常用数学符号数值宏定义
#define MIN_CHAR (-128)
#define MAX_CHAR 127
#define MIN_INT32 (-2147483647 - 1)
#define MAX_INT32 2147483647
#define MAX_REAL 3.402823466e+38F
#define MIN_REAL 1.175494351e-38F
#define MAX_UINT32 0xffffffff
#define REAL_1 0.99999f
#define PI 3.1415926535897932f
#define PI2 1.57079632679f
#define INV_PI 0.31830988618f
#define FASTASIN_VSPI2 1.5707963050f

#define MX_FRONT			0
#define MX_BACK				1
#define MX_ON				2

#define MX_CLIPPED			3
#define MX_CULLED			4
#define MX_VISIBLE			5

#define MX_INTERSECT		3
#define MX_OUT				4
#define MX_IN				5
#define MX_NOINTERSECT		6

#define MX_SHADOWON			0
#define MX_SHADOWBACK		1
#define MX_NOSHADOW			2



		template <typename T>
		inline T ABS(T t)
		{
			return t < 0 ? -t : t;
		}
		template <typename T>
		inline T Min(T t0, T t1)
		{
			return t0 < t1 ? t0 : t1;
		}
		template <typename T>
		inline T Max(T t0, T t1)
		{
			return t0 > t1 ? t0 : t1;
		}
		template <typename T>
		inline T Clamp(T Value, T Max, T Min)
		{
			if (Value >= Max)
			{
				return Max;
			}
			if (Value <= Min)
			{
				return Min;
			}
			return Value;
		}
		template <typename T>
		inline void Swap(T& t1, T& t2)
		{
			T temp;
			temp = t1;
			t1 = t2;
			t2 = temp;
		}

		//模板特化  Explicit specialization
		template <>
		inline float ABS(float t)
		{
			return FABS(t);
		}
		template <>
		inline int ABS(int t)
		{
			return IABS(t);
		}
		template <>
		inline long ABS(long t)
		{
			return LABS(t);
		}
		template <>
		inline long long ABS(long long t)
		{
			return LLABS(t);
		}

		inline int MXstoi(const TCHAR* p)
		{
			return _tstoi(p);
		}
		inline float MXstof(const TCHAR* p)
		{
			return (float)_tstof(p);
		}
		inline float FastAtan2(float Y, float X)
		{
			// return atan2f(Y,X);
			//  atan2f occasionally returns NaN with perfectly valid input (possibly due to a compiler or library bug).
			//  We are replacing it with a minimax approximation with a max relative error of 7.15255737e-007 compared to the C library function.
			//  On PC this has been measured to be 2x faster than the std C version.

			const float absX = FABS(X);
			const float absY = FABS(Y);
			const bool yAbsBigger = (absY > absX);
			float t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
			float t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

			if (t0 == 0.f)
				return 0.f;

			float t3 = t1 / t0;
			float t4 = t3 * t3;

			static const float c[7] = {
				+7.2128853633444123e-03f,
				-3.5059680836411644e-02f,
				+8.1675882859940430e-02f,
				-1.3374657325451267e-01f,
				+1.9856563505717162e-01f,
				-3.3324998579202170e-01f,
				+1.0f };

			t0 = c[0];
			t0 = t0 * t4 + c[1];
			t0 = t0 * t4 + c[2];
			t0 = t0 * t4 + c[3];
			t0 = t0 * t4 + c[4];
			t0 = t0 * t4 + c[5];
			t0 = t0 * t4 + c[6];
			t3 = t0 * t3;

			t3 = yAbsBigger ? (0.5f * PI) - t3 : t3;
			t3 = (X < 0.0f) ? PI - t3 : t3;
			t3 = (Y < 0.0f) ? -t3 : t3;

			return t3;
		}

		inline float Fmod(float X, float Y)
		{
			if (FABS(Y) <= EPSILON_E8)
			{
				return 0.f;
			}
			const float Div = (X / Y);
			// All floats where abs(f) >= 2^23 (8388608) are whole numbers so do not need truncation, and avoid overflow in TruncToFloat as they get even larger.
			const float Quotient = FABS(Div) < 8388608.f ? int(Div) : Div;
			float IntPortion = Y * Quotient;

			// Rounding and imprecision could cause IntPortion to exceed X and cause the result to be outside the expected range.
			// For example Fmod(55.8, 9.3) would result in a very small negative value!
			if (FABS(IntPortion) > FABS(X))
			{
				IntPortion = X;
			}

			const float Result = X - IntPortion;
			return Result;
		}
		/** Return true if value is NaN (not a number). */
		inline bool IsNaN(float A)
		{
			return ((*(unsigned int*)&A) & 0x7FFFFFFF) > 0x7F800000;
		}
		/** Return true if value is finite (not NaN and not Infinity). */
		inline bool IsFinite(float A)
		{
			return ((*(unsigned int*)&A) & 0x7F800000) != 0x7F800000;
		}
		inline bool IsNegativeFloat(const float& A)
		{
			return ((*(unsigned int*)&A) >= (unsigned int)0x80000000); // Detects sign bit.
		}
		inline void SinCos(float* ScalarSin, float* ScalarCos, float Value)
		{
			// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
			float quotient = (INV_PI * 0.5f) * Value;
			if (Value >= 0.0f)
			{
				quotient = (float)((int)(quotient + 0.5f));
			}
			else
			{
				quotient = (float)((int)(quotient - 0.5f));
			}
			float y = Value - (2.0f * PI) * quotient;

			// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
			float sign;
			if (y > PI2)
			{
				y = PI - y;
				sign = -1.0f;
			}
			else if (y < -PI2)
			{
				y = -PI - y;
				sign = -1.0f;
			}
			else
			{
				sign = +1.0f;
			}

			float y2 = y * y;

			// 11-degree minimax approximation
			*ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

			// 10-degree minimax approximation
			float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
			*ScalarCos = sign * p;
		}

		// Note:  We use FASTASIN_VSPI2 instead of HALF_PI inside of FastASin(), since it was the value that accompanied the minimax coefficients below.
		// It is important to use exactly the same value in all places inside this function to ensure that FastASin(0.0f) == 0.0f.
		// For comparison:
		//		PI2				== 1.57079632679f == 0x3fC90FDB
		//		HALF_PI3			== 1.5707963050f  == 0x3fC90FDA

		/**
		 * Computes the ASin of a scalar value.
		 *
		 * @param Value  input angle
		 * @return ASin of Value
		 */
		inline float FastAsin(float Value)
		{
			// Clamp input to [-1,1].
			bool nonnegative = (Value >= 0.0f);
			float x = ABS(Value);
			float omx = 1.0f - x;
			if (omx < 0.0f)
			{
				omx = 0.0f;
			}
			float root = SQRT(omx);
			// 7-degree minimax approximation
			float result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x + 0.0889789874f) * x - 0.2145988016f) * x + FASTASIN_VSPI2;
			result *= root; // acos(|x|)
			// acos(x) = pi - acos(-x) when x < 0, asin(x) = pi/2 - acos(x)
			return (nonnegative ? FASTASIN_VSPI2 - result : result - FASTASIN_VSPI2);
		}
#define MX_SSE
#ifdef MX_SSE
#include "PC_SSE.h"
#endif
		inline unsigned int CalcAlign(unsigned int n, unsigned int align)
		{
			return ((n + align - 1) & (~(align - 1)));
			// return Matrix::Platform::MXAlign<unsigned int>(n, align);
		}
		inline float RadianToDegree(float Radian)
		{
			return 57.29578f * Radian;
			// return ( Radian * 180.0f ) / PI ;
		}
		inline float DegreeToRadian(float Degree)
		{
			// return ( Degree * PI ) /  180.0f;
			return 0.01745329f * Degree;
		}
		inline bool IsTwoPower(unsigned int uiN)
		{
			return !(uiN & (uiN - 1));
		}
		inline unsigned short FloatToHalf(float Value)
		{
			unsigned int Result;

			unsigned int IValue = ((unsigned int*)(&Value))[0];
			unsigned int Sign = (IValue & 0x80000000U) >> 16U;
			IValue = IValue & 0x7FFFFFFFU; //Hack off the sign

			if (IValue > 0x47FFEFFFU)
			{
				// The number is too large to be represented as a half.  Saturate to infinity.
				Result = 0x7FFFU;
			}
			else
			{
				if (IValue < 0x38800000U)
				{
					// The number is too small to be represented as a normalized half.
					// Convert it to a denormalized value.
					unsigned int Shift = 113U - (IValue >> 23U);
					IValue = (0x800000U | (IValue & 0x7FFFFFU)) >> Shift;
				}
				else
				{
					// Rebias the exponent to represent the value as a normalized half.
					IValue += 0xC8000000U;
				}

				Result = ((IValue + 0x0FFFU + ((IValue >> 13U) & 1U)) >> 13U) & 0x7FFFU;
			}
			return (unsigned short)(Result | Sign);
		}
		inline float HalfToFloat(unsigned short Value)
		{

			unsigned int Mantissa;
			unsigned int Exponent;
			unsigned int Result;

			Mantissa = (unsigned int)(Value & 0x03FF);

			if ((Value & 0x7C00) != 0) // The value is normalized
			{
				Exponent = (unsigned int)((Value >> 10) & 0x1F);
			}
			else if (Mantissa != 0) // The value is denormalized
			{
				// Normalize the value in the resulting float
				Exponent = 1;

				do
				{
					Exponent--;
					Mantissa <<= 1;
				} while ((Mantissa & 0x0400) == 0);

				Mantissa &= 0x03FF;
			}
			else // The value is zero
			{
				Exponent = (unsigned int)-112;
			}

			Result = ((Value & 0x8000) << 16) | // Sign
				((Exponent + 112) << 23) | // Exponent
				(Mantissa << 13);          // Mantissa

			return *(float*)&Result;
		}
		// f must [0,1]
		inline unsigned int CompressUnitFloat(float f, unsigned int Bit = 16)
		{
			unsigned int nIntervals = 1 << Bit;
			float scaled = f * (nIntervals - 1);
			unsigned int rounded = (unsigned int)(scaled + 0.5f);
			if (rounded > nIntervals - 1)
			{
				rounded = nIntervals - 1;
			}
			return rounded;
		}
		inline unsigned int CompressFloat(float f, float Max, float Min, unsigned int Bit = 16)
		{
			float Unitf = (f - Min) / (Max - Min);
			return CompressUnitFloat(Unitf, Bit);
		}
		inline float DecompressUnitFloat(unsigned int quantized, unsigned int Bit = 16)
		{
			unsigned int nIntervals = 1 << Bit;
			float IntervalSize = 1.0f / (nIntervals - 1);

			return quantized * IntervalSize;
		}
		inline float DecompressFloat(unsigned int quantized, float Max, float Min, unsigned int Bit = 16)
		{
			float Unitf = DecompressUnitFloat(quantized, Bit);
			return (Min + Unitf * (Max - Min));
		}
		inline float ClampAxis(float Degree)
		{
			// returns Degree in the range (-360,360)
			Degree = FMOD(Degree, 360.f);

			if (Degree < 0.f)
			{
				// shift to [0,360) range
				Degree += 360.f;
			}

			return Degree;
		}
		inline float NormalizeAxis(float Degree)
		{
			// returns Degree in the range [0,360)
			Degree = ClampAxis(Degree);

			if (Degree > 180.f)
			{
				// shift to (-180,180]
				Degree -= 360.f;
			}

			return Degree;
		}
		inline int FastLog2(int x)
		{
			float fx;
			unsigned int ix, exp;
			fx = (float)x;
			ix = *(unsigned int*)&fx;
			exp = (ix >> 23) & 0xFF;
			return exp - 127;
		}

		//-360.....360 can use
		inline float ClampAngle(float AngleDegrees, float MinAngleDegrees, float MaxAngleDegrees)
		{
			float MaxDelta = ClampAxis(MaxAngleDegrees - MinAngleDegrees) * 0.5f; // 0..180
			float RangeCenter = ClampAxis(MinAngleDegrees + MaxDelta);            // 0..360
			float DeltaFromCenter = NormalizeAxis(AngleDegrees - RangeCenter);    // -180..180

			// maybe clamp to nearest edge
			if (DeltaFromCenter > MaxDelta)
			{
				return NormalizeAxis(RangeCenter + MaxDelta);
			}
			else if (DeltaFromCenter < -MaxDelta)
			{
				return NormalizeAxis(RangeCenter - MaxDelta);
			}

			// already in range, just return it
			return NormalizeAxis(AngleDegrees);
		}
		inline int Rand() { return rand(); }
		inline void RandInit(int Seed) { srand(Seed); }
		inline float FRand() { return Rand() / (float)RAND_MAX; }

		inline unsigned int HashCombine(unsigned int A, unsigned int C)
		{
			unsigned int B = 0x9e3779b9;
			A += B;

			A -= B;
			A -= C;
			A ^= (C >> 13);
			B -= C;
			B -= A;
			B ^= (A << 8);
			C -= A;
			C -= B;
			C ^= (B >> 13);
			A -= B;
			A -= C;
			A ^= (C >> 12);
			B -= C;
			B -= A;
			B ^= (A << 16);
			C -= A;
			C -= B;
			C ^= (B >> 5);
			A -= B;
			A -= C;
			A ^= (C >> 3);
			B -= C;
			B -= A;
			B ^= (A << 10);
			C -= A;
			C -= B;
			C ^= (B >> 15);

			return C;
		}
		inline unsigned int PointerHash(const void* Key, unsigned int C = 0)
		{
			USIZE_TYPE PtrInt = 0;
#if WINDOWS_PLATFORM
#if _WIN64
			PtrInt = reinterpret_cast<USIZE_TYPE>(Key) >> 4;

#else
			PtrInt = unsigned int(Key);
#endif
#else
			MAC_ASSERT(0);
#endif
			return HashCombine((unsigned int)PtrInt, C);
		}
		inline unsigned int GetTypeHash(const unsigned char A)
		{
			return A;
		}

		inline unsigned int GetTypeHash(const char A)
		{
			return A;
		}

		inline unsigned int GetTypeHash(const unsigned short A)
		{
			return A;
		}

		inline unsigned int GetTypeHash(const short A)
		{
			return A;
		}

		inline unsigned int GetTypeHash(const int A)
		{
			return A;
		}

		inline unsigned int GetTypeHash(const unsigned int A)
		{
			return A;
		}

		inline unsigned int GetTypeHash(const unsigned long long A)
		{
			return (unsigned int)A + ((unsigned int)(A >> 32) * 23);
		}

		inline unsigned int GetTypeHash(const long long A)
		{
			return (unsigned int)A + ((unsigned int)(A >> 32) * 23);
		}

		inline unsigned int GetTypeHash(float A)
		{
			return *(unsigned int*)&A;
		}
		inline unsigned int GetTypeHash(double A)
		{
			return GetTypeHash(*(const unsigned long long*) & A);
		}
		inline unsigned int GetTypeHash(const void* A)
		{
			return PointerHash(A);
		}
		inline unsigned int GetTypeHash(void* A)
		{
			return PointerHash(A);
		}
		inline unsigned int Rounding(float fNum)
		{
			return unsigned int(fNum + 0.5f);
		}
		inline unsigned int FloorLog2(unsigned int Value)
		{
			unsigned int pos = 0;
			if (Value >= 1 << 16)
			{
				Value >>= 16;
				pos += 16;
			}
			if (Value >= 1 << 8)
			{
				Value >>= 8;
				pos += 8;
			}
			if (Value >= 1 << 4)
			{
				Value >>= 4;
				pos += 4;
			}
			if (Value >= 1 << 2)
			{
				Value >>= 2;
				pos += 2;
			}
			if (Value >= 1 << 1)
			{
				pos += 1;
			}
			return (Value == 0) ? 0 : pos;
		}
		inline unsigned int CountLeadingZeros(unsigned int Value)
		{
			if (Value == 0)
				return 32;
			return 31 - FloorLog2(Value);
		}
		inline unsigned int CeilLogTwo(unsigned int Arg)
		{
			unsigned int Bitmask = ((unsigned int)(CountLeadingZeros(Arg) << 26)) >> 31;
			return (32 - CountLeadingZeros(Arg - 1)) & (~Bitmask);
		}
	}
}