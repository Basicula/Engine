#pragma once

#include "../renderer2d.h"
#include "../renderable2d.h"

namespace Engine
{
	namespace Graphics
	{

		class Layer
		{
		protected:
			Renderer2D * m_Renderer;
			std::vector<Renderable2D*>  m_Renderables;
			Shader* m_Shader;
			Math::mat4 m_ProjectionMatrix;

		protected:
			Layer(Renderer2D* renderer, Shader* shader, Math::mat4 projectionMatrix);

		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();

		};

	}
}
