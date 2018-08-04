


#ifndef __SIMPLE_DATA_H__
#define __SIMPLE_DATA_H__

typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned long uint32;

#define MAX(a,b) ((a >= b) ? a : b)
#define MIN(a,b) ((a <= b) ? a : b)

#include <cstdlib>
#include <string>
using namespace std;

struct doublex;
struct fuzzy_double;
class box;
class data_pair;
class list;

enum type_identifier {TI_VOID, TI_MEM_BLOCK, TI_BOOL, TI_UCHAR, TI_UINT16, TI_INT, TI_DOUBLE, TI_DOUBLEX, TI_FUZZY, TI_STRING, TI_POINTER, 
	TI_BOX, TI_PAIR, TI_LIST};

class simple_data
{
private:
	type_identifier the_type_id;
	int the_type_size; 
	void* the_data;

	static int get_type_size(type_identifier the_type_id);
	void copy_new_data(const void* new_data);
	void fill_with_0(); // Fill the memory with data that is equivalent to 0.
	void copy(const simple_data* existing_data); 
	void clear();
	void read_from_stream(istream& input);

public:
	simple_data();
	simple_data(type_identifier new_type_id, int new_type_size); // Fill the memory with an appropriate 0.
	simple_data(type_identifier new_type_id, int new_type_size, const void* new_data); 
	simple_data(istream& input);
	simple_data(const simple_data& existing_data);
	simple_data(const simple_data* existing_data);
	simple_data& operator=(const simple_data& existing_data);
	~simple_data();

	type_identifier get_type_id() const;
	int get_type_size() const;
	void* get_the_data() const;

	short compare(const simple_data& data_2) const; // Returns +1 if *this > data_2; returns -1 if *this < data_2; and returns 0 if *this == data_2.
	bool operator==(const simple_data& data_2) const;
	bool operator!=(const simple_data& data_2) const;
	bool operator<(const simple_data& data_2) const;
	bool operator>(const simple_data& data_2) const;
	bool operator<=(const simple_data& data_2) const;
	bool operator>=(const simple_data& data_2) const;

	string print() const;

	// Data type specific functions:
	bool read_bool() const;
	static simple_data write_bool(bool new_bool);
	uchar read_uchar() const;
	static simple_data write_uchar(uchar new_uchar);
	uint16 read_uint16() const;
	static simple_data write_uint16(uint16 new_uint16);
	int read_int() const;
	static simple_data write_int(int new_int);
	double read_double() const;
	static simple_data write_double(double new_double);
	doublex read_doublex() const;
	static simple_data write_doublex(doublex new_doublex);
	fuzzy_double read_fuzzy_double() const;
	static simple_data write_fuzzy_double(fuzzy_double new_fuzzy_double);
	string read_string() const;
	static simple_data write_string(string new_string);
	void* read_pointer() const;
	static simple_data write_pointer(void* new_pointer);
	box read_box() const;
	static simple_data write_box(const box& new_box);
	data_pair read_pair() const;
	static simple_data write_pair(const data_pair& new_pair);
	list read_list() const;
	static simple_data write_list(const list& new_list);
};


#endif

