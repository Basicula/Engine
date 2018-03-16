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
#include "src\graphics\layers\groupr.h"
#include "src\graphics\texture.h"

#define TEST 0
using namespace Engine;
using namespace Graphics;
using namespace Math;

bool sq(Vector2 a, Vector2 b, Vector2 c)
{
	return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) < 0;
}

int main() {

	Window window("Test", 800, 600);
	mat4 ortho = mat4::orthographic(0, 16, 0, 9, -1, 1);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();

	TileLayer layer(&shader);
	srand(time(NULL));
	/*for (float x = -16.0f; x < 16.0f; x++)
	{
		for (float y = -9.0f; y < 9.0f; y++)
		{
			layer.add(new Sprite(x, y, 0.9f, 0.9f, Vector4(rand() * 100.0f / 100.0f, rand() * 100.0f / 100.0f, rand() * 100.0f / 100.0f, 1.0f)));
		}
	}*/
	layer.add(new Sprite(-3, -3, 16, 9, Vector4(1, 0, 0, 1)));
	Timer time;
	float t = 0;
	unsigned int frames = 0;

	glActiveTexture(GL_TEXTURE0);
	Texture tex("TrumpetShape.png");
	tex.bind();

	shader.enable();
	shader.setUniform1i("tex", 0);
	shader.setUniformMat4("pr_matrix", Math::mat4::orthographic(-16, 16, -9, 9, -1, 1));

#if TEST == 3
	int n = 30;
	std::vector<Vector2> vertecies(n);
	for (int i = 0; i < n; i++)
	{
		float x = rand() % 300 / 10.0f - 15.0f;
		float y = rand() % 160 / 10.0f - 8.0f;
		vertecies[i] = Vector2(x, y);
	}

	std::sort(vertecies.begin(), vertecies.end());
	Vector2 A = vertecies[0], B = vertecies[n - 1];
	float dx = A.x - B.x;
	float dy = A.y - B.y;
	std::vector<Vector2> path;
	path.push_back(vertecies[0]);
	for (int i = 1; i < n; i++)
	{
		if (path.size() == 1) path.push_back(vertecies[i]);
		else
		{
			if (sq(A, vertecies[i], B))
			{
				while (path.size() >= 2 && !sq(path[path.size() - 2], path[path.size() - 1], vertecies[i]))
				{
					path.pop_back();
				}
				path.push_back(vertecies[i]);
			}
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (path.size() == 1) path.push_back(vertecies[i]);
		else
		{
			if (!sq(A, vertecies[i], B))
			{
				while (path.size() >= 2 && !sq(path[path.size() - 2], path[path.size() - 1], vertecies[i]))
				{
					path.pop_back();
				}
				path.push_back(vertecies[i]);
			}
		}
	}
#endif

#if TEST == 2
	std::vector<Vector2> vertecies;
	float len = 5;
	vertecies.push_back(Vector2(-15, 0));
	vertecies.push_back(Vector2(15, 0));
	while (vertecies.size() < 10)
	{
		float x = rand() % 28 - 14.0f;
		float y = rand() % 14 - 7.0f;
		Vector2 vec(x, y);

		bool ok = true;

		for (int i = 0; i < vertecies.size(); i++)
		{
			if (vertecies[i].dist(vec) < len)
			{
				ok = false;
				break;
			}
		}
		if (ok) vertecies.push_back(vec);
	}
	sort(vertecies.begin(), vertecies.end());

	std::vector<std::vector<Vector2>> graph(vertecies.size());
	for (int i = 0; i < vertecies.size(); i++)
	{
		int k = max(rand() % 4, 2);
		for (int j = i + 1; j < vertecies.size() && j - i <= k; j++)
		{
			graph[i].push_back(vertecies[j]);
		}
	}
#endif


	std::vector<Vector2> dots;
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		x = x * 32.0f / 800.0f - 16.0f;
		y = 9.0f - y * 18.0f / 600.0f;
		shader.setUniform2f("light_pos", Vector2(x, y));


#if TEST == 3
		for (int i = 0; i < vertecies.size(); i++)
		{
			glBegin(GL_LINE_LOOP);
			for (int j = 0; j < 360; j++)
			{
				float rad = toRadians(j);
				glVertex2f(vertecies[i].x + cos(rad) * 0.1f, vertecies[i].y + sin(rad) * 0.1f);
			}
			glEnd();
		}

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < path.size(); i++)
		{
			glVertex2f(path[i].x, path[i].y);
		}
		glEnd();
#endif

#if TEST == 2
		for (int i = 0; i < vertecies.size(); i++)
		{
			glBegin(GL_TRIANGLE_FAN);
			for (int j = 0; j < 360; j++)
			{
				float rad = toRadians(j);
				glVertex2f(vertecies[i].x + cos(rad) * 0.25f, vertecies[i].y + sin(rad) * 0.25f);
			}
			glEnd();
		}

		shader.setUniform4f("colour", Vector4(0, 1, 0, 1));
		for (int i = 0; i < vertecies.size(); i++)
		{
			float x = vertecies[i].x;
			float y = vertecies[i].y;
			for (int j = 0; j < graph[i].size(); j++)
			{
				glBegin(GL_LINES);
				glVertex2f(x, y);
				glVertex2f(graph[i][j].x, graph[i][j].y);
				glEnd();

				float k = fabs(y - graph[i][j].y) / fabs(x - graph[i][j].x);
				float xx = graph[i][j].x - 0.1f;
				float yy = graph[i][j].y + ((graph[i][j].y - y < 0) ? 0.1f*k : -0.1f*k);
				glBegin(GL_TRIANGLE_FAN);
				for (int j = 0; j < 360; j++)
				{
					float rad = toRadians(j);
					glVertex2f(xx + cos(rad) * 0.1f, yy + sin(rad) * 0.1f);
				}
				glEnd();
			}
		}

#elif TEST == 1
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
				for (int j = 0; j < 360; j++)
				{
					float rad = toRadians(j);
					glVertex2f(dots[i].x + cos(rad) * 0.1f, dots[i].y + sin(rad) * 0.1f);
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
#elif TEST == 0
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