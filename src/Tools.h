#ifndef MRC_TOOLS_H
#define MRC_TOOLS_H
#pragma once
#include <iostream>
//ENDHEAD
namespace Maracas {
	/* =========================================== *
	 * simple binary search in array
	 * =========================================== */
	template<typename T>
	int binarySearch(const T* array, int count, T& element) {
		int lowerBound = 0;
		int upperBound = count-1;
		int middle;
		while (lowerBound <= upperBound) {
			middle = (lowerBound + upperBound)/2;
			if (array[middle] < element) {
				lowerBound = middle + 1;
			} else if (array[middle] > element) {
				upperBound = middle - 1;
			} else {
				return middle;
			}
		}
		//todo... something nicer
		return -1;
	}

	/* =========================================== *
	 * linked list
	 * =========================================== */
	template<typename T>
	struct listElement {
		listElement<T>* previous;
		T* element;
		listElement<T>* next;
		listElement(T* _element): previous(nullptr), element(_element), next(nullptr) {}
		listElement(listElement<T>* _previous, T* _element, listElement<T>* next): previous(_previous), element(_element), next(next) {}
	};

	template<typename T>
	class LinkedList {
		public:
			LinkedList():m_count(0) {
				head = tail = current = nullptr;
			}
			virtual ~LinkedList() {
				listElement<T>* tmp = tail;
				while (tail) {
					tmp = tail->next;
					delete tail->element;
					delete tail;
					tail = tmp;
				}
			}
			void display() {
				listElement<T>* tmp = tail;
				while (tmp) {
					std::cout << *(tmp->element) << " ; ";
					tmp = tmp->next;
				}
				std::cout << std::endl;
			}
			virtual void insertAfter(T* element) {
				if (m_count++) {
					current->next = new listElement<T>(current,element,current->next);
					if (current == head) {
						head = current->next;
					}
				} else {
					head = tail = current = new listElement<T>(element);
				}
			}
			virtual void insertBefore(T* element) {
				if (m_count++) {
					current->previous = new listElement<T>(current->previous, element, current);
					if (current == tail) {
						tail = current->previous;
					}
				} else {
					head = tail = current = new listElement<T>(element);
				}
			}
			virtual void insertBegin(T* element) {
				if (m_count++) {
					tail->previous = new listElement<T>(nullptr,element,tail);
					tail = tail->previous;
				} else {
					head = tail = current = new listElement<T>(element);
				}
			}
			virtual void insertEnd(T* element) {
				if (m_count++) {
					head->next = new listElement<T>(head,element,nullptr);
					head = head->next;
				} else {
					head = tail = current = new listElement<T>(element);
				}
			}
			virtual T* next() {
				current = current->next;
				return current->element;
			}
			virtual T* previous() {
				current = current->previous;
				return current->element;
			}
			virtual T* popBegin() {
				listElement<T>* tmp = tail;
				T* popped = tmp->element;
				tail = tail->next;
				delete tmp;
				if (tail) {
					tail->previous = nullptr;
				} else {
					head = current = nullptr;
				}
				m_count--;
				return popped;
			}
			virtual T* popEnd() {
				listElement<T>* tmp = head;
				T* popped = tmp->element;
				head = head->previous;
				delete tmp;
				if (head) {
					head->next = nullptr;
				} else {
					tail = current = nullptr;
				}
				m_count--;
				return popped;
			}
			virtual T* pop() {
				listElement<T>* newCurrent = nullptr;
				T* popped = current->element;
				if (current->previous) {
					current->previous->next = current->next;
					newCurrent = current->previous;
				} else {
					tail = current->next;
				}
				if (current->next) {
					current->next->previous = current->previous;
					newCurrent = current->next;
				} else {
					head = current->previous;
				}
				listElement<T>* tmp = current;
				current = newCurrent;
				delete tmp;
				m_count--;
				return popped;
			}
			virtual bool empty() {
				return m_count==0;
			}
			virtual inline T* getCurrent() { return current->element; }
			virtual inline T* getTail() { return tail->element; }
			virtual inline T* getHead() { return head->element; }
			virtual inline void begin() { current = tail; }
			virtual inline void end() { current = head; }
			virtual inline int getCount() { return m_count; }
		protected:
			int m_count;
			listElement<T>* tail;
			listElement<T>* head;
			listElement<T>* current;
	};

	template<typename T>
	class SmartPointer {
		public:
			SmartPointer(): m_element(nullptr), m_count(nullptr) {}
			SmartPointer(T* element): m_element(element), m_count(new int(0)) {}
			SmartPointer(const SmartPointer<T>& other): m_element(other.m_element), m_count(other.m_count) {}
			~SmartPointer() {
				if (m_count && !((*m_count)--)) {
					if (m_element) {
						delete m_element;
					}
					delete m_count;
				}
			}
			inline T* operator->() { return m_element; }
			inline T& operator*() { return *m_element; }
			SmartPointer<T>& operator=(const SmartPointer<T>& other) {
				T* oldElement = m_element;
				int* oldCount = m_count;
				m_element = other.m_element;
				m_count = other.m_count;
				(*m_count)++;
				if (oldCount && !((*oldCount)--)) {
					if (oldElement) {
						delete oldElement;
					}
					delete oldCount;
				}
				return *this;
			}
		protected:
			T* m_element;
			int* m_count;
	};
}

#endif
