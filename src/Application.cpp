#include "Application.h"
#include "GraphicsData.h"

namespace Maracas {
	Application* Application::s_instance;
	Application::Application() {
		MRC_CORE_ASSERT(!s_instance,"Application already exists!");
		s_instance = this;
		MRC_CORE_INFO("Application started");

		/*BufferElement test[] = {{ShaderData::Float2,"a_position"}};
		BufferLayout b(test, 1);
		VertexArray vao = OpenGL_VertexArray();*/

	}

	Application::~Application() {
		MRC_CORE_INFO("Application destroyed");
	}

	bool Application::onWindowClosed(WindowClosedEvent& event) {
		m_running = false;
		return true;
	}

	void Application::onEvent(Event& event) {
		MRC_TRACE(event.toString());
		dispatch<WindowClosedEvent>(event,BIND(Application::onWindowClosed));
	}

	void Application::run() {
		while (m_running) {
			onUpdate();
		}
	}

	Application* Application::get() {
		MRC_ASSERT(s_instance,"Application doesn't exist");
		return s_instance;
	}
}
