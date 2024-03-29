
/*----------------------------------------------------------------*/
inline void Vector3::Set(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}
/*----------------------------------------------------------------*/
inline float Vector3::GetLength(void)const
{
	return SQRT(x * x + y * y + z * z);
}
/*----------------------------------------------------------------*/

inline float Vector3::GetSqrLength(void) const
{
	return (x * x + y * y + z * z);
}

/*----------------------------------------------------------------*/

inline void Vector3::Negate(void)
{
	x = -x;  y = -y;  z = -z;
}
/*----------------------------------------------------------------*/
inline void Vector3::Normalize(void)
{

	float f = x * x + y * y + z * z;
	if (f > EPSILON_E4)
	{
#ifdef MX_SSE
		f = InvSqrt(f);
#else
		f = (float)1.0f / SQRT(f);
#endif
		x *= f; y *= f; z *= f;
	}
	else
	{
		*this = Vector3::ms_Zero;
	}
}
/*----------------------------------------------------------------*/
inline void Vector3::Cross(const Vector3& v1, const Vector3& v2)
{

	x = v1.y * v2.z - v1.z * v2.y;
	y = v1.z * v2.x - v1.x * v2.z;
	z = v1.x * v2.y - v1.y * v2.x;
}
/*----------------------------------------------------------------*/
