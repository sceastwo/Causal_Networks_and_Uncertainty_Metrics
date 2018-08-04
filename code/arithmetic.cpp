
#include "simple_data.h"
#include "box.h"
#include "pair.h"
#include "list.h"
#include "node.h"
#include "arithmetic.h"

#include "doublex.h"
#include "fuzzy_number.h"

#include "endless_array_i.h"
//#include "endless_array_p.h"

//#include "endless_hash_table_i.h"

#include "token_parsing.h"


bool arith_is_bool(const simple_data& the_data)
{
	return (the_data.get_type_id() == TI_BOOL);
}

bool arith_read_bool(const simple_data& the_data)
{
	if (the_data.get_type_id() == TI_BOOL)
	{
		return the_data.read_bool();
	}
	return false;
}

bool arith_is_uchar(const simple_data& the_data)
{
	return (the_data.get_type_id() == TI_BOOL) || (the_data.get_type_id() == TI_UCHAR);
}

uchar arith_read_uchar(const simple_data& the_data)
{
	if (the_data.get_type_id() == TI_BOOL)
	{
		return (uchar) the_data.read_bool();
	}
	else if (the_data.get_type_id() == TI_UCHAR)
	{
		return the_data.read_uchar();
	}
	return 0;
}

bool arith_is_uint16(const simple_data& the_data)
{
	return (the_data.get_type_id() == TI_BOOL) || (the_data.get_type_id() == TI_UCHAR) || (the_data.get_type_id() == TI_UINT16);
}

uint16 arith_read_uint16(const simple_data& the_data)
{
	if (the_data.get_type_id() == TI_BOOL)
	{
		return (uint16) the_data.read_bool();
	}
	else if (the_data.get_type_id() == TI_UCHAR)
	{
		return (uint16) the_data.read_uchar();
	}
	else if (the_data.get_type_id() == TI_UINT16)
	{
		return the_data.read_uint16();
	}
	return 0;
}

bool arith_is_int(const simple_data& the_data)
{
	return (the_data.get_type_id() == TI_BOOL) || (the_data.get_type_id() == TI_UCHAR) || (the_data.get_type_id() == TI_UINT16) || (the_data.get_type_id() == TI_INT);
}

int arith_read_int(const simple_data& the_data)
{
	if (the_data.get_type_id() == TI_BOOL)
	{
		return (int) the_data.read_bool();
	}
	else if (the_data.get_type_id() == TI_UCHAR)
	{
		return (int) the_data.read_uchar();
	}
	else if (the_data.get_type_id() == TI_UINT16)
	{
		return (int) the_data.read_uint16();
	}
	else if (the_data.get_type_id() == TI_INT)
	{
		return the_data.read_int();
	}
	return 0;
}

bool arith_is_double(const simple_data& the_data)
{
	return (the_data.get_type_id() == TI_BOOL) || (the_data.get_type_id() == TI_UCHAR) || (the_data.get_type_id() == TI_UINT16) || (the_data.get_type_id() == TI_INT)
		|| (the_data.get_type_id() == TI_DOUBLE);
}

double arith_read_double(const simple_data& the_data)
{
	if (the_data.get_type_id() == TI_BOOL)
	{
		return (double) the_data.read_bool();
	}
	else if (the_data.get_type_id() == TI_UCHAR)
	{
		return (double) the_data.read_uchar();
	}
	else if (the_data.get_type_id() == TI_UINT16)
	{
		return (double) the_data.read_uint16();
	}
	else if (the_data.get_type_id() == TI_INT)
	{
		return (double) the_data.read_int();
	}
	else if (the_data.get_type_id() == TI_DOUBLE)
	{
		return the_data.read_double();
	}
	return 0;
}

bool arith_is_doublex(const simple_data& the_data)
{
	return (the_data.get_type_id() == TI_BOOL) || (the_data.get_type_id() == TI_UCHAR) || (the_data.get_type_id() == TI_UINT16) || (the_data.get_type_id() == TI_INT)
		|| (the_data.get_type_id() == TI_DOUBLE) || (the_data.get_type_id() == TI_DOUBLEX);
}

