#pragma once

#include <GL\glew.h>
#include "../math/maths.h"
#include <vector>

namespace Engine {

	namespace Graphics {

		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<Math::mat4> m_TransformationStack;
			const Math::mat4* m_TransformationBack;

		protected:
			Renderer2D()
			{
				m_TransformationStack.push_back(Math::mat4::identity());
				m_TransformationBack = &m_TransformationStack.back();
			}

		public:
			void push(Math::mat4 matrix, bool override = false)
			{
				if (override)
					m_TransformationStack.push_back(matrix);
				else
					m_TransformationStack.push_back(m_TransformationStack.back()*matrix);

				m_TransformationBack = &m_TransformationStack.back();
			}

			void pop()
			{
				if (m_TransformationStack.size() > 1)
					m_TransformationStack.pop_back();

				m_TransformationBack = &m_TransformationStack.back();
			}

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void end() {}
			virtual void flush() = 0;
		};

	}
}
