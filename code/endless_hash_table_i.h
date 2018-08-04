

#ifndef __ENDLESS_HASH_TABLE_H__
#define __ENDLESS_HASH_TABLE_H__

typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned long uint32;

#define MAX(a,b) (a >= b) ? a : b
#define MIN(a,b) (a <= b) ? a : b

#include <cstdlib>

class endless_hash_table_i
{
	static int input_bus_length; // The true length
	static int input_length; // The length used for reading
	static char* input;

	static void finger_input_length();

	class hash_node_i
	{
	public:
		int local_data_length;
		char* local_data;

		bool blocking_flag; // A flag that determines if the contents behind the current node is effectively 0.

		hash_node_i* child_0;
		hash_node_i* child_1;

		hash_node_i();
		~hash_node_i();

		void finger_local_data(int index);
	};
	static hash_node_i* root_node;
	static hash_node_i* curr_node;

	static void finger_key();
public:
	static void set_input_length(int new_length);
	static void write_input(int offset, int data_length, char* new_data);

	static void write_output(int offset, int data_length, char* output_data);
	static void read_output(int offset, int data_length, char* output_data);
	static void zero_at_input(); 
};

#endif


