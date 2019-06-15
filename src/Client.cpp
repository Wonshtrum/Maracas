#include "Application.h"


class MyApp : public Maracas::Application {
	public:
		MyApp() {}
		~MyApp() {}
		void run() override {
			m_running = true;
			MRC_INFO("Application started");
			m_window = Maracas::Window::createWindow("Client Application",600,400);
			m_window->setEventCallback(BIND(MyApp::onEvent));
			while (m_running) {
				glClearColor(0.05,0.2,0.3,1);
				glClear(GL_COLOR_BUFFER_BIT);
				m_window->onUpdate();
			}
			delete m_window;
			MRC_INFO("Application stoped");
		}
	private:
		Maracas::Window* m_window;
};

Maracas::Application* Maracas::createApplication() {
	return new MyApp();
}

