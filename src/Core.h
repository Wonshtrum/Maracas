#ifndef MRC_CORE_H
#define MRC_CORE_H
#pragma once

/* =========================================== *
 * load config
 * =========================================== */
#include "config.h"

/* =========================================== *
 * load external libraries
 * =========================================== */
#include <iostream>
#include <sstream>
#include <chrono>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//ENDHEAD

/* =========================================== *
 * debug-dependant macros
 * =========================================== */
#ifdef DEBUG_MOD
	#define MRC_CORE_TRACE(...)  ::Maracas::Log::getCoreLogger()->log(Maracas::trace,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_CORE_DEBUG(...)  ::Maracas::Log::getCoreLogger()->log(Maracas::debug,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_CORE_INFO(...)   ::Maracas::Log::getCoreLogger()->log(Maracas::info,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_CORE_WARN(...)   ::Maracas::Log::getCoreLogger()->log(Maracas::warning,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_CORE_ERROR(...)  ::Maracas::Log::getCoreLogger()->log(Maracas::error,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_CORE_CRITIC(...) ::Maracas::Log::getCoreLogger()->log(Maracas::critical,__FILE__,__LINE__,__VA_ARGS__)

	#define MRC_TRACE(...)  ::Maracas::Log::getClientLogger()->log(Maracas::trace,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_DEBUG(...)  ::Maracas::Log::getClientLogger()->log(Maracas::debug,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_INFO(...)   ::Maracas::Log::getClientLogger()->log(Maracas::info,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_WARN(...)   ::Maracas::Log::getClientLogger()->log(Maracas::warning,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_ERROR(...)  ::Maracas::Log::getClientLogger()->log(Maracas::error,__FILE__,__LINE__,__VA_ARGS__)
	#define MRC_CRITIC(...) ::Maracas::Log::getClientLogger()->log(Maracas::critical,__FILE__,__LINE__,__VA_ARGS__)
	
	#define MRC_CORE_ASSERT(x,...) { if (!(x)) { MRC_CORE_CRITIC("Assertion Failed: " __VA_ARGS__); exit(-1); } }
	#define MRC_ASSERT(x,...) { if ((!x)) { MRC_CRITIC("Assertion Failed: " __VA_ARGS__); exit(-1); } }

	#define DEBUG_ONLY(x) x
#else
	#define MRC_CORE_TRACE(...)
	#define MRC_CORE_DEBUG(...)
	#define MRC_CORE_INFO(...)
	#define MRC_CORE_WARN(...)
	#define MRC_CORE_ERROR(...)
	#define MRC_CORE_CRITIC(...)

	#define MRC_TRACE(...)
	#define MRC_DEBUG(...)
	#define MRC_INFO(...)
	#define MRC_WARN(...)
	#define MRC_ERROR(...)
	#define MRC_CRITIC(...)

	#define MRC_CORE_ASSERT(x,...)
	#define MRC_ASSERT(x,...)

	#define DEBUG_ONLY(x)
#endif

/* =========================================== *
 * debug-agnostic macros
 * =========================================== */
#define BIT(x) (1 << x)


/* =========================================== *
 * load internal libraries
 * =========================================== */
#include "Log.h"
#include "Tools.h"

#endif
