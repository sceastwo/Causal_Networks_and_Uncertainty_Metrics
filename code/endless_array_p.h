

#ifndef __ENDLESS_ARRAY_P_H__
#define __ENDLESS_ARRAY_P_H__

typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned long uint32;

//#define MAX(a,b) (a >= b) ? a : b
//#define MIN(a,b) (a <= b) ? a : b

#include <cstdlib>

/* The "endless_array_p" (p = pointer) is a series of arrays that are pre-allocated memory that can be utilized by any algorithm that needs them.
Most algorithms, that cannot anticipate upfront about how much memory they will require, can use one of the endless arrays to cache data.
The arrays are extended on an as needs basis, but are never deallocated (except for when the data needs to moved for extension of the array).
This means that the allocated memory lingers for the next algorithm that needs it.
The arrays themselves are arrays of pointers denoted by type "void*". The actual data is referenced by these pointers, and allocation and 
	deallocation of the small amounts of memory referenced by these pointers is the responsibility of the algorithms themselves.*/

class endless_array_p
{
	static int num_of_available_arrays;
	static int* array_lengths;
	static void*** the_arrays;
	static int curr_array_index; // Indexes the current array that is being used, not a specific element.

public:
	static void finger_entry(int arr_index, int index); // Check if entry "index" exists at array "arr_index". If not, extend the array of arrays, or an array to create it. 

	static void goto_array(int arr_index);
	static void next_array();
	static void previous_array();
	static int get_array_index();
	static void* get_ptr(int index);
	static void set_ptr(int index, void* new_ptr);
};

#endif
