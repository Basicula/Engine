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

int main() {
	using namespace Engine;
	using namespace Graphics;
	using namespace Math;

	Window window("Test", 800, 600);
#if 0
	GLfloat vertices[] =
	{
		4, 4, 0.0f,
		10, 4, 0.0f,
		4, 10, 0.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
#else
	
#endif

	mat4 ortho = mat4::orthographic(0, 16, 0, 9, -1, 1);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	Renderable2D sprite(Vector3(3, 3, 0), Vector2(4, 4), Vector4(1, 0, 0, 1), shader);
	Simple2DRenderer renderer;

	shader.setUniform2f("light_pos", Vector2(4, 4));
	shader.setUniform4f("colour", Vector4(1, 0, 0, 1));

	std::vector<Vector2> dots;
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		x = x * 16.0 / 800;
		y = 9 - y * 9.0 / 600;
		shader.setUniform2f("light_pos", Vector2(x, y));
#if 1
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
			}

		}

		if (dots.size() > 1)
		{
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

			std::vector<Vector2> newdots =
			{
				Vector2(1,1),
				Vector2(5,5)
			};
			graph = Graph::cubeInterpolation(dots);
			shader.setUniform4f("colour", Vector4(0, 1, 0, 1));
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < graph.size(); i++)
			{
				glVertex2f(graph[i].x, graph[i].y);
			}
			glEnd();
	}
#else
		renderer.submit(&sprite);
		renderer.flush();
#endif
		window.update();
}

	return 0;
}