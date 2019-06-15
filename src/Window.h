#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
#include "Event.h"

/* =========================================== *
 * window specific macros
 * =========================================== */
#define GRAB_DATA windowData& data = *(windowData*)glfwGetWindowUserPointer(window)

namespace Maracas {
	using EventCallback = std::function<void(Event&)>;
	//typedef void (*EventCallback)(Event&);
	/* =========================================== *
	 * data contained in a Maracas Window
	 * =========================================== */
	struct windowData {
		char* title;
		unsigned int width, height;
		EventCallback callback;
	};

	/* =========================================== *
	 * GLFW and OPENGL initialisation
	 * =========================================== */
	static bool s_GLFWInitialized = false;
	static void initGLFW() {
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			MRC_CORE_ASSERT(success, "Could not initialized GLFW");
			glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
			glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
			glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
			MRC_CORE_INFO("GLFW initialized");
		}
	}
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//           EXTREMELY TEMPORARY
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	static void initGLEW() {
		int success = glewInit();
		MRC_CORE_ASSERT(success == GLEW_OK, "Could not initialized GLEW");
		MRC_CORE_INFO("GLEW initialized");
		MRC_CORE_INFO(glGetString(GL_VERSION));
		s_GLFWInitialized = true;
	}

	class GLFW_Window;
	/* =========================================== *
	 * abstracted class Window, Maracas API
	 * =========================================== */
	class Window {
		public:
			static Window* createWindow(char* title, unsigned int width, unsigned int height);
			virtual ~Window() {}
			virtual unsigned int getWidth() { return m_data.width; }
			virtual unsigned int getHeight() { return m_data.height; }
			virtual void setEventCallback(EventCallback callback) { m_data.callback = callback; }
			virtual void onUpdate() = 0;
		protected:
			virtual void init() = 0;
			virtual void shutdown() = 0;
			virtual void create(char* title, unsigned int width, unsigned int height) { m_data = {title, width, height, nullptr}; init(); }
			windowData m_data;
	};


	/* =========================================== *
	 * implemented class Window with GLFW
	 * =========================================== */
	class GLFW_Window : public Window {
		public:
			GLFW_Window(char* title, unsigned int width, unsigned int height) { create(title, width, height); }
			~GLFW_Window() { shutdown(); };
			void onUpdate() override;
		protected:
			void init() override;
			void shutdown() override;
		private:
			GLFWwindow* m_window;
	};
}
