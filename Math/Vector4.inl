
/*----------------------------------------------------------------*/
inline void Vector4::Set(float _x, float _y, float _z, float _w)
{
	x = _x; y = _y; z = _z; w = _w;
}
Vector3 Vector4::GetV3()const
{
	return Vector3(x, y, z);
}
/*----------------------------------------------------------------*/
inline void Vector4::GetV3(Vector3& V)const
{

	V.x = x;
	V.y = y;
	V.z = z;
}
/*----------------------------------------------------------------*/
inline void Vector4::Set(const Vector3& V)
{
	x = V.x;
	y = V.y;
	z = V.z;
	w = 1.0f;
}
