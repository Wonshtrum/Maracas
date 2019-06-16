#pragma once

/* =========================================== *
 * simple binary search in array
 * =========================================== */
#include "Core.h"

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
	}
}
