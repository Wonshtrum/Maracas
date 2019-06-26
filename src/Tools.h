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
			virtual ~LinkedList() {
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
			virtual void insertAfter(T* element) {
				current->next = new listElement<T>(current,element,current->next);
				if (current == head) {
					head = current->next;
				}
				m_count++;
			}
			virtual void insertBefore(T* element) {
				current->previous = new listElement<T>(current->previous, element, current);
				if (current == tail) {
					tail = current->previous;
				}
			}
			virtual void insertBegin(T* element) {
				tail = new listElement<T>(nullptr,element,tail);
				m_count++;
			}
			virtual void insertEnd(T* element) {
				head->next = new listElement<T>(head,element,nullptr);
				head = head->next;
				m_count++;
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
				T* popped = tail->element;
				tail = tail->next;
				tail->previous = nullptr;
				m_count--;
				return popped;
			}
			virtual T* popEnd() {
				T* popped = head->element;
				head = head->previous;
				head->next = nullptr;
				m_count--;
				return popped;
			}
			virtual T* pop() {
				listElement<T>* tmp;
				T* popped = head->element;
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
				current = tmp;
				return popped;
			}
			virtual inline T* getCurrent() { return current->element; }
			virtual inline T* getTail() { return tail->element; }
			virtual inline T* getHead() { return head->element; }
			virtual inline void begin() { current = tail; }
			virtual inline void end() { current = head; }
		protected:
			int m_count;
			listElement<T>* tail;
			listElement<T>* head;
			listElement<T>* current;
	};
}

#endif
