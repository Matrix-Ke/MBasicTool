#include "Line3.h"
#include "Math/Matrix4x4.h"
#include "Ray3.h"
#include "Segment3.h"

#include "Plane3.h"
#include "Triangle3.h"
#include "Rectangle3.h"
#include "Polygon3.h"

#include "OBB3.h"
#include "AABB3.h"
#include "Sphere3.h"

// using namespace Matrix::Math;

/*----------------------------------------------------------------*/
Matrix::Primitive::Line3::Line3()
{
}
/*----------------------------------------------------------------*/
Matrix::Primitive::Line3::Line3(const Matrix::Math::Vector3 &Orig, const Matrix::Math::Vector3 &Dir)
{
    Set(Orig, Dir);
}
/*----------------------------------------------------------------*/
Matrix::Primitive::Line3::~Line3()
{
}
/*----------------------------------------------------------------*/
bool Matrix::Primitive::Line3::GetParameter(const Matrix::Math::Vector3 &Point, float &fLineParameter) const
{
    Matrix::Math::Vector3 Temp = Point - m_Orig;
    if (Temp.IsParallel(m_Dir))
    {
        fLineParameter = Temp.GetLength();
        return 1;
    }
    else
        return 0;
}
Matrix::Primitive::Line3::Line3(const Line3 &rhs)
{
    this->m_Orig = rhs.m_Orig;
    this->m_Dir = rhs.m_Dir;
}
/*----------------------------------------------------------------*/
void Matrix::Primitive::Line3::Transform(const Line3 &Line, const Matrix::Math::Matrix4x4 &Mat)
{
    m_Dir = Mat.Apply3X3(Line.m_Dir);
    m_Dir.Normalize();
    m_Orig = Line.m_Orig * Mat;
}

