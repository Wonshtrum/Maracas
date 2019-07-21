#include "Application.h"

namespace Maracas {
	Application* Application::s_instance;
	Application::Application() {
		MRC_CORE_ASSERT(!s_instance,"Application already exists!");
		s_instance = this;
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
		dispatch<WindowClosedEvent>(event,BIND(Application::onWindowClosed));
		m_layerStack.onEvent(event);
	}

	void Application::run() {
		auto lastFrameTime = std::chrono::steady_clock::now();
		auto timeNow = lastFrameTime;
		float deltaTime;
		while (m_running) {
			lastFrameTime = timeNow;
			timeNow = std::chrono::steady_clock::now();
			deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(timeNow - lastFrameTime).count()/1000000.0;
			onUpdate(deltaTime);
		}
	}

	Application* Application::get() {
		MRC_ASSERT(s_instance,"Application doesn't exist");
		return s_instance;
	}
}
