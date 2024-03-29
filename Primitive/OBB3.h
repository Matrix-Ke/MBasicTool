#pragma once
#include "Math/Vector3.h"
#include "Plane3.h"
#include "Triangle3.h"
#include "AABB3.h"

/*****************************************************************************************


							   p1  _______________________________ P0
								  /|                            /|
								/  |                          /  |
							  /    |m_A[1]  |        m_A[2] /    |
						  p5/______|________|______/______/ p4   |
							|      |        |    /        |      |
							|  p2  |_ _  _ _|  / _ _ _ _ _|_ _ __| p3
							|     /         |/____________|      /
							|	 /	             m_A[0]    |    /
							|  /                          |  /
						p6	|/____________________________|/ p7



Plane0 right Plane1 left Plane2 front Plane3 back Plane4 up Plane5 down
****************************************************************************************/
namespace Matrix
{
	namespace Primitive
	{
		class Math::Matrix3;
		class Ray3;
		class Segment3;

		class Plane3;
		class Polygon3;
		class Triangle3;
		class Rectangle3;

		class AABB3;
		class Sphere3;

		class MATRIX_PRIMITIVE_API OBB3
		{
		private:
			Matrix::Math::Vector3 m_A[3];   // 3个轴
			Matrix::Math::Vector3 m_Center; // 中心点
			float m_fA[3];                   // 3个半轴的长度
		public:
			OBB3();
			~OBB3();
			//构造AABB
			OBB3(const Matrix::Math::Vector3 A[3], float fA[3], const Matrix::Math::Vector3& Center);
			OBB3(const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, const Matrix::Math::Vector3& A2,
				float fA0, float fA1, float fA2,
				const Matrix::Math::Vector3& Center);
			//通过点集合构造AABB
			void CreateOBB(const Matrix::Math::Vector3* const pPointArray, unsigned int uiPointNum);
			//合并AABB
			OBB3 MergeOBB(const OBB3& OBB) const;
			//取得6个平面
			void GetPlane(Plane3 pPlanes[6]) const;
			//取得8个点
			void GetPoint(Matrix::Math::Vector3 Point[8]) const;
			//取得6个矩形
			void GetRectangle(Rectangle3 Rectangle[6]) const;
			//获得变换到OBB下变换矩阵，物体必须和OBB在同一个坐标系下
			void GetTransform(Matrix::Math::Matrix4x4& m) const;
			//得到点参数
			bool GetParameter(const Matrix::Math::Vector3& Point, float fOBBParameter[3]) const;
			//用给定的OBB和变换矩阵来构造OBB
			void Transform(const OBB3& OBB, const Matrix::Math::Matrix4x4& Mat);
			AABB3 GetAABB() const;
			/*********************************** inline *************************************/
			inline void Set(const Matrix::Math::Vector3 A[3], float fA[3], const Matrix::Math::Vector3& Center);
			inline void Set(const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, const Matrix::Math::Vector3& A2,
				float fA0, float fA1, float fA2,
				const Matrix::Math::Vector3& Center);

			inline void GetA(Matrix::Math::Vector3 A[3]) const;
			inline void GetfA(float fA[3]) const;
			inline const Matrix::Math::Vector3& GetCenter() const;
			//根据参数返回点
			inline Matrix::Math::Vector3 GetParameterPoint(float fOBBParameter[3]) const;
			inline Matrix::Math::Vector3 GetParameterPoint(float fOBBParameter0, float fOBBParameter1, float fOBBParameter2) const;

			/*************************************距离************************************************/
			//点和OBB距离
			float SquaredDistance(const Matrix::Math::Vector3& Point, float fOBBParameter[3])const;
			//直线和OBB距离
			float SquaredDistance(const Line3& Line, float fOBBParameter[3], float& fLineParameter)const;
			//射线和OBB距离
			float SquaredDistance(const Ray3& Ray, float fOBBParameter[3], float& fRayParameter)const;
			//线段和OBB距离
			float SquaredDistance(const Segment3& Segment, float fOBBParameter[3], float& fSegmentParameter)const;

			//三角形和OBB距离
			float SquaredDistance(const Triangle3& Triangle, float OBBParameter[3],
				float TriangleParameter[3])const;

			//矩形和OBB距离
			float SquaredDistance(const Rectangle3& Rectangle, float OBBParameter[3],
				float RectangleParameter[2])const;
			//OBB和OBB距离
			float SquaredDistance(const OBB3& OBB, float OBB1Parameter[3],
				float OBB2Parameter[3])const;

			//OBB和球的距离
			float Distance(const Sphere3& Sphere, float fOBBParameter[3], Matrix::Math::Vector3& SpherePoint)const;

			//OBB和平面距离
			float Distance(const Plane3& Plane, Matrix::Math::Vector3& OBBPoint, Matrix::Math::Vector3& PlanePoint)const;

			//多边形和OBB距离
			float SquaredDistance(const Polygon3& Polygon,
				float OBBParameter[3], int& IndexTriangle,
				float TriangleParameter[3])const;
			/********************************RelationWith******************************************/
			//点和OBB位置关系
			//IT_In IT_Out IT_On
			int RelationWith(const Matrix::Math::Vector3& Point)const;
			//测试直线与OBB位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Line3& Line, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试射线与OBB位置关系
			//IT_NoIntersect NTERSECT
			int RelationWith(const Ray3& Ray, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试线段与OBB位置关系
			//IT_NoIntersect NTERSECT IT_In
			int RelationWith(const Segment3& Segment, unsigned int& Quantity, float& tNear, float& tFar)const;
			//测试平面和OBB位置关系
			//IT_Front IT_Back IT_Intersect
			int RelationWith(const Plane3& Plane)const;
			//测试三角形与OBB位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Triangle3& Triangle)const;

			//矩形和OBB位置关系
			//IT_NoIntersect IT_Intersect IT_In
			int RelationWith(const Rectangle3& Rectangle)const;

			//OBB和OBB位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const OBB3& OBB)const;

			//OBB和圆位置关系
			//IT_NoIntersect IT_Intersect
			int RelationWith(const Sphere3& Sphere)const;
		private:
			/*void OBBProj(const OBB3 &OBB, const Matrix::Math::Vector3 &vcV,
				float *pfMin, float *pfMax)const;
			void TriProj(const Matrix::Math::Vector3 &v0, const Matrix::Math::Vector3 &v1,
				const Matrix::Math::Vector3 &v2, const Matrix::Math::Vector3 &vcV,
				float *pfMin, float *pfMax)const;

			void Face (int i0, int i1, int i2, Matrix::Math::Vector3 Pnt,
						Matrix::Math::Vector3 Dir, Matrix::Math::Vector3 PmE,
						float& rfSqrDistance,float &fLParam)const;
			void CaseNoZeros (Matrix::Math::Vector3& Pnt,
							const Matrix::Math::Vector3& Dir, float& rfSqrDistance,float &fLParam)const;
			void Case0 (int i0, int i1, int i2, Matrix::Math::Vector3& Pnt,
						const Matrix::Math::Vector3& Dir, float& rfSqrDistance,float &fLParam)const;

			void Case00 (int i0, int i1, int i2,
							Matrix::Math::Vector3& Pnt, const Matrix::Math::Vector3& Dir,  float& rfSqrDistance,float &fLParam)const;
			void Case000 (Matrix::Math::Vector3& Pnt, float& rfSqrDistance)const;*/
		};

#include "OBB3.inl"
	}
}