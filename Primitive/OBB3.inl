/*----------------------------------------------------------------*/
inline void OBB3::Set(const Matrix::Math::Vector3 A[3], float fA[3], const Matrix::Math::Vector3& Center)
{
	m_A[0] = A[0];
	m_A[1] = A[1];
	m_A[2] = A[2];
	m_A[0].Normalize();
	m_A[1].Normalize();
	m_A[2].Normalize();
	m_fA[0] = Math::ABS(fA[0]);
	m_fA[1] = Math::ABS(fA[1]);
	m_fA[2] = Math::ABS(fA[2]);
	m_Center = Center;

}
/*----------------------------------------------------------------*/
inline void OBB3::Set(const Matrix::Math::Vector3& A0, const Matrix::Math::Vector3& A1, const Matrix::Math::Vector3& A2,
	float fA0, float fA1, float fA2,
	const Matrix::Math::Vector3& Center)
{

	m_A[0] = A0;
	m_A[1] = A1;
	m_A[2] = A2;

	m_A[0].Normalize();
	m_A[1].Normalize();
	m_A[2].Normalize();

	m_fA[0] = Math::ABS(fA0);
	m_fA[1] = Math::ABS(fA1);
	m_fA[2] = Math::ABS(fA2);
	m_Center = Center;
}
/*----------------------------------------------------------------*/
inline void OBB3::GetA(Matrix::Math::Vector3 A[3])const
{
	for (int i = 0; i < 3; i++)
	{
		A[i] = m_A[i];
	}
}
/*----------------------------------------------------------------*/
inline void OBB3::GetfA(float fA[3])const
{
	for (int i = 0; i < 3; i++)
	{
		fA[i] = m_fA[i];
	}
}
/*----------------------------------------------------------------*/
inline const Matrix::Math::Vector3& OBB3::GetCenter()const
{

	return m_Center;
}
/*----------------------------------------------------------------*/
inline Matrix::Math::Vector3 OBB3::GetParameterPoint(float fOBBParameter[3])const
{
	return (m_Center + m_A[0] * fOBBParameter[0] + m_A[1] * fOBBParameter[1] + m_A[2] * fOBBParameter[2]);

}
inline Matrix::Math::Vector3 OBB3::GetParameterPoint(float fOBBParameter0, float fOBBParameter1, float fOBBParameter2)const
{

	return (m_Center + m_A[0] * fOBBParameter0 + m_A[1] * fOBBParameter1 + m_A[2] * fOBBParameter2);

}