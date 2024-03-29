#include "Ray3.h"
#include "Ray3.h"
#include "Segment3.h"

#include "Plane3.h"
#include "Triangle3.h"
#include "Rectangle3.h"
#include "Polygon3.h"

#include "OBB3.h"
#include "AABB3.h"
#include "Sphere3.h"

using namespace Matrix::Primitive;
/*----------------------------------------------------------------*/
Ray3::Ray3()
{
}
/*----------------------------------------------------------------*/
Ray3::Ray3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir)
{
	Set(Orig, Dir);
}
/*----------------------------------------------------------------*/
Ray3::~Ray3()
{
}

/*----------------------------------------------------------------*/
bool Ray3::GetParameter(const Matrix::Math::Vector3& Point, float& fRayParameter) const
{
	if (!Matrix::Primitive::Line3::GetParameter(Point, fRayParameter))
		return 0;

	if (fRayParameter < 0)
		return 0;

	return 1;
}
/*----------------------------------------------------------------*/
void Ray3::Transform(const Ray3& Ray, const Matrix::Math::Matrix4x4& Mat)
{

	Matrix::Primitive::Line3::Transform(Ray, Mat);
}


float Ray3::SquaredDistance(const Matrix::Math::Vector3& Point, float& fLineParameter) const
{
	float fSqDis = Matrix::Primitive::Line3::SquaredDistance(Point, fLineParameter);
	if (fLineParameter >= 0)
		return fSqDis;
	else
	{
		fLineParameter = 0;
		Matrix::Math::Vector3 Diff;
		Diff = Point - m_Orig;
		return Diff.GetSqrLength();
	}
}
/*----------------------------------------------------------------*/
float Ray3::SquaredDistance(const Line3& Line, float& fRayParameter, float& fLineParameter) const
{
	return Line.SquaredDistance(*this, fLineParameter, fRayParameter);
}
/*----------------------------------------------------------------*/
float Ray3::SquaredDistance(const Ray3& Ray, float& fRay1Parameter, float& fRay2Parameter) const
{
	const Line3 Line = Ray;
	float sqrDist = SquaredDistance(Line, fRay1Parameter, fRay2Parameter);
	if (fRay2Parameter < 0)
	{
		fRay2Parameter = 0;
		sqrDist = SquaredDistance(Ray.m_Orig, fRay1Parameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Ray3::SquaredDistance(const Segment3& Segment, float& fRayParameter, float& fSegmentParameter) const
{

	const Ray3 Ray = Segment;
	float sqrDist = SquaredDistance(Ray, fRayParameter, fSegmentParameter);
	float fLen = Segment.GetLen();
	if (fSegmentParameter > fLen)
	{
		fSegmentParameter = fLen;
		Matrix::Math::Vector3 End = Segment.GetEnd();
		sqrDist = SquaredDistance(End, fRayParameter);
	}
	return sqrDist;
}
/*----------------------------------------------------------------*/
float Ray3::SquaredDistance(const Triangle3& Triangle, float& fRayParameter, float fTriangleParameter[3]) const
{
	float sqrDist = Matrix::Primitive::Line3::SquaredDistance(Triangle, fRayParameter, fTriangleParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		//sqrDist = Triangle.SquaredDistance(m_Orig, )
		sqrDist = Point3(m_Orig).SquaredDistance(Triangle, fTriangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Ray3::SquaredDistance(const Rectangle3& Rectangle, float& fRayParameter, float fRectangleParameter[2]) const
{
	float sqrDist = Matrix::Primitive::Line3::SquaredDistance(Rectangle, fRayParameter, fRectangleParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		sqrDist = Point3(m_Orig).SquaredDistance(Rectangle, fRectangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Ray3::SquaredDistance(const OBB3& OBB, float& fRayParameter, float fOBBParameter[3]) const
{
	float sqrDist = Matrix::Primitive::Line3::SquaredDistance(OBB, fRayParameter, fOBBParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		sqrDist = OBB.SquaredDistance(m_Orig, fOBBParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Ray3::Distance(const Sphere3& Sphere, float& fRayParameter, Matrix::Math::Vector3& SpherePoint) const
{
	return Sphere.Distance(*this, SpherePoint, fRayParameter);
}
/*----------------------------------------------------------------*/
float Ray3::Distance(const Plane3& Plane, Matrix::Math::Vector3& RayPoint, Matrix::Math::Vector3& PlanePoint) const
{
	return Plane.Distance(*this, PlanePoint, RayPoint);
}
/*----------------------------------------------------------------*/
float Ray3::SquaredDistance(const AABB3& AABB, float& fRayParameter, float fAABBParameter[3]) const
{
	float sqrDist = Matrix::Primitive::Line3::SquaredDistance(AABB, fRayParameter, fAABBParameter);
	if (fRayParameter < 0)
	{
		fRayParameter = 0;
		sqrDist = AABB.SquaredDistance(m_Orig, fAABBParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Ray3::SquaredDistance(const Polygon3& Polygon, float& fRayParameter,
	int& IndexTriangle,
	float fTriangleParameter[3]) const
{

	return Polygon.SquaredDistance(*this, IndexTriangle, fTriangleParameter, fRayParameter);
}


int Ray3::RelationWith(const Triangle3& Triangle, bool bCull, float& fRayParameter,
	float fTriangleParameter[3]) const
{
	if (Matrix::Primitive::Line3::RelationWith(Triangle, bCull, fRayParameter, fTriangleParameter) == IT_NoIntersect)
		return IT_NoIntersect;
	if (fRayParameter < 0.0f)
		return IT_NoIntersect;
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Plane3& Plane, bool bCull, float& fRayParameter) const
{
	int iFlag = Matrix::Primitive::Line3::RelationWith(Plane, bCull, fRayParameter);
	if (iFlag != IT_Intersect)
		return iFlag;
	if (fRayParameter < 0.0f)
	{
		iFlag = Point3(m_Orig).RelationWith(Plane);
		return iFlag;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Rectangle3& Rectangle, bool bCull, float& fRayParameter,
	float fRectangleParameter[2]) const
{
	if (Matrix::Primitive::Line3::RelationWith(Rectangle, bCull, fRayParameter, fRectangleParameter) == IT_NoIntersect)
		return IT_NoIntersect;
	if (fRayParameter < 0.0f)
		return IT_NoIntersect;

	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const OBB3& OBB, unsigned int& Quantity, float& tNear, float& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(OBB, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return IT_NoIntersect;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Sphere3& sphere, unsigned int& Quantity, float& tNear, float& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(sphere, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return IT_NoIntersect;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const AABB3& AABB, unsigned int& Quantity, float& tNear, float& tFar) const
{
	if (Matrix::Primitive::Line3::RelationWith(AABB, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tFar < 0.0f)
	{
		Quantity = 0;
		return IT_NoIntersect;
	}
	if (tNear < 0.0f)
	{
		Quantity = 1;
		tNear = tFar;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Ray3::RelationWith(const Polygon3& Polygon, float& fRayParameter,
	bool bCull, int& iIndexTriangle, float fTriangleParameter[3]) const
{

	return Polygon.RelationWith(*this, bCull, iIndexTriangle, fTriangleParameter, fRayParameter);
}