doublex arith_read_doublex(const simple_data& the_data)
{
	if (the_data.get_type_id() == TI_BOOL)
	{
		return doublex((double) the_data.read_bool());
	}
	else if (the_data.get_type_id() == TI_UCHAR)
	{
		return doublex((double) the_data.read_uchar());
	}
	else if (the_data.get_type_id() == TI_UINT16)
	{
		return doublex((double) the_data.read_uint16());
	}
	else if (the_data.get_type_id() == TI_INT)
	{
		return doublex((double) the_data.read_int());
	}
	else if (the_data.get_type_id() == TI_DOUBLE)
	{
		return doublex(the_data.read_double());
	}
	else if (the_data.get_type_id() == TI_DOUBLEX)
	{
		return the_data.read_doublex();
	}
	return doublex(0.0);
}

bool arith_is_fuzzy(const simple_data& the_data)
{
	return (the_data.get_type_id() == TI_BOOL) || (the_data.get_type_id() == TI_UCHAR) || (the_data.get_type_id() == TI_UINT16) || (the_data.get_type_id() == TI_INT)
		|| (the_data.get_type_id() == TI_DOUBLE) || (the_data.get_type_id() == TI_DOUBLEX) || (the_data.get_type_id() == TI_FUZZY);
}

fuzzy_double arith_read_fuzzy(const simple_data& the_data)
{
	if (the_data.get_type_id() == TI_BOOL)
	{
		return fuzzy_double((double) the_data.read_bool());
	}
	else if (the_data.get_type_id() == TI_UCHAR)
	{
		return fuzzy_double((double) the_data.read_uchar());
	}
	else if (the_data.get_type_id() == TI_UINT16)
	{
		return fuzzy_double((double) the_data.read_uint16());
	}
	else if (the_data.get_type_id() == TI_INT)
	{
		return fuzzy_double((double) the_data.read_int());
	}
	else if (the_data.get_type_id() == TI_DOUBLE)
	{
		return fuzzy_double(the_data.read_double());
	}
	else if (the_data.get_type_id() == TI_DOUBLEX)
	{
		return fuzzy_double(the_data.read_doublex());
	}
	else if (the_data.get_type_id() == TI_FUZZY)
	{
		return the_data.read_fuzzy_double();
	}
	return fuzzy_double(0.0);
}


