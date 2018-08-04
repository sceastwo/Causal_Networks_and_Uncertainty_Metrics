

#include "token_parsing.h"
#include "doublex.h"


const doublex doublex::positive_infinity(0.0,doublex::pos_inf);
const doublex doublex::negative_infinity(0.0,doublex::neg_inf);
const doublex doublex::undefined(0.0,doublex::NaN);


void doublex::read_from_stream(istream& input)
{
	string curr_token;
	curr_token = read_token(input);
	if (curr_token == "pos_inf")
	{
		d = 0.0;
		flags = pos_inf;
	}
	else if (curr_token == "neg_inf")
	{
		d = 0.0;
		flags = neg_inf;
	}
	else if (curr_token == "NaN")
	{
		d = 0.0;
		flags = NaN;
	}
	else
	{
		d = stod(curr_token);
		flags = normal;
	}
}

double doublex::get_d()
{
	return d;
}

void doublex::set_d(double new_d)
{
	d = new_d;
	flags = normal;
}


doublex::doublex()
{
	d = 0.0;
	flags = normal;
}

doublex::doublex(double new_d)
{
	d = new_d;
	flags = normal;
}

doublex::doublex(double new_d, states new_flags)
{
	d = new_d;
	flags = new_flags;
}

doublex::doublex(istream& input)
{
	read_from_stream(input);
}

doublex::doublex(const doublex& new_d)
{
	d = new_d.d;
	flags = new_d.flags;
}

doublex& doublex::operator=(const doublex& new_d)
{
	d = new_d.d;
	flags = new_d.flags;
	return *this;
}


short int doublex::get_sign() const
{
	if (flags == normal)
	{
		if (d > 0.0)
		{
			return 1;
		}
		else if (d < 0.0)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	else if (flags == pos_inf)
	{
		return 4;
	}
	else if (flags == neg_inf)
	{
		return -4;
	}
	else
	{
		return 0;
	}
}

bool doublex::is_zero() const
{
	return (flags == normal) && (d == 0.0);
}

bool doublex::is_normal() const
{
	return (flags == normal);
}

bool doublex::is_NaN() const
{
	return (flags == NaN);
}

doublex doublex::operator+(const doublex& op_2) const
{
	doublex sum;
	sum.d = d + op_2.d;
	if ((flags != normal) || (op_2.flags != normal))
	{
		short int s1 = get_sign();
		short int s2 = op_2.get_sign();

		if (s1 + s2 >= 3)
		{
			sum.flags = pos_inf;
		}
		else if (s1 + s2 <= -3)
		{
			sum.flags = neg_inf;
		}
		else 
		{
			sum.flags = NaN;
		}
	}
	else
	{
		sum.flags = normal;
	}
	return sum;
}

doublex& doublex::operator+=(const doublex& op_2)
{
	return operator=(operator+(op_2));
}

doublex doublex::operator-() const
{
	doublex neg_d;
	neg_d.d = -d;
	switch (flags)
	{
	case normal:
		neg_d.flags = normal;
		break;
	case pos_inf:
		neg_d.flags = neg_inf;
		break;
	case neg_inf:
		neg_d.flags = pos_inf;
		break;
	case NaN:
		neg_d.flags = NaN;
		break;
	}
	return neg_d;
}

doublex doublex::operator-(const doublex& op_2) const
{
	return operator+(-op_2);
}

doublex& doublex::operator-=(const doublex& op_2)
{
	return operator=(operator-(op_2));
}

doublex doublex::operator*(const doublex& op_2) const
{
	doublex product;
	product.d = d*op_2.d;
	if ((flags != normal) || (op_2.flags != normal))
	{
		short int s1 = get_sign();
		short int s2 = op_2.get_sign();
		if (s1*s2 >= 3)
		{
			product.flags = pos_inf;
		}
		else if (s1*s2 <= -3)
		{
			product.flags = neg_inf;
		}
		else
		{
			product.flags = NaN;
		}
	}
	else
	{
		product.flags = normal;
	}
	return product;
}

doublex doublex::inv() const
{
	doublex inv_d;
	if (flags == normal)
	{
		if (d != 0.0)
		{
			inv_d.d = 1/d;
			inv_d.flags = normal;
		}
		else
		{
			inv_d.d = 0.0;
			inv_d.flags = pos_inf;
		}
	}
	else if ((flags == pos_inf) || (flags == neg_inf))
	{
		inv_d.d = 0.0;
		inv_d.flags = normal;
	}
	else 
	{
		inv_d.d = 0.0;
		inv_d.flags = NaN;
	}

	return inv_d;
}

doublex doublex::operator/(const doublex& op_2) const
{
	return operator*(op_2.inv());
}


short doublex::compare(const doublex& op_2) const
{
	if ((flags != normal) || (op_2.flags != normal))
	{
		short int s1 = get_sign();
		short int s2 = op_2.get_sign();
		if (s1 < s2)
		{
			return -1;
		}
		else if (s1 > s2)
		{
			return +1;
		}
		else if ((s1 == s2) && (s1 != 0))
		{
			return 0;
		}
		else
		{
			if (flags == NaN)
			{
				if (op_2.flags == NaN)
				{
					return 0;
				}
				else
				{
					return +1;
				}
			}
			else 
			{
				if (op_2.flags == NaN)
				{
					return -1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
	else
	{
		if (d < op_2.d)
		{
			return -1;
		}
		else if (d > op_2.d)
		{
			return +1;
		}
		else
		{
			return 0;
		}
	}
}

bool doublex::operator==(const doublex& op_2) const
{
	return (compare(op_2) == 0);
}

bool doublex::operator<(const doublex& op_2) const
{
	return (compare(op_2) < 0);
}

bool doublex::operator>(const doublex& op_2) const
{
	return (compare(op_2) > 0);
}

bool doublex::operator<=(const doublex& op_2) const
{
	return (compare(op_2) <= 0);
}

bool doublex::operator>=(const doublex& op_2) const
{
	return (compare(op_2) >= 0);
}

string doublex::print() const
{
	string output = "";
	switch (flags)
	{
	case doublex::normal:
		output += to_string(d);
		break;
	case doublex::pos_inf:
		output += "pos_inf";
		break;
	case doublex::neg_inf:
		output += "neg_inf";
		break;
	case doublex::NaN:
		output += "NaN";
		break;
	}
	return output;
}

std::ostream& operator<<(std::ostream& out, doublex dx)
{
	/*switch (dx.flags)
	{
	case doublex::normal:
		out << dx.d;
		break;
	case doublex::pos_inf:
		out << "+infty";
		break;
	case doublex::neg_inf:
		out << "-infty";
		break;
	case doublex::NaN:
		out << "NaN";
		break;
	}*/
	out << dx.print();
	return out;
}


