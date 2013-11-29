#include "pt_sorting.h"
#include <stdio.h>
#include <stdlib.h>

int temp_swap = 0;
int const THRESHOLD = 16;

static int find_middle(register int start, register int end) {
	//int middle = (end + start) / 2; overflow integer
	return start + (end - start) / 2;
}

static void swap(register int * a, register int * b) {
	temp_swap = *a;
	*a = *b;
	*b = temp_swap;
}

// end is inclusive
int is_sorted(register int * a, register int start, register int end) {
	for (register int i = start; i < end; i++) {
		if (*(a + i) > *(a + i + 1)) {
			//printf("a[i] = %i, a[i + 1] = %i\n", a[i], a[i+1]);
			return 0;
		}
	}
	return 1;
}

/**	The following insertion sort is adapted from
	http://megocode3.wordpress.com/2008/01/28/8/
*/
static void insertion_sort_sub(register int * a, register int start, register int end) {
	register int temp = 0;
	register int j = 0;
	
	for	(register int i = start + 1; i < end; i++) {
		temp = *(a + i);
		j = i - 1;

		while (temp < *(a + j) && (j >= 0)) {
			*(a + j + 1) = *(a + j);
			j--;
		}
		*(a + j + 1) = temp;
	}
}

void insertion_sort(register int a[], register int length) {
	insertion_sort_sub(a, 0, length);
}
// end of insertion sort methods

/*	Inplace Heap Sort Using iterative	*/
/*	Reference:
	http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Heapsort
	http://www2.units.it/ipl/students_area/imm2/files/Numerical_Recipes.pdf
*/
void heap_sort(register int a[], register int length) {
	register int temp;
	register int parent_index = length / 2;
	register int temp_index;
	register int left_child_index;

	while (length != 0) {
		if (parent_index > 0) {
			parent_index--;			
			temp = *(a + parent_index);		
		} else {
			length--;    
            temp = *(a + length);     
            *(a + length) = *(a); 	
		}

		temp_index = parent_index;
        left_child_index = temp_index * 2 + 1;
        while (left_child_index < length) {
    
            if (left_child_index + 1 < length && 
            			*(a + left_child_index + 1) > *(a + left_child_index)) {
                left_child_index++;
            }
            if (*(a + left_child_index) > temp) {
                *(a + temp_index) = *(a + left_child_index);
                temp_index = left_child_index;
                left_child_index = temp_index * 2 + 1;
            } else {
            	break; 
            }
        }
        *(a + temp_index) = temp; 	
	}
}

/**	The following non-inplace merge sort algorithm is adapted from 
	Programming 2 course by Dr. Denis Rinfet
*/
static void merge(register int * a, register const int start, register const int middle, register const int end) {
	register int i;
	register int j;
	register int k = start;
	register const int leftLength = middle - start + 1;
	register const int rightLength = end - middle;
	
	// Using stack to store array to increase performace 
	// But may cause out of memory if the array has too many elements
	int left[leftLength];
	int right[rightLength];
	// using heap to store array is more stable but lower performance
//	register int * left =  malloc(sizeof(int) * leftLength);
//	register int * right = malloc(sizeof(int) * rightLength);
	
	// init left array
	for (i = 0; i < leftLength; i++) {
		*(left + i) = *(a + i + start);
	}
	
	// init right array
	for (j = 0; j < rightLength; j++) {
		*(right + j) = *(a + j + middle + 1);
	}
	
	// reset index
	i = 0;
	j = 0;
	
	// loop until all elements from start to end are sorted
	while (k <= end) {
		// if elements in the left array are less than those of right
		// then put them in array a
		while (i < leftLength && j < rightLength && *(left + i) <= *(right + j)) {
			*(a + k) = *(left + i);
			i++;
			k++;
		}
		
		// same as previous loop
		while (i < leftLength && j < rightLength && *(left + i) >= *(right + j)) {
			*(a + k) = *(right + j);
			j++;
			k++;
		}
		
		// if the left array runs out of elements 
		if (i >= leftLength) {
			// then copy remain elements from right array to array a
			while (j < rightLength) {
				*(a + k) = *(right + j);
				j++;
				k++;
			}
		}
		
		// same as previous if
		if (j >= rightLength) {
			while (i < leftLength) {
				*(a + k) = *(left + i);
				i++;
				k++;
			}
		}
	}
	// if the array is stored in heap, it is essential to free memory
//	free(left);
//	free(right);
}

static void merge_sort_divide(register int * a, register int start, register int end) {
	if (start >= end || is_sorted(a, start, end)) return;

	register const int middle = find_middle(start, end);
	// divide the array into 2 parts
	merge_sort_divide(a, start, middle);
	merge_sort_divide(a, middle + 1, end);

	// merge the 2 parts together
	merge(a, start, middle, end);
}

void merge_sort(register int a[], register int length) {
	if (length < 2) return;
	merge_sort_divide(a, 0, length - 1);
}
// end of merge sort methods

