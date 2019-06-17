#include "Application.h"


class MyApp : public Maracas::Application {
	public:
		MyApp() {
			MRC_INFO("Application started");
			m_window = Maracas::Window::createWindow("Client Application",600,400);
			m_window->setEventCallback(BIND(MyApp::onEvent));
		}
		~MyApp() {
			delete m_window;
			MRC_INFO("Application stoped");
		}
		void onUpdate() override {
			m_window->onUpdate();
			if (Maracas::InputsStates::getKey(MRC_KEY_RIGHT) && Maracas::InputsStates::getKey(MRC_KEY_LEFT)) {
				MRC_DEBUG("<---->");
			} else if (Maracas::InputsStates::getKey(MRC_KEY_RIGHT)) {
				MRC_DEBUG("   -->");
			} else if (Maracas::InputsStates::getKey(MRC_KEY_LEFT)) {
				MRC_DEBUG("<--   ");
			}
		}
	private:
		Maracas::Window* m_window;
};

Maracas::Application* Maracas::createApplication() {
	return new MyApp();
}

