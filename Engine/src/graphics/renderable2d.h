#pragma once

#include "buffer\buffer.h"
#include "buffer\indexbuffer.h"
#include "buffer\vertexarray.h"

#include "../math/maths.h"
#include "shader.h"

namespace Engine {

	namespace Graphics {

		class Renderable2D
		{
		protected:
			Math::Vector2 m_Size;
			Math::Vector3 m_Position;
			Math::Vector4 m_Color;

			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			Shader& m_Shader;

		public:
			Renderable2D(Math::Vector3 position, Math::Vector2 size, Math::Vector4 color, Shader& shader)
				:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
			{
				m_VertexArray = new VertexArray();

				GLfloat vertices[] =
				{
					0,		0,		0,
					0,		size.y,	0,
					size.x,	size.y,	0,
					size.x,	0,		0
				};

				GLfloat colors[] =
				{
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w,
					color.x,color.y,color.z,color.w
				};

				m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLushort indices[] = { 0,1,2,2,3,0 };
				m_IndexBuffer = new IndexBuffer(indices, 6);
			}

			virtual ~Renderable2D()
			{
				delete m_VertexArray;
				delete m_IndexBuffer;
			}

			inline const VertexArray* getVAO() const { return m_VertexArray; };
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; };
			inline Shader& getShader() const { return m_Shader; };

			inline const Math::Vector3& getPosition() const { return m_Position; };
			inline const Math::Vector2& getSize() const { return m_Size; };
			inline const Math::Vector4& getColor() const { return m_Color; };
		};
	}
}

