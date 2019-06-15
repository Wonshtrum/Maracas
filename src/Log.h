#pragma once

/* =========================================== *
 * log specific macros
 * =========================================== */
#define COLOR(x) "\033[38;5;" << Maracas::Logger::levelToColor(x) << "m"
#define BOLD "\033[1m"
#define END "\033[0m"

namespace Maracas {
	/* =========================================== *
	 * color enumeration
	 * =========================================== */
	enum color {
		black = 0,
		red = 1,
		green = 2,
		blue = 4,
		grey = 8,
		yellow = 11,
		lightBlue = 14,
		darkRed = 88
	};
	
	/* =========================================== *
 	 * log level enumeration
	 * =========================================== */
	enum logLevel {
		trace = 0,
		debug = 1,
		info = 2,
		warning = 3,
		error = 4,
		critical = 5
	};

	/* =========================================== *
	 * class Logger, responsible for logging
	 * =========================================== */
	class Logger {
		public:
			Logger(char* name):m_name(name), m_level(trace), m_bold(false) { log(trace, "MASTER", 42, "logger initialized"); }
			~Logger() { log(trace, "MASTER", 42, "logger terminated"); };
			void header(logLevel level, char* file, int line);
			template<typename... T>
			void log(logLevel level, char* file, int line, T... param) {
				if ( level >= m_level ) {
					header(level, file, line);
					const int a[] = {(std::cout << param,0)...};
					std::cout << END << std::endl;
                		}
			};
			void setLevel(logLevel level) { m_level = level; };
			void setBold(bool bold) { m_bold = bold; };
			static color levelToColor(logLevel level) { return s_colorCode[level]; }
			static color s_colorCode[6];
		private:
			char* m_name;
			logLevel m_level;
			bool m_bold;
	};

	/* =========================================== *
	 * class Log, contain 2 loggers
	 * =========================================== */
	class Log {
		public:
			static void init();
			static void terminate() { delete s_CoreLogger; delete s_ClientLogger; }
			inline static Logger* getCoreLogger() { return s_CoreLogger; }
			inline static Logger* getClientLogger() { return s_ClientLogger; }
		private:
			static Logger* s_CoreLogger;
			static Logger* s_ClientLogger;
	};
}
