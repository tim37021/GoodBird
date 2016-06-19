#include <GoodBird/GoodBirdGame.h>
#include <GoodBird/Bird.h>
#include <cstdlib>

namespace GoodBird
{
	// private class here
	class MyContactListener : public b2ContactListener
	{
	public:
		virtual void BeginContact(b2Contact* contact)
		{
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			if ( bodyUserDataA && bodyUserDataB ) {
				static_cast<Core::PhysicsEntity *>( bodyUserDataA )->startContact(*static_cast<Core::PhysicsEntity *>(bodyUserDataB));
				static_cast<Core::PhysicsEntity *>( bodyUserDataB )->startContact(*static_cast<Core::PhysicsEntity *>(bodyUserDataA));
			}
		}
  
    	virtual void EndContact(b2Contact* contact)
    	{
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			if ( bodyUserDataA && bodyUserDataB ) {
				static_cast<Core::PhysicsEntity *>( bodyUserDataA )->endContact(*static_cast<Core::PhysicsEntity *>(bodyUserDataB));
				static_cast<Core::PhysicsEntity *>( bodyUserDataB )->endContact(*static_cast<Core::PhysicsEntity *>(bodyUserDataA));
			}
    	}
	};
	static MyContactListener listener;

	GoodBirdGame::GoodBirdGame():
		mWorld(b2Vec2(0.0f, -9.8f)), mLastUpdateTime(0.0f), mObserverX(0.0f), mObserverY(0.0f)
	{
		mWorld.SetContactListener(&listener);

		Bird *newBird = new Bird(mWorld);
		newBird->setPosition((int32_t)rand()%10-5, (int32_t)rand()%10-5);
		mEntities.push_back(newBird);
	}	

	GoodBirdGame::~GoodBirdGame()
	{
		for(auto entity: mEntities) 
			delete entity;
	}

	void GoodBirdGame::update(double globalTime)
	{
		mWorld.Step(globalTime - mLastUpdateTime, 6, 2);

		for(auto entity: mEntities) 
			entity->update(globalTime);

		Bird *newBird = new Bird(mWorld);
		newBird->setPosition((int32_t)rand()%10-5, (int32_t)rand()%10-5);
		mEntities.push_back(newBird);

		mLastUpdateTime = globalTime;
	}

	void GoodBirdGame::draw(Rendering::RenderInterface &renderer)
	{
		Math::Matrix3x3 view({1, 0, -mObserverX, 0, 1, -mObserverY, 0, 0, 1});

		for(auto entity: mEntities) 
			entity->draw(renderer, view);
	}

	void GoodBirdGame::moveObserver(float dx, float dy) 
	{
		mObserverX += dx;
		mObserverY += dy;
	}
}