#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "OtherMath.h"

/*
	正变换的变换顺序是S,R,T

	1. 如果要把一个节点 M 变换到以另一个节点 N 为坐标系下的空间位置，首先要做的就是保证当前要变换的 M 的位置和 N 的位置都在同一坐标系下，
	2. 接着就要搞清楚是左乘还是右乘, 最后要弄清楚平移、旋转、缩放的先后顺序，一般情况下是先缩放后旋转再平移。
	3. 每个引擎都有自己的规定。本引擎讲的都是左乘，也就是说，矩阵始终在向量右面，比如：对于一个顶点 v，使用矩阵变换 v′ = v M。
*/

namespace Matrix
{
	namespace Math
	{
		class MATRIX_MATH_API VSTransform
		{

		private:
			Matrix4 m_mCombine;
			Matrix4 m_mCombineInverse;
			void Combine();
			Vector3 m_fScale;
			Matrix3 m_mRotate;
			Vector3 m_vTranslate;
			bool m_bIsCombine;
			bool m_bIsHaveInverse;

		public:
			VSTransform();
			~VSTransform();

			inline const Matrix4& GetCombine();
			inline const Matrix4& GetCombineInverse();
			inline const Vector3& GetScale() const;
			inline const Vector3& GetTranslate() const;
			inline const Matrix3& GetRotate() const;
			inline void GetDir(Vector3& Dir, Vector3& Up, Vector3& Right) const;
			inline void SetScale(const Vector3& fScale);
			inline void SetTranslate(const Vector3& Translate);
			inline void SetRotate(const Matrix3& Rotate);

			enum // Transform type
			{
				TT_POS,
				TT_DIR,
				TT_MAX
			};
			void ApplyForward(const Vector3& In, Vector3& Out, unsigned int uiTransformType);
			enum // Transform Flag
			{
				TF_SCALE = 1,
				TF_ROTATE = 2,
				TF_TRANSFORM = 4,
				TF_ALL = TF_SCALE | TF_TRANSFORM | TF_ROTATE
			};
			//Product 函数用于对两个变换进行叠加，可以指定对 t2 的平移、旋转、缩放分量中的哪一个进行叠加。
			void Product(const VSTransform& t1, const VSTransform& t2, unsigned int TransformFlag = TF_ALL);
			void Inverse(VSTransform& Out) const;
			void ApplyInverse(const Vector3& In, Vector3& Out, unsigned int uiTransformType);

			void SetMatrix(const Matrix4& VSMat);

			void Interpolation(const VSTransform& t1, const VSTransform& t2, float t);

			void Indetity();
			const static VSTransform ms_Indetity;
		};

#include "Transform.inl"
	}
};
