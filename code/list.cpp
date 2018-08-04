
#include "simple_data.h"
#include "pair.h"
#include "list.h"

#include "endless_array_i.h"
#include "endless_array_p.h"

#include "doublex.h"
#include "fuzzy_number.h"

#include "token_parsing.h"

#define LIST_BLOCK_SIZE 5



list* read_list_ptr(const simple_data& the_data)
{
	return *reinterpret_cast<list**>(the_data.get_the_data());
}

simple_data write_list_ptr(list* new_list_ptr)
{
	return simple_data(TI_MEM_BLOCK,sizeof(list*),&new_list_ptr);
}

// **********************************************************************

void list::copy(const list* existing_list)
{
	the_list_size = existing_list->the_list_size;
	max_list_size = existing_list->max_list_size;
	the_list = new simple_data[max_list_size];
	for (int i = 0; i < the_list_size; i++)
	{
		the_list[i] = existing_list->the_list[i];
	}
}

void list::clear()
{
	delete[] the_list;
}

void list::read_from_stream(istream& input)
{
	string curr_token;

	curr_token = read_token(input);
	the_list_size = stoi(curr_token);
	max_list_size = (the_list_size / LIST_BLOCK_SIZE + 1) * LIST_BLOCK_SIZE;
	the_list = new simple_data[max_list_size];

	curr_token = read_token(input);
	if (curr_token != "<")
	{
		throw "list::read_from_stream: expected \'<\'\n";
	}
	for (int i = 0; i < the_list_size; i++)
	{
		the_list[i] = simple_data(input);

		if (i < the_list_size-1)
		{
			curr_token = read_token(input);
			if (curr_token != ",")
			{
				throw "list::read_from_stream: expected \',\'\n";
			}
		}
	}
	curr_token = read_token(input);
	if (curr_token != ">")
	{
		throw "list::read_from_stream: expected \'>\'\n";
	}
}

// *******************************************************************************

list::list()
{
	the_list_size = 0;
	max_list_size = 0;
	the_list = new simple_data[max_list_size];
}

list::list(const simple_data& new_entry)
{
	the_list_size = 1;
	max_list_size = LIST_BLOCK_SIZE;
	the_list = new simple_data[max_list_size];
	the_list[0] = new_entry;
}

list::list(int new_list_size)
{
	the_list_size = new_list_size;
	max_list_size = (the_list_size / LIST_BLOCK_SIZE + 1) * LIST_BLOCK_SIZE;
	the_list = new simple_data[the_list_size];
	for (int i = 0; i < the_list_size; i++)
	{
		the_list[i] = simple_data();
	}
}

list::list(int new_list_size, const simple_data* new_entries)
{
	the_list_size = new_list_size;
	max_list_size = (the_list_size / LIST_BLOCK_SIZE + 1) * LIST_BLOCK_SIZE;
	the_list = new simple_data[the_list_size];
	for (int i = 0; i < the_list_size; i++)
	{
		the_list[i] = new_entries[i];
	}
}

list::list(istream& input)
{
	read_from_stream(input);
}

list::list(const list& existing_list)
{
	copy(&existing_list);
}

list::list(const list* existing_list)
{
	copy(existing_list);
}

list& list::operator=(const list& existing_list)
{
	clear();
	copy(&existing_list);
	return *this;
}

list::~list()
{
	clear();
}

// ***************************************************

int list::get_list_size() const
{
	return the_list_size;
}

simple_data list::operator[](int index)
{
	finger_entry(index);
	return the_list[index];
}

// ****************************************************

// Find query in the list, and return its membership status. Static variables are updated with the results of the search.
bool list::find(const simple_data& query)
{
	query_found_flag = false;
	query_index = 0;
	multiple_instances_flag = false;
	for (int i = 0; i < the_list_size; i++)
	{
		if (the_list[i] == query)
		{
			if (!query_found_flag)
			{
				query_found_flag = true;
				query_index = i;
			}
			else
			{
				multiple_instances_flag = true;
			}
		}
	}
	return query_found_flag;
}

bool list::query_found_flag = false;

int list::query_index = 0;

bool list::multiple_instances_flag = false;

bool list::get_query_found_flag()
{
	return query_found_flag;
}

int list::get_query_index()
{
	return query_index;
}

bool list::get_multiple_instances_flag()
{
	return multiple_instances_flag;
}

// **************************************************

void list::finger_entry(int index)
{
	if (index >= max_list_size)
	{
		int new_max_size = ((index+1) / LIST_BLOCK_SIZE + 1) * LIST_BLOCK_SIZE;
		simple_data* new_list = new simple_data[new_max_size];
		for (int i = 0; i < the_list_size; i++)
		{
			new_list[i] = the_list[i];
		}
		for (int i = the_list_size; i < new_max_size; i++)
		{
			new_list[i] = simple_data();
		}
		delete[] the_list;

		the_list_size = index + 1;
		max_list_size = new_max_size;
		the_list = new_list;
	}
	else if (index >= the_list_size)
	{
		for (int i = the_list_size; i <= index; i++)
		{
			the_list[i] = simple_data();
		}
		the_list_size = index + 1;
	}
}

void list::resize(int new_size)
{
	finger_entry(new_size-1);
	if (new_size < the_list_size)
	{
		for (int i = new_size; i < the_list_size; i++)
		{
			the_list[i] = simple_data();
		}
	}
	the_list_size = new_size;
}

void list::set_entry(int index, const simple_data& new_entry)
{
	finger_entry(index);
	the_list[index] = new_entry;
}

