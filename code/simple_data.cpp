
#include "simple_data.h"
#include "box.h"
#include "pair.h"
#include "list.h"

#include "doublex.h"
#include "fuzzy_number.h"

#include "token_parsing.h"

int simple_data::get_type_size(type_identifier the_type_id)
{
	if (the_type_id == TI_VOID)
	{
		return 0;
	}
	else if (the_type_id == TI_MEM_BLOCK)
	{
		return 0;
	}
	else if (the_type_id == TI_BOOL)
	{
		return sizeof(bool);
	}
	else if (the_type_id == TI_UCHAR)
	{
		return sizeof(uchar);
	}
	else if (the_type_id == TI_UINT16)
	{
		return sizeof(uint16);
	}
	else if (the_type_id == TI_INT)
	{
		return sizeof(int);
	}
	else if (the_type_id == TI_DOUBLE)
	{
		return sizeof(double);
	}
	else if (the_type_id == TI_DOUBLEX)
	{
		return sizeof(doublex);
	}
	else if (the_type_id == TI_FUZZY)
	{
		return sizeof(fuzzy_double);
	}
	else if (the_type_id == TI_STRING)
	{
		return sizeof(string);
	}
	else if (the_type_id == TI_POINTER)
	{
		return sizeof(void*);
	}
	else if (the_type_id == TI_BOX)
	{
		return sizeof(box);
	}
	else if (the_type_id == TI_PAIR)
	{
		return sizeof(data_pair);
	}
	else if (the_type_id == TI_LIST)
	{
		return sizeof(list);
	}
	return 0;
}

void simple_data::copy_new_data(const void* new_data)
{
	switch (the_type_id)
	{
	case TI_VOID:
		{
			the_data = NULL;
		}
		break;
	case TI_MEM_BLOCK:
		{
			the_data = new uchar[the_type_size];
			for (uint16 i = 0; i < the_type_size; i++)
			{
				*(reinterpret_cast<uchar*>(the_data)+i) = *(reinterpret_cast<const uchar*>(new_data)+i);
			}
		}
		break;
	case TI_BOOL:
		{
			the_data = new bool(*reinterpret_cast<const bool*>(new_data));
		}
		break;
	case TI_UCHAR:
		{
			the_data = new uchar(*reinterpret_cast<const uchar*>(new_data));
		}
		break;
	case TI_UINT16:
		{
			the_data = new uint16(*reinterpret_cast<const uint16*>(new_data));
		}
		break;
	case TI_INT:
		{
			the_data = new int(*reinterpret_cast<const int*>(new_data));
		}
		break;
	case TI_DOUBLE:
		{
			the_data = new double(*reinterpret_cast<const double*>(new_data));
		}
		break;
	case TI_DOUBLEX:
		{
			the_data = new doublex(*reinterpret_cast<const doublex*>(new_data));
		}
		break;
	case TI_FUZZY:
		{
			the_data = new fuzzy_double(*reinterpret_cast<const fuzzy_double*>(new_data));
		}
		break;
	case TI_STRING:
		{
			the_data = new string(*reinterpret_cast<const string*>(new_data));
		}
		break;
	case TI_POINTER:
		{
			typedef void* VOID_PTR;
			the_data = new void*(*reinterpret_cast<const VOID_PTR*>(new_data));
		}
		break;
	case TI_BOX:
		{
			the_data = new box(*reinterpret_cast<const box*>(new_data));
		}
		break;
	case TI_PAIR:
		{
			the_data = new data_pair(*reinterpret_cast<const data_pair*>(new_data));
		}
		break;
	case TI_LIST:
		{
			the_data = new list(*reinterpret_cast<const list*>(new_data));
		}
		break;
	}
}

