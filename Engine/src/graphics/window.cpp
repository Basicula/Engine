#include "window.h"

namespace Engine {
	namespace Graphics {

		void window_resize(GLFWwindow *window, int width, int heidth);
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

		Window::Window(const char *name, int width, int heidth)
		{
			m_Title = name;
			m_Width = width;
			m_Heidth = heidth;
			if (!init())
				glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}

			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				printf("Failed initialize GLFW\n");
				return false;
			}
			m_Window = glfwCreateWindow(m_Width, m_Heidth, m_Title, NULL, NULL);
			if (!m_Window)
			{
				glfwTerminate();
				printf("Window didn't create\n");
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			if (glewInit() != GLEW_OK) {
				printf("Couldn't initialized GLEW");
				return false;
			}

			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_MOUSE_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		void window_resize(GLFWwindow *window, int width, int heidth)
		{
			glViewport(0, 0, width, heidth);
		}

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window);
		}


		Window::~Window()
		{
			glfwTerminate();
		}

	}
}