#ifndef _GOODBIRD_BIRD_H_
#define _GOODBIRD_BIRD_H_

#include <GoodBird/Core.h>
#include <GoodBird/Rendering.h>

namespace GoodBird
{
	class Bird: public Core::PhysicsEntity
	{
	public:
		Bird(b2World &);
		virtual void draw(Rendering::RenderInterface &renderer, Math::Matrix3x3 trans);

		virtual void startContact(Core::PhysicsEntity &other);
		virtual void endContact(Core::PhysicsEntity &other);
	private:
		Rendering::TextureHandle mTexture;
		Math::Vector3 mColor;
	};
}

#endif