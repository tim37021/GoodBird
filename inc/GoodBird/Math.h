#ifndef _GOODBIRD_MATH_H_
#define	_GOODBIRD_MATH_H_

#include <vector>

namespace GoodBird
{
	namespace Math
	{
		struct Vector3
		{
		public:
			float data[3];
			Vector3(): Vector3(0.0f) {}
			Vector3(float);
			Vector3(float x, float y, float z=1.0f);

			float getX() const
			{ return data[0]; }
			float getY() const
			{ return data[1]; }
			float getZ() const
			{ return data[2]; }

			// I only implement necessary operator
			Vector3 operator+(const Vector3 &rhs) const;
			Vector3 operator-(const Vector3 &rhs) const;
			Vector3 operator*(const Vector3 &rhs) const;
			Vector3 operator*(float scale) const;
		};

		struct Matrix3x3
		{
		public:
			float data[3][3];
			// Create Identity Matrix
			Matrix3x3();
			Matrix3x3(const std::vector<float> &data);
			Matrix3x3(const Matrix3x3 &)=default;
			// Might be useful if you need change of basis matrix
			//Matrix3x3(const Vector3 &u, const Vector3 &v, const Vector3 &w);

			// I only implement necessary operator
			Matrix3x3 operator*(const Matrix3x3 &rhs) const;
			Vector3 operator*(const Vector3 &rhs) const;
		};

		struct Vertex
		{
			Vector3 pos;
			Vector3 color;
			Vector3 texCoord;
			Vertex()=default;
			Vertex(const Vector3 &, const Vector3 &, const Vector3 &);
		};

		class Transformable
		{
		public:
			Transformable();
			Matrix3x3 getMatrix() const;

			void setPosition(float x, float y);
			// You might need getPosition()....
		protected:
			float mX, mY;
			float mAngle;
			// a flag for child class
			bool mDirty;
		};
	}
}

#endif