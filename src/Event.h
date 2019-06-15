#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"

/* =========================================== *
 * event specific macros
 * =========================================== */
#define EVENT_CLASS_CATEGORY(category) virtual inline int getCategoryFlags() override { return category; }
#define EVENT_CLASS_TYPE(type) inline static eventType getStaticType() { return type; }\
	virtual eventType getEventType() override { return type; }\
	virtual char* getName() override { return #type; }

namespace Maracas {
	/* =========================================== *
	 * event type enumeration
	 * =========================================== */
	enum eventType {
		None = 0,
		WindowClosed, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,	//todo
		KeyPressed, KeyReleased,						//done
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled	//todo
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
		friend class EventDispatcher;
		public:
			inline static eventType getStaticType() { return None; }
			virtual eventType getEventType() = 0;
			virtual char* getName() = 0;
			virtual inline int getCategoryFlags() = 0;
			virtual std::string toString() { return getName(); }
			virtual inline bool isInCategory(eventCategory category) { return getCategoryFlags() & category; }
			virtual inline void setHandled(bool handled) { m_handled = handled; }
		protected:
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
			KeyPressedEvent(int keyCode, int repeatCount): KeyEvent(keyCode), m_repeatCount(repeatCount) {}
			inline int getRepeatCount() { return m_repeatCount; }
			std::string toString() override {
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
			KeyReleasedEvent(int keyCode): KeyEvent(keyCode) {}
			std::string toString() override {
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
		protected:
			MouseButtonEvent(int button): m_button(button) {}
			int m_button;
	};

	/* =========================================== *
	 * mouse button pressed
	 * =========================================== */
	class MouseButtonPressedEvent: public MouseButtonEvent {
		public:
			MouseButtonPressedEvent(int button): MouseButtonEvent(button) {}
			std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": " << m_button;
				return ss.str();
			}
			EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/* =========================================== *
	 * mouse button released
	 * =========================================== */
	class MouseButtonReleasedEvent: public MouseButtonEvent {
		public:
			MouseButtonReleasedEvent(int button): MouseButtonEvent(button) {}
			std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": " << m_button;
				return ss.str();
			}
			EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	/* =========================================== *
	 * mouse moved
	 * =========================================== */
	class MouseMovedEvent: public Event {
		public:
			MouseMovedEvent(int x, int y): m_x(x), m_y(y) {}
			inline int getX() { return m_x; }
			inline int getY() { return m_y; }
			std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": ( " << m_x << " ; " << m_y << " )";
				return ss.str();
			}
		EVENT_CLASS_CATEGORY(EventCategoryMouse)
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
			std::string toString() override {
				std::stringstream ss;
				ss << getName() << ": ( " << m_dx << " ; " << m_dy << " )";
				return ss.str();
			}
			EVENT_CLASS_CATEGORY(EventCategoryMouse)
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
			event.setHandled(func(*(T*)&event));
			return true;
		}
		return false;
	}
}
