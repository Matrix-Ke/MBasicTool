#pragma once
#include "Plane3.h"
#include "Platform/MemoryManager.h"

namespace Matrix
{
    namespace Primitive
    {
        class Ray3;
        class Segment3;

        class Plane3;
        class Triangle3;
        class Rectangle3;

        class AABB3;
        class OBB3;
        class Sphere3;

        class MATRIX_PRIMITIVE_API Polygon3 : public Plane3, public Platform::MemoryAllcManager
        {
        private:
            unsigned int m_PointNum;         //点个数
            unsigned int m_IndexNum;         //索引个数
            bool m_Flag;                     // 标志位
            Matrix::Math::Vector3 *m_pPoint; // 点列表
            USHORT *m_pIndex;        // 索引列表
        public:
            Polygon3();
            ~Polygon3();

            Polygon3(const Matrix::Math::Vector3 *pPoint, unsigned int PointNum);
            //拷贝
            bool CopyFrom(const Polygon3 &Polygon);
            //反转面
            void SwapFaces();
            /*********************************** inline *************************************/
            inline void Set(const Matrix::Math::Vector3 *pPoint, unsigned int PointNum);
            inline unsigned int GetPointNum() const;
            inline unsigned int GetIndexNum() const;
            inline const Matrix::Math::Vector3 *const GetpPoint() const;
            inline const USHORT *const GetpIndex() const;
            inline unsigned int GetFlag() const;

            /*************************************距离************************************************/
            //点和多边形距离
            float SquaredDistance(const Matrix::Math::Vector3 &Point, int &IndexTriangle, float fTriangleParameter[3]) const;
            //多边形和多边形距离
            float SquaredDistance(const Triangle3 &Triangle,
                                   int &IndexTriangle,
                                   float fTriangle1Parameter[3],
                                   float fTriangle2Parameter[3]) const;
            //多边形和矩形距离
            float SquaredDistance(const Rectangle3 &Rectangle,
                                   int &IndexTriangle,
                                   float fTriangleParameter[3],
                                   float fRectangleParameter[2]) const;

            //直线和多边形距离
            float SquaredDistance(const Line3 &Line, int &IndexTriangle,
                                   float fTriangleParameter[3], float &fLineParameter) const;
            //射线和多边形距离
            float SquaredDistance(const Ray3 &Ray, int &IndexTriangle,
                                   float fTriangleParameter[3], float &fRayParameter) const;
            //线段和多边形距离
            float SquaredDistance(const Segment3 &Segment, int &IndexTriangle,
                                   float fTriangleParameter[3], float &fSegmentParameter) const;
            //多边形和OBB距离
            float SquaredDistance(const OBB3 &OBB, int &IndexTriangle,
                                   float TriangleParameter[3], float OBBParameter[3]) const;
            //多边形和球的距离
            float Distance(const Sphere3 &Sphere, int &IndexTriangle,
                            float fTriangleParameter[3], Matrix::Math::Vector3 &SpherePoint) const;

            //平面和多边形距离
            float Distance(const Plane3 &Plane, int &IndexTriangle,
                            Matrix::Math::Vector3 &TrianglePoint, Matrix::Math::Vector3 &PlanePoint) const;
            //多边形和AABB距离
            float SquaredDistance(const AABB3 &AABB, int &IndexTriangle,
                                   float TriangleParameter[3], float AABBParameter[3]) const;

            //多边形和多边形距离
            float SquaredDistance(const Polygon3 &Polygon, int &Index1Triangle,
                                   float Triangle1Parameter[3], int &Index2Triangle,
                                   float Triangle2Parameter[3]) const;
            /********************************RelationWith******************************************/
            //测试直线与多边形位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
            // IT_NoIntersect NTERSECT
            int RelationWith(const Line3 &Line, bool bCull, int &iIndexTriangle, float fTriangleParameter[3],
                             float &fLineParameter) const;
            //测试射线与多边形位置关系
            // IT_NoIntersect NTERSECT
            int RelationWith(const Ray3 &Ray, bool bCull, int &iIndexTriangle, float fTriangleParameter[3],
                             float &fRayParameter) const;
            //测试线段与多边形位置关系
            // IT_NoIntersect NTERSECT
            int RelationWith(const Segment3 &Segment, bool bCull, int &iIndexTriangle, float fTriangleParameter[3],
                             float &fSegmentParameter) const;
            //平面和多边形位置关系
            // IT_On IT_Front IT_Back IT_Intersect
            int RelationWith(const Plane3 &Plane) const;
            int RelationWith(const Plane3 &Plane, Segment3 &Segment) const;
            //多边形和三角形位置关系
            // IT_NoIntersect IT_Intersect
            int RelationWith(const Triangle3 &Triangle) const;
            int RelationWith(const Triangle3 &Triangle, Segment3 &Segment) const;
            //多边形和矩形位置关系
            // IT_NoIntersect IT_Intersect
            int RelationWith(const Rectangle3 &Rectangle) const;
            int RelationWith(const Rectangle3 &Rectangle, Segment3 &Segment) const;
            //多边形和AABB位置关系
            // IT_NoIntersect IT_Intersect IT_In
            int RelationWith(const AABB3 &AABB) const;

            //多边形和OBB位置关系
            // IT_NoIntersect IT_Intersect IT_In
            int RelationWith(const OBB3 &OBB) const;

            //多边形和圆位置关系
            // IT_NoIntersect IT_Intersect IT_In
            int RelationWith(const Sphere3 &Sphere) const;

            ///*************************************** Clip *********************************/
            ////平面减切多边形
            // void	Clip(const Plane3& Plane,
            //	Polygon3& pFront,
            //	Polygon3& pBack)const;
            ////用AABB剪切多边形用来适合AABB
            // void	Clip(const AABB3& ABBB);
        };
#include "Polygon3.inl"
    }
}