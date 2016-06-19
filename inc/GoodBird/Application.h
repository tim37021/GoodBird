#ifndef _GOODBIRD_APPLICATION_H_
#define _GOODBIRD_APPLICATION_H_

#include <SFML/Graphics.hpp>
#include <GoodBird/GoodBirdGame.h>
#include <GoodBird/SFMLRenderer.h>

namespace GoodBird
{
	class Application
	{
	public:
		Application();
		void run();
	private:
		sf::RenderWindow mWindow;
		GoodBirdGame mGame;
		Rendering::SFMLRenderer mRenderer;
		sf::Clock mFPSClock, mGameClock;
		uint32_t mFPSTmp, mFPS;

		void handleEvents();
		void calculateFPS();
	};
}

#endif