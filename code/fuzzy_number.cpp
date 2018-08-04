
#include "token_parsing.h"
#include "fuzzy_number.h"


bool fuzzy_double::valid(doublex new_l, doublex new_c, doublex new_u)
{
	return (!(new_l > new_c) && !(new_c > new_u));
}

void fuzzy_double::read_from_stream(istream& input)
{
	string curr_token;

	curr_token = read_token(input);
	if (curr_token != "(")
	{
		throw "fuzzy_double::read_from_stream(istream& input): expected \"(\"";
	}

	l = doublex(input);

	curr_token = read_token(input);
	if (curr_token != ",")
	{
		throw "fuzzy_double::read_from_stream(istream& input): expected \",\"";
	}

	c = doublex(input);

	curr_token = read_token(input);
	if (curr_token != ",")
	{
		throw "fuzzy_double::read_from_stream(istream& input): expected \",\"";
	}

	u = doublex(input);

	curr_token = read_token(input);
	if (curr_token != ")")
	{
		throw "fuzzy_double::read_from_stream(istream& input): expected \")\"";
	}
}

doublex fuzzy_double::get_l()
{
	return l;
}

void fuzzy_double::set_l(doublex new_l)
{
	l = new_l;
	if (!valid(l,c,u))
	{
		throw "Invalid fuzzy_double: (l > c).";
	}
}

doublex fuzzy_double::get_c()
{
	return c;
}

void fuzzy_double::set_c(doublex new_c)
{
	c = new_c;
	if (!valid(l,c,u))
	{
		throw "Invalid fuzzy_double: (c < l) || (c > u).";
	}
}

doublex fuzzy_double::get_u()
{
	return u;
}

void fuzzy_double::set_u(doublex new_u)
{
	u = new_u;
	if (!valid(l,c,u))
	{
		throw "Invalid fuzzy_double: (u < c).";
	}
}

void fuzzy_double::set_all(double new_l, double new_c, double new_u)
{
	l = doublex(new_l);
	c = doublex(new_c);
	u = doublex(new_u);

	if (!valid(l,c,u))
	{
		throw "Invalid fuzzy_double.";
	}
}

void fuzzy_double::set_all(doublex new_l, doublex new_c, doublex new_u)
{
	l = new_l;
	c = new_c;
	u = new_u;

	if (!valid(l,c,u))
	{
		throw "Invalid fuzzy_double.";
	}
}

bool fuzzy_double::contains_0()
{
	return (l <= doublex(0.0)) && (doublex(0.0) <= u);
}

fuzzy_double::fuzzy_double()
{
	l = doublex(0.0);
	c = doublex(0.0);
	u = doublex(0.0);
}

fuzzy_double::fuzzy_double(double new_c)
{
	l = doublex(new_c);
	c = doublex(new_c);
	u = doublex(new_c);
}

fuzzy_double::fuzzy_double(doublex new_c)
{
	l = new_c;
	c = new_c;
	u = new_c;
}

fuzzy_double::fuzzy_double(double new_l, double new_c, double new_u)
{
	l = doublex(new_l);
	c = doublex(new_c);
	u = doublex(new_u);

	if (!valid(l,c,u))
	{
		throw "Invalid fuzzy_double.\n";
	}
}

fuzzy_double::fuzzy_double(doublex new_l, doublex new_c, doublex new_u)
{
	l = new_l;
	c = new_c;
	u = new_u;

	if (!valid(l,c,u))
	{
		throw "Invalid fuzzy_double.\n";
	}
}

fuzzy_double::fuzzy_double(istream& input)
{
	read_from_stream(input);
}

fuzzy_double::fuzzy_double(const fuzzy_double& the_fuzzy_double)
{
	l = the_fuzzy_double.l;
	c = the_fuzzy_double.c;
	u = the_fuzzy_double.u;
}

fuzzy_double& fuzzy_double::operator=(const fuzzy_double& the_fuzzy_double)
{
	l = the_fuzzy_double.l;
	c = the_fuzzy_double.c;
	u = the_fuzzy_double.u;
	return *this;
}

fuzzy_double fuzzy_double::operator+(const fuzzy_double& op_2) const
{
	return fuzzy_double(l + op_2.l, c + op_2.c, u + op_2.u);
}

fuzzy_double& fuzzy_double::operator+=(const fuzzy_double& op_2)
{
	operator=(operator+(op_2));
	return *this;
}

fuzzy_double fuzzy_double::operator-() const
{
	return fuzzy_double(-u, -c, -l);
}

fuzzy_double fuzzy_double::operator-(const fuzzy_double& op_2) const
{
	return (*this)+(-op_2); 
}