float Matrix::Primitive::Line3::SquaredDistance(const Matrix::Math::Vector3 &Point, float &fLineParameter) const
{
    Matrix::Math::Vector3 Diff = Point - m_Orig;

    fLineParameter = m_Dir.Dot(Diff);

    Diff -= m_Dir * fLineParameter;

    return Diff.GetSqrLength();
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::SquaredDistance(const Line3 &Line, float &fLine1Parameter, float &fLine2Parameter) const
{
    float SquareDis;
    Matrix::Math::Vector3 Diff = m_Orig - Line.m_Orig;
    float a01 = -(m_Dir.Dot(Line.m_Dir));
    float b0 = m_Dir.Dot(Diff);
    float c = Diff.GetSqrLength();
    float det = 1 - a01 * a01;

    if (Math::ABS(det) >= EPSILON_E4)
    {
        float b1 = -(Line.m_Dir.Dot(Diff));
        float invDet = 1 / det;
        fLine1Parameter = (a01 * b1 - b0) * invDet;
        fLine2Parameter = (a01 * b0 - b1) * invDet;
        SquareDis = fLine1Parameter * (fLine1Parameter + a01 * fLine2Parameter + 2 * b0) + fLine2Parameter * (a01 * fLine1Parameter + fLine2Parameter + 2 * b1) + c;
    }
    else
    {
        fLine1Parameter = -b0;
        fLine2Parameter = 0;

        SquareDis = b0 * fLine1Parameter + c;
    }
    return SquareDis;
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::SquaredDistance(const Ray3 &Ray, float &fLineParameter, float &fRayParameter) const
{
    const Line3 Line = Ray;
    float sqrDist = SquaredDistance(Line, fLineParameter, fRayParameter);

    if (fRayParameter < 0)
    {
        fRayParameter = 0;
        sqrDist = SquaredDistance(Ray.m_Orig, fLineParameter);
    }
    return sqrDist;
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::SquaredDistance(const Segment3 &Segment, float &fLineParameter, float &fSegmentParameter) const
{
    const Ray3 Ray = Segment;
    float sqrDist = SquaredDistance(Ray, fLineParameter, fSegmentParameter);
    float fLen = Segment.GetLen();

    if (fSegmentParameter > fLen)
    {
        Matrix::Math::Vector3 End = Segment.GetEnd();
        fSegmentParameter = fLen;
        sqrDist = SquaredDistance(End, fLineParameter);
    }
    return sqrDist;
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::SquaredDistance(const Triangle3 &Triangle, float &fLineParameter, float fTriangleParameter[3]) const
{
    Matrix::Math::Vector3 TrianglePoint[3];
    Triangle.GetPoint(TrianglePoint);

    float fSqrDist = MAX_REAL;
    float fSqrDistTmp;
    Segment3 Edge;
    float Tempt0, Tempt1;
    Edge.Set(TrianglePoint[0], TrianglePoint[1]);
    fSqrDistTmp = SquaredDistance(Edge, Tempt0, Tempt1);

    if (fSqrDistTmp < fSqrDist)
    {

        fLineParameter = Tempt0;

        fTriangleParameter[1] = Tempt1 / Edge.GetLen();
        fTriangleParameter[0] = 1.0f - fTriangleParameter[1];
        fTriangleParameter[2] = 0.0f;

        fSqrDist = fSqrDistTmp;
    }

    Edge.Set(TrianglePoint[0], TrianglePoint[2]);
    fSqrDistTmp = SquaredDistance(Edge, Tempt0, Tempt1);

    if (fSqrDistTmp < fSqrDist)
    {

        fLineParameter = Tempt0;

        fTriangleParameter[1] = 0.0f;
        fTriangleParameter[2] = Tempt1 / Edge.GetLen();
        fTriangleParameter[0] = 1.0f - fTriangleParameter[2];

        fSqrDist = fSqrDistTmp;
    }

    Edge.Set(TrianglePoint[1], TrianglePoint[2]);
    fSqrDistTmp = SquaredDistance(Edge, Tempt0, Tempt1);

    if (fSqrDistTmp < fSqrDist)
    {

        fLineParameter = Tempt0;

        fTriangleParameter[1] = Tempt1 / Edge.GetLen();
        fTriangleParameter[2] = 1.0f - fTriangleParameter[1];
        fTriangleParameter[0] = 0.0f;

        fSqrDist = fSqrDistTmp;
    }
    return fSqrDist;
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::SquaredDistance(const Rectangle3 &Rectangle, float &fLineParameter, float fRectangleParameter[2]) const
{
    //没有测试相交

    float fSqrDist = MAX_REAL;
    float fSqrDistTmp;
    Matrix::Math::Vector3 r[4];

    Matrix::Math::Vector3 A[2];
    Rectangle.GetA(A);
    float fA[2];
    Rectangle.GetfA(fA);

    Matrix::Math::Vector3 Temp0 = Rectangle.GetCenter() + A[0] * fA[0];
    Matrix::Math::Vector3 Temp1 = Rectangle.GetCenter() + A[0] * (-fA[0]);
    r[0] = Temp0 + A[1] * fA[1];
    r[1] = Temp0 + A[1] * (-fA[1]);
    r[2] = Temp1 + A[1] * (-fA[1]);
    r[3] = Temp1 + A[1] * fA[1];

    Segment3 Edge;
    Edge.Set(r[0], r[1]);

    float fT0, fT1;
    fSqrDistTmp = SquaredDistance(Edge, fT0, fT1);

    if (fSqrDistTmp < fSqrDist)
    {
        fSqrDist = fSqrDistTmp;
        fLineParameter = fT0;
        fRectangleParameter[0] = fA[0];
        fRectangleParameter[1] = fT1 - fA[1];
    }
    Edge.Set(r[2], r[1]);

    fSqrDistTmp = SquaredDistance(Edge, fT0, fT1);

    if (fSqrDistTmp < fSqrDist)
    {
        fSqrDist = fSqrDistTmp;
        fLineParameter = fT0;
        fRectangleParameter[0] = fA[1];
        fRectangleParameter[1] = fT1 - fA[0];
    }
    Edge.Set(r[3], r[2]);

    fSqrDistTmp = SquaredDistance(Edge, fT0, fT1);

    if (fSqrDistTmp < fSqrDist)
    {
        fSqrDist = fSqrDistTmp;
        fLineParameter = fT0;
        fRectangleParameter[0] = -fA[0];
        fRectangleParameter[1] = fT1 - fA[1];
    }
    Edge.Set(r[3], r[0]);
    fSqrDistTmp = SquaredDistance(Edge, fT0, fT1);

    if (fSqrDistTmp < fSqrDist)
    {
        fSqrDist = fSqrDistTmp;
        fLineParameter = fT0;
        fRectangleParameter[0] = -fA[1];
        fRectangleParameter[1] = fT1 - fA[0];
    }
    return fSqrDist;
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::SquaredDistance(const OBB3 &OBB, float &fLineParameter, float fOBBParameter[3]) const
{

    return OBB.SquaredDistance(*this, fOBBParameter, fLineParameter);
}
/*----------------------------------------------------------------*/
//直线和球的距离
float Matrix::Primitive::Line3::Distance(const Sphere3 &Sphere, float &fLineParameter, Matrix::Math::Vector3 &SpherePoint) const
{
    return Sphere.Distance(*this, SpherePoint, fLineParameter);
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::Distance(const Plane3 &Plane, Matrix::Math::Vector3 &LinePoint, Matrix::Math::Vector3 &PlanePoint) const
{
    return Plane.Distance(*this, PlanePoint, LinePoint);
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::SquaredDistance(const AABB3 &AABB, float &fLineParameter, float fAABBParameter[3]) const
{
    return AABB.SquaredDistance(*this, fAABBParameter, fLineParameter);
}
/*----------------------------------------------------------------*/
float Matrix::Primitive::Line3::SquaredDistance(const Polygon3 &Polygon, float &fLineParameter,
                                                 int &IndexTriangle,
                                                 float fTriangleParameter[3]) const
{

    return Polygon.SquaredDistance(*this, IndexTriangle, fTriangleParameter, fLineParameter);
}

int Matrix::Primitive::Line3::RelationWith(const Triangle3 &Triangle, bool bCull, float &fLineParameter, float fTriangleParameter[3]) const
{
    Matrix::Math::Vector3 pvec, tvec, qvec;
    Matrix::Math::Vector3 TrianglePoint[3];
    Triangle.GetPoint(TrianglePoint);
    Matrix::Math::Vector3 edge1 = TrianglePoint[1] - TrianglePoint[0];
    Matrix::Math::Vector3 edge2 = TrianglePoint[2] - TrianglePoint[0];

    pvec.Cross(m_Dir, edge2);

    float det = edge1.Dot(pvec);
    if ((bCull) && (det < EPSILON_E4))
        return IT_NoIntersect;
    else if ((det < EPSILON_E4) && (det > -EPSILON_E4))
        return IT_NoIntersect;

    float f_det = 1.0f / det;
    tvec = m_Orig - TrianglePoint[0];
    float u = (tvec.Dot(pvec)) * f_det;
    if (u < 0.0f || u > 1)
        return IT_NoIntersect;

    qvec.Cross(tvec, edge1);
    float v = (m_Dir.Dot(qvec)) * f_det;
    if (v < 0.0f || u + v > 1)
        return IT_NoIntersect;

    float f = (edge2.Dot(qvec)) * f_det;

    fTriangleParameter[1] = u;
    fTriangleParameter[2] = v;
    fTriangleParameter[0] = 1.0f - u - v;
    fLineParameter = f;

    return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const Matrix::Primitive::Plane3 &Plane, bool bCull, float &fLineParameter) const
{
    float Vd = Plane.GetN().Dot(m_Dir);

    if (Math::ABS(Vd) < EPSILON_E4)
    {
        return Point3(m_Orig).RelationWith(Plane);
    }

    if (bCull && (Vd > 0.0f))
        return IT_NoIntersect;

    float Vo = -((Plane.GetN().Dot(Point3(m_Orig))) + Plane.GetfD());

    float _t = Vo / Vd;

    fLineParameter = _t;

    return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const Rectangle3 &Rectangle, bool bCull, float &fLineParameter, float fRectangleParameter[2]) const
{
    Plane3 Plane = Rectangle.GetPlane();
    Math::Vector3 PlanePoint;
    if (bCull)
    {
        if (Point3(m_Orig).RelationWith(Plane) == IT_Back)
            return IT_NoIntersect;
    }
    if (RelationWith(Plane, bCull, fLineParameter) == IT_Intersect)
    {
        Matrix::Math::Vector3 Point = GetParameterPoint(fLineParameter);
        if (Rectangle.GetParameter(Point, fRectangleParameter))
        {
            return IT_Intersect;
        }
    }
    return IT_NoIntersect;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const OBB3 &OBB, unsigned int &Quantity, float &tNear, float &tFar) const
{
    float e, f, t1, t2, temp;
    float tmin = -MAX_REAL,
           tmax = MAX_REAL;
    Matrix::Math::Vector3 A[3];
    float fA[3];
    Matrix::Math::Vector3 vcP = OBB.GetCenter() - m_Orig;
    OBB.GetA(A);
    OBB.GetfA(fA);
    for (unsigned int i = 0; i < 3; i++)
    {
        e = A[i].Dot(vcP);
        f = A[i].Dot(m_Dir);
        if (Math::ABS(f) > EPSILON_E4)
        {

            t1 = (e + fA[i]) / f;
            t2 = (e - fA[i]) / f;

            if (t1 > t2)
            {
                temp = t1;
                t1 = t2;
                t2 = temp;
            }
            if (t1 > tmin)
                tmin = t1;
            if (t2 < tmax)
                tmax = t2;
            if (tmin > tmax)
                return IT_NoIntersect;
            if (tmax < 0.0f)
                return IT_NoIntersect;
        }
        else if (((-e - fA[i]) > 0.0f) || ((-e + fA[i]) < 0.0f))
            return IT_NoIntersect;
    }

    return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const Sphere3 &sphere, unsigned int &Quantity, float &tNear, float &tFar) const
{
    Matrix::Math::Vector3 Delta = m_Orig - sphere.m_Center;
    float a0 = Delta.Dot(Delta) - sphere.m_fRadius * sphere.m_fRadius;
    float a1 = Delta.Dot(m_Dir);
    float Disc = a1 * a1 - a0;
    if (Disc < 0)
    {
        Quantity = 0;
    }
    else if (Disc >= EPSILON_E4)
    {
        float root = SQRT(Disc);

        tFar = -a1 + root;
        tNear = -a1 - root;
        Quantity = 2;
    }
    else
    {
        tNear = -a1;
        tFar = -a1;
        Quantity = 1;
    }

    if (Quantity == 0)
        return IT_NoIntersect;
    else
        return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const AABB3 &AABB, unsigned int &Quantity, float &tNear, float &tFar) const
{
    float t0, t1, tmp;
    tNear = -MAX_REAL;
    tFar = MAX_REAL;
    Matrix::Math::Vector3 MaxT;
    Matrix::Math::Vector3 Min = AABB.GetMinPoint();
    Matrix::Math::Vector3 Max = AABB.GetMaxPoint();

    for (int i = 0; i < 3; i++)
    {
        if (Math::ABS(m_Dir.m[i]) < EPSILON_E4)
        {
            if ((m_Orig.m[i] < Min.m[i]) ||
                (m_Orig.m[i] > Max.m[i]))
                return IT_NoIntersect;
        }
        t0 = (Min.m[i] - m_Orig.m[i]) / m_Dir.m[i];
        t1 = (Max.m[i] - m_Orig.m[i]) / m_Dir.m[i];
        if (t0 > t1)
        {
            tmp = t0;
            t0 = t1;
            t1 = tmp;
        }
        if (t0 > tNear)
            tNear = t0;
        if (t1 < tFar)
            tFar = t1;
        if (tNear > tFar)
            return IT_NoIntersect;
        if (tFar < 0)
            return IT_NoIntersect;
    }
    return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Matrix::Primitive::Line3::RelationWith(const Polygon3 &Polygon, float &fLineParameter,
                                           bool bCull, int &iIndexTriangle, float fTriangleParameter[3]) const
{
    return Polygon.RelationWith(*this, bCull, iIndexTriangle, fTriangleParameter, fLineParameter);
}