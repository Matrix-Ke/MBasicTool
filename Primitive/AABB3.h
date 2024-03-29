#pragma once
#include "Plane3.h"
#include "Rectangle3.h"
#include "Math/CMathInterface.h"

/*
AABB轴对称边界盒，3个中心轴A1,A2,A3永远平行于当前所在坐标轴，中心轴为单位坐标轴，fA1,fA2,fA3为半轴长度，所有内部的点都可以表示成
a * A1 + b * A2 + c * A3 a,b,c为参数，并且|a|<=fA1,|b|<=fA2,|c|<=fA3
*/
namespace Matrix
{
	namespace Primitive
	{
		class MATRIX_PRIMITIVE_API AABB3
		{
		private:
			static const Matrix::Math::Vector3 m_A[3]; // 3个轴
			Matrix::Math::Vector3 m_Center;            // 中心点
			float m_fA[3];                              // 3个半轴的长度
			Matrix::Math::Vector3 m_Max;               //最大点
			Matrix::Math::Vector3 m_Min;               //最小点
		public:
			AABB3();
			~AABB3();

			//通过最大点和最小点构造AABB
			AABB3(const Matrix::Math::Vector3& Max, const Matrix::Math::Vector3& Min);
			//通过中心点和3个轴的半长度构造AABB
			AABB3(const Matrix::Math::Vector3& Center, float fA0, float fA1, float fA2);
			AABB3(const Matrix::Math::Vector3& Center, float fA[3]);
			//通过点集合构造AABB
			void CreateAABB(const Matrix::Math::Vector3* const pPointArray, unsigned int uiPointNum);
			/*********************************** inline *************************************/
			//设置相应的参数
			inline void Set(const Matrix::Math::Vector3& Max, const Matrix::Math::Vector3& Min);
			inline void Set(const Matrix::Math::Vector3& Center, float fA0, float fA1, float fA2);
			inline void Set(const Matrix::Math::Vector3& Center, float fA[3]);
			//获取相应的参数
			inline void GetfA(float fA[3]) const;
			inline const Matrix::Math::Vector3& GetCenter() const;
			inline Matrix::Math::Vector3 GetParameterPoint(float fAABBParameter[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(float fAABBParameter0, float fAABBParameter1, float fAABBParameter2) const;
			inline const Matrix::Math::Vector3& GetMaxPoint() const;
			inline const Matrix::Math::Vector3& GetMinPoint() const;
			//得到AABB6个平面
			void GetPlane(Plane3 pPlanes[6]) const;
			//得到AABB8个点
			void GetPoint(Matrix::Math::Vector3 Point[8]) const;
			//得到AABB6个矩形
			void GetRectangle(Rectangle3 Rectangle[6]) const;
			//给定AABB内一点返回AABB的参数
			bool GetParameter(const Matrix::Math::Vector3& Point, float fAABBParameter[3]) const;
			//用矩阵变换AABB
			void Transform(const AABB3& AABB,
				const Matrix::Math::Matrix4x4& m, bool bHasProject = false);
			//合并2个AABB
			AABB3 MergeAABB(const AABB3& AABB) const;
			void GetQuadAABB(AABB3 AABB[4]) const;
			void GetOctAABB(AABB3 AABB[8]) const;
			AABB3 GetMin(const AABB3& AABB) const;

			bool GetIntersect(AABB3& AABB, AABB3& OutAABB) const;

			/*************************************距离************************************************/
			//点和AABB距离
			float SquaredDistance(const Matrix::Math::Vector3& Point, float fAABBParameter[3])const;
			//直线和AABB距离
			float SquaredDistance(const Line3& Line, float fAABBParameter[3], float& fLineParameter)const;
			//射线和AABB距离
			float SquaredDistance(const Ray3& Ray, float fAABBParameter[3], float& fRayParameter)const;
			//线段和AABB距离
			float SquaredDistance(const Segment3& Segment, float fAABBParameter[3], float& fSegmentParameter)const;

			//三角形和AABB距离
			float SquaredDistance(const Triangle3& Triangle, float AABBParameter[3],
				float TriangleParameter[3])const;

			//矩形和AABB距离
			float SquaredDistance(const Rectangle3& Rectangle, float AABBParameter[3],
				float RectangleParameter[2])const;
			//AABB和AABB距离
			float SquaredDistance(const AABB3& AABB, float AABB1Parameter[3],
				float AABB2Parameter[3])const;
			//AABB和球的距离
			float Distance(const Sphere3& Sphere, float fAABBParameter[3], Matrix::Math::Vector3& SpherePoint)const;

			//AABB和平面距离
			float Distance(const Plane3& Plane, Matrix::Math::Vector3& AABBPoint, Matrix::Math::Vector3& PlanePoint)const;

			//多边形和AABB距离
			float SquaredDistance(const Polygon3& Polygon, float AABBParameter[3], int& IndexTriangle,
				float TriangleParameter[3])const;
			/********************************RelationWith******************************************/
			//点和AABB位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const Matrix::Math::Vector3& Point)const;
			//测试直线与AABB位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Line3& Line, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试射线与AABB位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Ray3& Ray, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试线段与AABB位置关系
			//IT_NoIntersect NTERSECT IT_In
			int RelationWith(const Segment3& Segment, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试平面和AABB位置关系
			//IT_Front IT_Back IT_Intersect
			int RelationWith(const Plane3& Plane)const;
			//三角形和AABB位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Triangle3& Triangle)const;
			//矩形和AABB位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Rectangle3& Rectangle)const;

			//AABB和AABB位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const AABB3& AABB)const;

			//AABB和圆位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Sphere3& Sphere)const;
		};

#include "AABB3.inl"
	}
};
