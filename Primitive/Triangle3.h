#pragma once
#include "Plane3.h"
/***************************************************************************************

					fTriangleParameter[1]
		   m_V[0]	_________________________m_V[1]
				   \                       /
					\                     /
					 \                   /
					  \                 /
					   \               /
						\             /
fTriangleParameter[2]  \           /  fTriangleParameter[0]
						  \         /
						   \       /
							 \    /
							  \  /
							   \/m_V[2]
***************************************************************************************/
namespace Matrix
{
	namespace Primitive
	{
		class Ray3;
		class Segment3;

		class Plane3;
		class Polygon3;
		class Rectangle3;

		class AABB3;
		class OBB3;
		class Sphere3;

		class MATRIX_PRIMITIVE_API Triangle3 : public Plane3
		{
		private:
			Matrix::Math::Vector3 m_V[3];

		public:
			Triangle3();
			~Triangle3();
			Triangle3(const Matrix::Math::Vector3& P0, const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2);
			Triangle3(const Matrix::Math::Vector3 Point[3]);
			bool GetParameter(const Matrix::Math::Vector3& Point, float fTriangleParameter[3]) const;
			void Transform(const Triangle3& Triangle, const Matrix::Math::Matrix4x4& Mat);
			/*************************************inline************************************************/

			inline void Set(const Matrix::Math::Vector3& P1, const Matrix::Math::Vector3& P2, const Matrix::Math::Vector3& P3);
			inline void Set(const Matrix::Math::Vector3 Point[3]);
			inline void GetPoint(Matrix::Math::Vector3 Point[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(float fTriangleParameter[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(float fTriangleParameter0,
				float fTriangleParameter1, float fTriangleParameter2) const;

			/*************************************距离************************************************/
			//点和三角形距离
			float SquaredDistance(const Matrix::Math::Vector3& Point, float fTriangleParameter[3])const;
			//三角形和三角形距离
			float SquaredDistance(const Triangle3& Triangle,
				float fTriangle1Parameter[3],
				float fTriangle2Parameter[3])const;
			//三角形和矩形距离
			float SquaredDistance(const Rectangle3& Rectangle,
				float fTriangleParameter[3],
				float fRectangleParameter[2])const;

			//直线和三角形距离
			float SquaredDistance(const Line3& Line, float fTriangleParameter[3], float& fLineParameter)const;
			//射线和三角形距离
			float SquaredDistance(const Ray3& Ray, float fTriangleParameter[3], float& fRayParameter)const;
			//线段和三角形距离
			float SquaredDistance(const Segment3& Segment, float fTriangleParameter[3], float& fSegmentParameter)const;
			//三角形和OBB距离
			float SquaredDistance(const OBB3& OBB, float TriangleParameter[3], float OBBParameter[3])const;
			//三角形和球的距离
			float Distance(const Sphere3& Sphere, float fTriangleParameter[3], Matrix::Math::Vector3& SpherePoint)const;

			//平面和三角形距离
			float Distance(const Plane3& Plane, Matrix::Math::Vector3& TrianglePoint, Matrix::Math::Vector3& PlanePoint)const;
			//三角形和AABB距离
			float SquaredDistance(const AABB3& AABB, float TriangleParameter[3]
				, float AABBParameter[3])const;
			//三角形和多边形距离
			float SquaredDistance(const Polygon3& Polygon,
				float fTriangle1Parameter[3],
				int& IndexTriangle,
				float fTriangle2Parameter[3])const;
			/********************************RelationWith******************************************/
			//测试直线与三角形位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
			//IT_NoIntersect NTERSECT
			int RelationWith(const Line3& Line, bool bCull, float fTriangleParameter[3],
				float& fLineParameter)const;
			//测试射线与三角形位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Ray3& Ray, bool bCull, float fTriangleParameter[3],
				float& fRayParameter)const;
			//测试线段与三角形位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Segment3& Segment, bool bCull, float fTriangleParameter[3],
				float& fSegmentParameter)const;
			//平面和三角形位置关系
			//IT_On IT_Front IT_Back IT_Intersect
			int RelationWith(const Plane3& Plane)const;
			int RelationWith(const Plane3& Plane, Segment3& Segment)const;
			//三角形和三角形位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Triangle3& Triangle)const;
			int RelationWith(const Triangle3& Triangle, Segment3& Segment)const;
			//三角形和矩形位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Rectangle3& Rectangle)const;
			int RelationWith(const Rectangle3& Rectangle, Segment3& Segment)const;
			//三角形和AABB位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const AABB3& AABB)const;

			//三角形和OBB位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const OBB3& OBB)const;

			//三角形和圆位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Sphere3& Sphere)const;
		};

#include "Triangle3.inl"

	}
}