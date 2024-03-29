#pragma once
#include "CMathInterface.h"

namespace Matrix
{
	namespace Math
	{
		class Matrix3;
		class Matrix4x4;
		class Quaternion;
		//向量
		class MATRIX_MATH_API Vector3
		{
		public:
			union
			{
				float m[3];
				struct
				{
					//行向量
					float x, y, z;
				};
			};

			Vector3(void);
			Vector3(float _x, float _y, float _z);

			/*************************************inline************************************************/
			inline void Set(float _x, float _y, float _z);
			inline float GetLength(void) const;    // 长度
			inline float GetSqrLength(void) const; // 长度平方
			inline void Negate(void);               // 乘以-1
			inline void Normalize(void);            // 单位化
			inline void Cross(const Vector3& v1,  //叉积
				const Vector3& v2);

			float AngleWith(Vector3& v);  // 两个向量的夹角(弧度)
			void Create(const Vector3& v1, // 构造向量从点v1到v2
				const Vector3& v2);

			/*            N     _
					 \	  /|\   /|
				Dir	  \	   |   /  Reflect
					  _\|  |  /
			--------------------------
			*/
			Vector3 ReflectDir(const Vector3& N) const;

			void operator+=(const Vector3& v);
			void operator-=(const Vector3& v);

			void operator*=(float f);
			void operator/=(float f);
			void operator+=(float f);
			void operator-=(float f);

			float Dot(const Vector3& v) const; //点积
			Vector3 Vector3::Cross(const Vector3& v);
			bool operator==(const Vector3& v) const;

			Vector3 operator*(float f) const;
			Vector3 operator/(float f) const;
			Vector3 operator+(float f) const;
			Vector3 operator-(float f) const;

			Quaternion operator*(const Quaternion& q) const;
			Vector3 operator*(const Matrix3& m) const;
			Vector3 operator*(const Matrix4x4& m) const;
			Vector3 operator+(const Vector3& v) const;
			Vector3 operator-(const Vector3& v) const;
			Vector3 operator/(const Vector3& v) const;
			Vector3 operator*(const Vector3& v) const;

			void operator/=(const Vector3& v);
			void operator*=(const Vector3& v);
			bool IsParallel(const Vector3& Vector) const;


			const static Vector3 ms_Up;
			const static Vector3 ms_Right;
			const static Vector3 ms_Front;
			const static Vector3 ms_Zero;
			const static Vector3 ms_One;
		}; // class

#include "Vector3.inl"
	}
}