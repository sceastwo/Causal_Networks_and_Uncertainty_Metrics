


#ifndef __ENDLESS_ARRAY_I_H__
#define __ENDLESS_ARRAY_I_H__

typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned long uint32;

//#define MAX(a,b) (a >= b) ? a : b
//#define MIN(a,b) (a <= b) ? a : b

#include <cstdlib>

/* The "endless_array_i" (i = inline) is a series of arrays that are pre-allocated memory that can be utilized by any algorithm that needs them.
Most algorithms, that cannot anticipate upfront about how much memory they will require, can use one of the endless arrays to cache data.
The arrays are extended on an as needs basis, but are never deallocated (except for when the data needs to be moved for extension of the array).
This means that the allocated memory lingers for the next algorithm that needs it.
Each array is "two dimensional", meaning that it is an array of arrays.
In addition, there are many layers of two dimensional arrays to support access from various locations on the function call stack. 
Each function call on the call stack has its own unique two dimensional array.
The arrays themselves are arrays of bytes denoted by type "char". Reinterpret casts to and from char* are required to write and read from the array.*/

class endless_array_i
{
	static int num_of_layers;
	static int* x_ranges; // x is the outer index of the two dimensional array.
	static int** y_ranges;
	static char*** the_arrays;
	static int curr_layer; // Indexes the current array that is being used, not a specific element.

public:
	static void finger_entry(int layer, int x, int y); // Check if entry "index" exists at array "arr_index". If not, extend the array of arrays, or an array to create it. 

	static void goto_layer(int layer);
	static void next_layer();
	static void previous_layer();
	static int get_layer();
	static void write_data(int x, int y, int data_stride, int data_length, const char* new_data); // Write a block of data to the endless array.
	static char* get_ptr(int x, int y);
	static void read_data(int x, int y, int data_stride, int data_length, char* output_data); // Read a block of data from the endless array.
};

#endif



