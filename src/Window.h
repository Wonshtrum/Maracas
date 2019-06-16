#ifndef MRC_WINDOW_H
#define MRC_WINDOW_H
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
//ENDHEAD
namespace Maracas {
	using EventCallback = std::function<void(Event&)>;
	//typedef void (*EventCallback)(Event&);
	/* =========================================== *
	 * data contained in a Maracas Window
	 * =========================================== */
	struct windowData {
		const char* title;
		unsigned int width, height;
		EventCallback callback;
	};

	/* =========================================== *
	 * GLFW and OPENGL initialisation
	 * =========================================== */
	void initGLFW();
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	//           EXTREMELY TEMPORARY
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	void initGLEW();

	class GLFW_Window;
	/* =========================================== *
	 * abstracted class Window, Maracas API
	 * =========================================== */
	class Window {
		public:
			static Window* createWindow(const char* title, unsigned int width, unsigned int height);
			virtual ~Window() {}
			virtual unsigned int getWidth() { return m_data.width; }
			virtual unsigned int getHeight() { return m_data.height; }
			virtual void setEventCallback(EventCallback callback) { m_data.callback = callback; }
			virtual void onUpdate() = 0;
		protected:
			virtual void init() = 0;
			virtual void shutdown() = 0;
			virtual void create(const char* title, unsigned int width, unsigned int height) { m_data = {title, width, height, nullptr}; init(); }
			windowData m_data;
	};


	/* =========================================== *
	 * implemented class Window with GLFW
	 * =========================================== */
	class GLFW_Window : public Window {
		public:
			GLFW_Window(const char* title, unsigned int width, unsigned int height) { create(title, width, height); }
			~GLFW_Window() { shutdown(); };
			void onUpdate() override;
		protected:
			void init() override;
			void shutdown() override;
		private:
			GLFWwindow* m_window;
	};
}

#endif
