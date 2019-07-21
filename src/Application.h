#ifndef MRC_APPLICATION_H
#define MRC_APPLICATION_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
#include "Event.h"
#include "Window.h"
#include "GraphicsContext.h"
#include "GraphicsData.h"
#include "Shader.h"
#include "Layer.h"

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
			virtual void onUpdate(float deltaTime) = 0;
			inline static Application* get();
		protected:
			bool m_running = true;
			LayerStack m_layerStack;
			static Application* s_instance;
	};

	/* =========================================== *
	 * client hook to create Application
	 * =========================================== */
	Application* createApplication();
}

#endif