simple_data binary_op(const simple_data& data_1, const simple_data& data_2, binary_op_code the_op_code)
{
	simple_data data_2_modified; // the negative or inverse of data_2 is computed if the operation is subtraction or division. 
	if (the_op_code == OP_SUBTRACTION)
	{
		data_2_modified = unary_op(data_2,OP_NEGATIVE,simple_data());
	}
	else if (the_op_code == OP_DIVISION)
	{
		data_2_modified = unary_op(data_2,OP_INVERSE,simple_data());
	}
	else
	{
		data_2_modified = data_2;
	}

	// Default cases if one operand is void:
	if (data_1.get_type_id() == TI_VOID)
	{
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION) || (the_op_code == OP_MAX))
		{
			return data_2_modified;
		}
		else
		{
			return simple_data();
		}
	}
	if (data_2.get_type_id() == TI_VOID)
	{
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION) || (the_op_code == OP_MAX))
		{
			return data_1;
		}
		else
		{
			return simple_data();
		}
	}

	if ((data_1.get_type_id() == TI_MEM_BLOCK) && (data_2.get_type_id() == TI_MEM_BLOCK))
	{
		int new_type_size = 0;
		int max_new_type_size = ((data_1.get_type_size() >= data_2.get_type_size()) ? data_1.get_type_size() : data_2.get_type_size()) + 1;
		uchar* new_result = new uchar[max_new_type_size];
		while ((new_type_size < data_1.get_type_size()) || (new_type_size < data_2.get_type_size()))
		{
			uchar byte_1, byte_2;
			if (new_type_size < data_1.get_type_size())
			{
				byte_1 = *(reinterpret_cast<const uchar*>(data_1.get_the_data()) + new_type_size);
			}
			else
			{
				byte_1 = 0;
			}
			if (new_type_size < data_2.get_type_size())
			{
				byte_2 = *(reinterpret_cast<const uchar*>(data_2.get_the_data()) + new_type_size);
			}
			else
			{
				byte_2 = 0;
			}
			if (the_op_code == OP_ADDITION)
			{
				new_result[new_type_size] = byte_1 + byte_2;
			}
			else if (the_op_code == OP_MULTIPLICATION)
			{
				new_result[new_type_size] = byte_1 * byte_2;
			}
			else if (the_op_code == OP_SUBTRACTION)
			{
				new_result[new_type_size] = byte_1 - byte_2;
			}
			else if (the_op_code == OP_DIVISION)
			{
				new_result[new_type_size] = byte_1;
			}
			else if (the_op_code == OP_MAX)
			{
				new_result[new_type_size] = MAX(byte_1,byte_2);
			}
			else
			{
				new_result[new_type_size] = MIN(byte_1,byte_2);
			}
			new_type_size++;
		}
		simple_data result = simple_data(TI_MEM_BLOCK, new_type_size, new_result);
		delete[] new_result;
		return result;
	}

	if (arith_is_bool(data_1) && arith_is_bool(data_2_modified))
	{
		bool arg_1 = arith_read_bool(data_1);
		bool arg_2 = arith_read_bool(data_2_modified);
		bool result;
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION) || (the_op_code == OP_MAX))
		{
			result = arg_1 || arg_2;
		}
		else
		{
			result = arg_1 && arg_2;
		}
		return simple_data(TI_BOOL, sizeof(bool), &result);
	}
	else if (arith_is_uchar(data_1) && arith_is_uchar(data_2_modified))
	{
		uchar arg_1 = arith_read_uchar(data_1);
		uchar arg_2 = arith_read_uchar(data_2_modified);
		uchar result;
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION))
		{
			result = arg_1 + arg_2;
		}
		else if ((the_op_code == OP_MULTIPLICATION) || (the_op_code == OP_DIVISION))
		{
			result = arg_1 * arg_2;
		}
		else if (the_op_code == OP_MAX)
		{
			result = MAX(arg_1,arg_2);
		}
		else
		{
			result = MIN(arg_1,arg_2);
		}
		return simple_data(TI_UCHAR, sizeof(uchar), &result);
	}
	else if (arith_is_uint16(data_1) && arith_is_uint16(data_2_modified))
	{
		uint16 arg_1 = arith_read_uint16(data_1);
		uint16 arg_2 = arith_read_uint16(data_2_modified);
		uint16 result;
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION))
		{
			result = arg_1 + arg_2;
		}
		else if ((the_op_code == OP_MULTIPLICATION) || (the_op_code == OP_DIVISION))
		{
			result = arg_1 * arg_2;
		}
		else if (the_op_code == OP_MAX)
		{
			result = MAX(arg_1,arg_2);
		}
		else
		{
			result = MIN(arg_1,arg_2);
		}
		return simple_data(TI_UINT16, sizeof(uint16), &result);
	}
	else if (arith_is_int(data_1) && arith_is_int(data_2_modified))
	{
		int arg_1 = arith_read_int(data_1);
		int arg_2 = arith_read_int(data_2_modified);
		int result;
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION))
		{
			result = arg_1 + arg_2;
		}
		else if ((the_op_code == OP_MULTIPLICATION) || (the_op_code == OP_DIVISION))
		{
			result = arg_1 * arg_2;
		}
		else if (the_op_code == OP_MAX)
		{
			result = MAX(arg_1,arg_2);
		}
		else
		{
			result = MIN(arg_1,arg_2);
		}
		return simple_data(TI_INT, sizeof(int), &result);
	}
	else if (arith_is_double(data_1) && arith_is_double(data_2_modified))
	{ // Floating point types:
		double arg_1 = arith_read_double(data_1);
		double arg_2 = arith_read_double(data_2_modified);
		double result;
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION))
		{
			result = arg_1 + arg_2;
		}
		else if ((the_op_code == OP_MULTIPLICATION) || (the_op_code == OP_DIVISION))
		{
			result = arg_1 * arg_2;
		}
		else if (the_op_code == OP_MAX)
		{
			result = MAX(arg_1,arg_2);
		}
		else
		{
			result = MIN(arg_1,arg_2);
		}
		return simple_data(TI_DOUBLE, sizeof(double), &result);
	}
	else if (arith_is_doublex(data_1) && arith_is_doublex(data_2_modified))
	{
		doublex arg_1 = arith_read_doublex(data_1);
		doublex arg_2 = arith_read_doublex(data_2_modified);
		doublex result;
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION))
		{
			result = arg_1 + arg_2;
		}
		else if ((the_op_code == OP_MULTIPLICATION) || (the_op_code == OP_DIVISION))
		{
			result = arg_1 * arg_2;
		}
		else if (the_op_code == OP_MAX)
		{
			result = MAX(arg_1,arg_2);
		}
		else
		{
			result = MIN(arg_1,arg_2);
		}
		return simple_data(TI_DOUBLEX, sizeof(doublex), &result);
	}
	else if (arith_is_fuzzy(data_1) && arith_is_fuzzy(data_2_modified))
	{
		fuzzy_double arg_1 = arith_read_fuzzy(data_1);
		fuzzy_double arg_2 = arith_read_fuzzy(data_2_modified);
		fuzzy_double result;
		if ((the_op_code == OP_ADDITION) || (the_op_code == OP_SUBTRACTION))
		{
			result = arg_1 + arg_2;
		}
		else if ((the_op_code == OP_MULTIPLICATION) || (the_op_code == OP_DIVISION))
		{
			result = arg_1 * arg_2;
		}
		else if (the_op_code == OP_MAX)
		{
			result = MAX(arg_1,arg_2);
		}
		else
		{
			result = MIN(arg_1,arg_2);
		}
		return simple_data(TI_FUZZY, sizeof(fuzzy_double), &result);
	}

	// Container types:

	if ((data_1.get_type_id() == TI_BOX) && (data_2.get_type_id() == TI_BOX))
	{
		box arg_1 = data_1.read_box();
		box arg_2 = data_2.read_box();
		box result(binary_op(arg_1.get_data(),arg_2.get_data(),the_op_code));
		return simple_data(TI_BOX, sizeof(box), &result);
	}
	else if ((data_1.get_type_id() == TI_PAIR) && (data_2.get_type_id() == TI_PAIR))
	{
		data_pair arg_1 = data_1.read_pair();
		data_pair arg_2 = data_2.read_pair();
		data_pair result(binary_op(arg_1.get_data_1(),arg_2.get_data_1(),the_op_code),binary_op(arg_1.get_data_2(),arg_2.get_data_2(),the_op_code));
		return simple_data(TI_PAIR, sizeof(data_pair), &result);
	}
	else if ((data_1.get_type_id() == TI_LIST) && (data_2.get_type_id() == TI_LIST))
	{
		list arg_1 = data_1.read_list();
		list arg_2 = data_2.read_list();

		int new_list_size = MAX(arg_1.get_list_size(),arg_2.get_list_size());

		list result(new_list_size);

		for (int i = 0; i < new_list_size; i++)
		{
			simple_data entry_1;
			if (i < arg_1.get_list_size())
			{
				entry_1 = arg_1[i];
			}
			simple_data entry_2;
			if (i < arg_2.get_list_size())
			{
				entry_2 = arg_2[i];
			}
			result.set_entry(i,binary_op(entry_1,entry_2,the_op_code));
		}

		return simple_data(TI_LIST, sizeof(list), &result);
	}

	// Default return value:
	return data_1;
}

