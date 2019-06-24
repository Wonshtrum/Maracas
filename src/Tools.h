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
		~listElement() { delete element; }
	};
	template<typename T>
	class LinkedList {
		public:
			LinkedList(T* element):m_count(0) {
				head = tail = current = new listElement<T>(element);
			}
			~LinkedList() {
				listElement<T>* tmp = tail;
				do {
					tmp = tail->next;
					delete tail;
					tail = tmp;
				} while (tail);
			}
			void display() {
				listElement<T>* tmp = tail;
				do {
					std::cout << *(tmp->element) << " ; ";
					tmp = tmp->next;
				} while (tmp);
				std::cout << std::endl;
			}
			void insertAfter(T* element) {
				current->next = new listElement<T>(current,element,current->next);
				if (current == head) {
					head = current->next;
				}
				m_count++;
			}
			void insertBefore(T* element) {
				current->previous = new listElement<T>(current->previous, element, current);
				if (current == tail) {
					tail = current->previous;
				}
			}
			void insertBegin(T* element) {
				tail = new listElement<T>(nullptr,element,tail);
				m_count++;
			}
			void insertEnd(T* element) {
				head->next = new listElement<T>(head,element,nullptr);
				head = head->next;
				m_count++;
			}
			T& next() {
				current = current->next;
				return *(current->element);
			}
			T& previous() {
				current = current->previous;
				return *(current->element);
			}
			void popBegin() {
				tail = tail->next;
				delete tail->previous;
				tail->previous = nullptr;
				m_count--;
			}
			void popEnd() {
				head = head->previous;
				delete head->next;
				head->next = nullptr;
				m_count--;
			}
			void pop() {
				listElement<T>* tmp;
				if (current->previous) {
					current->previous->next = current->next;
					tmp = current->previous;
				} else {
					tail = current->next;
				}
				if (current->next) {
					current->next->previous = current->previous;
					tmp = current->next;
				} else {
					head = current->previous;
				}
				delete current;
				current = tmp;
			}
			inline T& getCurrent() { return *(current->element); }
			inline T& getTail() { return *(tail->element); }
			inline T& getHead() { return *(head->element); }
			inline void begin() { current = tail; }
			inline void end() { current = head; }
		private:
			int m_count;
			listElement<T>* tail;
			listElement<T>* head;
			listElement<T>* current;
	};
}

#endif
