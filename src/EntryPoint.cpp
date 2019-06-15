#include "Application.h"

//extern Maracas::Application* Maracas::CreateApplication();

int main(int argc, char** argv) {
	Maracas::Log::init();
	Maracas::Application* app = Maracas::createApplication();
	app->run();
	delete app;
	Maracas::Log::terminate();
	return 0;
}
