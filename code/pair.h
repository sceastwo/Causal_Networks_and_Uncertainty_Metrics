


#ifndef __PAIR_H__
#define __PAIR_H__

typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned long uint32;

//#define MAX(a,b) ((a >= b) ? a : b)
//#define MIN(a,b) ((a <= b) ? a : b)

#include <cstdlib>
#include <string>
using namespace std;

#include "simple_data.h"

class data_pair
{
	simple_data data_1;
	simple_data data_2;

	void copy(const data_pair* existing_pair); 
	void clear();
	void read_from_stream(istream& input);

public:
	data_pair();
	data_pair(const simple_data& new_data_1, const simple_data& new_data_2); // Basic initialization.
	data_pair(istream& input);
	data_pair(const data_pair& existing_pair); 
	data_pair(const data_pair* existing_pair);
	data_pair& operator=(const data_pair& existing_pair); 
	~data_pair();

	simple_data get_data_1() const;
	simple_data get_data_2() const;
	void set_data_1(const simple_data& new_data_1);
	void set_data_2(const simple_data& new_data_2);

	short compare(const data_pair& pair_2) const; // Returns +1 if *this > pair_2; returns -1 if *this < pair_2; and returns 0 if *this == pair_2.
	bool operator==(const data_pair& pair_2) const;
	bool operator!=(const data_pair& pair_2) const;
	bool operator<(const data_pair& pair_2) const;
	bool operator>(const data_pair& pair_2) const;
	bool operator<=(const data_pair& pair_2) const;
	bool operator>=(const data_pair& pair_2) const;

	string print() const;
};


#endif


