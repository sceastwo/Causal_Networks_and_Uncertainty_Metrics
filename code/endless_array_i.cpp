

#include "endless_array_i.h"

#define LAYER_BLOCK_SIZE 1
#define X_BLOCK_SIZE 50
#define Y_BLOCK_SIZE 50

int endless_array_i::num_of_layers = 0;
int* endless_array_i::x_ranges = NULL;
int** endless_array_i::y_ranges = NULL;
char*** endless_array_i::the_arrays = NULL;
int endless_array_i::curr_layer = 0;

// *********************************************************

void endless_array_i::finger_entry(int layer, int x, int y)
{
	if (layer >= num_of_layers)
	{
		int new_num_of_layers = ((layer+1) / LAYER_BLOCK_SIZE + 1) * LAYER_BLOCK_SIZE;
		int* new_x_ranges = new int[new_num_of_layers];
		int** new_y_ranges = new int*[new_num_of_layers];
		char*** new_arrays = new char**[new_num_of_layers];
		for (int i = 0; i < num_of_layers; i++)
		{
			new_x_ranges[i] = x_ranges[i];
			new_y_ranges[i] = y_ranges[i];
			new_arrays[i] = the_arrays[i];
		}
		for (int i = num_of_layers; i < new_num_of_layers; i++)
		{
			new_x_ranges[i] = 0;
			new_y_ranges[i] = new int[0];
			new_arrays[i] = new char*[0];
		}
		delete[num_of_layers] x_ranges;
		delete[num_of_layers] y_ranges;
		delete[num_of_layers] the_arrays;
		num_of_layers = new_num_of_layers;
		x_ranges = new_x_ranges;
		y_ranges = new_y_ranges;
		the_arrays = new_arrays;
	}
	if (x >= x_ranges[layer])
	{
		int new_x_range = ((x+1) / X_BLOCK_SIZE + 1) * X_BLOCK_SIZE;
		int* new_y_ranges = new int[new_x_range];
		char** new_arrays = new char*[new_x_range];
		for (int i = 0; i < x_ranges[layer]; i++)
		{
			new_y_ranges[i] = y_ranges[layer][i];
			new_arrays[i] = the_arrays[layer][i];
		}
		for (int i = x_ranges[layer]; i < new_x_range; i++)
		{
			new_y_ranges[i] = 0;
			new_arrays[i] = new char[0];
		}
		delete[x_ranges[layer]] y_ranges[layer];
		delete[x_ranges[layer]] the_arrays[layer];
		x_ranges[layer] = new_x_range;
		y_ranges[layer] = new_y_ranges;
		the_arrays[layer] = new_arrays;
	}
	if (y >= y_ranges[layer][x])
	{
		int new_y_range = ((y+1) / Y_BLOCK_SIZE + 1) * Y_BLOCK_SIZE;
		char* new_array = new char[new_y_range];
		for (int i = 0; i < y_ranges[layer][x]; i++)
		{
			new_array[i] = the_arrays[layer][x][i];
		}
		for (int i = y_ranges[layer][x]; i < new_y_range; i++)
		{
			new_array[i] = 0;
		}
		delete[y_ranges[layer][x]] the_arrays[layer][x];
		y_ranges[layer][x] = new_y_range;
		the_arrays[layer][x] = new_array;
	}
}

// *********************************************************

void endless_array_i::goto_layer(int layer)
{
	finger_entry(layer,0,0);
	curr_layer = layer;
}

void endless_array_i::next_layer()
{
	finger_entry(curr_layer+1,0,0);
	curr_layer++;
}

void endless_array_i::previous_layer()
{
	if (curr_layer > 0)
	{
		curr_layer--;
	}
}

int endless_array_i::get_layer()
{
	return curr_layer;
}

void endless_array_i::write_data(int x, int y, int data_stride, int data_length, const char* new_data)
{
	finger_entry(curr_layer, x, y+data_stride*(data_length-1));
	for (int i = 0; i < data_length; i++)
	{
		the_arrays[curr_layer][x][y + i*data_stride] = new_data[i];
	}
}

char* endless_array_i::get_ptr(int x, int y)
{
	finger_entry(curr_layer, x, y);
	return the_arrays[curr_layer][x] + y;
}

void endless_array_i::read_data(int x, int y, int data_stride, int data_length, char* output_data)
{
	finger_entry(curr_layer, x, y+data_stride*(data_length-1));
	for (int i = 0; i < data_length; i++)
	{
		output_data[i] = the_arrays[curr_layer][x][y + i*data_stride];
	}
}



#undef LAYER_BLOCK_SIZE
#undef X_BLOCK_SIZE
#undef Y_BLOCK_SIZE