simple_data operator+(const simple_data& data_1, const simple_data& data_2)
{
	return binary_op(data_1, data_2, OP_ADDITION);
}

simple_data operator*(const simple_data& data_1, const simple_data& data_2)
{
	return binary_op(data_1, data_2, OP_MULTIPLICATION);
}

simple_data operator-(const simple_data& data_1, const simple_data& data_2)
{
	return binary_op(data_1, data_2, OP_SUBTRACTION);
}

simple_data operator/(const simple_data& data_1, const simple_data& data_2)
{
	return binary_op(data_1, data_2, OP_DIVISION);
}

node* node_binary_op(node* root_node_1, node* root_node_2, bool max_degree_flag, binary_op_code the_op_code)
{
	node::tracker_index++;

	node* product_root_node = node::product_subgraph(root_node_1,root_node_2, max_degree_flag);
	
	node::set_node_tracker(product_root_node);
	while (!node::end_of_trace())
	{
		if (!node::has_backtracked())
		{
			node* curr_node = node::get_node_tracker();
			data_pair the_operand_pair = curr_node->get_the_data().read_pair();
			simple_data operand_1 = the_operand_pair.get_data_1();
			simple_data operand_2 = the_operand_pair.get_data_2();

			curr_node->set_the_data(binary_op(operand_1,operand_2,the_op_code));
		}

		node::advance_node_tracker();
	}

	node::tracker_index--;

	return product_root_node;
}


