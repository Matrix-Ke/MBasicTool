#include "Segment3.h"

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
Segment3::Segment3()
{
}
/*----------------------------------------------------------------*/
Segment3::~Segment3()
{
}
/*----------------------------------------------------------------*/
Segment3::Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& End)
{
	Set(Orig, End);
}
/*----------------------------------------------------------------*/
Segment3::Segment3(const Matrix::Math::Vector3& Orig, const Matrix::Math::Vector3& Dir, float fLen)
{
	Set(Orig, Dir, fLen);
}
/*----------------------------------------------------------------*/
void Segment3::Transform(const Segment3& Segment, const Matrix::Math::Matrix4x4& Mat)
{

	m_Orig = Mat * Segment.m_Orig;
	m_End = Mat * Segment.m_End;
	m_Dir = Mat.Apply3X3(Segment.m_Dir);
	m_Dir.Normalize();
	m_fLen = Segment.m_fLen;
}
/*----------------------------------------------------------------*/
bool Segment3::GetParameter(const Matrix::Math::Vector3& Point, float& fSegmentParameter) const
{
	if (!Ray3::GetParameter(Point, fSegmentParameter))
		return 0;
	if (fSegmentParameter > m_fLen)
		return 0;
	return 1;
}


float Segment3::SquaredDistance(const Matrix::Math::Vector3& Point, float& fSegmentParameter) const
{
	float SqDis = Ray3::SquaredDistance(Point, fSegmentParameter);
	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		Matrix::Math::Vector3 Diff;
		Diff = Point - m_End;
		return Diff.GetSqrLength();
	}
	else
	{
		return SqDis;
	}
}
/*----------------------------------------------------------------*/
float Segment3::SquaredDistance(const Line3& Line, float& fSegmentParameter, float& fLineParameter) const
{
	return Line.SquaredDistance(*this, fLineParameter, fSegmentParameter);
}
/*----------------------------------------------------------------*/
float Segment3::SquaredDistance(const Ray3& Ray, float& fSegmentParameter, float& fRayParameter) const
{
	return Ray.SquaredDistance(*this, fRayParameter, fSegmentParameter);
}
/*----------------------------------------------------------------*/
float Segment3::SquaredDistance(const Segment3& Segment, float& fSegment1Parameter, float& fSegment2Parameter) const
{
	const Ray3& Ray = Segment;
	float sqrDist = SquaredDistance(Ray, fSegment1Parameter, fSegment2Parameter);
	float fLen = Segment.GetLen();
	if (fSegment2Parameter > fLen)
	{
		fSegment2Parameter = fLen;
		Matrix::Math::Vector3 End = Segment.GetEnd();
		sqrDist = SquaredDistance(End, fSegment1Parameter);
	}
	return sqrDist;
}
/*----------------------------------------------------------------*/
float Segment3::SquaredDistance(const Triangle3& Triangle, float& fSegmentParameter, float fTriangleParameter[3]) const
{
	float sqrDist = Ray3::SquaredDistance(Triangle, fSegmentParameter, fTriangleParameter);

	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = Point3(m_End).SquaredDistance(Triangle, fTriangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Segment3::SquaredDistance(const Rectangle3& Rectangle, float& fSegmentParameter, float fRectangleParameter[2]) const
{
	float sqrDist = Ray3::SquaredDistance(Rectangle, fSegmentParameter, fRectangleParameter);

	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = Point3(m_End).SquaredDistance(Rectangle, fRectangleParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Segment3::SquaredDistance(const OBB3& OBB, float& fSegmentParameter, float fOBBParameter[3]) const
{
	float sqrDist = Ray3::SquaredDistance(OBB, fSegmentParameter, fOBBParameter);
	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = OBB.SquaredDistance(m_End, fOBBParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Segment3::Distance(const Sphere3& Sphere, float& fSegmentParameter, Matrix::Math::Vector3& SpherePoint) const
{

	return Sphere.Distance(*this, SpherePoint, fSegmentParameter);
}
/*----------------------------------------------------------------*/
float Segment3::Distance(const Plane3& Plane, Matrix::Math::Vector3& SegmentPoint, Matrix::Math::Vector3& PlanePoint) const
{
	return Plane.Distance(*this, PlanePoint, SegmentPoint);
}
/*----------------------------------------------------------------*/
float Segment3::SquaredDistance(const AABB3& AABB, float& fSegmentParameter, float fAABBParameter[3]) const
{
	float sqrDist = Ray3::SquaredDistance(AABB, fSegmentParameter, fAABBParameter);
	if (fSegmentParameter > m_fLen)
	{
		fSegmentParameter = m_fLen;
		sqrDist = AABB.SquaredDistance(m_End, fAABBParameter);
	}

	return sqrDist;
}
/*----------------------------------------------------------------*/
float Segment3::SquaredDistance(const Polygon3& Polygon, float& fSegmentParameter,
	int& IndexTriangle,
	float fTriangleParameter[3]) const
{

	return Polygon.SquaredDistance(*this, IndexTriangle, fTriangleParameter, fSegmentParameter);
}

/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Triangle3& Triangle, bool bCull, float& fSegmentParameter,
	float fTriangleParameter[3]) const
{
	if (Ray3::RelationWith(Triangle, bCull, fSegmentParameter, fTriangleParameter) == IT_NoIntersect)
		return IT_NoIntersect;
	if (fSegmentParameter > m_fLen)
		return IT_NoIntersect;
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Plane3& Plane, bool bCull, float& fSegmentParameter) const
{
	int iFlag = Ray3::RelationWith(Plane, bCull, fSegmentParameter);
	if (iFlag != IT_Intersect)
		return iFlag;
	if (fSegmentParameter > m_fLen)
	{
		return Point3(m_Orig).RelationWith(Plane);
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Rectangle3& Rectangle, bool bCull, float& fSegmentParameter,
	float fRectangleParameter[2]) const
{

	if (Ray3::RelationWith(Rectangle, bCull, fSegmentParameter, fRectangleParameter) == IT_NoIntersect)
		return IT_NoIntersect;
	if (fSegmentParameter > m_fLen)
		return IT_NoIntersect;
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const OBB3& OBB, unsigned int& Quantity, float& tNear, float& tFar) const
{
	if (Ray3::RelationWith(OBB, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (Point3(m_Orig).RelationWith(OBB) != IT_Out)
			return IT_In;
		return IT_NoIntersect;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Sphere3& sphere, unsigned int& Quantity, float& tNear, float& tFar) const
{
	if (Ray3::RelationWith(sphere, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (Point3(m_Orig).RelationWith(sphere) != IT_Out)
			return IT_In;
		return IT_NoIntersect;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const AABB3& AABB, unsigned int& Quantity, float& tNear, float& tFar) const
{

	if (Ray3::RelationWith(AABB, Quantity, tNear, tFar) == IT_NoIntersect)
		return IT_NoIntersect;
	if (tNear > m_fLen)
	{
		Quantity = 0;
		if (Point3(m_Orig).RelationWith(AABB) != IT_Out)
			return IT_In;
		return IT_NoIntersect;
	}

	if (tFar > m_fLen)
	{
		Quantity = 1;
		tFar = tNear;
	}
	return IT_Intersect;
}
/*----------------------------------------------------------------*/
int Segment3::RelationWith(const Polygon3& Polygon, float& fSegmentParameter,
	bool bCull, int& iIndexTriangle, float fTriangleParameter[3]) const
{

	return Polygon.RelationWith(*this, bCull, iIndexTriangle, fTriangleParameter, fSegmentParameter);
}