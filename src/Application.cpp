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

		mObserverSpeedX = 0;
		mObserverSpeedY = 0;

	}

	void Application::run()
	{
	    while(mWindow.isOpen()) {
	        handleEvents();
	        mWindow.clear();

	        mGame.update(mGameClock.getElapsedTime().asSeconds());

	        mGame.moveObserver(mObserverSpeedX*mGameClock.getElapsedTime().asSeconds(), mObserverSpeedY*mGameClock.getElapsedTime().asSeconds());
	        mGameClock.restart();

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
	            case sf::Event::KeyPressed:
	            	if(event.key.code == sf::Keyboard::Left)
	            		mObserverSpeedX = -100;
	            	if(event.key.code == sf::Keyboard::Right)
	            		mObserverSpeedX = 100;
	            	break;
	            case sf::Event::KeyReleased:
	            	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && event.key.code == sf::Keyboard::Left)
	            		mObserverSpeedX = 0;
	            	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && event.key.code == sf::Keyboard::Right)
	            		mObserverSpeedX = 0;	            
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