void list::append(const simple_data& new_entry)
{
	int old_list_size = the_list_size;
	finger_entry(the_list_size);
	the_list[old_list_size] = new_entry;
}

void list::append(const list& new_entries)
{
	int old_list_size = the_list_size;
	finger_entry(the_list_size+new_entries.the_list_size-1);

	for (int i = 0; i < new_entries.the_list_size; i++)
	{
		the_list[old_list_size+i] = new_entries.the_list[i];
	}
}

list* list::list_append(const list& list_of_lists)
{
	int total_list_size = 0;
	for (int i = 0; i < list_of_lists.get_list_size(); i++)
	{
		total_list_size += reinterpret_cast<const list*>(list_of_lists.the_list[i].get_the_data())->the_list_size;
	}
	simple_data* total_list_arr = new simple_data[total_list_size];
	int curr_index = 0;
	for (int i = 0; i < list_of_lists.get_list_size(); i++)
	{
		list* curr_list = reinterpret_cast<list*>(list_of_lists.the_list[i].get_the_data());
		for (int j = 0; j < curr_list->the_list_size; j++)
		{
			total_list_arr[curr_index] = (*curr_list)[j];
			curr_index++;
		}
	}

	list* total_list = new list(total_list_size,total_list_arr);

	delete[] total_list_arr;

	return total_list;
}

void list::insert_element(int index, const simple_data& new_entry)
{
	int old_list_size = the_list_size;
	finger_entry(old_list_size);
	finger_entry(index);

	for (int i = the_list_size-1; i > index; i--) // Decreasing i
	{
		the_list[i] = the_list[i-1];
	}
	the_list[index] = new_entry;
}

void list::delete_element(int index)
{
	int old_list_size = the_list_size;
	finger_entry(index);

	for (int i = index; i < the_list_size-1; i++)
	{
		the_list[i] = the_list[i+1];
	}

	resize(old_list_size-1);
}

list* list::sort(bool remove_duplicates_flag)
{
	int sorted_list_size = 0;
	simple_data* sorted_list_arr = new simple_data[the_list_size];

	bool* used_flags = new bool[the_list_size];
	for (int i = 0; i < the_list_size; i++)
	{
		used_flags[i] = false;
	}
	bool complete_flag = false;
	while (!complete_flag) // SORTING
	{
		complete_flag = true;
		for (int i = 0; i < the_list_size; i++) // SORTING
		{
			if (!used_flags[i]) // Is there an unused entries?
			{
				complete_flag = false;
				break;
			}
		}
		if (!complete_flag) // SORTING Find the next smallest element.
		{
			bool found_flag = false; // Has an unused entry been encountered yet?
			int min_index = 0;
			for (int i = 0; i < the_list_size; i++) // SORTING
			{
				if (!used_flags[i])
				{
					if (found_flag)
					{
						if (the_list[i].compare(the_list[min_index]) < 0)
						{
							min_index = i;
						}
					}
					else
					{
						min_index = i;
						found_flag = true;
					}
				}
			}
			if (remove_duplicates_flag) // If duplicates are being removed, append only one new instance.
			{
				sorted_list_arr[sorted_list_size] = the_list[min_index];
				sorted_list_size++;
			}
			for (int i = 0; i < the_list_size; i++) // SORTING Mark all of the new element as "used" in the input array.
			{
				if (the_list[i].compare(the_list[min_index]) == 0)
				{
					used_flags[i] = true;
					if (!remove_duplicates_flag) // If duplicates are not being removed, append a new instance for each encounter.
					{
						sorted_list_arr[sorted_list_size] = the_list[min_index];
						sorted_list_size++;
					}
				}
			}
		}
	}

	list* new_list = new list(sorted_list_size, sorted_list_arr);

	delete[] used_flags;
	delete[] sorted_list_arr;

	return new_list;
}

list* list::generate_sublist(int lower_bound, int upper_bound)
{
	if (lower_bound < 0)
	{
		throw "list::generate_sublist(int lower_bound, int upper_bound, bool deep_copy_flag): invalid lower_bound\n";
	}
	if (upper_bound < lower_bound)
	{
		throw "list::generate_sublist(int lower_bound, int upper_bound, bool deep_copy_flag): invalid upper_bound\n";
	}

	finger_entry(upper_bound);

	return new list((upper_bound-lower_bound)+1, the_list + lower_bound);
}

short list::compare(const list& list_2) const
{
	int i = 0;
	while (true)
	{
		if (the_list[i].compare(list_2.the_list[i]) < 0)
		{
			return -1;
		}
		else if (the_list[i].compare(list_2.the_list[i]) > 0)
		{
			return +1;
		}
		i++;
		if ((i >= the_list_size) && (i < list_2.the_list_size))
		{
			return -1;
		}
		else if ((i < the_list_size) && (i >= list_2.the_list_size))
		{
			return +1;
		}
		else if ((i >= the_list_size) && (i >= list_2.the_list_size))
		{
			return 0;
		}
	}
	return 0;
}

bool list::operator==(const list& list_2) const
{
	return (compare(list_2) == 0);
}

bool list::operator<(const list& list_2) const
{
	return (compare(list_2) < 0);
}

// *****************************************************

string list::print() const
{
	string output = "";
	output += to_string(the_list_size) + " < ";
	for (int i = 0; i < the_list_size; i++)
	{
		output += the_list[i].print() + " ";
		if (i < the_list_size-1)
		{
			output += ", ";
		}
	}
	output += ">";
	return output;
}

// *******************************************************


