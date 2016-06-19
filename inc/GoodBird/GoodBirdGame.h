#ifndef _GOODBIRD_GOODBIRDGAME_H_
#define _GOODBIRD_GOODBIRDGAME_H_

#include <Box2D/Box2D.h>
#include <GoodBird/Core.h>

namespace GoodBird
{
	class GoodBirdGame
	{
	public:
		GoodBirdGame();
		~GoodBirdGame();

		void update(double globalTime);
		void draw(Rendering::RenderInterface &renderer);

		void moveObserver(float dx, float dy);
	private:
		b2World mWorld;
		std::vector<Core::Entity *> mEntities;
		double mLastUpdateTime;
		float mObserverX, mObserverY;
	};
}

#endif