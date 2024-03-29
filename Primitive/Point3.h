#pragma once
#include "Math/Vector3.h"

#ifdef	Primitive_EXPORTS
#define MATRIX_PRIMITIVE_API __declspec(dllexport)
#else   
#define MATRIX_PRIMITIVE_API __declspec(dllimport)
#endif // Primitive_EXPORTS


namespace Matrix
{
	namespace Primitive
	{

		//判断两个物体的位置关系的，通过其英文名称都可以判断出它们的具体含义
		enum IntersectionType
		{
			IT_Front = 0,
			IT_Back = 1,
			IT_On = 2,
			IT_Clipped = 3,
			IT_Culled = 4,
			IT_Visible = 5,
			IT_Intersect = 7,			//3
			IT_Out = 8,					//4
			IT_In = 9,					//5
			IT_NoIntersect = 10			//6
		};

		class Matrix3;
		class Quaternion;
		class Ray3;
		class Line3;
		class Plane3;
		class Ray3;
		class Segment3;
		class Triangle3;
		class Rectangle3;
		class OBB3;
		class Sphere3;
		class AABB3;
		class Matrix4x4;
		class Polygon3;


		class MATRIX_PRIMITIVE_API Point3 : public  Math::Vector3
		{
		public:

			Point3(const Point3& rhs);
			Point3(const Vector3& rhs);
			Point3& operator = (const Vector3& rhs);

		public:
			/********************************距离******************************************/
			//点和点距离
			float SquaredDistance(const Vector3& Point) const;
			//点到直线距离
			float SquaredDistance(const Line3& Line, float& fLineParameter)const;
			//点和射线距离
			float SquaredDistance(const Ray3& Ray, float& fRayParameter)const;
			//点和线段距离
			float SquaredDistance(const Segment3& Segment, float& fSegmentParameter)const;
			//点和三角形距离
			float SquaredDistance(const Triangle3& Triangle, float fTriangleParameter[3])const;
			//点和矩形距离
			float SquaredDistance(const Rectangle3& Rectangle, float fRectangleParameter[2])const;
			//点和OBB距离
			float SquaredDistance(const OBB3& OBB, float fOBBParameter[3])const;
			//点和球的距离
			float Distance(const Sphere3& Sphere, Vector3& SpherePoint)const;
			//点和平面距离
			float Distance(const Plane3& Plane, Vector3& PlanePoint)const;
			//点和AABB距离
			float SquaredDistance(const AABB3& AABB, float fAABBParameter[3])const;
			//点和多边形距离
			float SquaredDistance(const Polygon3& Polygon, int& IndexTriangle, float fTriangleParameter[3])const;
			/********************************RelationWith******************************************/
			//点和球位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const Sphere3& Sphere)const;
			//点和平面位置关系
			//IT_Front IT_Back IT_On
			int RelationWith(const Plane3& Plane)const;
			//点和OBB位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const OBB3& OBB)const;
			//点和AABB位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const AABB3& AABB)const;
		};
	}
}