void simple_data::fill_with_0()
{
	switch (the_type_id)
	{
	case TI_VOID:
		{
			the_data = NULL;
		}
		break;
	case TI_MEM_BLOCK:
		{
			the_data = new uchar[the_type_size];
			for (uint16 i = 0; i < the_type_size; i++)
			{
				*(reinterpret_cast<uchar*>(the_data)+i) = 0;
			}
		}
		break;
	case TI_BOOL:
		{
			the_data = new bool(false);
		}
		break;
	case TI_UCHAR:
		{
			the_data = new uchar(0);
		}
		break;
	case TI_UINT16:
		{
			the_data = new uint16(0);
		}
		break;
	case TI_INT:
		{
			the_data = new int(0);
		}
		break;
	case TI_DOUBLE:
		{
			the_data = new double(0.0);
		}
		break;
	case TI_DOUBLEX:
		{
			the_data = new doublex(0.0);
		}
		break;
	case TI_FUZZY:
		{
			the_data = new fuzzy_double(0.0);
		}
		break;
	case TI_STRING:
		{
			the_data = new string();
		}
		break;
	case TI_POINTER:
		{
			the_data = new void*();
		}
		break;
	case TI_BOX:
		{
			the_data = new box();
		}
		break;
	case TI_PAIR:
		{
			the_data = new data_pair();
		}
		break;
	case TI_LIST:
		{
			the_data = new list();
		}
		break;
	}
}

void simple_data::copy(const simple_data* existing_data)
{
	the_type_id = existing_data->the_type_id;
	the_type_size = existing_data->the_type_size;
	copy_new_data(existing_data->the_data);
}

void simple_data::clear()
{
	switch (the_type_id)
	{
	case TI_VOID:
		break;
	case TI_MEM_BLOCK:
		{
			delete[the_type_size] reinterpret_cast<uchar*>(the_data);
		}
		break;
	case TI_BOOL:
		{
			delete reinterpret_cast<bool*>(the_data);
		}
		break;
	case TI_UCHAR:
		{
			delete reinterpret_cast<uchar*>(the_data);
		}
		break;
	case TI_UINT16:
		{
			delete reinterpret_cast<uint16*>(the_data);
		}
		break;
	case TI_INT:
		{
			delete reinterpret_cast<int*>(the_data);
		}
		break;
	case TI_DOUBLE:
		{
			delete reinterpret_cast<double*>(the_data);
		}
		break;
	case TI_DOUBLEX:
		{
			delete reinterpret_cast<doublex*>(the_data);
		}
		break;
	case TI_FUZZY:
		{
			delete reinterpret_cast<fuzzy_double*>(the_data);
		}
		break;
	case TI_STRING:
		{
			delete reinterpret_cast<string*>(the_data);
		}
		break;
	case TI_POINTER:
		{
			delete reinterpret_cast<void**>(the_data);
		}
		break;
	case TI_BOX:
		{
			delete reinterpret_cast<box*>(the_data);
		}
		break;
	case TI_PAIR:
		{
			delete reinterpret_cast<data_pair*>(the_data);
		}
		break;
	case TI_LIST:
		{
			delete reinterpret_cast<list*>(the_data);
		}
		break;
	}
}

