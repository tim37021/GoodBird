#ifndef _GOODBIRD_RENDERING_H_
#define _GOODBIRD_RENDERING_H_

#include <GoodBird/Math.h>
#include <vector>
#include <cstdint>

namespace GoodBird
{
	namespace Rendering
	{
		enum Primitive
		{
			POINTS,
			LINES,
			LINES_STRIP,
			TRIANGLES,
			TRIANGLES_STRIP,
			TRIANGLES_FAN,
			QUADS
		};

		typedef intptr_t TextureHandle;
		class RenderInterface
		{
		public:
			// Ask to draw triangles
			virtual void drawGeometry(Primitive primitive, const std::vector<Math::Vertex> &vertices, 
				const std::vector<uint32_t> &indices, TextureHandle texture,
				const Math::Matrix3x3 &mat)=0;
			virtual bool loadTexture(const char filename[], TextureHandle &handle)=0;
			virtual void releaseTexture(TextureHandle handle)=0;
		};

		class Drawable
		{
		public:
			virtual ~Drawable()=default;
			virtual void draw(RenderInterface &renderer, Math::Matrix3x3 trans)=0;
		};
	}
}

#endif