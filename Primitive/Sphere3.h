#pragma once
#include "Line3.h"
#include "AABB3.h"

namespace Matrix
{
	namespace Primitive
	{
		class Ray3;
		class Segment3;

		class Plane3;
		class Polygon3;
		class Triangle3;
		class Rectangle3;

		class AABB3;
		class OBB3;


		class MATRIX_PRIMITIVE_API Sphere3
		{
		public:
			Matrix::Math::Vector3 m_Center; //中心
			float m_fRadius;                 //半径
			Sphere3();
			~Sphere3();
			Sphere3(const Matrix::Math::Vector3& Center, float fRadius);
			//根绝点来建立包围球
			void CreateSphere(const Matrix::Math::Vector3* pPointArray, unsigned int uiPointNum);
			//结合包围球
			Sphere3 MergeSpheres(const Sphere3& Sphere) const;
			//变换球体
			void Transform(const Sphere3& Sphere, const Matrix::Math::Matrix4x4& Mat);
			AABB3 GetAABB() const;
			/*************************************inline************************************************/
			inline void Set(const Matrix::Math::Vector3& Center, float fRadius);

			/*************************************距离************************************************/
			//点和球的距离
			float Distance(const Matrix::Math::Vector3& Point, Matrix::Math::Vector3& SpherePoint)const;
			//线和球的距离
			float Distance(const Line3& Line, Matrix::Math::Vector3& SpherePoint, float& fLineParameter)const;
			//射线和球的距离
			float Distance(const Ray3& Ray, Matrix::Math::Vector3& SpherePoint, float& fRayParameter)const;
			//线段和球的距离
			float Distance(const Segment3& Segment, Matrix::Math::Vector3& SpherePoint, float& fSegmentParameter)const;
			//OBB和球的距离
			float Distance(const OBB3& OBB, Matrix::Math::Vector3& SpherePoint, float fOBBParameter[3])const;
			//平面和球的距离
			float Distance(const Plane3& Plane, Matrix::Math::Vector3& SpherePoint)const;
			//矩形和球的距离
			float Distance(const Rectangle3& Rectangle, Matrix::Math::Vector3& SpherePoint, float fRectangleParameter[2])const;
			//三角形和球的距离
			float Distance(const Triangle3 Triangle, Matrix::Math::Vector3& SpherePoint, float fTriangleParameter[3])const;
			//AABB和球的距离
			float Distance(const AABB3& AABB, Matrix::Math::Vector3& SpherePoint, float fAABBParameter[3])const;

			//多边形和球的距离
			float Distance(const Polygon3& Polygon, Matrix::Math::Vector3& SpherePoint, int& IndexTriangle,
				float fTriangleParameter[3])const;
			/********************************RelationWith******************************************/
			//点和球位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const Matrix::Math::Vector3& Point)const;
			//直线与球位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Line3& Line, unsigned int& Quantity, float& tNear, float& tFar)const;
			//射线与球位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Ray3& Ray, unsigned int& Quantity, float& tNear, float& tFar)const;
			//线段与球位置关系
			//IT_NoIntersect NTERSECT IT_In
			int RelationWith(const Segment3& Segment, unsigned int& Quantity, float& tNear, float& tFar)const;
			//平面与球的位置关系
			//IT_Front IT_Back IT_Intersect
			int RelationWith(const Plane3& Plane)const;
			//三角形和圆位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Triangle3 Triangle)const;
			//矩形和圆位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Rectangle3& Rectangle)const;

			//OBB和圆位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const OBB3& OBB)const;
			//园和圆位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Sphere3& Sphere)const;
		};

#include "Sphere3.inl"
	}
}