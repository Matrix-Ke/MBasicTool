#pragma once
#include "Line3.h"
#include "Math/Matrix4x4.h"

namespace Matrix
{
    namespace Primitive
    {
        class Segment3;

        class Plane3;
        class Polygon3;
        class Triangle3;
        class Rectangle3;

        class AABB3;
        class OBB3;
        class Sphere3;

        //射线
        class MATRIX_PRIMITIVE_API Ray3 : public Line3
        {
        public:
            Ray3();
            Ray3(const Matrix::Math::Vector3 &Orig, const Matrix::Math::Vector3 &Dir);
            ~Ray3();

            bool GetParameter(const Matrix::Math::Vector3 &Point, float &fRayParameter) const;
            void Transform(const Ray3 &Ray, const Matrix::Math::Matrix4x4 &Mat);
            /************************inline***************************************/
            inline Matrix::Math::Vector3 GetParameterPoint(float fRayParameter) const;

            /********************************RelationWith******************************************/
            //测试射线与三角形是否位置关系 bCull为是否为背面剪裁,是否考虑朝向,t返回相交长度
            // IT_NoIntersect NTERSECT
            int RelationWith(const Triangle3 &Triangle, bool bCull, float &fRayParameter,
                             float fTriangleParameter[3]) const;
            //测试射线与平面位置关系
            // IT_NoIntersect NTERSECT IT_On IT_Back IT_Front
            int RelationWith(const Plane3 &Plane, bool bCull, float &fRayParameter) const;
            //测试射线与矩形位置关系
            // IT_NoIntersect NTERSECT
            int RelationWith(const Rectangle3 &Rectangle, bool bCull, float &fRayParameter,
                             float fRectangleParameter[2]) const;

            //测试射线与OBB位置关系
            // IT_NoIntersect NTERSECT
            int RelationWith(const OBB3 &OBB, unsigned int &Quantity, float &tNear, float &tFar) const;
            //测试直线与AABB位置关系
            // IT_NoIntersect NTERSECT
            int RelationWith(const AABB3 &AABB, unsigned int &Quantity, float &tNear, float &tFar) const;
            //测试射线与球位置关系
            // IT_NoIntersect NTERSECT
            int RelationWith(const Sphere3 &sphere, unsigned int &Quantity, float &tNear, float &tFar) const;
            //测试射线与多边形位置关系
            // IT_NoIntersect NTERSECT
            int RelationWith(const Polygon3 &Polygon, float &fRayParameter,
                             bool bCull, int &iIndexTriangle, float fTriangleParameter[3]) const;
            /*************************************距离************************************************/
            //点和射线距离
            float SquaredDistance(const Matrix::Math::Vector3 &Point, float &fLineParameter) const;
            //直线和射线距离
            float SquaredDistance(const Line3 &Line, float &fRayParameter, float &fLineParameter) const;
            //射线和射线距离
            float SquaredDistance(const Ray3 &Ray, float &fRay1Parameter, float &fRay2Parameter) const;
            //射线和线段距离
            float SquaredDistance(const Segment3 &Segment, float &fRayParameter, float &fSegmentParameter) const;
            //射线和三角形距离
            float SquaredDistance(const Triangle3 &Triangle, float &fRayParameter, float fTriangleParameter[3]) const;
            //射线和矩形距离
            float SquaredDistance(const Rectangle3 &Rectangle, float &fRayParameter, float fRectangleParameter[2]) const;
            //射线和OBB距离
            float SquaredDistance(const OBB3 &OBB, float &fRayParameter, float fOBBParameter[3]) const;
            //射线和球的距离
            float Distance(const Sphere3 &Sphere, float &fRayParameter, Matrix::Math::Vector3 &SpherePoint) const;
            //射线和平面距离
            float Distance(const Plane3 &Plane, Matrix::Math::Vector3 &RayPoint, Matrix::Math::Vector3 &PlanePoint) const;
            //射线和AABB距离
            float SquaredDistance(const AABB3 &AABB, float &fRayParameter, float fAABBParameter[3]) const;
            //射线和多边形距离
            float SquaredDistance(const Polygon3 &Polygon, float &fRayParameter, int &IndexTriangle, float fTriangleParameter[3]) const;
        }; // class
           /*----------------------------------------------------------------*/

#include "Ray3.inl"

    };

};
