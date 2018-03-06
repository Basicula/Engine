#pragma once
#include <iostream>
#include <vector>
#include <GL\glew.h>
#include "../math/maths.h"
#include "../utils/fileutils.h"

namespace Engine {

	namespace Graphics {

		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char *m_VertPath;
			const char *m_FragPath;

		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const Math::Vector2& vector);
			void setUniform3f(const GLchar* name, const Math::Vector3& vector);
			void setUniform4f(const GLchar* name, const Math::Vector4& vector);
			void setUniformMat4(const GLchar* name, const Math::mat4& matrix);

			void enable() const;
			void disable() const;

		private:
			GLint getUniformLocation(const GLchar* name);
			GLuint load();
		};

	}
}