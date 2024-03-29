#pragma once
namespace Matrix
{
	namespace Math
	{
		class Matrix3;
		class Vector3;
		class  MATRIX_MATH_API Quaternion
		{
		public:
			union
			{
				float m[4];
				struct
				{
					float w, x, y, z;
				};
			};

			Quaternion(void);
			Quaternion(float _w, float _x, float _y, float _z);
			void Set(float _w, float _x, float _y, float _z);
			//通过旋转轴和旋转角构造四元数
			void CreateAxisAngle(const Vector3& Axis, float fAngle);
			//由欧拉角构造四元数
			void  CreateEuler(float fRoll, float fPitch, float fYaw);
			//单位化
			void  Normalize();
			//求共轭
			Quaternion  GetConjugate()const;
			//得到欧拉角
			void  GetEulers(float& fRoll, float& fPitch, float& fYaw)const;
			//从四元数得到变换矩阵
			void  GetMatrix(Matrix3& Matrix)const;
			//得到长度
			float GetLength(void)const;
			//取得逆
			Quaternion GetInverse()const;
			//取得旋转轴和旋转角
			void GetAxisAngle(Vector3& Axis, float& fAngle)const;
			void    operator /= (float f);
			Quaternion operator /  (float f)const;

			void    operator *= (float f);
			Quaternion operator *  (float f)const;

			//// rotation of a vector by a quaternion
			Vector3 operator *  (const Vector3& v) const;

			Quaternion operator *  (const Quaternion& q) const;
			void    operator *= (const Quaternion& q);

			void    operator += (const Quaternion& q);
			Quaternion operator +  (const Quaternion& q) const;

			void    operator -= (const Quaternion& q);
			Quaternion operator -  (const Quaternion& q) const;

			bool operator ==(const Quaternion& q)const;
			//求点积
			float Dot(const Quaternion& q)const;
			//求共轭
			Quaternion operator ~(void) const;

			//求q2绕q1旋转后的四元数
			void Rotate(const Quaternion& q1, const Quaternion& q2);

			//旋转一个向量
			Vector3 Rotate(const Vector3& v)const;
			//插值
			void Slerp(float t, const Quaternion& q1, const Quaternion& q2);
			//三角形2维球型插值
			void TriangleSlerp(float t1, float t2, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3);
			//四元数样条插值
			void Slerp(float t, const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2);
			void SlerpSValueOf(const Quaternion& q1, const Quaternion& q2, const Quaternion& q3);
			//求幂
			Quaternion Pow(float exp)const;
			//求以e为底的对数
			Quaternion Ln()const;
			//求以e为底指数
			Quaternion Exp()const;



		}; // class
		/*----------------------------------------------------------------*/
	}
}