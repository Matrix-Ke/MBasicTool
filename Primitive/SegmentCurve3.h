#pragma once
#include "Curve3.h"
#include "Segment3.h"
/*
曲线段

*/
namespace Matrix
{
	namespace Primitive
	{

		class MATRIX_PRIMITIVE_API SegmentCurve3 : public Curve3
		{
		public:
			SegmentCurve3();
			~SegmentCurve3();
			void Set(const Segment3& Segment);
			Segment3& GetSegment();
			virtual unsigned int GetCurveType() { return CT_SEGMENT; }
			virtual void GetFrenetFrameBNT(float t, Matrix::Math::Vector3& B, Matrix::Math::Vector3& N, Matrix::Math::Vector3& T);
			inline virtual Matrix::Math::Vector3 GetFirstDerivative(float t);
			inline virtual Matrix::Math::Vector3 GetSecondDerivative(float t);
			inline virtual Matrix::Math::Vector3 GetThirdDerivative(float t);
			inline virtual float GetLength(float t1, float t2, unsigned int uiIterations);
			inline virtual Matrix::Math::Vector3 GetPoint(float t);
			inline virtual float GetTotalLength(unsigned int uiIterations);
			inline virtual float GetTime(float fLength, unsigned int uiIterations = 32,
				float fTolerance = EPSILON_E4);
			inline virtual float GetCurvature(float fTime);
			inline virtual float GetTorsion(float fTime);

		private:
			Segment3 m_Segment;
		};

#include "SegmentCurve3.inl"
	}
}