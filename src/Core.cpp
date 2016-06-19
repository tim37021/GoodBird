#include <GoodBird/Core.h>

namespace GoodBird
{
	namespace Core
	{
		PhysicsEntity::PhysicsEntity(b2World &world, std::vector<Math::Vector3> &vertices, bool isDynamic)
		{
			b2BodyDef bodyDef;
			if(isDynamic)
				bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(0.0f, 0.0f);
			mBody = world.CreateBody(&bodyDef);

			// Convert to Box2D data structure
			std::vector<b2Vec2> b2vertices;
			b2vertices.resize(vertices.size());
			for(uint32_t i=0; i<vertices.size(); i++)
				b2vertices[i].Set(vertices[i].getX(), vertices[i].getY());

			mShape = new b2PolygonShape();
			static_cast<b2PolygonShape *>(mShape)->Set(b2vertices.data(), b2vertices.size());

			mFixture.shape = mShape;
			mFixture.density = 1.0f;
			mFixture.friction = 0.3f;

			mBody->CreateFixture(&mFixture);
			mBody->SetUserData(this);
		}

		PhysicsEntity::PhysicsEntity(b2World &world, float radius, bool isDynamic)
		{
			b2BodyDef bodyDef;
			if(isDynamic)
				bodyDef.type = b2_dynamicBody;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(0.0f, 0.0f);
			mBody = world.CreateBody(&bodyDef);

			mShape = new b2CircleShape();
			static_cast<b2CircleShape *>(mShape)->m_radius = radius;

			mFixture.shape = mShape;
			mFixture.density = 1.0f;
			mFixture.friction = 0.3f;

			mBody->CreateFixture(&mFixture);
			mBody->SetUserData(this);
		}

		PhysicsEntity::~PhysicsEntity()
		{
			delete mShape;
		}

		void PhysicsEntity::update(double globalTime)
		{
			if(mDirty) {
				mBody->SetTransform({mX, mY}, mAngle);
				mDirty = false;
			}else {
				b2Vec2 pos = mBody->GetPosition();
				mX = pos.x;
				mY = pos.y;

				mAngle = mBody->GetAngle();
			}
		}

		void PhysicsEntity::setDensity(float density)
		{
			mFixture.density = density; 
		}

		void PhysicsEntity::setFriction(float friction)
		{
			mFixture.friction = friction;
		}

	}
}