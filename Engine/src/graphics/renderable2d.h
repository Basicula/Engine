#pragma once

#include "buffer\buffer.h"
#include "buffer\indexbuffer.h"
#include "buffer\vertexarray.h"

#include "renderer2d.h"

#include "../math/maths.h"
#include "shader.h"

namespace Engine {

	namespace Graphics {

		struct VertexData
		{
			Math::Vector3 vertex;
			Math::Vector2 uv;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			Math::Vector2 m_Size;
			Math::Vector3 m_Position;
			Math::Vector4 m_Color;
			std::vector<Math::Vector2> m_UV;

		protected:
			Renderable2D()
			{
				setUVDefaults();
			}

		public:
			Renderable2D(Math::Vector3 position, Math::Vector2 size, Math::Vector4 color)
				:m_Position(position), m_Size(size), m_Color(color)
			{
				setUVDefaults();
			}

			virtual ~Renderable2D() {}

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			inline const Math::Vector3& getPosition() const { return m_Position; }
			inline const Math::Vector2& getSize() const { return m_Size; }
			inline const Math::Vector4& getColor() const { return m_Color; }
			inline const std::vector<Math::Vector2>& getUV() const { return m_UV; }

		private:
			void setUVDefaults()
			{
				m_UV.push_back(Math::Vector2(0, 0));
				m_UV.push_back(Math::Vector2(0, 1));
				m_UV.push_back(Math::Vector2(1, 1));
				m_UV.push_back(Math::Vector2(1, 0));
			}
		};
	}
}

