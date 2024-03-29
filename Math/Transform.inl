inline const Matrix4x4& Transform::GetCombine()
{

	Combine();

	return m_mCombine;
}
inline const Matrix4x4& Transform::GetCombineInverse()
{

	Combine();

	if (!m_bIsHaveInverse)
	{
		m_bIsHaveInverse = 1;
		m_mCombineInverse.InverseOf(m_mCombine);
	}
	return m_mCombineInverse;

}
inline const Vector3& Transform::GetScale()const
{
	return m_fScale;

}
inline const Vector3& Transform::GetTranslate()const
{
	return m_vTranslate;

}
inline const Matrix3& Transform::GetRotate()const
{
	return m_mRotate;

}
inline void Transform::SetScale(const Vector3& fScale)
{

	m_fScale = fScale;

	m_bIsCombine = 0;
	m_bIsHaveInverse = 0;
}
inline void Transform::SetTranslate(const Vector3& Translate)
{
	m_vTranslate = Translate;
	m_bIsCombine = 0;
	m_bIsHaveInverse = 0;
}
inline void Transform::SetRotate(const Matrix3& Rotate)
{
	m_mRotate = Rotate;

	m_bIsCombine = 0;
	m_bIsHaveInverse = 0;

}
void Transform::GetDir(Vector3& Dir, Vector3& Up, Vector3& Right)const
{
	Right.x = m_mRotate._00;
	Right.y = m_mRotate._01;
	Right.z = m_mRotate._02;

	Up.x = m_mRotate._10;
	Up.y = m_mRotate._11;
	Up.z = m_mRotate._12;

	Dir.x = m_mRotate._20;
	Dir.y = m_mRotate._21;
	Dir.z = m_mRotate._22;
}