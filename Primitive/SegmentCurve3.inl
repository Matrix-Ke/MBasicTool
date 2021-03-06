inline void SegmentCurve3::GetFrenetFrameBNT(float t, Matrix::Math::Vector3& B, Matrix::Math::Vector3& N, Matrix::Math::Vector3& T)
{
	Curve3::GetFixedUpBNT(t, B, N, T);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3	SegmentCurve3::GetFirstDerivative(float t)
{

	return m_Segment.GetDir() * m_Segment.GetLen();
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3	SegmentCurve3::GetSecondDerivative(float t)
{
	return Matrix::Math::Vector3(0, 0, 0);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3	SegmentCurve3::GetThirdDerivative(float t)
{

	return Matrix::Math::Vector3(0, 0, 0);
}
/*----------------------------------------------------------------*/
inline float		SegmentCurve3::GetLength(float t1, float t2, unsigned int uiIterations)
{

	return m_Segment.GetLen() * (t2 - t1);
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3	SegmentCurve3::GetPoint(float t)
{
	return m_Segment.GetParameterPoint(t * m_Segment.GetLen());
}
/*----------------------------------------------------------------*/
inline float		SegmentCurve3::GetTotalLength(unsigned int uiIterations)
{
	return m_Segment.GetLen();

}
/*----------------------------------------------------------------*/
inline float SegmentCurve3::GetTime(float fLength, unsigned int uiIterations,
	float fTolerance)
{
	return fLength / m_Segment.GetLen();

}
/*----------------------------------------------------------------*/
inline float SegmentCurve3::GetCurvature(float fTime)
{
	return 0;
}
/*----------------------------------------------------------------*/
inline float SegmentCurve3::GetTorsion(float fTime)
{
	return 0;
}
/*----------------------------------------------------------------*/