#include <GoodBird/Application.h>
#include <GoodBird/GoodBirdGame.h>
#include <GoodBird/SFMLRenderer.h>
#include <GL/glew.h>

namespace GoodBird
{
	Application::Application():
		mRenderer(mWindow)
	{
		mWindow.create(sf::VideoMode(800, 600), L"GoodBird");
		mWindow.setActive();
    	glewExperimental = GL_TRUE;
    	glewInit();
		mWindow.setFramerateLimit(60);
	}

	void Application::run()
	{
	    while(mWindow.isOpen()) {
	        handleEvents();
	        mWindow.clear();

	        mGame.update(mGameClock.getElapsedTime().asSeconds());

	        mWindow.pushGLStates();
	       	mGame.draw(mRenderer);
	       	mWindow.popGLStates();

	        mWindow.display();

	        calculateFPS();
	    }
	}

	void Application::handleEvents()
	{
	    sf::Event event;
	    while(mWindow.pollEvent(event)) {
	        switch(event.type) {
	            case sf::Event::Closed:
	                mWindow.close();
	                break;
	            default:;
	        }
	    }
	}

	void Application::calculateFPS()
	{
	    mFPSTmp++;
	    if(mFPSClock.getElapsedTime().asSeconds() >= 1.0f) {
	        mFPSClock.restart();
	        mFPS = mFPSTmp;
	        mFPSTmp = 0;
	    }
	}
}