void simple_data::read_from_stream(istream& input)
{
	string curr_token = read_token(input);
	if (curr_token == "0")
	{
		the_type_id = TI_VOID;
		the_type_size = 0;
		the_data = NULL;
	}
	else if (curr_token == "TI_MEM_BLOCK")
	{
		the_type_id = TI_MEM_BLOCK;
		curr_token = read_token(input);
		the_type_size = stoi(curr_token);
		the_type_size = (the_type_size >= 1) ? the_type_size : 1;
		the_data = new uchar[the_type_size];
		input >> std::ws;
		input.read(reinterpret_cast<char*>(the_data),the_type_size);
	}
	else if (curr_token == "bool")
	{
		the_type_id = TI_BOOL;
		the_type_size = sizeof(bool);
		curr_token = read_token(input);
		the_data = new bool((bool) stoi(curr_token));
	}
	else if (curr_token == "c")
	{
		the_type_id = TI_UCHAR;
		the_type_size = sizeof(uchar);
		curr_token = read_token(input);
		the_data = new uchar(curr_token[0]);
	}
	else if (curr_token == "uint16")
	{
		the_type_id = TI_UINT16;
		the_type_size = sizeof(uint16);
		curr_token = read_token(input);
		the_data = new uint16((uint16) stoi(curr_token));
	}
	else if (curr_token == "i")
	{
		the_type_id = TI_INT;
		the_type_size = sizeof(int);
		curr_token = read_token(input);
		the_data = new int(stoi(curr_token));
	}
	else if (curr_token == "d")
	{
		the_type_id = TI_DOUBLE;
		the_type_size = sizeof(double);
		curr_token = read_token(input);
		the_data = new double(stod(curr_token));
	}
	else if (curr_token == "dx")
	{
		the_type_id = TI_DOUBLEX;
		the_type_size = sizeof(doublex);
		the_data = new doublex(input);
	}
	else if (curr_token == "fuzzy")
	{
		the_type_id = TI_FUZZY;
		the_type_size = sizeof(fuzzy_double);
		the_data = new fuzzy_double(input);
	}
	else if (curr_token == "s")
	{
		the_type_id = TI_STRING;
		the_type_size = sizeof(string);
		curr_token = read_token(input);
		the_data = new string(curr_token);
	}
	else if (curr_token == "box")
	{
		the_type_id = TI_BOX;
		the_type_size = sizeof(box);
		the_data = new box(input);
	}
	else if (curr_token == "pair")
	{
		the_type_id = TI_PAIR;
		the_type_size = sizeof(data_pair);
		the_data = new data_pair(input);
	}
	else if (curr_token == "list")
	{
		the_type_id = TI_LIST;
		the_type_size = sizeof(list);
		the_data = new list(input);
	}
	else
	{
		throw get_c_str(string("simple_data::read_from_stream: ") + curr_token + string(" is not a valid type identifier"));
	}
}

// ***********************************************************

simple_data::simple_data()
{
	the_type_id = TI_VOID;
	the_type_size = 0;
	the_data = NULL;
}

simple_data::simple_data(type_identifier new_type_id, int new_type_size)
{
	the_type_id = new_type_id;
	if (the_type_id != TI_MEM_BLOCK)
	{
		the_type_size = get_type_size(the_type_id);
	}
	else
	{
		the_type_size = new_type_size;
	}
	fill_with_0();
}

simple_data::simple_data(type_identifier new_type_id, int new_type_size, const void* new_data) 
{
	the_type_id = new_type_id;
	if (the_type_id != TI_MEM_BLOCK)
	{
		the_type_size = get_type_size(the_type_id);
	}
	else
	{
		the_type_size = new_type_size;
	}
	copy_new_data(new_data);
}

simple_data::simple_data(istream& input)
{
	read_from_stream(input);
}

simple_data::simple_data(const simple_data& existing_data)
{
	copy(&existing_data);
}

simple_data::simple_data(const simple_data* existing_data)
{
	copy(existing_data);
}

simple_data& simple_data::operator=(const simple_data& existing_data)
{
	clear();
	copy(&existing_data);
	return *this;
}

simple_data::~simple_data()
{
	clear();
}

// *************************************************************

type_identifier simple_data::get_type_id() const 
{
	return the_type_id;
}

int simple_data::get_type_size() const 
{
	return the_type_size;
}

void* simple_data::get_the_data() const 
{
	return the_data;
}

// *************************************************************

