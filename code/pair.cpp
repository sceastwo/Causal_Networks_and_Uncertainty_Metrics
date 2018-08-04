
#include "simple_data.h"
#include "pair.h"
#include "list.h"

#include "endless_array_i.h"

#include "token_parsing.h"



// *************************************************

void data_pair::copy(const data_pair* existing_pair)
{
	data_1 = existing_pair->data_1;
	data_2 = existing_pair->data_2;
}

void data_pair::clear()
{
}

void data_pair::read_from_stream(istream& input)
{
	string curr_token;

	curr_token = read_token(input);
	if (curr_token != "<")
	{
		throw "data_pair::read_from_stream: expected \'<\'\n";
	}

	data_1 = simple_data(input);

	curr_token = read_token(input);
	if (curr_token != ",")
	{
		throw "data_pair::read_from_stream: expected \',\'\n";
	}

	data_2 = simple_data(input);

	curr_token = read_token(input);
	if (curr_token != ">")
	{
		throw "data_pair::read_from_stream: expected \'>\'\n";
	}
}

// ************************************************************

data_pair::data_pair()
{
	data_1 = simple_data();
	data_2 = simple_data();
}

data_pair::data_pair(const simple_data& new_data_1, const simple_data& new_data_2)
{
	data_1 = new_data_1;
	data_2 = new_data_2;
}

data_pair::data_pair(istream& input)
{
	read_from_stream(input);
}

data_pair::data_pair(const data_pair& existing_pair)
{
	copy(&existing_pair);
}

data_pair::data_pair(const data_pair* existing_pair)
{
	copy(existing_pair);
}

data_pair& data_pair::operator=(const data_pair& existing_pair)
{
	clear();
	copy(&existing_pair);
	return *this;
}

data_pair::~data_pair()
{
	clear();
}

// ******************************************************

simple_data data_pair::get_data_1() const
{
	return data_1;
}

simple_data data_pair::get_data_2() const
{
	return data_2;
}

void data_pair::set_data_1(const simple_data& new_data_1)
{
	data_1 = new_data_1;
}

void data_pair::set_data_2(const simple_data& new_data_2)
{
	data_2 = new_data_2;
}

// ******************************************************

short data_pair::compare(const data_pair& pair_2) const 
{
	short c = data_1.compare(pair_2.data_1);

	if (c != 0)
	{
		return c;
	}

	c = data_2.compare(pair_2.data_2);

	return c;
}

bool data_pair::operator==(const data_pair& pair_2) const
{
	return (compare(pair_2) == 0);
}

bool data_pair::operator!=(const data_pair& pair_2) const
{
	return (compare(pair_2) != 0);
}

bool data_pair::operator<(const data_pair& pair_2) const
{
	return (compare(pair_2) < 0);
}

bool data_pair::operator>(const data_pair& pair_2) const
{
	return (compare(pair_2) > 0);
}

bool data_pair::operator<=(const data_pair& pair_2) const
{
	return (compare(pair_2) <= 0);
}

bool data_pair::operator>=(const data_pair& pair_2) const
{
	return (compare(pair_2) >= 0);
}

// **********************************************************

string data_pair::print() const
{
	endless_array_i::next_layer();

	int output_length = 0;
	string curr_string = "";

	endless_array_i::write_data(0,output_length,1,2,"< ");
	output_length += 2;

	curr_string = data_1.print();
	endless_array_i::write_data(0,output_length,1,curr_string.length(),curr_string.c_str());
	output_length += curr_string.length();

	endless_array_i::write_data(0,output_length,1,3," , ");
	output_length += 3;

	curr_string = data_2.print();
	endless_array_i::write_data(0,output_length,1,curr_string.length(),curr_string.c_str());
	output_length += curr_string.length();

	endless_array_i::write_data(0,output_length,1,2," >");
	output_length += 2;

	char* printed_c_string = new char[output_length];
	endless_array_i::read_data(0,0,1,output_length,printed_c_string);
	string printed_string = string(printed_c_string,output_length);
	delete[] printed_c_string;

	endless_array_i::previous_layer();

	return printed_string;
}





