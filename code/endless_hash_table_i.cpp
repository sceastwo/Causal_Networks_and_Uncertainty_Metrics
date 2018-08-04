
#include "endless_hash_table_i.h"

int endless_hash_table_i::input_bus_length = 0;
int endless_hash_table_i::input_length = 0;
char* endless_hash_table_i::input = NULL;

#define INPUT_BLOCK_SIZE 1
#define OUTPUT_BLOCK_SIZE 1

void endless_hash_table_i::finger_input_length()
{
	if (input_length > input_bus_length)
	{
		int new_input_bus_length = (input_length / INPUT_BLOCK_SIZE) * INPUT_BLOCK_SIZE;
		char* new_input = new char[new_input_bus_length];
		for (int i = 0; i < input_bus_length; i++)
		{
			new_input[i] = input[i];
		}
		for (int i = input_bus_length; i < new_input_bus_length; i++)
		{
			new_input[i] = 0;
		}
		delete[] input;
		input_bus_length = new_input_bus_length;
		input = new_input;
	}
}


endless_hash_table_i::hash_node_i::hash_node_i()
{
	local_data_length = 0;
	local_data = new char[0];

	blocking_flag = false;

	child_0 = NULL;
	child_1 = NULL;
}

endless_hash_table_i::hash_node_i::~hash_node_i()
{
	delete[] local_data;

	delete child_0;
	delete child_1;
}

void endless_hash_table_i::hash_node_i::finger_local_data(int index)
{
	if (index >= local_data_length)
	{
		int new_local_data_length = ((index+1) / OUTPUT_BLOCK_SIZE) * OUTPUT_BLOCK_SIZE;
		char* new_local_data = new char[new_local_data_length];
		for (int i = 0; i < local_data_length; i++)
		{
			new_local_data[i] = local_data[i];
		}
		for (int i = local_data_length; i < new_local_data_length; i++)
		{
			new_local_data[i] = 0;
		}
		delete[] local_data;
		local_data_length = new_local_data_length;
		local_data = new_local_data;
	}
}


endless_hash_table_i::hash_node_i* endless_hash_table_i::root_node = NULL;
endless_hash_table_i::hash_node_i* endless_hash_table_i::curr_node = NULL;

void endless_hash_table_i::finger_key()
{
	int level = 0;
	int byte_index = 0;
	int bit_offset = 0;
	char curr_byte = 0;

	if (root_node == NULL)
	{
		root_node = new hash_node_i;
	}

	curr_node = root_node;
	while (level < input_length)
	{
		// Push back the blocking barrier if present:
		if (curr_node->blocking_flag)
		{
			// Wipe the local data:
			for (int i = 0; i < curr_node->local_data_length; i++)
			{
				curr_node->local_data[i] = 0;
			}

			curr_node->blocking_flag = false;
			if (curr_node->child_0 != NULL)
			{
				curr_node->child_0->blocking_flag = true;
			}
			if (curr_node->child_1 != NULL)
			{
				curr_node->child_1->blocking_flag = true;
			}
		}

		// Extract the current bit from the input:
		if (bit_offset == 0)
		{
			curr_byte = input[byte_index];
		}
		else
		{
			curr_byte = curr_byte >> 1;
		}
		bool the_bit = (bool) (curr_byte & 0x01);

		if (!the_bit)
		{
			if (curr_node->child_0 == NULL)
			{
				curr_node->child_0 = new hash_node_i;
			}
			curr_node = curr_node->child_0;
		}
		else
		{
			if (curr_node->child_1 == NULL)
			{
				curr_node->child_1 = new hash_node_i;
			}
			curr_node = curr_node->child_1;
		}

		// Advance to the next bit:
		level++;
		if (bit_offset >= 7)
		{
			byte_index++;
			bit_offset = 0;
		}
		else
		{
			bit_offset++;
		}
	}
}

void endless_hash_table_i::set_input_length(int new_length)
{
	input_length = new_length;
	finger_input_length();
}

void endless_hash_table_i::write_input(int offset, int data_length, char* new_data)
{
	if (offset+data_length > input_length)
	{
		input_length = offset+data_length;
		finger_input_length();
	}

	for (int i = 0; i < data_length; i++)
	{
		input[offset+i] = new_data[i];
	}
}

void endless_hash_table_i::write_output(int offset, int data_length, char* output_data)
{
	if (offset+data_length > curr_node->local_data_length)
	{
		curr_node->finger_local_data(offset+data_length-1);
	}

	for (int i = 0; i < data_length; i++)
	{
		curr_node->local_data[offset+i] = output_data[i];
	}
}

void endless_hash_table_i::read_output(int offset, int data_length, char* output_data)
{
	if (offset+data_length > curr_node->local_data_length)
	{
		curr_node->finger_local_data(offset+data_length-1);
	}

	for (int i = 0; i < data_length; i++)
	{
		output_data[i] = curr_node->local_data[offset+i];
	}
}

void endless_hash_table_i::zero_at_input()
{
	curr_node->blocking_flag = true;
}

#undef INPUT_BLOCK_SIZE 
#undef OUTPUT_BLOCK_SIZE 
