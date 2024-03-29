/*----------------------------------------------------------------*/
inline void Vector2::Set(float _x, float _y)
{
	x = _x; y = _y;
}
/*----------------------------------------------------------------*/
inline void Vector2::Normalize(void)
{
	float f = x * x + y * y;
	if (f > EPSILON_E4)
	{

#ifdef MX_SSE
		f = InvSqrt(f);
#else
		f = (float)1.0f / SQRT(f);
#endif
		x *= f; y *= f;
	}
	else
	{
		Set(0.0f, 0.0f);
	}
}