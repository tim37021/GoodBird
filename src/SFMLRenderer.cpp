#include <GoodBird/SFMLRenderer.h>

static sf::PrimitiveType PrimitiveSFMLMap[] = 
	{sf::Points, sf::Lines, sf::LinesStrip, sf::Triangles, sf::TrianglesStrip,
		sf::TrianglesFan, sf::Quads};

namespace GoodBird
{
	namespace Rendering
	{
		SFMLRenderer::SFMLRenderer(sf::RenderTarget &target)
			: mTarget(target), mView(sf::FloatRect(0, 0, 400, -300))
		{
			mView.move(-200, 150);
		}

		void SFMLRenderer::drawGeometry(Primitive primitive,
			const std::vector<Math::Vertex> &vertices, 
			const std::vector<uint32_t> &indices, TextureHandle texture,
			const Math::Matrix3x3 &mat)
		{
			mTarget.setView(mView);
			sf::VertexArray polygon(PrimitiveSFMLMap[primitive], indices.size());
			for(uint32_t i=0; i<indices.size(); i++) {
				const Math::Vector3 &vec = mat*vertices[indices[i]].pos;
				polygon[i].position = sf::Vector2f(vec.getX(), vec.getY());
				polygon[i].color = sf::Color(vertices[indices[i]].color.getX()*255, vertices[indices[i]].color.getY()*255, vertices[indices[i]].color.getZ()*255, 255);
				polygon[i].texCoords = sf::Vector2f(vertices[indices[i]].texCoord.getX(), vertices[indices[i]].texCoord.getY());
			}
			if(texture!=0) {
				sf::Texture::bind(reinterpret_cast<sf::Texture *>(texture));
			}
			mTarget.draw(polygon);
		}

		bool SFMLRenderer::loadTexture(const char filename[], TextureHandle &handle)
		{
			auto it = mTexturePool.find(filename);
			if(it == mTexturePool.cend()) {
				sf::Texture texture;
				bool result = texture.loadFromFile(filename);
				if(result) {
					mTexturePool[filename] = texture;
					handle = reinterpret_cast<TextureHandle>(&mTexturePool[filename]);
				}
				return result;
			}else {
				handle = reinterpret_cast<TextureHandle>(&it->second);
				return true;
			}
		}

		void SFMLRenderer::releaseTexture(TextureHandle handle)
		{
			// not necessary at this moment
		}
	}

}