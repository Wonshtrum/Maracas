#include "Core.h"

namespace Maracas {
	color Logger::s_colorCode[6] = {grey, lightBlue, green, yellow, red, darkRed};

	void Maracas::Logger::header(logLevel level, char* file, int line) {
		std::cout << (m_bold ? BOLD : "") << COLOR(level) << "[" << file << "(" << line << ")] " << m_name << ": ";
	}
	
	Logger* Log::s_CoreLogger;
	Logger* Log::s_ClientLogger;
	void Log::init() {
		Log::s_CoreLogger = new Logger((char*)"MARACAS");
		//s_CoreLogger->setLevel(debug);
		s_CoreLogger->setBold(true);
		s_ClientLogger = new Logger((char*)"APP");
		//s_ClientLogger->setLevel(critical);
	}
}
