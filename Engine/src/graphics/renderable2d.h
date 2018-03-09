#pragma once

#include "buffer\buffer.h"
#include "buffer\indexbuffer.h"
#include "buffer\vertexarray.h"

#include "../math/maths.h"
#include "shader.h"

namespace Engine {

	namespace Graphics {

		struct VertexData
		{
			Math::Vector3 vertex;
			//Math::Vector4 color;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			Math::Vector2 m_Size;
			Math::Vector3 m_Position;
			Math::Vector4 m_Color;
			
		public:
			Renderable2D(Math::Vector3 position, Math::Vector2 size, Math::Vector4 color)
				:m_Position(position), m_Size(size), m_Color(color)
			{}

			virtual ~Renderable2D() {}


			inline const Math::Vector3& getPosition() const { return m_Position; };
			inline const Math::Vector2& getSize() const { return m_Size; };
			inline const Math::Vector4& getColor() const { return m_Color; };
		};
	}
}

