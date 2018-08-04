

#include "endless_array_p.h"

#define ARR_BLOCK_SIZE 1
#define BLOCK_SIZE 50

int endless_array_p::num_of_available_arrays = 0;
int* endless_array_p::array_lengths = NULL;
void*** endless_array_p::the_arrays = NULL;
int endless_array_p::curr_array_index = 0;

// *********************************************************

void endless_array_p::finger_entry(int arr_index, int index)
{
	if (arr_index >= num_of_available_arrays)
	{
		// Extend the array of arrays.
		int new_num_of_arrays = ((arr_index+1) / ARR_BLOCK_SIZE + 1) * ARR_BLOCK_SIZE;
		int* new_array_of_lengths = new int[new_num_of_arrays];
		void*** new_array_of_pointers = new void**[new_num_of_arrays];
		for (int i = 0; i < num_of_available_arrays; i++)
		{
			new_array_of_lengths[i] = array_lengths[i];
			new_array_of_pointers[i] = the_arrays[i];
		}
		for (int i = num_of_available_arrays; i < new_num_of_arrays; i++)
		{
			new_array_of_lengths[i] = BLOCK_SIZE;
			new_array_of_pointers[i] = new void*[new_array_of_lengths[i]];
		}
		if (array_lengths != NULL)
		{
			delete[] array_lengths;
		}
		if (the_arrays != NULL)
		{
			delete[] the_arrays;
		}
		num_of_available_arrays = new_num_of_arrays;
		array_lengths = new_array_of_lengths;
		the_arrays = new_array_of_pointers;
	}
	if (index >= array_lengths[arr_index])
	{
		// Extend an array.
		int new_length = ((index+1) / BLOCK_SIZE + 1) * BLOCK_SIZE;
		void** new_array = new void*[new_length];
		for (int i = 0; i < array_lengths[arr_index]; i++)
		{
			new_array[i] = the_arrays[arr_index][i];
		}
		for (int i = array_lengths[arr_index]; i < new_length; i++)
		{
			new_array[i] = 0;
		}
		delete[] the_arrays[arr_index];
		array_lengths[arr_index] = new_length;
		the_arrays[arr_index] = new_array;
	}
}

// *********************************************************

void endless_array_p::goto_array(int arr_index)
{
	finger_entry(arr_index,0);
	curr_array_index = arr_index;
}

void endless_array_p::next_array()
{
	finger_entry(curr_array_index+1,0);
	curr_array_index++;
}

void endless_array_p::previous_array()
{
	if (curr_array_index > 0)
	{
		curr_array_index--;
	}
}

int endless_array_p::get_array_index()
{
	return curr_array_index;
}

void* endless_array_p::get_ptr(int index)
{
	return the_arrays[curr_array_index][index];
}

void endless_array_p::set_ptr(int index, void* new_ptr)
{
	the_arrays[curr_array_index][index] = new_ptr;
}

#undef ARR_BLOCK_SIZE
#undef BLOCK_SIZE 