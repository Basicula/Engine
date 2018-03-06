#pragma once
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Engine {

	namespace Graphics {

#define MAX_KEYS			1024
#define MAX_MOUSE_BUTTONS	32

		class Window {
		private:
			int m_Width, m_Heidth;
			const char *m_Title;
			GLFWwindow *m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_MOUSE_BUTTONS];
			double mx, my;

		public:
			Window(const char *name, int weidth, int  heidth);
			~Window();
			void clear() const;
			void update();
			bool closed() const;

			inline int getWidth() const { return m_Width; };
			inline int getHeidth() const { return m_Heidth; };

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;

		private:
			bool init();
			friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}