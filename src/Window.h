#ifndef MRC_WINDOW_H
#define MRC_WINDOW_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
#include "Event.h"
#include "GraphicsContext.h"

/* =========================================== *
 * window specific macros
 * =========================================== */
#define GRAB_DATA windowData& data = *(windowData*)glfwGetWindowUserPointer(window)
//ENDHEAD
namespace Maracas {
	using EventCallback = std::function<void(Event&)>;
	/* =========================================== *
	 * data contained in a Maracas Window
	 * =========================================== */
	struct windowData {
		const char* title;
		unsigned int width, height;
		EventCallback callback;
	};

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
			static void initGLFW();
			GLFW_Window(const char* title, unsigned int width, unsigned int height) { create(title, width, height); }
			~GLFW_Window() { shutdown(); };
			virtual void onUpdate() override;
		protected:
			virtual void init() override;
			virtual void shutdown() override;
		private:
			GLFWwindow* m_window;
			GraphicsContext* m_context;
			static bool s_GLFWInitialized;
	};

	/* =========================================== *
	 * implemented dummy class Window (debug)
	 * =========================================== */
	class DEBUG_Window : public Window {
		public:
			DEBUG_Window(const char* title, unsigned int width, unsigned int height) { create(title, width, height); }
			~DEBUG_Window() { shutdown(); };
			virtual void onUpdate() override;
		protected:
			virtual void init() override;
			virtual void shutdown() override;
	};
}

#endif
