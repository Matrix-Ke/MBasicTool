#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"

namespace Matrix
{
	namespace Math
	{
		//矩阵
		class MATRIX_MATH_API Matrix4x4
		{
		public:
			union
			{
				float m[16];
				struct
				{
					float _00, _01, _02, _03;
					float _10, _11, _12, _13;
					float _20, _21, _22, _23;
					float _30, _31, _32, _33;
				};
				float M[4][4];
			};

			Matrix4x4(void);
			Matrix4x4(float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33);

			//用3*3矩阵创建
			void CreateFrom3X3(const Matrix3& Mat);
			//平移矩阵
			void CreateTranslate(float dx, float dy, float dz);
			void CreateTranslate(const Vector3& V);
			//建立变换矩阵
			void CreateInWorldObject(const Vector3& U, const Vector3& V, const Vector3& N, const Vector3& Point);

			//建立广告牌变换矩阵;
			//@parameter: 广告牌位置
			void CreateFromBillboard(const Vector3& vcPos, const Matrix3& CameraRotMatrix, bool bAxisY); //相机或其他矩阵,是否只绕Y轴旋转
			//够建相机矩阵(根据视见方向)， 已经单位化了
			//$parameter   相机位置 ,观察方向 ,够建相机矩阵(根据目标位置)
			bool CreateFromLookDir(const Vector3& vcPos, const Vector3& vcDir, const Vector3& vcWorldUp = Vector3(0, 1, 0));

			//@parameter
			bool CreateFromLookAt(const Vector3& vcPos, const Vector3& vcLookAt, const Vector3& vcWorldUp = Vector3(0, 1, 0));
			//建立透视投影矩阵
			//@parameter:  X方向张角 ,宽高比 ,近剪裁面 ,远剪裁面
			bool CreatePerspective(float fFov, float fAspect, float fZN, float fZF);
			//建立正交投影矩阵
			//@parameter： 宽,高， 近裁剪面， 远裁剪面
			bool CreateOrthogonal(float fW,
				float fH,
				float fZN,
				float fZF);
			//建立视口矩阵
			bool CreateViewPort(float fX, float fY, float fWidth, float fHeight, float fMinz, float fMaxz);
			// void CreatePointLightPlaneShadow(const Vector3 & LightPoint,const Plane3 &Plane);
			// void CreateInfiniteLightPlaneShadow(const Vector3 & LightDir,const Plane3 &Plane);
			Matrix4x4 operator*(float f) const;
			Matrix4x4 operator+(float f) const;
			Matrix4x4 operator-(float f) const;
			Matrix4x4 operator+(const Matrix4x4& Matirx) const;
			Matrix4x4 operator-(const Matrix4x4& Matirx) const;

			void operator*=(float f);
			void operator+=(float f);
			void operator-=(float f);
			void operator+=(const Matrix4x4& Matirx);
			void operator-=(const Matrix4x4& Matirx);

			bool operator==(const Matrix4x4& v) const;
			float* operator[](size_t row_index);
			const float* operator[](size_t row_index) const;

			//加入把3*3矩阵 旋转或者缩放
			void Add3X3(const Matrix3& Mat);
			//添加平移
			void AddTranslate(const Vector3& V);
			void AddTranslate(float dx, float dy, float dz);

			///*********************************** inline *************************************/

			inline void Identity(void); //单位矩阵
			inline void SetZero();
			inline void TransposeOf(const Matrix4x4& Matrix); //转置
			inline void InverseOf(const Matrix4x4& Mat);      //求逆

			inline Matrix4x4 GetTranspose() const; //转置
			inline Matrix4x4 GetInverse() const;   //求逆

			inline Vector3 GetTranslation(void) const;             //得到平移量
			inline void Get3X3(Matrix3& Mat) const;                //得到3*3部分
			inline Matrix4x4 operator*(const Matrix4x4& Matirx) const; // 矩阵相乘
			inline Vector3 operator*(const Vector3& vc) const;     // 矩阵和向量乘
			inline Vector4 operator*(const Vector4& vc) const;     // 矩阵和向量乘

			//应用3X3部分
			inline Vector3 Apply3X3(const Vector3& v) const;
			//应用平移
			inline Vector3 ApplyTranlaste(const Vector3& Point) const;

			//按行获得向量
			void GetRowVector(Vector4 Row[4]) const;
			//按行列得向量
			void GetColumnVector(Vector4 Column[4]) const;

			void GetRowVector(Vector4& Row0, Vector4& Row1, Vector4& Row2, Vector4& Row3) const;
			void GetColumnVector(Vector4& Column0, Vector4& Column1, Vector4& Column2, Vector4& Column3) const;
			const static Matrix4x4 ms_Materix3X3WIdentity;
			const static Matrix4x4 ms_3DMax_To_Engine;
		}; // class

#include "Matrix4x4.inl"
	}
}