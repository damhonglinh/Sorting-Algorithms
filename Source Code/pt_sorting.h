#ifndef PT_SORTING
#define PT_SORTING

/** Sort an int array using the selection sort algorithm.
  * Sort function number: 1
  * @param a the int array to be sorted in place
  * @param length the length of array a
  */
void selection_sort(int a[], int length);

/** Sort an int array using the insertion sort algorithm.
  * Sort function number: 2
  * @param a the int array to be sorted in place
  * @param length the length of array a
  */
void insertion_sort(int a[], int length);

/** Sort an int array using the merge sort algorithm.
  * Sort function number: 3
  * @param a the int array to be sorted in place
  * @param length the length of array a
  */
void merge_sort(int a[], int length);

/** Sort an int array using the heap sort algorithm.
  * Sort function number: 4
  * @param a the int array to be sorted in place
  * @param length the length of array a
  */
void heap_sort(int a[], int length);

/** Sort an int array using the quicksort algorithm with Hoare's partitioning.
  * Sort function number: 5
  * @param a the int array to be sorted in place
  * @param length the length of array a
  */
void quick_sort_hoare(int a[], int length);

/** Sort an int array using the quicksort algorithm with median partitioning.
  * Sort function number: 6
  * @param a the int array to be sorted in place
  * @param length the length of array a
  */
void quick_sort_median(int a[], int length);

/** Sort an int array using the quicksort algorithm with randomised partitioning.
  * Sort function number: 7
  * @param a the int array to be sorted in place
  * @param length the length of array a
  */
void quick_sort_random(int a[], int length);


#endif
