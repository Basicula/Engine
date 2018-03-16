#pragma once

#include <cstddef>
#include "renderer2d.h"
#include "buffer\indexbuffer.h"
#include "renderable2d.h"

namespace Engine
{

	namespace Graphics
	{
#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_INDECES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_BUFFER_SIZE	RENDERER_MAX_SPRITES * RENDERER_SPRITE_SIZE

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_COLOR_INDEX	2

		class BatchRenderer2D :public Renderer2D
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLsizei m_IndexCount;
			VertexData* m_Buffer;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D* renderable)  override;
			void end() override;
			void flush() override;

		private:
			void init();
		};

	}
}
