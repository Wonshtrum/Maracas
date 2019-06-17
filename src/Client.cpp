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
				m_window->onUpdate();
				if (Maracas::InputsStates::getKey(MRC_KEY_RIGHT) && Maracas::InputsStates::getKey(MRC_KEY_LEFT)) {
					MRC_DEBUG("<---->");
				} else if (Maracas::InputsStates::getKey(MRC_KEY_RIGHT)) {
					MRC_DEBUG("   -->");
				} else if (Maracas::InputsStates::getKey(MRC_KEY_LEFT)) {
					MRC_DEBUG("<--   ");
				}
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

