
#include "simple_data.h"
#include "box.h"

#include "endless_array_i.h"

#include "token_parsing.h"



// *************************************************

void box::copy(const box* existing_box)
{
	the_data = existing_box->the_data;
}

void box::clear()
{
}

void box::read_from_stream(istream& input)
{
	the_data = simple_data(input);
}


// *************************************************

box::box()
{
	the_data = simple_data();
}

box::box(const simple_data& new_data)
{
	the_data = new_data;
}

box::box(istream& input)
{
	read_from_stream(input);
}

box::box(const box& existing_box)
{
	copy(&existing_box);
}

box::box(const box* existing_box)
{
	copy(existing_box);
}

box& box::operator=(const box& existing_box)
{
	clear();
	copy(&existing_box);

	return *this;
}

box::~box()
{
	clear();
}

// *************************************************

simple_data box::get_data() const
{
	return the_data;
}

void box::set_data(const simple_data& new_data)
{
	the_data = new_data;
}

// *************************************************

short box::compare(const box& box_2) const
{
	return the_data.compare(box_2.the_data);
}

bool box::operator==(const box& box_2) const
{
	return (compare(box_2) == 0);
}

bool box::operator!=(const box& box_2) const
{
	return (compare(box_2) != 0);
}

bool box::operator<(const box& box_2) const
{
	return (compare(box_2) < 0);
}

bool box::operator>(const box& box_2) const
{
	return (compare(box_2) > 0);
}

bool box::operator<=(const box& box_2) const
{
	return (compare(box_2) <= 0);
}

bool box::operator>=(const box& box_2) const
{
	return (compare(box_2) >= 0);
}

// ********************************************************

string box::print() const
{
	return the_data.print();
}


