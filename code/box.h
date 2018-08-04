


#ifndef __BOX_H__
#define __BOX_H__

typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned long uint32;

#define MAX(a,b) ((a >= b) ? a : b)
#define MIN(a,b) ((a <= b) ? a : b)

#include <cstdlib>
#include <string>
using namespace std;

#include "simple_data.h"

class box
{
	simple_data the_data;

	void copy(const box* existing_box); 
	void clear();
	void read_from_stream(istream& input);

public:
	box();
	box(const simple_data& new_data); // Basic initialization.
	box(istream& input);
	box(const box& existing_box); 
	box(const box* existing_box);
	box& operator=(const box& existing_box); 
	~box();

	simple_data get_data() const;
	void set_data(const simple_data& new_data);

	short compare(const box& box_2) const; // Returns +1 if *this > box_2; returns -1 if *this < box_2; and returns 0 if *this == box_2.
	bool operator==(const box& box_2) const;
	bool operator!=(const box& box_2) const;
	bool operator<(const box& box_2) const;
	bool operator>(const box& box_2) const;
	bool operator<=(const box& box_2) const;
	bool operator>=(const box& box_2) const;

	string print() const;
};


#endif


