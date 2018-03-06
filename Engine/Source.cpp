#include "src\graphics\window.h"
#include "src\math\maths.h"
#include "src\utils\fileutils.h"
#include "src\graphics\shader.h"
#include "src\graphics\buffer\buffer.h"
#include "src\graphics\buffer\indexbuffer.h"
#include "src\graphics\buffer\vertexarray.h"

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
	GLfloat vertices[] =
	{
		0,	0,	0.0f,
		0,	5, 0.0f,
		5,	5,	0.0f,
		5,	0,	0.0f
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	Buffer* vbo = new Buffer(vertices,4*3,3);
	IndexBuffer ibo(indices, 6);

	vao.addBuffer(vbo, 0);

#endif

	mat4 ortho = mat4::orthographic(0, 16, 0, 9, -1, 1);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(Vector3(1, 1, 0)));

	shader.setUniform2f("light_pos", Vector2(4, 4));
	shader.setUniform4f("colour", Vector4(1, 0, 0, 1));

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Vector2(x * 16 / 800, 9-y * 9 / 600));
#if 0
		glDrawArrays(GL_TRIANGLES, 0, 3);
#else
		vao.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(Vector3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		shader.setUniformMat4("ml_matrix", mat4::translation(Vector3(5, 5, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		vao.unbind();
#endif
		window.update();
	}

	return 0;
}