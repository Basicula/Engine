#pragma once

#include "../renderable2d.h"

namespace Engine
{

	namespace Graphics
	{

		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_Renderables;
			Math::mat4 m_TransformationMatrix;
			
		public:
			Group(const Math::mat4& transform);
			~Group();
			void submit(Renderer2D* renderer) const override; 
			void add(Renderable2D* renderable);
		};
	}
}
