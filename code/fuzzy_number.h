

#ifndef __FUZZY_NUMBER_H__
#define __FUZZY_NUMBER_H__

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

typedef unsigned short int uint16;

#include "doublex.h"

struct fuzzy_double
{
private:
	doublex l, c, u;

	bool valid(doublex new_l, doublex new_c, doublex new_u);

	void read_from_stream(istream& input);

public:
	doublex get_l();
	void set_l(doublex new_l);

	doublex get_c();
	void set_c(doublex new_c);

	doublex get_u();
	void set_u(doublex new_u);

	void set_all(double new_l, double new_c, double new_u);
	void set_all(doublex new_l, doublex new_c, doublex new_u);

	bool contains_0();

	fuzzy_double();
	fuzzy_double(double new_c);
	fuzzy_double(doublex new_c);
	fuzzy_double(double new_l, double new_c, double new_u);
	fuzzy_double(doublex new_l, doublex new_c, doublex new_u);
	fuzzy_double(istream& input);
	fuzzy_double(const fuzzy_double& the_fuzzy_double);
	fuzzy_double& operator=(const fuzzy_double& the_fuzzy_double);

	fuzzy_double operator+(const fuzzy_double& op_2) const;
	fuzzy_double& operator+=(const fuzzy_double& op_2);
	fuzzy_double operator-() const;
	fuzzy_double operator-(const fuzzy_double& op_2) const;
	fuzzy_double& operator-=(const fuzzy_double& op_2);
	fuzzy_double operator*(const fuzzy_double& op_2) const;
	fuzzy_double operator/(const fuzzy_double& op_2) const;

	short compare(const fuzzy_double& op_2) const; // Returns +1 if *this > op_2; returns -1 if *this < op_2; and returns 0 if *this == op_2.
	bool operator==(const fuzzy_double& op_2) const;
	bool operator<(const fuzzy_double& op_2) const;
	bool operator>(const fuzzy_double& op_2) const;
	bool operator<=(const fuzzy_double& op_2) const;
	bool operator>=(const fuzzy_double& op_2) const;

	string print();
};

std::istream& operator>>(std::istream& in_stream, fuzzy_double& the_fuzzy_double);
std::ostream& operator<<(std::ostream& out_stream, fuzzy_double& the_fuzzy_double);

#endif


