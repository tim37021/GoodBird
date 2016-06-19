#include <GoodBird/Math.h>
#include <cmath>

namespace GoodBird
{
	namespace Math
	{

		Vector3::Vector3(float v)
			: data{v, v, v}
		{
		}

		Vector3::Vector3(float x, float y, float z)
			: data{x, y, z}
		{

		}

		Vector3 Vector3::operator+(const Vector3 &rhs) const
		{
			return Vector3(data[0]+rhs.data[0], data[1]+rhs.data[1], data[2]+rhs.data[2]);
		}

		Vector3 Vector3::operator-(const Vector3 &rhs) const
		{
			return Vector3(data[0]-rhs.data[0], data[1]-rhs.data[1], data[2]-rhs.data[2]);
		}	

		Vector3 Vector3::operator*(const Vector3 &rhs) const
		{
			return Vector3(data[0]*rhs.data[0], data[1]*rhs.data[1], data[2]*rhs.data[2]);
		}

		Vector3 Vector3::operator*(float scale) const
		{
			return Vector3(data[0]*scale, data[1]*scale, data[2]*scale);
		}

		Matrix3x3::Matrix3x3()
			: data{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}
		{

		}

		Matrix3x3::Matrix3x3(const std::vector<float> &d)
			: data{{d[0], d[1], d[2]}, {d[3], d[4], d[5]}, {d[6], d[7], d[8]}}
		{

		}

		Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &rhs) const
		{
			// I use for-loop here, you can unroll the loop, it will be a lot faster
			Matrix3x3 result;
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					result.data[i][j]=0.f;
					for(int k=0; k<3; k++) 
						result.data[i][j]+=data[i][k]*rhs.data[k][j];
				}
			}
			return result;
		}

		Vector3 Matrix3x3::operator*(const Vector3 &rhs) const
		{
			return Vector3(data[0][0]*rhs.data[0]+data[0][1]*rhs.data[1]+data[0][2]*rhs.data[2], 
					data[1][0]*rhs.data[0]+data[1][1]*rhs.data[1]+data[1][2]*rhs.data[2], 
					data[2][0]*rhs.data[0]+data[2][1]*rhs.data[1]+data[2][2]*rhs.data[2]);
		}

		Transformable::Transformable()
			: mX(0.0f), mY(0.0f), mAngle(0.0f), mDirty(false)
		{

		}

		void Transformable::setPosition(float x, float y)
		{
			mX = x;
			mY = y;
			mDirty = true;
		}

		Matrix3x3 Transformable::getMatrix() const
		{
			Matrix3x3 rot(
			{
				cosf(mAngle), -sinf(mAngle), 0, 
				sinf(mAngle), cosf(mAngle), 0, 
				0		   , 0          , 1
			});
			Matrix3x3 translate(
			{
				1, 0, mX,
				0, 1, mY,
				0, 0, 1
			});
			return translate*rot;
		}

		Vertex::Vertex(const Vector3 & p, const Vector3 & c, const Vector3 &t):
			pos(p), color(c), texCoord(t)
		{

		}
	}
}