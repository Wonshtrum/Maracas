#ifndef MRC_EVENT_H
#define MRC_EVENT_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
#include "InputsEquiv.h"

/* =========================================== *
 * event specific macros
 * =========================================== */
#define EVENT_CLASS_CATEGORY(category) virtual inline int getCategoryFlags() override { return category; }
#define EVENT_CLASS_TYPE(type) inline static eventType getStaticType() { return type; }\
	virtual eventType getEventType() override { return type; }\
	virtual const char* getName() override { return #type; }
//ENDHEAD
namespace Maracas {
	/* =========================================== *
	 * memory structure for input polling
	 * =========================================== */
	struct InputsStates {
		static int GLFWkeys[KEY_COUNT];
		static int GLFWequivKey[KEY_COUNT];
		static int GLFWmouseButtons[MOUSE_BUTTON_COUNT];
		static int GLFWequivMouseButtons[MOUSE_BUTTON_COUNT];
		static bool keys[KEY_COUNT];
		static bool mouseButtons[MOUSE_BUTTON_COUNT];
		static int cursorX;
		static int cursorY;
		inline static void setKey(int key, bool value) { keys[key] = value; }
		inline static void setMouseButton(int button, bool value) { mouseButtons[button] = value; }
		inline static void setCursorPos(int x, int y) { cursorX = x; cursorY = y; }
		inline static bool getKey(int key) { return keys[key]; }
		inline static bool getMouseButton(int button) { return mouseButtons[button]; }
		inline static int getCursorX() { return cursorX; }
		inline static int getCursorY() { return cursorY; }
		inline static int getGLFWequivKey(int key) { return GLFWequivKey[binarySearch(GLFWkeys, KEY_COUNT, key)]; }
		inline static int getGLFWequivMouseButton(int button) { return GLFWequivMouseButtons[binarySearch(GLFWmouseButtons, MOUSE_BUTTON_COUNT, button)]; }
	};

	/* =========================================== *
	 * event type enumeration
	 * =========================================== */
	enum eventType {
		None = 0,
		WindowClosed, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,	//todo
		KeyPressed, KeyReleased,						//done
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled	//done
	};

	/* =========================================== *
	 * event category enumeration
	 * =========================================== */
	enum eventCategory {
		EventCategoryApplication = BIT(0),
		EventCategoryInput =       BIT(1),
		EventCategoryKeyBoard =    BIT(2),
		EventCategoryMouse =       BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	/* =========================================== *
	 * class Event, usable by Maracas event system
	 * =========================================== */
	class Event {
		public:
			inline static eventType getStaticType() { return None; }
			virtual eventType getEventType() = 0;
			virtual const char* getName() = 0;
			virtual int getCategoryFlags() = 0;
			virtual std::string toString() { return getName(); }
			virtual inline bool isInCategory(eventCategory category) { return getCategoryFlags() & category; }
			bool m_handled = false;
	};

	/* =========================================== *
	 * printable event
	 * =========================================== */
	inline std::ostream& operator<< (std::ostream& os, Event& event) { os << event.toString(); return os; }
	
	/* =========================================== *
	 * window closed event
	 * =========================================== */
	class WindowClosedEvent: public Event {
		public:
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
			EVENT_CLASS_TYPE(WindowClosed)
	};

	/* =========================================== *
	 * window resized
	 * =========================================== */
	class WindowResizedEvent: public Event {
		public:
			WindowResizedEvent(unsigned int width, unsigned int height): m_width(width), m_height(height) {}
			inline unsigned int getWidth() { return m_width; }
			inline unsigned int getHeight() { return m_height; }
			virtual std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": ( " << m_width << " ; " << m_height << " )";
				return ss.str();
			}
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
			EVENT_CLASS_TYPE(WindowResized)
		private:
			unsigned int m_width;
			unsigned int m_height;
	};

	/* =========================================== *
	 * key related event
	 * =========================================== */
	class KeyEvent: public Event {
		public:
			inline int getKeyCode() { return m_keyCode; }
			EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)
		protected:
			KeyEvent(int keyCode): m_keyCode(keyCode) {}
			int m_keyCode;
	};

	/* =========================================== *
	 * key pressed
	 * =========================================== */
	class KeyPressedEvent: public KeyEvent {
		public:
			KeyPressedEvent(int keyCode, int repeatCount): KeyEvent(keyCode), m_repeatCount(repeatCount) { InputsStates::setKey(keyCode, true); }
			inline int getRepeatCount() { return m_repeatCount; }
			virtual std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": " << m_keyCode << " (x" << m_repeatCount << ")";
				return ss.str();
			}
			EVENT_CLASS_TYPE(KeyPressed)
		private:
			int m_repeatCount;
	};

	/* =========================================== *
	 * key released
	 * =========================================== */
	class KeyReleasedEvent: public KeyEvent {
		public:
			KeyReleasedEvent(int keyCode): KeyEvent(keyCode) { InputsStates::setKey(keyCode, false); }
			virtual std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": " << m_keyCode;
				return ss.str();
			}
			EVENT_CLASS_TYPE(KeyReleased)
	};
	
	/* =========================================== *
	 * mouse button related event
	 * =========================================== */
	class MouseButtonEvent: public Event {
		public:
			inline int getButton() { return m_button; }
			EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
			virtual std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": " << m_button;
				return ss.str();
			}
		protected:
			MouseButtonEvent(int button): m_button(button) {}
			int m_button;
	};

	/* =========================================== *
	 * mouse button pressed
	 * =========================================== */
	class MouseButtonPressedEvent: public MouseButtonEvent {
		public:
			MouseButtonPressedEvent(int button): MouseButtonEvent(button) { InputsStates::setMouseButton(button, true); }
			EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/* =========================================== *
	 * mouse button released
	 * =========================================== */
	class MouseButtonReleasedEvent: public MouseButtonEvent {
		public:
			MouseButtonReleasedEvent(int button): MouseButtonEvent(button) { InputsStates::setMouseButton(button, false); }
			EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	/* =========================================== *
	 * mouse moved
	 * =========================================== */
	class MouseMovedEvent: public Event {
		public:
			MouseMovedEvent(int x, int y): m_x(x), m_y(y) { InputsStates::setCursorPos(x, y); }
			inline int getX() { return m_x; }
			inline int getY() { return m_y; }
			virtual std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": ( " << m_x << " ; " << m_y << " )";
				return ss.str();
			}
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
			EVENT_CLASS_TYPE(MouseMoved)
		private:
			int m_x;
			int m_y;
	};

	/* =========================================== *
	 * mouse scrolled
	 * =========================================== */
	class MouseScrolledEvent: public Event {
		public:
			MouseScrolledEvent(float dx, float dy): m_dx(dx), m_dy(dy) {}
			inline float getDx() { return m_dx; }
			inline float getDy() { return m_dy; }
			virtual std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": ( " << m_dx << " ; " << m_dy << " )";
				return ss.str();
			}
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
			EVENT_CLASS_TYPE(MouseScrolled)
		private:
			float m_dx;
			float m_dy;
	};

	/* =========================================== *
	 * event dispatcher
	 * =========================================== */
	template<typename T>
	bool dispatch(Event& event, std::function<bool(T&)> func) {
		if (event.getEventType() == T::getStaticType()) {
			event.m_handled = func(*(T*)&event);
			return true;
		}
		return false;
	}
}

#endif
