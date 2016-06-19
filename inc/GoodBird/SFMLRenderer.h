#ifndef _GOODBIRD_SFMLRENDERER_H_
#define _GOODBIRD_SFMLRENDERER_H_

#include <GoodBird/Rendering.h>
#include <SFML/Graphics.hpp>

namespace GoodBird
{
	namespace Rendering
	{
		class SFMLRenderer: public RenderInterface
		{
		public:
			SFMLRenderer(sf::RenderTarget &target);
			// Ask to draw triangles
			virtual void drawGeometry(Primitive primitive, const std::vector<Math::Vertex> &vertices, 
				const std::vector<uint32_t> &indices, TextureHandle texture, 
				const Math::Matrix3x3 &mat);
			virtual bool loadTexture(const char filename[], TextureHandle &handle);
			virtual void releaseTexture(TextureHandle handle);
		private:
			std::map<std::string, sf::Texture> mTexturePool;
			sf::RenderTarget &mTarget;
			sf::View mView;
		};
	}
}

#endif