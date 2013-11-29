#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "pt_utils.h"
#include "pt_sorting.h"
#include "pt_gen_timings.h"

#define BIT_SIZE 16
#define NUMBER_OF_SORTS 6

extern int is_sorted(int * a, int start, int end);

int main(int argc, char * argv[]) {
	if (argc != 3) {
		printf("Please enter 2 arguments!\n");
		printf("The first argument is the length of array to test Insertion Sort\n");
		printf("The second argument is that of array to test the other 6 sorts\n");
		return 0;
	}
	int lengthInsertionSort = atoi(*(argv + 1));
	int lengthOtherSorts = atoi(*(argv + 2));
	
	// init function pointer	
	void (*fp[NUMBER_OF_SORTS])(int *, int);
	*fp = insertion_sort;
	*(fp + 1) = merge_sort;
	*(fp + 2) = heap_sort;
	*(fp + 3) = quick_sort_hoare;
	*(fp + 4) = quick_sort_median;
	*(fp + 5) = quick_sort_random;
	
	char * functionNames[NUMBER_OF_SORTS] = {"insertion_sort", "merge_sort",
								"heap_sort", "quick_sort_hoare",
								"quick_sort_median", "quick_sort_random"};
	
	for (int i = 0; i < NUMBER_OF_SORTS; i++) {
		unsigned int totalTime = 0;		

		int length = 0;
		if (i == 0) 	length = lengthInsertionSort;
		else 			length = lengthOtherSorts;
		
		for (int j = 0; j < 3; j++) {
			// set different seeds for different tests
			srand((j / (i + 1)) * time(NULL)); 
			
			// generate array with length size.
			// each integer is 16-bits size
			int *arr = gen_rand_int_array(length, BIT_SIZE);
			
			totalTime += timing(arr, length, *(fp + i));
			if (!is_sorted(arr, 0, length - 1)) printf("Sorting fails\n");
			free(arr);
		}
		printf("%s,\tsize: %i,\ttime: %i\n",
				*(functionNames + i), length, totalTime / 3);
	}
}

int timing(int * a, int length, void (*pointer)(int *, int)) {
	clock_t startClock = clock();
	
	(* pointer)(a, length);
	clock_t endClock = clock();
	
	return (endClock - startClock) / 1000.0;// convert to ms
}