fuzzy_double& fuzzy_double::operator-=(const fuzzy_double& op_2) 
{
	*this = (*this)-op_2;
	return *this;
}

fuzzy_double fuzzy_double::operator*(const fuzzy_double& op_2) const
{
	doublex lb = l*op_2.l;
	doublex ub = l*op_2.l;

	doublex curr_prod = l*op_2.u;
	lb = (lb <= curr_prod) ? lb : curr_prod;
	ub = (ub >= curr_prod) ? ub : curr_prod;
		
	curr_prod = u*op_2.l;
	lb = (lb <= curr_prod) ? lb : curr_prod;
	ub = (ub >= curr_prod) ? ub : curr_prod;

	curr_prod = u*op_2.u;
	lb = (lb <= curr_prod) ? lb : curr_prod;
	ub = (ub >= curr_prod) ? ub : curr_prod;

	return fuzzy_double(lb, c*op_2.c, ub);
}

fuzzy_double fuzzy_double::operator/(const fuzzy_double& op_2) const
{
	doublex lb = l/op_2.l;
	doublex ub = l/op_2.l;

	doublex curr_quot = l/op_2.u;
	lb = (lb <= curr_quot) ? lb : curr_quot;
	ub = (ub >= curr_quot) ? ub : curr_quot;
		
	curr_quot = u/op_2.l;
	lb = (lb <= curr_quot) ? lb : curr_quot;
	ub = (ub >= curr_quot) ? ub : curr_quot;

	curr_quot = u/op_2.u;
	lb = (lb <= curr_quot) ? lb : curr_quot;
	ub = (ub >= curr_quot) ? ub : curr_quot;

	return fuzzy_double(lb, c/op_2.c, ub);
}

short fuzzy_double::compare(const fuzzy_double& op_2) const
{
	if (c < op_2.c)
	{
		return -1;
	}
	else if (c > op_2.c)
	{
		return +1;
	}
	else
	{
		if (l < op_2.l)
		{
			return -1;
		}
		else if (l > op_2.l)
		{
			return +1;
		}
		else
		{
			if (u < op_2.u)
			{
				return -1;
			}
			else if (u > op_2.u)
			{
				return +1;
			}
			else
			{
				return 0;
			}
		}
	}
}


bool fuzzy_double::operator==(const fuzzy_double& op_2) const
{
	return (compare(op_2) == 0);
}

bool fuzzy_double::operator<(const fuzzy_double& op_2) const
{
	return (compare(op_2) < 0);
}

bool fuzzy_double::operator>(const fuzzy_double& op_2) const
{
	return (compare(op_2) > 0);
}

bool fuzzy_double::operator<=(const fuzzy_double& op_2) const
{
	return (compare(op_2) <= 0);
}

bool fuzzy_double::operator>=(const fuzzy_double& op_2) const
{
	return (compare(op_2) >= 0);
}

string fuzzy_double::print()
{
	string output = "";
	output += "( ";
	output += l.print();
	output += " , ";
	output += c.print();
	output += " , ";
	output += u.print();
	output += " )";
	return output;
}

std::istream& operator>>(std::istream& in_stream, fuzzy_double& the_fuzzy_double)
{
	/*char c_buffer;
	double d_buffer1, d_buffer2, d_buffer3;

	in_stream >> std::ws;
	in_stream >> c_buffer;
	if (c_buffer != '(')
	{
		throw "Expected \'(\'";
	}

	in_stream >> std::ws;
	in_stream >> d_buffer1;

	in_stream >> std::ws;
	in_stream >> c_buffer;
	if (c_buffer != ',')
	{
		throw "Expected \',\'";
	}

	in_stream >> std::ws;
	in_stream >> d_buffer2;

	in_stream >> std::ws;
	in_stream >> c_buffer;
	if (c_buffer != ',')
	{
		throw "Expected \',\'";
	}

	in_stream >> std::ws;
	in_stream >> d_buffer3;

	in_stream >> std::ws;
	in_stream >> c_buffer;
	if (c_buffer != ')')
	{
		throw "Expected \')\'";
	}

	the_fuzzy_double.set_all(d_buffer1,d_buffer2,d_buffer3);*/

	the_fuzzy_double = fuzzy_double(in_stream);

	return in_stream;
}


std::ostream& operator<<(std::ostream& out_stream, fuzzy_double& the_fuzzy_double)
{
	/*out_stream << std::fixed
			   << '('
			   << the_fuzzy_double.get_l()
			   << ','
			   << the_fuzzy_double.get_c()
			   << ','
			   << the_fuzzy_double.get_u()
			   << ')';*/
	out_stream << the_fuzzy_double.print();

	return out_stream;
}

