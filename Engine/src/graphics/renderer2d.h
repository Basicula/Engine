#pragma once

#include <GL\glew.h>
#include "../math/maths.h"
#include "renderable2d.h"

namespace Engine {

	namespace Graphics {

		class Renderer2D
		{
		public:
			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void end() {}
			virtual void flush() = 0;
		};

	}
}
