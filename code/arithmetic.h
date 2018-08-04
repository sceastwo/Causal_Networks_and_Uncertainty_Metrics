


#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#define MAX(a,b) ((a >= b) ? a : b)
#define MIN(a,b) ((a <= b) ? a : b)

#include "simple_data.h"
#include "node.h"

#include "doublex.h"
#include "fuzzy_number.h"

// The following functions handle the fact that a bool can be cast to uchar, uint16, int, double, etc. while a double cannot be cast to bool and so on.
bool arith_is_bool(const simple_data& the_data); // Can be cast to bool?
bool arith_read_bool(const simple_data& the_data);
bool arith_is_uchar(const simple_data& the_data); // Can be cast to uchar?
uchar arith_read_uchar(const simple_data& the_data);
bool arith_is_uint16(const simple_data& the_data); // Can be cast to uint16?
uint16 arith_read_uint16(const simple_data& the_data);
bool arith_is_int(const simple_data& the_data);
int arith_read_int(const simple_data& the_data);
bool arith_is_double(const simple_data& the_data);
double arith_read_double(const simple_data& the_data);
bool arith_is_doublex(const simple_data& the_data);
doublex arith_read_doublex(const simple_data& the_data);
bool arith_is_fuzzy(const simple_data& the_data);
fuzzy_double arith_read_fuzzy(const simple_data& the_data);

enum binary_op_code {OP_ADDITION, OP_MULTIPLICATION, OP_SUBTRACTION, OP_DIVISION, OP_MAX, OP_MIN};
simple_data binary_op(const simple_data& data_1, const simple_data& data_2, binary_op_code the_op_code); 
simple_data operator+(const simple_data& data_1, const simple_data& data_2);
simple_data operator*(const simple_data& data_1, const simple_data& data_2);
simple_data operator-(const simple_data& data_1, const simple_data& data_2);
simple_data operator/(const simple_data& data_1, const simple_data& data_2);
node* node_binary_op(node* root_node_1, node* root_node_2, bool max_degree_flag, binary_op_code the_op_code);

enum unary_op_code {OP_NEGATIVE, OP_INVERSE, OP_INTEGER_MULTIPLICATION};
simple_data unary_op(const simple_data& the_data, unary_op_code the_op_code, const simple_data& extra_data);
simple_data operator-(const simple_data& the_data);
simple_data inv(const simple_data& the_data);
simple_data operator*(int factor, const simple_data& the_data);
simple_data operator*(const simple_data& the_data, int factor);
node* node_unary_op(node* root_node, unary_op_code the_op_code, const simple_data& extra_data);

node* marginalize(node* root_node, int depth, bool keep_degree_flag);
node* condition(node* root_node, int depth, int child_index, bool keep_degree_flag);

node* DS_binary_op(node* root_node_1, node* root_node_2, bool max_degree_flag, binary_op_code the_op_code);
node* DS_collapse(node* root_node);

#endif


