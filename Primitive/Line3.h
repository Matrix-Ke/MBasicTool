#pragma once
#include "Point3.h"



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
		class Sphere3;


		class MATRIX_PRIMITIVE_API Line3
		{
		protected:
			Matrix::Math::Vector3 m_Orig; // 源点
			Matrix::Math::Vector3 m_Dir;  // 方向
		public:
			Line3();
			Line3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir);
			~Line3();
			//拷贝构造函数
			Line3(const Line3& rhs);

			void Transform(const Line3& Line, const Matrix::Math::Matrix4x4& Mat);
			bool GetParameter(const Matrix::Math::Vector3& Point, float& fLineParameter) const;
			/************************inline***************************************/
			inline void Set(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir);
			inline const Matrix::Math::Vector3& GetOrig() const;
			inline const Matrix::Math::Vector3& GetDir() const;

			inline Matrix::Math::Vector3 GetParameterPoint(float fLineParameter) const;



			//点到直线距离
			float SquaredDistance(const Matrix::Math::Vector3& Point, float& fLineParameter)const;
			//直线和直线的距离
			float SquaredDistance(const Line3& Line, float& fLine1Parameter, float& fLine2Parameter)const;
			//直线和射线距离
			float SquaredDistance(const Ray3& Ray, float& fLineParameter, float& fRayParameter)const;
			//直线和线段距离
			float SquaredDistance(const Segment3& Segment, float& fLineParameter, float& fSegmentParameter)const;
			//直线和三角形距离
			float SquaredDistance(const Triangle3& Triangle, float& fLineParameter, float fTriangleParameter[3])const;
			//直线和矩形距离
			float SquaredDistance(const Rectangle3& Rectangle, float& fLineParameter, float fRectangleParameter[2])const;
			//直线和OBB距离
			float SquaredDistance(const OBB3& OBB, float& fLineParameter, float fOBBParameter[3])const;
			//直线和球的距离
			float Distance(const Sphere3& Sphere, float& fLineParameter, Matrix::Math::Vector3& SpherePoint)const;
			//直线和平面距离
			float Distance(const Plane3& Plane, Matrix::Math::Vector3& LinePoint, Matrix::Math::Vector3& PlanePoint)const;
			//直线和AABB距离
			float SquaredDistance(const AABB3& AABB, float& fLineParameter, float fAABBParameter[3])const;

			//直线和多边形距离
			float SquaredDistance(const Polygon3& Polygon, float& fLineParameter,
				int& IndexTriangle,
				float fTriangleParameter[3])const;


			/********************************RelationWith******************************************/
			//测试直线与三角形位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
			//IT_NoIntersect NTERSECT
			int RelationWith(const Triangle3& Triangle, bool bCull, float& fLineParameter,
				float fTriangleParameter[3])const;
			//测试直线与平面位置关系
			//IT_NoIntersect NTERSECT IT_On IT_Back IT_Front
			int RelationWith(const Plane3& Plane, bool bCull, float& fLineParameter)const;
			//测试直线与矩形位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Rectangle3& Rectangle, bool bCull, float& fLineParameter,
				float fRectangleParameter[2])const;
			//测试直线与球位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Sphere3& sphere, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试直线与OBB位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const OBB3& OBB, unsigned int& Quantity, float& tNear, float& tFar)const;

			//测试直线与AABB位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const AABB3& AABB, unsigned int& Quantity, float& tNear, float& tFar)const;

			//测试直线与多边形位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
			//IT_NoIntersect NTERSECT
			int RelationWith(const Polygon3& Polygon, float& fLineParameter,
				bool bCull, int& iIndexTriangle, float fTriangleParameter[3])const;
			/*************************************距离************************************************/
		};

#include "Line3.inl"
	}
}