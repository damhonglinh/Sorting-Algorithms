#ifndef PT_UTILS
#define PT_UTILS

/** Generate a random int between 0 and 2^(nbits-1)
  * @param nbits the number of bits to use
  */
int pt_rand(int nbits);

/** Generate an array containing random int.
  * The array will be allocated on the heap.
  * @param length the length of the array
  * @param nbits the number of bits to pass to pt_rand
  */
int * gen_rand_int_array(int length, int nbits);

/** Copy the source array into the destination.
  * Assumes there is enough space in the destination to hold everything.
  * @param src the source array
  * @param dst the destination array
  * @param length the number of elements to copy
  */
void copy_int_array(int src[], int dst[], int length);

/** Clone an array.
  * The cloned array will be allocated on the heap.
  * @param a the array to clone
  * @param length the length of the array
  */
int * clone_int_array(int a[], int length);

/** Print an array of int.
  * @param a the array to print
  * @param length the length of the array
  */
void print_int_array(int a[], int length);


#endif