short simple_data::compare(const simple_data& data_2) const 
{
	if ((int) the_type_id < (int) data_2.the_type_id)
	{
		return -1;
	}
	if ((int) the_type_id > (int) data_2.the_type_id)
	{
		return +1;
	}
	switch (the_type_id)
	{
	case TI_VOID:
		{
			return 0;
		}
		break;
	case TI_MEM_BLOCK:
		{
			int i = 0;
			while (true)
			{
				if (*(reinterpret_cast<uchar*>(the_data)+i) < *(reinterpret_cast<uchar*>(data_2.the_data)+i))
				{
					return -1;
				}
				else if (*(reinterpret_cast<uchar*>(the_data)+i) > *(reinterpret_cast<uchar*>(data_2.the_data)+i))
				{
					return +1;
				}
				i++;
				if ((i >= the_type_size) && (i < data_2.the_type_size)) // *this is shorter
				{
					return -1;
				}
				else if ((i < the_type_size) && (i >= data_2.the_type_size)) // *this is longer
				{
					return +1;
				}
				else if ((i >= the_type_size) && (i >= data_2.the_type_size)) // *this == element_2
				{
					return 0;
				}
			}
		}
		break;
	case TI_BOOL:
		{
			if (*reinterpret_cast<bool*>(the_data) < *reinterpret_cast<bool*>(data_2.the_data))
			{
				return -1;
			}
			else if (*reinterpret_cast<bool*>(the_data) > *reinterpret_cast<bool*>(data_2.the_data))
			{
				return +1;
			}
			else 
			{
				return 0;
			}
		}
		break;
	case TI_UCHAR:
		{
			if (*reinterpret_cast<uchar*>(the_data) < *reinterpret_cast<uchar*>(data_2.the_data))
			{
				return -1;
			}
			else if (*reinterpret_cast<uchar*>(the_data) > *reinterpret_cast<uchar*>(data_2.the_data))
			{
				return +1;
			}
			else 
			{
				return 0;
			}
		}
		break;
	case TI_UINT16:
		{
			if (*reinterpret_cast<uint16*>(the_data) < *reinterpret_cast<uint16*>(data_2.the_data))
			{
				return -1;
			}
			else if (*reinterpret_cast<uint16*>(the_data) > *reinterpret_cast<uint16*>(data_2.the_data))
			{
				return +1;
			}
			else 
			{
				return 0;
			}
		}
		break;
	case TI_INT:
		{
			if (*reinterpret_cast<int*>(the_data) < *reinterpret_cast<int*>(data_2.the_data))
			{
				return -1;
			}
			else if (*reinterpret_cast<int*>(the_data) > *reinterpret_cast<int*>(data_2.the_data))
			{
				return +1;
			}
			else 
			{
				return 0;
			}
		}
		break;
	case TI_DOUBLE:
		{
			if (*reinterpret_cast<double*>(the_data) < *reinterpret_cast<double*>(data_2.the_data))
			{
				return -1;
			}
			else if (*reinterpret_cast<double*>(the_data) > *reinterpret_cast<double*>(data_2.the_data))
			{
				return +1;
			}
			else 
			{
				return 0;
			}
		}
		break;
	case TI_DOUBLEX:
		{
			return (*reinterpret_cast<doublex*>(the_data)).compare(*reinterpret_cast<doublex*>(data_2.the_data));
		}
		break;
	case TI_FUZZY:
		{
			return (*reinterpret_cast<fuzzy_double*>(the_data)).compare(*reinterpret_cast<fuzzy_double*>(data_2.the_data));
		}
		break;
	case TI_STRING:
		{
			if (*reinterpret_cast<string*>(the_data) < *reinterpret_cast<string*>(data_2.the_data))
			{
				return -1;
			}
			else if (*reinterpret_cast<string*>(the_data) > *reinterpret_cast<string*>(data_2.the_data))
			{
				return +1;
			}
			else 
			{
				return 0;
			}
		}
		break;
	case TI_POINTER:
		{
			if (*reinterpret_cast<void**>(the_data) < *reinterpret_cast<void**>(data_2.the_data))
			{
				return -1;
			}
			else if (*reinterpret_cast<void**>(the_data) > *reinterpret_cast<void**>(data_2.the_data))
			{
				return +1;
			}
			else
			{
				return 0;
			}
		}
		break;
	case TI_BOX:
		{
			return (*reinterpret_cast<box*>(the_data)).compare(*reinterpret_cast<box*>(data_2.the_data));
		}
		break;
	case TI_PAIR:
		{
			return (*reinterpret_cast<data_pair*>(the_data)).compare(*reinterpret_cast<data_pair*>(data_2.the_data));
		}
		break;
	case TI_LIST:
		{
			return (*reinterpret_cast<list*>(the_data)).compare(*reinterpret_cast<list*>(data_2.the_data));
		}
		break;
	}
	return 0;
}