/*	Quick Sort Hoare Partitioning	*/
/*	Reference
	http://en.wikipedia.org/wiki/Quicksort
	http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_sorting.aspx
*/
static int hoare_partition(register int a[], register int left, register int right) {
	//get the 1st element of sub-array as pivot
	register int pivot = left;
	//create temp variabe=le for swapping
	//loop through sub-array to sort *smaller number on the left, *larger number on the right
	while (left < right) {
		// the pivotIndex is just a counter to indicate the number of elements are less than pivot
		// if any elements are less than the pivot, which is at the end index
		if (*(a + left) < *(a + right)) {
			// then swap them with elements at pivotIndex
			swap(a + pivot, a + left);
			pivot++;
		}
		left++;
	}
	//swap the real value of pivot back to its position
	swap((a + pivot), (a + right));
	// return the pivot position
	return pivot;
}

static void quick_sort_h(register int a[], register int left, register int right) {
	//if array is empty or only 1 element sort is redudant
	if	(left < right && !is_sorted(a, left, right)) {
		if ((right - left) < THRESHOLD) {
			insertion_sort_sub(a, left, right + 1);
			return;
		}
		//get the pivot index
		register int pivot_index = hoare_partition(a, left, right);
		//recursively run the sort again with half-left and half-right of the array
		quick_sort_h(a, left, pivot_index - 1);
		quick_sort_h(a, pivot_index + 1, right);	
	}
}

void quick_sort_hoare(register int a[], register int length) {
	quick_sort_h(a, 0, length - 1); 
}
// end of quicksort hoare partition methods

/**	The following quicksort algorithm with median partition is adapted from 
	http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_sorting.aspx
*/
static int find_median_pivot(register int * a, register int start, register int end) {
	register int middle = find_middle(start, end);
	register int pivot;
	
	// find the larger between start and end
	if (*(a + start) > *(a + end)) {
		pivot = start;
	} else {
		pivot = end;
	}
	
	// if the pivot is the largest element 
	if (*(a + pivot) > *(a + middle)) {
		// then change the pivot to middle which is the median
		pivot = middle;
	}
	// else the pivot is already median
	return pivot;
}

static int median_partition(register int * a, register int start, register int end) {
	// find the pivot index which is the median of the start, middle and end of array a
	register int pivotIndex = find_median_pivot(a, start, end);

	// swap the pivot with start
	swap(a + pivotIndex, a + start);
	pivotIndex = start;
	
	while (start < end) {
		// the pivotIndex is just a counter to indicate the number of elements are less than pivot
		// if any elements are less than the pivot, which is at the end index
		if (*(a + start) < *(a + end)) {
			// then swap them with elements at pivotIndex
			swap(a + pivotIndex, a + start);
			pivotIndex++;
		}
		start++;
	}
	
	// swap element at end with element at pivot so that the pivot is really at pivot index
	swap(a + pivotIndex, a + end);
	return pivotIndex;
}

static void quick_sort_median_sub(register int * a, register int start, register int end) {
	if (start < end && !is_sorted(a, start, end)) {
		if ((end - start) < THRESHOLD) {
			insertion_sort_sub(a, start, end + 1);
			return;
		}
		register int pivot = median_partition(a, start, end);// get the pivot index which is already sorted
		quick_sort_median_sub(a, start, pivot - 1);// continues sorting left side of the pivot
		quick_sort_median_sub(a, pivot + 1, end);// continues sorting right side of the pivot
	}
}

void quick_sort_median(register int a[], register int length) {
	quick_sort_median_sub(a, 0, length - 1);// argument end is inclusive
}
// end of quicksort median partition methods

/*	Quick Sort Random Partitioning	*/
/*	Reference
	http://en.wikipedia.org/wiki/Quicksort
	http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_sorting.aspx
*/
static int random_partition(register int a[], register int left, register int right) {
	//get the 1st element of sub-array as pivot
	register int pivot = left;
	//create temp variabe=le for swapping
	//loop through sub-array to sort *smaller number on the left, *larger number on the right
	while (left < right) {
		// the pivotIndex is just a counter to indicate the number of elements are less than pivot
		// if any elements are less than the pivot, which is at the end index
		if (*(a + left) < *(a + right)) {
			// then swap them with elements at pivotIndex
			swap(a + pivot, a + left);
			pivot++;
		}
		left++;
	}
	
	//swap the real value of pivot back to its position
	swap((a + pivot), (a + right));
	// return the pivot position
	return pivot;
}

static void quick_sort_r(register int a[], register int left, register int right) {
	//if array is empty or only 1 element sort is redudant
	if (left < right && !is_sorted(a, left, right)) {
		if ((right - left) < THRESHOLD) {
			insertion_sort_sub(a, left, right + 1);
			return;
		}
		//get the random number
		register int random = rand() % (right - left + 1) + left;
		//swap random to the last
		swap((a + random), (a + right));
	
		//get the pivot index
		register int pivot_index = random_partition(a, left, right);
		
		//recursively run the sort again with half-left and half-right of the array
		quick_sort_r(a, left, pivot_index - 1);
		quick_sort_r(a, pivot_index + 1, right);
	}
}

void quick_sort_random(register int a[], register int length) {
	quick_sort_r(a, 0, length - 1);
}
// end of quicksort random partition methods