simple_data unary_op(const simple_data& the_data, unary_op_code the_op_code, const simple_data& extra_data)
{
	if (the_data.get_type_id() == TI_VOID)
	{
		return simple_data();
	}
	else if (the_data.get_type_id() == TI_MEM_BLOCK)
	{
		return the_data;
	}
	else if (the_data.get_type_id() == TI_BOOL)
	{
		bool arg = the_data.read_bool();
		if (the_op_code == OP_NEGATIVE || the_op_code == OP_INVERSE)
		{
			bool result = !arg;
			return simple_data(TI_BOOL, sizeof(bool), &result);
		}
		else
		{
			bool result = (extra_data.read_int() == 0) ? false : arg;
			return simple_data(TI_BOOL, sizeof(bool), &result);
		}
	}
	else if (the_data.get_type_id() == TI_UCHAR)
	{
		uchar arg = the_data.read_uchar();
		if (the_op_code == OP_NEGATIVE)
		{
			uchar result = !arg;
			return simple_data(TI_UCHAR, sizeof(uchar), &result);
		}
		else if (the_op_code == OP_INVERSE)
		{
			double result = 1.0/((double) arg);
			return simple_data(TI_DOUBLE, sizeof(double), &result);
		}
		else
		{
			int result = extra_data.read_int() * ((int) arg);
			return simple_data(TI_INT, sizeof(int), &result);
		}
	}
	else if (the_data.get_type_id() == TI_UINT16)
	{
		uint16 arg = the_data.read_uint16();
		if (the_op_code == OP_NEGATIVE)
		{
			int result = -((int) arg);
			return simple_data(TI_INT, sizeof(int), &result);
		}
		else if (the_op_code == OP_INVERSE)
		{
			double result = 1.0/((double) arg);
			return simple_data(TI_DOUBLE, sizeof(double), &result);
		}
		else
		{
			int result = extra_data.read_int() * ((int) arg);
			return simple_data(TI_INT, sizeof(int), &result);
		}
	}
	else if (the_data.get_type_id() == TI_INT)
	{
		int arg = the_data.read_int();
		if (the_op_code == OP_NEGATIVE)
		{
			int result = -arg;
			return simple_data(TI_INT, sizeof(int), &result);
		}
		else if (the_op_code == OP_INVERSE)
		{
			double result = 1.0/((double) arg);
			return simple_data(TI_DOUBLE, sizeof(double), &result);
		}
		else
		{
			int result = extra_data.read_int() * arg;
			return simple_data(TI_INT, sizeof(int), &result);
		}
	}
	else if (the_data.get_type_id() == TI_DOUBLE)
	{
		double arg = the_data.read_double();
		double result; 
		if (the_op_code == OP_NEGATIVE)
		{
			result = -arg;
		}
		else if (the_op_code == OP_INVERSE)
		{
			result = 1.0/arg;
		}
		else 
		{
			result = ((double) extra_data.read_int()) * arg;
		}
		return simple_data(TI_DOUBLE, sizeof(double), &result);
	}
	else if (the_data.get_type_id() == TI_DOUBLEX)
	{
		doublex arg = the_data.read_doublex();
		doublex result; 
		if (the_op_code == OP_NEGATIVE)
		{
			result = -arg;
		}
		else if (the_op_code == OP_INVERSE)
		{
			result = arg.inv();
		}
		else
		{
			result = doublex((double) extra_data.read_int()) * arg;
		}
		return simple_data(TI_DOUBLEX, sizeof(doublex), &result);
	}
	else if (the_data.get_type_id() == TI_FUZZY)
	{
		fuzzy_double arg = the_data.read_fuzzy_double();
		fuzzy_double result; 
		if (the_op_code == OP_NEGATIVE)
		{
			result = -arg;
		}
		else if (the_op_code == OP_INVERSE)
		{
			result = fuzzy_double(1.0)/arg;
		}
		else
		{
			result = fuzzy_double((double) extra_data.read_int()) * arg;
		}
		return simple_data(TI_FUZZY, sizeof(fuzzy_double), &result);
	}
	else if (the_data.get_type_id() == TI_STRING)
	{
		return the_data;
	}
	else if (the_data.get_type_id() == TI_BOX)
	{
		box arg = the_data.read_box();
		box result = box(unary_op(arg.get_data(),the_op_code,extra_data));
		return simple_data(TI_BOX, sizeof(box), &result);
	}
	else if (the_data.get_type_id() == TI_PAIR)
	{
		data_pair arg = the_data.read_pair();
		data_pair result = data_pair(unary_op(arg.get_data_1(),the_op_code,extra_data), unary_op(arg.get_data_2(),the_op_code,extra_data));
		return simple_data(TI_PAIR, sizeof(data_pair), &result);
	}
	else if (the_data.get_type_id() == TI_LIST)
	{
		list arg = the_data.read_list();
		list result(arg.get_list_size());
		for (int i = 0; i < arg.get_list_size(); i++)
		{
			result.set_entry(i, unary_op(arg[i],the_op_code,extra_data));
		}
		return simple_data(TI_LIST, sizeof(list), &result);
	}

	// Default return value:
	return the_data;
}

