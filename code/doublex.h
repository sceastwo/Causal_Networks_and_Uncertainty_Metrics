


#ifndef __DOUBLEX_H__
#define __DOUBLEX_H__

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

struct doublex
{
	friend std::ostream& operator<<(std::ostream& out, doublex dx);

private:
	double d;
	enum states {normal, pos_inf, neg_inf, NaN} flags; 

	void read_from_stream(istream& input);

public:
	static const doublex positive_infinity;
	static const doublex negative_infinity;
	static const doublex undefined;

	double get_d();
	void set_d(double new_d);

	doublex();
	doublex(double new_d);
private:
	doublex(double new_d, states new_flags);
public:
	doublex(istream& input);
	doublex(const doublex& new_d);
	doublex& operator=(const doublex& new_d);

	short int get_sign() const;
	bool is_zero() const;
	bool is_normal() const;
	bool is_NaN() const;
	doublex operator+(const doublex& op_2) const;
	doublex& operator+=(const doublex& op_2);
	doublex operator-() const;
	doublex operator-(const doublex& op_2) const;
	doublex& operator-=(const doublex& op_2);
	doublex operator*(const doublex& op_2) const;
	doublex inv() const;
	doublex operator/(const doublex& op_2) const;

	short compare(const doublex& op_2) const; // Returns +1 if *this > op_2; returns -1 if *this < op_2; and returns 0 if *this == op_2.
	bool operator==(const doublex& op_2) const;
	bool operator<(const doublex& op_2) const;
	bool operator>(const doublex& op_2) const;
	bool operator<=(const doublex& op_2) const;
	bool operator>=(const doublex& op_2) const;

	string print() const;
};

std::ostream& operator<<(std::ostream& out, doublex dx);

#endif

