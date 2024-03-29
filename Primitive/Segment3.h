#pragma once
#include "Ray3.h"
#include "Math/Vector3.h"

namespace Matrix
{
	namespace Primitive
	{

		class Ray3;

		class Plane3;
		class Polygon3;
		class Triangle3;
		class Rectangle3;

		class AABB3;
		class OBB3;
		class Sphere3;


		class MATRIX_PRIMITIVE_API Segment3 : public Ray3
		{
		private:
			Matrix::Math::Vector3 m_End;
			float m_fLen;
		public:
			Segment3();
			~Segment3();
			Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End);
			Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, float fLen);
			bool GetParameter(const Matrix::Math::Vector3& Point, float& fSegmentParameter) const;
			//用矩阵变换射线
			void Transform(const Segment3& Segment, const Matrix::Math::Matrix4x4& Mat);
			/*************************************inline************************************************/
			inline const Matrix::Math::Vector3& GetEnd() const;
			inline float GetLen() const;
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End);
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, float fLen);
			inline Matrix::Math::Vector3 GetParameterPoint(float fSegmentParameter) const;

			/********************************RelationWith******************************************/
			//测试线段与三角形位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
			//IT_NoIntersect NTERSECT
			int RelationWith(const Triangle3& Triangle, bool bCull, float& fSegmentParameter,
				float fTriangleParameter[3])const;
			//测试线段与平面位置关系
			//IT_NoIntersect NTERSECT IT_On IT_Back IT_Front
			int RelationWith(const Plane3& Plane, bool bCull, float& fSegmentParameter)const;
			//测试线段与矩形位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Rectangle3& Rectangle, bool bCull, float& fSegmentParameter,
				float fRectangleParameter[2])const;

			//测试线段与OBB位置关系
			//IT_NoIntersect NTERSECT IT_In
			int RelationWith(const OBB3& OBB, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试线段与AABB位置关系
			//IT_NoIntersect NTERSECT IT_In
			int RelationWith(const AABB3& AABB, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试线段与球位置关系
			//IT_NoIntersect NTERSECT IT_In
			int RelationWith(const Sphere3& sphere, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试线段与多边形位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Polygon3& Polygon, float& fSegmentParameter,
				bool bCull, int& iIndexTriangle, float fTriangleParameter[3])const;

			/*************************************距离************************************************/
			//点和线段距离
			float SquaredDistance(const Matrix::Math::Vector3& Point, float& fSegmentParameter)const;
			//直线和线段距离
			float SquaredDistance(const Line3& Line, float& fSegmentParameter, float& fLineParameter)const;
			//射线和线段距离
			float SquaredDistance(const Ray3& Ray, float& fSegmentParameter, float& fRayParameter)const;
			//线段和线段距离
			float SquaredDistance(const Segment3& Segment, float& fSegment1Parameter, float& fSegment2Parameter)const;
			//线段和三角形距离
			float SquaredDistance(const Triangle3& Triangle, float& fSegmentParameter, float fTriangleParameter[3])const;
			//线段和矩形距离
			float SquaredDistance(const Rectangle3& Rectangle, float& fSegmentParameter, float fRectangleParameter[2])const;
			//线段和OBB距离
			float SquaredDistance(const OBB3& OBB, float& fSegmentParameter, float fOBBParameter[3])const;

			//线段和球的距离
			float Distance(const Sphere3& Sphere, float& fSegmentParameter, Matrix::Math::Vector3& SpherePoint)const;

			//线段和平面距离
			float Distance(const Plane3& Plane, Matrix::Math::Vector3& SegmentPoint, Matrix::Math::Vector3& PlanePoint)const;

			//线段和AABB距离
			float SquaredDistance(const AABB3& AABB, float& fSegmentParameter, float fAABBParameter[3])const;

			//线段和多边形距离
			float SquaredDistance(const Polygon3& Polygon, float& fSegmentParameter, int& IndexTriangle, float fTriangleParameter[3])const;
		};

#include "Segment3.inl"
	}
}