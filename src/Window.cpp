#include "Window.h"

namespace Maracas {
	bool GLFW_Window::s_GLFWInitialized = false;
	void GLFW_Window::initGLFW() {
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			MRC_CORE_ASSERT(success, "Could not initialized GLFW");
			MRC_CORE_INFO("GLFW initialized");
			s_GLFWInitialized = true;
		}
	}

	void GLFW_Window::init() {
		//Create window with GLFW
		initGLFW();
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title, nullptr, nullptr);
		//Create OpenGL environment
		m_context = new OpenGLContext(m_window);
		m_context->init();
		MRC_CORE_WARN("GLFW window created: \"", m_data.title, "\" (", m_data.width, "x", m_data.height, ")");

		//Set callbacks
		glfwSetWindowUserPointer(m_window, &m_data);
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			GRAB_DATA;
			WindowClosedEvent event;
			data.callback(event);
		});
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
			GRAB_DATA;
			int mrc_key = InputsStates::getGLFWequivKey(key);
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(mrc_key, 0);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(mrc_key);
					data.callback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(mrc_key, 1);
					data.callback(event);
					break;
				}
			}
		});
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			GRAB_DATA;
			int mrc_button = InputsStates::getGLFWequivMouseButton(button);
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(mrc_button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(mrc_button);
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
		glClearColor(0.05,0.2,0.3,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		m_context->swapBuffers();
	}
	
	void DEBUG_Window::init() { MRC_CORE_WARN("dummy window created: \"", m_data.title, "\" (", m_data.width, "x", m_data.height, ")"); }
	void DEBUG_Window::shutdown() { MRC_CORE_WARN("dummy window destroyed"); }
	void DEBUG_Window::onUpdate() { WindowClosedEvent event; m_data.callback(event); }
	
#if defined(USE_GLFW_WINDOW)
	Window* Window::createWindow(const char* title, unsigned int width, unsigned int height) { return new GLFW_Window(title, width, height); }
#else
	Window* Window::createWindow(const char* title, unsigned int width, unsigned int height) { return new DEBUG_Window(title, width, height); }
#endif
}