simple_data operator-(const simple_data& the_data)
{
	return unary_op(the_data, OP_NEGATIVE, simple_data());
}

simple_data inv(const simple_data& the_data)
{
	return unary_op(the_data, OP_INVERSE, simple_data());
}

simple_data operator*(int factor, const simple_data& the_data)
{
	return unary_op(the_data, OP_INTEGER_MULTIPLICATION, simple_data(TI_INT,sizeof(int),&factor));
}

simple_data operator*(const simple_data& the_data, int factor)
{
	return unary_op(the_data, OP_INTEGER_MULTIPLICATION, simple_data(TI_INT,sizeof(int),&factor));
}

node* node_unary_op(node* root_node, unary_op_code the_op_code, const simple_data& extra_data)
{
	node::tracker_index++;

	node* copy_root_node = node::copy_subgraph(root_node);
	
	node::set_node_tracker(copy_root_node);
	while (!node::end_of_trace())
	{
		if (!node::has_backtracked())
		{
			node* curr_node = node::get_node_tracker();
			simple_data the_operand = curr_node->get_the_data();

			curr_node->set_the_data(unary_op(the_operand,the_op_code,extra_data));
		}

		node::advance_node_tracker();
	}

	node::tracker_index--;

	return copy_root_node;
}

node* marginalize(node* root_node, int depth, bool keep_degree_flag)
{
	node::tracker_index++;

	node* copy_root_node = node::copy_subgraph(root_node);

	node::set_node_tracker(copy_root_node);
	while (!node::end_of_trace())
	{ // MARGINALIZE 
		if (!node::has_backtracked())
		{ // MARGINALIZE 
			node* curr_node = node::get_node_tracker();
			if (curr_node->get_depth() == depth && curr_node->get_degree() > 1)
			{
				int the_degree = curr_node->get_degree();

				// Calculate the marginal sum:
				node* marginal_sum = curr_node->get_child(0);
				for (int i = 1; i < curr_node->get_degree(); i++)
				{
					node* new_marginal_sum = node_binary_op(marginal_sum,curr_node->get_child(i),false,OP_ADDITION);
					node::destroy_subgraph(marginal_sum);
					marginal_sum = new_marginal_sum;
				}

				// Disconnect the children:
				while (curr_node->get_degree() > 0)
				{
					node* targeted_child = curr_node->get_child(curr_node->get_degree()-1);
					curr_node->delete_child(curr_node->get_degree()-1);
					node::destroy_subgraph(targeted_child);
				}

				// Connect the sum:
				if (keep_degree_flag)
				{
					for (int i = 0; i < the_degree; i++)
					{
						curr_node->add_child(marginal_sum);
					}
				}
				else
				{
					curr_node->add_child(marginal_sum);
				}
			} // MARGINALIZE 
		} // MARGINALIZE 

		node::advance_node_tracker();
	}

	node::tracker_index--;

	return copy_root_node;
}

