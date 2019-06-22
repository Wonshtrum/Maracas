#include "EntryPoint.h"

int main(int argc, char** argv) {
	Maracas::Log::init();
	Maracas::Application* app = Maracas::createApplication();
	app->run();
	delete app;
	Maracas::Log::terminate();
	return 0;
}
