#pragma once
#include "Plane3.h"
#include "Math/Vector3.h"

/********************************************************************************************


__________________
|        |        |
|    A[0]|        |
|		  |        |
|        |_A[1]___|
|                 |
|                 |
|_________________|


左手定则 法向量 为 cross (A[0],A[1]),规定可见 ，方向朝向屏幕外，
********************************************************************************************/
namespace Matrix
{
	namespace Primitive
	{
		class Ray3;
		class Segment3;

		class Plane3;
		class Polygon3;
		class Triangle3;

		class AABB3;
		class OBB3;
		class Sphere3;

		class MATRIX_PRIMITIVE_API Rectangle3 : public Plane3
		{
		private:
			Matrix::Math::Vector3 m_A[2];
			float m_fA[2];
			Matrix::Math::Vector3 m_Center;

		public:
			Rectangle3();
			~Rectangle3();
			Rectangle3(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, float fA0, float fA1);
			Rectangle3(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3 A[2], const float fA[2]);
			bool GetParameter(const Matrix::Math::Vector3& Point, float fRectangleParameter[2]) const;
			void Transform(const Rectangle3& Rectangle,
				const Matrix::Math::Matrix4x4& Mat);
			/*************************************inline************************************************/
			inline void Set(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, float fA0, float fA1);
			inline void Set(const Matrix::Math::Vector3& Center, const Matrix::Math::Vector3 A[2], const float fA[2]);
			inline void GetA(Matrix::Math::Vector3 A[2]) const;
			inline void GetfA(float fA[2]) const;
			inline const Matrix::Math::Vector3& GetCenter() const;
			inline void GetPoint(Matrix::Math::Vector3 Point[4]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(float fRectangleParameter[2]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(float fRectangleParameter0, float fRectangleParameter1) const;

			/*************************************距离************************************************/
			//点和矩形距离
			float SquaredDistance(const Matrix::Math::Vector3& Point, float fRectangleParameter[2])const;

			//矩形和矩形距离
			float SquaredDistance(const Rectangle3& Rectangle,
				float fRectangle1Parameter[2], float fRectangle2Parameter[2])const;

			//三角形和矩形距离
			float SquaredDistance(const Triangle3& Triangle, float fRectangleParameter[2], float fTriangleParameter[3])const;

			//直线和矩形距离
			float SquaredDistance(const Line3& Line, float fRectangleParameter[2], float& fLineParameter)const;
			//射线和矩形距离
			float SquaredDistance(const Ray3& Ray, float fRectangleParameter[2], float& fRayParameter)const;
			//线段和矩形距离
			float SquaredDistance(const Segment3& Segment, float fRectangleParameter[2], float& fSegmentParameter)const;
			//矩形和OBB距离
			float SquaredDistance(const OBB3& OBB, float RectangleParameter[2], float OBBParameter[3])const;
			//矩形和球的距离
			float Distance(const Sphere3& Sphere, float fRectangleParameter[2], Matrix::Math::Vector3& SpherePoint)const;
			//矩形和平面距离
			float Distance(const Plane3& Plane, Matrix::Math::Vector3& RectanglePoint, Matrix::Math::Vector3& PlanePoint)const;
			//矩形和AABB距离
			float SquaredDistance(const AABB3& AABB, float RectangleParameter[2]
				, float AABBParameter[3])const;

			//多边形和矩形距离
			float SquaredDistance(const Polygon3& Polygon,
				float fRectangleParameter[2],
				int& IndexTriangle,
				float fTriangleParameter[3])const;
			/********************************RelationWith******************************************/
			//测试直线与矩形位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Line3& Line, bool bCull, float fRectangleParameter[2], float& fLineParameter)const;
			//测试射线与矩形位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Ray3& Ray, bool bCull, float fRectangleParameter[2], float& fRayParameter)const;
			//测试线段与矩形位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Segment3& Segment, bool bCull, float fRectangleParameter[2], float& fSegmentParameter)const;
			//平面和矩形位置关系
			//IT_On IT_Front IT_Back IT_Intersect
			int RelationWith(const Plane3& Plane)const;
			int RelationWith(const Plane3& Plane, Segment3& Segment)const;
			//三角形和矩形位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Triangle3& Triangle)const;
			int RelationWith(const Triangle3& Triangle, Segment3& Segment)const;
			//矩形和矩形位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Rectangle3& Rectangle)const;
			int RelationWith(const Rectangle3& Rectangle, Segment3& Segment)const;
			//矩形和AABB位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const AABB3& AABB)const;

			//矩形和OBB位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const OBB3& OBB)const;

			//矩形和圆位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Sphere3& Sphere)const;
		};

#include "Rectangle3.inl"
	}
}