bool simple_data::operator==(const simple_data& data_2) const 
{
	return (compare(data_2) == 0);
}

bool simple_data::operator!=(const simple_data& data_2) const 
{
	return (compare(data_2) != 0);
}

bool simple_data::operator<(const simple_data& data_2) const 
{
	return (compare(data_2) < 0);
}

bool simple_data::operator>(const simple_data& data_2) const 
{
	return (compare(data_2) > 0);
}

bool simple_data::operator<=(const simple_data& data_2) const 
{
	return (compare(data_2) <= 0);
}

bool simple_data::operator>=(const simple_data& data_2) const 
{
	return (compare(data_2) >= 0);
}

// *************************************************************

string simple_data::print() const 
{
	string output = "";
	switch (the_type_id)
	{
	case TI_VOID:
		{
			output += "0";
		}
		break;
	case TI_MEM_BLOCK:
		{
			output += "TI_SIMPLE_STRUCTURE ";
			output += (to_string(the_type_size) + " ");
			output += string(reinterpret_cast<char*>(the_data),the_type_size);
		}
		break;
	case TI_BOOL:
		{
			output += "bool ";
			output += to_string(*reinterpret_cast<bool*>(the_data));
		}
		break;
	case TI_UCHAR:
		{
			output += "c ";
			output += *reinterpret_cast<uchar*>(the_data);
		}
		break;
	case TI_UINT16:
		{
			output += "uint16 ";
			output += to_string(*reinterpret_cast<uint16*>(the_data));
		}
		break;
	case TI_INT:
		{
			output += "i ";
			output += to_string(*reinterpret_cast<int*>(the_data));
		}
		break;
	case TI_DOUBLE:
		{
			output += "d ";
			output += to_string(*reinterpret_cast<double*>(the_data));
		}
		break;
	case TI_DOUBLEX:
		{
			output += "dx ";
			output += (*reinterpret_cast<doublex*>(the_data)).print();
		}
		break;
	case TI_FUZZY:
		{
			output += "fuzzy ";
			output += (*reinterpret_cast<fuzzy_double*>(the_data)).print();
		}
		break;
	case TI_STRING:
		{
			output += "s ";
			output += encode_string(*reinterpret_cast<string*>(the_data));
		}
		break;
	case TI_POINTER:
		{
			output += "pointer ";
		}
		break;
	case TI_BOX:
		{
			output += "box ";
			output += (*reinterpret_cast<box*>(the_data)).print();
		}
		break;
	case TI_PAIR:
		{
			output += "pair ";
			output += (*reinterpret_cast<data_pair*>(the_data)).print();
		}
		break;
	case TI_LIST:
		{
			output += "list ";
			output += (*reinterpret_cast<list*>(the_data)).print();
		}
		break;
	}
	return output;
}

// **********************************************************

bool simple_data::read_bool() const
{
	if (the_type_id != TI_BOOL)
	{
		throw "simple_data: invalid read_bool attempt.\n";
	}
	return *reinterpret_cast<bool*>(the_data);
}

simple_data simple_data::write_bool(bool new_bool)
{
	return simple_data(TI_BOOL,sizeof(bool),&new_bool);
}

uchar simple_data::read_uchar() const
{
	if (the_type_id != TI_UCHAR)
	{
		throw "simple_data: invalid read_uchar attempt.\n";
	}
	return *reinterpret_cast<uchar*>(the_data);
}

