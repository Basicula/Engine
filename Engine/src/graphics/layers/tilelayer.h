#pragma once
#pragma once

#include "layer.h"
#include "../batchrenderer2d.h"

namespace Engine
{
	namespace Graphics
	{

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			virtual ~TileLayer();
		};

	}
}
