#include "src\graphics\window.h"
#include "src\math\maths.h"
#include "src\utils\fileutils.h"
#include "src\graphics\shader.h"

int main() {
	using namespace Engine;
	using namespace Graphics;
	using namespace Math;

	Window window("Test", 800, 600);

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

	mat4 ortho = mat4::orthographic(0, 16, 0, 9, -1, 1);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::scale(Vector3(1, 1, 0)));

	shader.setUniform2f("light_pos", Vector2(4, 4));
	shader.setUniform4f("colour", Vector4(1, 0, 0, 1));

	while (!window.closed())
	{
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.update();
	}

	return 0;
}