#pragma once
#include "CMathInterface.h"
#include "Vector3.h"

namespace Matrix
{
	namespace Math
	{
		class Matrix4x4;
		//
		class MATRIX_MATH_API HalfVector4
		{
		public:
			union
			{
				unsigned short m[4];
				struct
				{
					unsigned short x, y, z, w;
				};
				struct
				{
					unsigned short r, g, b, a;
				};
			};
			HalfVector4 operator*(float f) const;
			HalfVector4 operator+(const HalfVector4& v) const;
			HalfVector4();
			HalfVector4(unsigned short _x, unsigned short _y, unsigned short _z, unsigned short _w);
		};
		// 4向量 颜色
		class MATRIX_MATH_API Vector4
		{
		public:
			union
			{
				float m[4];
				struct
				{
					float x, y, z, w;
				};
				struct
				{
					float r, g, b, a;
				};
			};

			Vector4(void);
			Vector4(float _x, float _y, float _z, float _w = 1.0f);
			Vector4(const Vector3& V);

			Vector4(unsigned char R, unsigned char G, unsigned char B, unsigned char A = 255);
			inline void GetV3(Vector3& V) const;
			inline Vector3 GetV3() const;
			inline void Set(const Vector3& V);
			inline void Set(float _x, float _y, float _z, float _w = 1.0f);
			Vector4 operator*(const Matrix4x4& m) const;

			void operator+=(const Vector4& v);
			void operator-=(const Vector4& v);
			void operator*=(const Vector4& v);
			void operator/=(const Vector4& v);

			void operator*=(float f);
			void operator/=(float f);
			void operator+=(float f);
			void operator-=(float f);

			Vector4 operator*(float f) const;
			Vector4 operator/(float f) const;
			Vector4 operator+(float f) const;
			Vector4 operator-(float f) const;

			Vector4 operator+(const Vector4& v) const;
			Vector4 operator-(const Vector4& v) const;
			Vector4 operator*(const Vector4& v) const;
			Vector4 operator/(const Vector4& v) const;

			bool operator==(const Vector4& v) const;

			DWORD GetDWARGB() const;
			DWORD GetDWRGBA() const;

			DWORD GetDWBGRA() const;
			DWORD GetDWABGR() const;
			void GetUCColor(unsigned char& R, unsigned char& G, unsigned char& B, unsigned char& A) const;

			void CreateFromARGB(DWORD ARGB);
			void CreateFromBGRA(DWORD BGRA);
			void CreateFromRGBA(DWORD RGBA);
			void CreateFromABGR(DWORD ABGR);
		}; // class

		typedef class Vector4 ColorRGBA;
		inline DWORD DWCOLORARGB(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			return ((DWORD)((((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff)));
		}
		inline DWORD DWCOLORBGRA(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			return ((DWORD)((((b) & 0xff) << 24) | (((g) & 0xff) << 16) | (((r) & 0xff) << 8) | ((a) & 0xff)));
		}
		inline DWORD DWCOLORRGBA(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			return ((DWORD)((((r) & 0xff) << 24) | (((g) & 0xff) << 16) | (((b) & 0xff) << 8) | ((a) & 0xff)));
		}
		inline DWORD DWCOLORABGR(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			return ((DWORD)((((a) & 0xff) << 24) | (((b) & 0xff) << 16) | (((g) & 0xff) << 8) | ((r) & 0xff)));
		}

		inline void DWCOLORGetARGB(DWORD ARGB, unsigned char& a, unsigned char& r, unsigned char& g, unsigned char& b)
		{
			a = (ARGB >> 24) & 0xff;
			r = (ARGB >> 16) & 0xff;
			g = (ARGB >> 8) & 0xff;
			b = (ARGB) & 0xff;
		}
		inline void DWCOLORGetBGRA(DWORD BGRA, unsigned char& a, unsigned char& r, unsigned char& g, unsigned char& b)
		{
			b = (BGRA >> 24) & 0xff;
			g = (BGRA >> 16) & 0xff;
			r = (BGRA >> 8) & 0xff;
			a = (BGRA) & 0xff;
		}
		inline void DWCOLORGetRGBA(DWORD RGBA, unsigned char& a, unsigned char& r, unsigned char& g, unsigned char& b)
		{
			r = (RGBA >> 24) & 0xff;
			g = (RGBA >> 16) & 0xff;
			b = (RGBA >> 8) & 0xff;
			a = (RGBA) & 0xff;
		}
		inline void DWCOLORGetABGR(DWORD ABGR, unsigned char& a, unsigned char& r, unsigned char& g, unsigned char& b)
		{
			a = (ABGR >> 24) & 0xff;
			b = (ABGR >> 16) & 0xff;
			g = (ABGR >> 8) & 0xff;
			r = (ABGR) & 0xff;
		}
		inline HalfVector4 FloatToHalf(const Vector4& v)
		{
			return HalfVector4(FloatToHalf(v.x), FloatToHalf(v.y), FloatToHalf(v.z), FloatToHalf(v.w));
		}
		inline Vector4 HalfToFloat(const HalfVector4& v)
		{
			return Vector4(HalfToFloat(v.x), HalfToFloat(v.y), HalfToFloat(v.z), HalfToFloat(v.w));
		}
#include "Vector4.inl"
	}
}