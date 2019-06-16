#include "Event.h"

namespace Maracas {
	int InputsStates::GLFWkeys[KEY_COUNT] = GLFW_KEYS_TAB;
	int InputsStates::GLFWequivKey[KEY_COUNT] = GLFW_EQUIV_KEYS_TAB;
	int InputsStates::GLFWmouseButtons[MOUSE_BUTTON_COUNT] = GLFW_MOUSE_BUTTONS_TAB;
	int InputsStates::GLFWequivMouseButtons[MOUSE_BUTTON_COUNT] = GLFW_EQUIV_MOUSE_BUTTONS_TAB;
	bool InputsStates::keys[KEY_COUNT] = { false };
	bool InputsStates::mouseButtons[MOUSE_BUTTON_COUNT] = { false };
	int InputsStates::cursorX = 0;
	int InputsStates::cursorY = 0;
}
