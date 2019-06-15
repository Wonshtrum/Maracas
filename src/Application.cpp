#include "Application.h"

namespace Maracas {
	Application::Application() {
		MRC_CORE_INFO("Application started");
	}
	Application::~Application() {
		MRC_CORE_INFO("Application destroyed");
	}
	bool Application::onWindowClosed(WindowClosedEvent& event) {
		m_running = false;
		return true;
	}
	void Application::onEvent(Event& event) {
		MRC_CORE_TRACE(event.toString());
		dispatch<WindowClosedEvent>(event,BIND(Application::onWindowClosed));
	}
}