node* condition(node* root_node, int depth, int child_index, bool keep_degree_flag)
{
	node::tracker_index++;

	node* copy_root_node = node::copy_subgraph(root_node);

	node::set_node_tracker(copy_root_node);
	while (!node::end_of_trace())
	{ // CONDITION 
		if (!node::has_backtracked())
		{ // CONDITION 
			node* curr_node = node::get_node_tracker();
			if (curr_node->get_depth() == depth)
			{
				if (child_index >= curr_node->get_degree())
				{
					throw "condition: invalid child_index\n";
				}

				int the_degree = curr_node->get_degree();

				// Disconnect all children except the chosen child:
				for (int i = curr_node->get_degree()-1; i >= 0; i--)
				{
					if (i != child_index)
					{
						node* targeted_child = curr_node->get_child(i);
						curr_node->delete_child(i);
						node::destroy_subgraph(targeted_child);
					}
				}

				// Replicate the pointer if needed:
				if (keep_degree_flag)
				{
					for (int i = 0; i < the_degree-1; i++)
					{
						curr_node->add_child(curr_node->get_child(0));
					}
				}
			} // CONDITION 
		} // CONDITION 

		node::advance_node_tracker();
	}

	node::tracker_index--;

	return copy_root_node;
}


node* DS_binary_op(node* root_node_1, node* root_node_2, bool max_degree_flag, binary_op_code the_op_code)
{
	node* resultant_root_node = new node(binary_op(root_node_1->get_the_data(),root_node_2->get_the_data(),the_op_code));

	for (int i = 0; i < root_node_1->get_degree(); i++)
	{
		node* curr_child_1 = root_node_1->get_child(i);
		for (int j = 0; j < root_node_2->get_degree(); j++)
		{
			node* curr_child_2 = root_node_2->get_child(j);

			resultant_root_node->add_child(node_binary_op(curr_child_1,curr_child_2,max_degree_flag,the_op_code));
		}
	}

	return resultant_root_node;
}

node* DS_collapse(node* root_node)
{
	node* condensed_root = node::condense(root_node);

	simple_data total_weight;
	list new_weights;
	list new_focal_elements;

	for (int i = 0; i < condensed_root->get_degree(); i++)
	{ // DS_collapse
		simple_data curr_weight = condensed_root->get_child(i)->get_the_data();
		node* curr_focal_element;
		try
		{
			curr_focal_element = condensed_root->get_child(i)->get_child(0);
		}
		catch (char* error)
		{
			throw "DS_collapse: focal element not found.\n";
		}

		if (new_focal_elements.find(write_node_ptr(curr_focal_element))) // Does the focal element already exist?
		{ // DS_collapse
			int found_index = list::get_query_index();
			new_weights.set_entry(found_index,new_weights[found_index] + curr_weight);
			total_weight = total_weight + curr_weight;
		}
		else // A new focal element has been found:
		{ // DS_collapse
			// Is the new focal element_empty?
			bool is_empty_flag = true;

			node::tracker_index++;

			node::set_node_tracker(curr_focal_element);
			while (!node::end_of_trace())
			{ // DS_collapse
				if (!node::has_backtracked())
				{
					node* curr_node = node::get_node_tracker();
					if (curr_node->get_the_data() == simple_data::write_bool(true))
					{
						is_empty_flag = false;
						break;
					}
				}
				node::advance_node_tracker();
			}

			node::tracker_index--;

			if (!is_empty_flag)
			{ // DS_collapse
				new_weights.append(curr_weight);
				new_focal_elements.append(write_node_ptr(curr_focal_element));
				total_weight = total_weight + curr_weight;
			}
		}
	}

	for (int i = 0; i < new_weights.get_list_size(); i++) // Normalize the weights
	{ // DS_collapse
		new_weights.set_entry(i,new_weights[i]/total_weight);
	}

	// Create the new root node:
	node* resultant_root_node = new node(condensed_root->get_the_data());
	for (int i = 0; i < new_weights.get_list_size(); i++)
	{ // DS_collapse
		node* new_focal_element_node = new node(new_weights[i]);
		new_focal_element_node->add_child(read_node_ptr(new_focal_elements[i]));
		resultant_root_node->add_child(new_focal_element_node);
	}

	node::destroy_subgraph(condensed_root);

	return resultant_root_node;
}


