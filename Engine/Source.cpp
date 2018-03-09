#include <vector>

#include "src\graphics\window.h"
#include "src\utils\fileutils.h"

#include "src\graphics\shader.h"
#include "src\graphics\buffer\buffer.h"
#include "src\graphics\buffer\indexbuffer.h"
#include "src\graphics\buffer\vertexarray.h"

#include "src\math\maths.h"
#include "src\_TestGraph\testfuncs.h"

#include "src\graphics\renderer2d.h"
#include "src\graphics\simple2drenderer.h"
#include "src\graphics\batchrenderer2d.h"

#include "src\graphics\static_sprite.h"
#include "src\graphics\sprite.h"

#include "src\utils\timer.h"
#include <time.h>

#include "src\graphics\layers\tilelayer.h"

int main() {
	using namespace Engine;
	using namespace Graphics;
	using namespace Math;

	Window window("Test", 800, 600);
	mat4 ortho = mat4::orthographic(0, 16, 0, 9, -1, 1);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", Vector2(4, 4));

	TileLayer layer(&shader);
	layer.add(new Sprite(0, 0, 4, 4, Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

	Timer time;
	float t = 0;
	unsigned int frames = 0;


	std::vector<Vector2> dots;
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		x = x * 32.0f / 800.0f - 16.0f;
		y = 9.0f - y * 18.0f / 600.0f;
		shader.enable();
		shader.setUniform2f("light_pos", Vector2(x, y));
#if 0
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			bool ok = true;
			for (int i = 0; i < dots.size(); i++)
			{
				if (fabs(x - dots[i].x) < 1e-3&&fabs(y - dots[i].y) < 1e-3) ok = !ok;
			}
			if (ok)
			{
				dots.push_back(Vector2(x, y));
				std::sort(dots.begin(), dots.end());
			}

		}

		if (dots.size() > 1)
		{
			shader.setUniform4f("colour", Vector4(1, 0, 0, 1));
			for (int i = 0; i < dots.size(); i++)
			{
				glBegin(GL_LINE_LOOP);
				glColor3f(1, 0, 0);
				for (int j = 0; j < 360; j++)
				{
					float rad = toRadians(j);
					glVertex2f(dots[i].x + cos(rad)*0.1, dots[i].y + sin(rad)*0.1);
				}
				glEnd();
			}

			shader.setUniform4f("colour", Vector4(1, 0, 0, 1));
			std::vector<Vector2> graph = Graph::lineInterpolation(dots);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < graph.size(); i++)
			{
				glVertex2f(graph[i].x, graph[i].y);
			}
			glEnd();

			/*graph = Graph::polyInterpolation(dots);
			shader.setUniform4f("colour", Vector4(0, 1, 0, 1));
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < graph.size(); i++)
			{
				glVertex2f(graph[i].x, graph[i].y);
			}
			glEnd();*/

			graph = Graph::cubeSplainInterpolation(dots);
			shader.setUniform4f("colour", Vector4(0, 0, 1, 1));
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < graph.size(); i++)
			{
				glVertex2f(graph[i].x, graph[i].y);
			}
			glEnd();

			graph = Graph::interpolationLagrange(dots);
			shader.setUniform4f("colour", Vector4(1, 1, 0, 1));
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < graph.size(); i++)
			{
				glVertex2f(graph[i].x, graph[i].y);
			}
			glEnd();
		}
#else
		layer.render();
#endif
		window.update();
		frames++;
		if (time.elapsed() - t > 1.0f)
		{
			t += 1.0f;
			printf("%d\n", frames);
			frames = 0;
		}
	}

	return 0;
}