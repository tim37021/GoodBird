#ifndef _GOODBIRD_CORE_H_
#define _GOODBIRD_CORE_H_

#include <Box2D/Box2D.h>
#include <GoodBird/Rendering.h>

namespace GoodBird
{
	namespace Core
	{

		class Entity: public Rendering::Drawable, public Math::Transformable
		{
		public:
			virtual ~Entity()=default;
			virtual void update(double globalTime)=0;
		};

		// This class act as a bridge between our Entity and Box2D 
		class PhysicsEntity: public Entity
		{
		public:
			PhysicsEntity(b2World &, std::vector<Math::Vector3> &vertices, bool isDynamic=true);
			PhysicsEntity(b2World &, float radius, bool isDynamic=true);
			virtual ~PhysicsEntity();
			// This update give us a chance to bring box2d things to our entity
			// directly opening b2Body for user is usually not a good choice 
			virtual void update(double globalTime);

			void setDensity(float density);
			void setFriction(float friction);

			// http://www.iforce2d.net/b2dtut/collision-filtering for more information
			void setCollisionGroup(uint16_t category, uint16_t bitmask);

			// Collision callback
			virtual void startContact(PhysicsEntity &other){}
			virtual void endContact(PhysicsEntity &other){}
		private:
			b2Body *mBody;
			b2Shape *mShape;
			b2FixtureDef mFixture;
		};
	}
}

#endif