simple_data simple_data::write_uchar(uchar new_uchar)
{
	return simple_data(TI_UCHAR,sizeof(uchar),&new_uchar);
}

uint16 simple_data::read_uint16() const
{
	if (the_type_id != TI_UINT16)
	{
		throw "simple_data: invalid read_uint16 attempt.\n";
	}
	return *reinterpret_cast<uint16*>(the_data);
}

simple_data simple_data::write_uint16(uint16 new_uint16)
{
	return simple_data(TI_UINT16,sizeof(uint16),&new_uint16);
}

int simple_data::read_int() const
{
	if (the_type_id != TI_INT)
	{
		throw "simple_data: invalid read_int attempt.\n";
	}
	return *reinterpret_cast<int*>(the_data);
}

simple_data simple_data::write_int(int new_int)
{
	return simple_data(TI_INT,sizeof(int),&new_int);
}

double simple_data::read_double() const
{
	if (the_type_id != TI_DOUBLE)
	{
		throw "simple_data: invalid read_double attempt.\n";
	}
	return *reinterpret_cast<double*>(the_data);
}

simple_data simple_data::write_double(double new_double)
{
	return simple_data(TI_DOUBLE,sizeof(double),&new_double);
}

doublex simple_data::read_doublex() const
{
	if (the_type_id != TI_DOUBLEX)
	{
		throw "simple_data: invalid read_doublex attempt.\n";
	}
	return *reinterpret_cast<doublex*>(the_data);
}

simple_data simple_data::write_doublex(doublex new_doublex)
{
	return simple_data(TI_DOUBLEX,sizeof(doublex),&new_doublex);
}

fuzzy_double simple_data::read_fuzzy_double() const
{
	if (the_type_id != TI_FUZZY)
	{
		throw "simple_data: invalid read_fuzzy_double attempt.\n";
	}
	return *reinterpret_cast<fuzzy_double*>(the_data);
}

simple_data simple_data::write_fuzzy_double(fuzzy_double new_fuzzy_double)
{
	return simple_data(TI_FUZZY,sizeof(fuzzy_double),&new_fuzzy_double);
}

string simple_data::read_string() const
{
	if (the_type_id != TI_STRING)
	{
		throw "simple_data: invalid read_string attempt.\n";
	}
	return *reinterpret_cast<string*>(the_data);
}

simple_data simple_data::write_string(string new_string)
{
	return simple_data(TI_STRING,sizeof(string),&new_string);
}

void* simple_data::read_pointer() const
{
	if (the_type_id != TI_POINTER)
	{
		throw "simple_data: invalid read_pointer attempt.\n";
	}
	return *reinterpret_cast<void**>(the_data);
}

simple_data simple_data::write_pointer(void* new_pointer)
{
	return simple_data(TI_POINTER,sizeof(void*),&new_pointer);
}

box simple_data::read_box() const
{
	if (the_type_id != TI_BOX)
	{
		throw "simple_data: invalid read_box attempt.\n";
	}
	return *reinterpret_cast<box*>(the_data);
}

simple_data simple_data::write_box(const box& new_box)
{
	return simple_data(TI_BOX,sizeof(box),&new_box);
}

data_pair simple_data::read_pair() const
{
	if (the_type_id != TI_PAIR)
	{
		throw "simple_data: invalid read_pair attempt.\n";
	}
	return *reinterpret_cast<data_pair*>(the_data);
}

simple_data simple_data::write_pair(const data_pair& new_pair)
{
	return simple_data(TI_PAIR,sizeof(data_pair),&new_pair);
}

list simple_data::read_list() const
{
	if (the_type_id != TI_LIST)
	{
		throw "simple_data: invalid read_list attempt.\n";
	}
	return *reinterpret_cast<list*>(the_data);
}

simple_data simple_data::write_list(const list& new_list)
{
	return simple_data(TI_LIST,sizeof(list),&new_list);
}



