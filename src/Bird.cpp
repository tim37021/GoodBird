#include <GoodBird/Bird.h>

namespace GoodBird
{

	static std::vector<Math::Vector3> quad = {Math::Vector3(-1, -1), 
		Math::Vector3(1, -1), Math::Vector3(1, 1), Math::Vector3(-1, 1)};

	Bird::Bird(b2World &world)
		: Core::PhysicsEntity(world, 10.0f), mTexture(0), mColor(1.0f)
	{

	}

	void Bird::draw(Rendering::RenderInterface &renderer, Math::Matrix3x3 trans)
	{
		if(mTexture == 0) {
			renderer.loadTexture("angry-bird.png", mTexture);
		}
		std::vector<Math::Vertex> vertices = {
			{quad[0]*10.0f, mColor, {0.0f, 1.0f}},
			{quad[1]*10.0f, mColor, {1.0f, 1.0f}},
			{quad[2]*10.0f, mColor, {1.0f, 0.0f}},
			{quad[3]*10.0f, mColor, {0.0f, 0.0f}}
		};
		// Because quad[] * 10 make w to 10 too. bring it back to 1...
		// You can fix this problem by adding Vector2 class
		vertices[0].pos.data[2]=1;
		vertices[1].pos.data[2]=1;
		vertices[2].pos.data[2]=1;
		vertices[3].pos.data[2]=1;

		const Math::Matrix3x3 &mat = getMatrix();
		renderer.drawGeometry(Rendering::TRIANGLES, vertices, {0, 1, 2, 0, 2, 3}, mTexture, trans*mat);
	}

	void Bird::startContact(Core::PhysicsEntity &other)
	{
		mColor = Math::Vector3(0.0, 1.0, 0.0);
	}

	void Bird::endContact(Core::PhysicsEntity &other)
	{
		mColor = Math::Vector3(1.0, 1.0, 1.0);
	}
}