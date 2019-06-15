#include "Window.h"

namespace Maracas {
	void GLFW_Window::init() {
		//Create window with GLFW
		initGLFW();
		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title, nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		//Create OpenGL environment
		initGLEW();
		glfwMakeContextCurrent(m_window);
		MRC_CORE_WARN("window created");

		//Set callbacks
		glfwSetWindowUserPointer(m_window, &m_data);
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			GRAB_DATA;
			WindowClosedEvent event;
			data.callback(event);
		});
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
			GRAB_DATA;
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.callback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.callback(event);
					break;
				}
			}
		});
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			GRAB_DATA;
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.callback(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double dx, double dy) {
			GRAB_DATA;
			MouseScrolledEvent event((float)dx, (float)dy);
			data.callback(event);
		});
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
			GRAB_DATA;
			MouseMovedEvent event((int)x, (int)y);
			data.callback(event);
		});
	}

	void GLFW_Window::shutdown() {
		glfwDestroyWindow(m_window);
		MRC_CORE_WARN("window destroyed");
	}

	void GLFW_Window::onUpdate() {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	Window* Window::createWindow(char* title, unsigned int width, unsigned int height) { return new GLFW_Window(title, width, height); }
}
