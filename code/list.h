


#ifndef __LIST_H__
#define __LIST_H__

typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned long uint32;

//#define MAX(a,b) ((a >= b) ? a : b)
//#define MIN(a,b) ((a <= b) ? a : b)

#include <cstdlib>
#include <string>
using namespace std;

#include "simple_data.h"

class list;

list* read_list_ptr(const simple_data& the_data);
simple_data write_list_ptr(list* new_list_ptr);

class list
{
	int the_list_size;
	int max_list_size;
	simple_data* the_list;

	void copy(const list* existing_list); 
	void clear(); 
	void read_from_stream(istream& input);

public:
	list();
	list(const simple_data& new_entry); // Create a one element list.
	list(int new_list_size); // Create a list of empty references.
	list(int new_list_size, const simple_data* new_entries);
	list(istream& input);
	list(const list& existing_list); 
	list(const list* existing_list);
	list& operator=(const list& existing_list); // A shallow copy is used.
	~list();

	int get_list_size() const;
	simple_data operator[](int index); // Indices start at 0.

	bool find(const simple_data& query); // Find query in the list, and return its membership status. Static variables are updated with the results of the search.
	static bool query_found_flag;
	static int query_index;
	static bool multiple_instances_flag;
	static bool get_query_found_flag();
	static int get_query_index();
	static bool get_multiple_instances_flag();

	void finger_entry(int index); // Expand the list if necessary to include index.
	void resize(int new_size);
	void set_entry(int index, const simple_data& new_entry);
	void append(const simple_data& new_entry); // Append the new entry to the end of the list.
	void append(const list& new_entries); // Append the new entries to the end of the list.
	static list* list_append(const list& list_of_lists);
	void insert_element(int index, const simple_data& new_entry); // Insert a new entry at the index, displacing existing entries to the right. 
	void delete_element(int index); // Delete the element at the index, displacing remaining elements to the left.
	list* sort(bool remove_duplicates_flag); 
	list* generate_sublist(int lower_bound, int upper_bound); // Indices start at 0.
	
	short compare(const list& list_2) const; // Returns +1 if *this > list_2; returns -1 if *this < list_2; and returns 0 if *this == list_2.
	bool operator==(const list& list_2) const; 
	bool operator!=(const list& list_2) const;
	bool operator<(const list& list_2) const;
	bool operator>(const list& list_2) const;
	bool operator<=(const list& list_2) const;
	bool operator>=(const list& list_2) const;

	string print() const;
};


#endif



