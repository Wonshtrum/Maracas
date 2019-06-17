#ifndef MRC_APPLICATION_H
#define MRC_APPLICATION_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
#include "Event.h"
#include "Window.h"

/* =========================================== *
 * application specific macros
 * =========================================== */
#define BIND(x) std::bind(&x,this,std::placeholders::_1)
//ENDHEAD
namespace Maracas {
	/* =========================================== *
	 * Application class (implemented by client)
	 * =========================================== */
	class Application {
		public:
			Application();
			virtual ~Application();
			virtual void onEvent(Event& event);
			bool onWindowClosed(WindowClosedEvent& event);
			virtual void run();
			virtual void onUpdate() = 0;
			inline static Application* get();
		protected:
			bool m_running = true;
			static Application* s_instance;
	};

	/* =========================================== *
	 * client hook to create Application
	 * =========================================== */
	Application* createApplication();
}

#endif
