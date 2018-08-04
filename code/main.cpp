
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
//using namespace std;

#include "simple_data.h"
#include "box.h"
#include "pair.h"
#include "list.h"
#include "node.h"

#include "doublex.h"
#include "fuzzy_number.h"

#include "endless_array_i.h"
#include "token_parsing.h"
#include "arithmetic.h"

// Exactly one of the macros below should be uncommeted at any time.
//#define __TESTING_TYPE_SIZES__
//#define __TESTING_CASTS__
//#define __TESTING_CONST__
//#define __TESTING_STRING_THROW__
//#define __TESTING_REFERENCE_RETURN__
//#define __TESTING_EXPRESSION_TREE__
//#define __TESTING_ENDLESS_ARRAY__
//#define __TESTING_TOKEN_READ__
//#define __TESTING_SIMPLE_DATA__
//#define __TESTING_MEM_BLOCK_DATA__
//#define __TESTING_BOX__
//#define __TESTING_PAIR__
//#define __TESTING_LIST__
//#define __TESTING_NODE__
//#define __TESTING_NODE_2__
//#define __TESTING_ARITHMETIC__
//#define __TESTING_ARITHMETIC_2__
#define __NO_TESTING__


#ifdef __TESTING_CONST__

void foo(const int* ptr)
{
	std::cout << *ptr << '\n';
	//*ptr = -1;
}

void foo2(int** ptr)
{
	std::cout << **ptr << '\n';
}

#endif

#ifdef __TESTING_REFERENCE_RETURN__
	class foo_class
	{
		int x;
	public:
		foo_class()
		{
			x = 0;
			cout << "NEW ";
		}

		foo_class(foo_class& existing_foo)
		{
			x = existing_foo.x;
			cout << "COPY ";
		}

		foo_class& operator=(foo_class& existing_foo)
		{
			x = existing_foo.x;
			cout << "ASSIGN ";
			return *this;
		}

		~foo_class()
		{
			cout << "DELETE ";
		}
	};

	foo_class foo_val_val_function(foo_class a_foo)
	{
		return a_foo;
	}

	foo_class foo_ref_val_function(foo_class& a_foo)
	{
		return a_foo;
	}

	foo_class& foo_ref_ref_function(foo_class& a_foo)
	{
		return a_foo;
	}

	foo_class* foo_ptr_ptr_function(foo_class* a_foo_ptr)
	{
		return a_foo_ptr;
	}

	/*foo_class& foo_ref_ref_function_2(foo_class& a_foo)
	{
		return foo_class();
	}*/

#endif

#ifdef __TESTING_EXPRESSION_TREE__
	int f(int x, int y)
	{
		std::cout << "f(" << x << "," << y << ")";
		return x + y;
	}
	int g(int x, int y)
	{
		std::cout << "g(" << x << "," << y << ")";
		return x + y;
	}

#endif

#ifdef __NO_TESTING__
	void instruction_set_name(list& name_list, list& node_list, string dest_name, node* resultant_node, const char* command_name)
	{
		// Check if the name already exists:
		if (name_list.find(simple_data::write_string(dest_name)))
		{ 
			int dest_name_index = list::get_query_index();
			node* old_node = read_node_ptr(node_list[dest_name_index]);
			node_list.find(write_node_ptr(old_node));
			if (!list::get_multiple_instances_flag()) // Destroy the subgraph indexed by the dest_name if it is indexed by no other name.
			{
				node::destroy_subgraph(old_node);
			}
			node_list.set_entry(dest_name_index,write_node_ptr(resultant_node));
		}
		else
		{ 
			name_list.append(simple_data::write_string(dest_name));
			node_list.append(write_node_ptr(resultant_node));
		}
	}

	node* instruction_read_source_node(list& name_list, list& node_list, istream& instructions_input, const char* command_name)
	{
		string source_name = read_token(instructions_input);
		node* source_node = NULL;
		if (name_list.find(simple_data::write_string(source_name)))
		{
			source_node = read_node_ptr(node_list[list::get_query_index()]);
		}
		else
		{
			throw get_c_str(string(command_name) + string(" source_name node not found.\n"));
		}
		return source_node;
	}

#endif

int main()
{
#ifdef __TESTING_TYPE_SIZES__
	{
		std::cout << sizeof(string) << '\n';
	}
#endif

#ifdef __TESTING_CASTS__
	{
		uint16 k = 200;
		unsigned char c = (unsigned char) k;
		uint16 k2 = (uint16) c;
		std::cout << k << ' ' << k2 << '\n';
	}
#endif

#ifdef __TESTING_CONST__
	{
		int* ptr = new int;
		*ptr = 5;
		foo(ptr);
		delete ptr;

		int** ptr_2 = new int*;
		*ptr_2 = new int;
		**ptr_2 = 7;
		foo(*ptr_2);
		foo2(ptr_2);
		delete *ptr_2;
		delete ptr_2;
	}
#endif

#ifdef __TESTING_STRING_THROW__
	try
	{
		throw "something\n";
	}
	catch (const char* error)
	{
		std::cerr << "const char* catch: " << error;
		system("PAUSE");
		return EXIT_FAILURE;
	}
	catch (string error)
	{
		std::cerr << "const string catch: " << error;
		system("PAUSE");
		return EXIT_FAILURE;
	}
#endif

#ifdef __TESTING_REFERENCE_RETURN__
	cout << "Testing default constructors:\n";
	foo_class a_foo;
	cout << "\n*********\n";
	foo_class b_foo;
	cout << "\n*********\n";
	cout << "Testing various parameter pass and return styles:\n";
	cout << "pass by value, return by value:\n";
	b_foo = foo_val_val_function(a_foo);
	cout << "\n*********\n";
	cout << "pass by reference, return by value:\n";
	b_foo = foo_ref_val_function(a_foo);
	cout << "\n*********\n";
	cout << "pass by reference, return by reference:\n";
	b_foo = foo_ref_ref_function(a_foo);
	cout << "\n*********\n";
	cout << "pass by reference, return by reference to a reference variable:\n";
	foo_class& c_foo = foo_ref_ref_function(a_foo);
	cout << "\n*********\n";
	cout << "pass by reference, return by reference to a pointer variable:\n";
	foo_class* d_foo_ptr = &foo_ref_ref_function(a_foo);
	cout << "\n*********\n";
	cout << "check if the pointer returned remains valid:\n";
	cout << (d_foo_ptr == &a_foo);
	cout << "\n*********\n";
	cout << "passing a temporary value by reference w/o const:\n";
	b_foo = foo_ref_val_function(foo_class());
	cout << "\n*********\n";
	foo_class* e_foo_ptr = foo_ptr_ptr_function(&foo_class());
	cout << "\n*********\n";
	cout << "multiple passes:\n";
	b_foo = foo_ref_val_function(foo_ref_val_function(a_foo));
	cout << "\n*********\n";
	b_foo = foo_ref_ref_function(foo_ref_ref_function(a_foo));
	cout << "\n*********\n";
	foo_class& e_foo = foo_ref_ref_function(foo_ref_ref_function(a_foo));
	cout << "\n*********\n";
#endif

#ifdef __TESTING_EXPRESSION_TREE__
	f(g(f(1,2),f(4,8)),g(16,32));
#endif

#ifdef __TESTING_ENDLESS_ARRAY__
	{
		for (int i = 0; i <= 9; i++)
		{
			for (int j = 0; j <= 9; j++)
			{
				char c = (char) 65 + i + j;
				endless_array_i::write_data(i,j,1,1,&c);
				char d;
				endless_array_i::read_data(i,j,1,1,&d);
				std::cout << '(' << c << ',' << d << ") ";
			}
			std::cout << '\n';
		}

		std::cout << "****************************\n";
		endless_array_i::next_layer();
		string str_sample = "ASSSSSSSSSSSS!!!!!!!!!!!!!";
		endless_array_i::write_data(2,0,1,str_sample.length(),str_sample.c_str());
		endless_array_i::previous_layer();
		std::cout << "****************************\n";

		for (int i = 0; i <= 9; i++)
		{
			for (int j = 0; j <= 9; j++)
			{
				char d;
				endless_array_i::read_data(i,j,1,1,&d);
				std::cout << d << " ";
			}
			std::cout << '\n';
		}

		std::cout << "****************************\n";
		endless_array_i::next_layer();
		char* c_str_sample = new char[str_sample.length()];
		endless_array_i::read_data(2,0,1,str_sample.length(),c_str_sample);
		for (int i = 0; i < str_sample.length(); i++)
		{
			std::cout << c_str_sample[i];
		}
		std::cout << '\n';
		char* c_str_sample_2 = new char[str_sample.length() / 2];
		endless_array_i::read_data(2,0,2,str_sample.length() / 2,c_str_sample_2);
		for (int i = 0; i < str_sample.length() / 2; i++)
		{
			std::cout << c_str_sample_2[i];
		}
		std::cout << '\n';
		std::cout << "****************************\n";

	}
#endif

#ifdef __TESTING_TOKEN_READ__
	{
		ifstream input("Test Files/read_token_test.txt");
		endless_array_i::next_layer();
		int num_of_tokens = 0;
		string curr_token = "";
		do
		{
			curr_token = read_token(input);
			std::cout << "********\n";
			std::cout << curr_token;
			std::cout << "\n********\n";
			endless_array_i::write_data(0,num_of_tokens*sizeof(string),1,sizeof(string),reinterpret_cast<char*>(&curr_token));
			num_of_tokens++;
		} while (curr_token != "");
		for (int i = 0; i < num_of_tokens; i++) 
		{
			endless_array_i::read_data(0,i*sizeof(string),1,sizeof(string),reinterpret_cast<char*>(&curr_token));
			std::cout << curr_token << ' ' << encode_string(curr_token) << '\n';
		}
		endless_array_i::previous_layer();
		std::cout << '\n';
	}
#endif

#ifdef __TESTING_SIMPLE_DATA__
	{
		simple_data e;
		std::cout << e.print() << '\n';
		ifstream input("Test Files/simple_data_test.txt");
		int num_of_data = 16;
		simple_data* e_arr = new simple_data[num_of_data];
		for (int i = 0; i < num_of_data; i++)
		{
			try
			{
				e_arr[i] = simple_data(input);
				std::cout << e_arr[i].print() << '\n';
			}
			catch (char* error)
			{
				std::cerr << error << '\n';
			}
		}
		simple_data** e_ptr_arr = new simple_data*[num_of_data];
		for (int i = 0; i < num_of_data; i++)
		{
			e_ptr_arr[i] = new simple_data(e_arr[i]);
			std::cout << (*(e_ptr_arr[i])).print() << '\n';
		}
		std::cout << '\n';
		for (int i = 0; i < num_of_data; i++)
		{
			for (uint16 j = 0; j < num_of_data; j++)
			{
				std::cout << (e_arr[i] == *(e_ptr_arr[j]));
			}
			std::cout << '\n';
		}
		std::cout << '\n';
		short int* comp_results = new short int[num_of_data*num_of_data];
		for (int i = 0; i < num_of_data; i++)
		{
			for (int j = 0; j < num_of_data; j++)
			{
				comp_results[num_of_data*i+j] = e_arr[i].compare(*(e_ptr_arr[j]))+1;
				std::cout << comp_results[num_of_data*i+j];
			}
			std::cout << '\n';
		}
		for (int i = 0; i < num_of_data; i++)
		{
			for (int j = 0; j < num_of_data; j++)
			{
				if (comp_results[num_of_data*i+j] + comp_results[num_of_data*j+i] != 2)
				{
					std::cout << "Comparison error: (" << i << "," << j << ")\n";
				}
			}
		}
		std::cout << '\n';
	}
#endif

#ifdef __TESTING_MEM_BLOCK_DATA__
	try
	{
		node* n = new node();
		simple_data d(TI_MEM_BLOCK,sizeof(node*),&n); 
		simple_data d2 = d;

		node* n2 = *reinterpret_cast<node**>(d2.get_the_data());

		std::cout << n << ' ' << n2 << ' ' << read_node_ptr(write_node_ptr(n)) << '\n';

	}
	catch (char* error)
	{
		std::cerr << error;
	}
#endif

#ifdef __TESTING_BOX__
	{
		box b;
		simple_data e(TI_BOX, 1, &b);
		std::cout << b.print() << '\n';
		std::cout << e.print() << '\n';
		ifstream input("Test Files/box_test.txt"); 
		box b2(input);
		std::cout << b2.print() << '\n';
		std::cout << simple_data::write_box(b2).print() << '\n';
	}
#endif

#ifdef __TESTING_PAIR__
	try 
	{
		data_pair p;
		std::cout << p.print() << '\n';
		ifstream input("Test Files/pair_test.txt");
		int num_of_pairs;
		input >> num_of_pairs;
		data_pair* pair_arr = new data_pair[num_of_pairs];
		for (int i = 0; i < num_of_pairs; i++)
		{
			pair_arr[i] = data_pair(input);
			std::cout << pair_arr[i].print() << '\n';
		}
		std::cout << '\n';
		for (int i = 0; i < num_of_pairs; i++)
		{
			std::cout << "[" << pair_arr[i].get_data_1().print() << "," << pair_arr[i].get_data_2().print() << "]\n";
		}
		std::cout << '\n';
		pair_arr[0].set_data_1(simple_data::write_int(42));
		pair_arr[0].set_data_2(simple_data::write_int(43));
		std::cout << pair_arr[0].print() << '\n';
	}
	catch (char* error)
	{
		std::cerr << error;
	}
#endif

#ifdef __TESTING_LIST__
	try
	{
		list l;
		std::cout << l.print() << '\n';
		ifstream input("Test Files/list_test.txt");
		int num_of_lists;
		input >> num_of_lists;
		list* l_arr = new list[num_of_lists];
		for (int i = 0; i < num_of_lists; i++)
		{
			l_arr[i] = list(input);
			std::cout << l_arr[i].print() << '\n';
		}
		std::cout << '\n';
		for (int i = 0; i < num_of_lists; i++)
		{
			for (int j = 0; j < l_arr[i].get_list_size(); j++)
			{
				std::cout << l_arr[i][j].print() << '\n';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
		
		// Testing find:
		std::cout << "Testing find\n";
		std::cout << '(' << l_arr[3].find(simple_data::write_uchar('u')) << ':';
		std::cout << list::get_query_found_flag() << ',' << list::get_query_index() << ',' << list::get_multiple_instances_flag() << ")\n";
		std::cout << '(' << l_arr[3].find(simple_data::write_uchar('a')) << ':';
		std::cout << list::get_query_found_flag() << ',' << list::get_query_index() << ',' << list::get_multiple_instances_flag() << ")\n";
		std::cout << '(' << l_arr[3].find(simple_data::write_string("something")) << ':'; 
		std::cout << list::get_query_found_flag() << ',' << list::get_query_index() << ',' << list::get_multiple_instances_flag() << ")\n";
		std::cout << '(' << l_arr[3].find(simple_data::write_int(5)) << ':';
		std::cout << list::get_query_found_flag() << ',' << list::get_query_index() << ',' << list::get_multiple_instances_flag() << ")\n";
		std::cout << '\n';

		// Testing set_entry:
		std::cout << "Testing set_entry\n";
		l_arr[2].set_entry(3,simple_data::write_bool(false));
		std::cout << l_arr[2].print() << '\n';
		l_arr[2].set_entry(3,simple_data::write_bool(true));
		std::cout << l_arr[2].print() << '\n';
		
		// Testing insert_element and delete_element:
		std::cout << "Testing inset_element and delete_element\n";
		l_arr[2].insert_element(3,simple_data::write_int(5));
		std::cout << l_arr[2].print() << '\n';
		l_arr[2].delete_element(3);
		std::cout << l_arr[2].print() << '\n';
		l_arr[2].insert_element(5,simple_data::write_int(5));
		std::cout << l_arr[2].print() << '\n';
		l_arr[2].delete_element(5);
		std::cout << l_arr[2].print() << '\n';
		
		// Testing append:
		std::cout << "Testing append\n";
		for (int i = 0; i < 8; i++)
		{
			l_arr[0].append(simple_data::write_int(i));
			std::cout << l_arr[0][i].read_int() << ' ';
		}
		std::cout << '\n';

		// Testing generate_sublist:
		std::cout << "Testing generate_sublist\n";
		std::cout << l_arr[2].generate_sublist(1,3)->print() << '\n';
		
		// Testing sort:
		std::cout << "Testing sort\n";
		std::cout << l_arr[5].sort(false)->print() << '\n';
		std::cout << l_arr[5].sort(true)->print() << '\n';
	}
	catch (char* error)
	{
		std::cerr << error;
	}
#endif

#ifdef __TESTING_NODE__
	try
	{
		int num_of_nodes = 20;
		list node_list;

		for (int i = 0; i < num_of_nodes; i++) // Create nodes:
		{
			// Default constructor:
			/*node_list.set_entry(i,write_node_ptr(new node()));
			if (n_arr[i]->get_the_data() != simple_data())
			{
				std::cerr << "n_arr[" << i << "]: Invalid data.\n";
			}*/
			// New data constructor:
			node_list.set_entry(i,write_node_ptr(new node(simple_data::write_int(i))));
			if (read_node_ptr(node_list[i])->get_the_data().read_int() != i)
			{
				std::cerr << "1: n_arr[" << i << "]: Invalid data.\n";
			}

			if (read_node_ptr(node_list[i])->get_degree() != 0)
			{
				std::cerr << "1: n_arr[" << i << "]: Invalid degree.\n";
			}
		}

		for (int i = 0; i < num_of_nodes; i++) // Add child nodes:
		{
			for (int j = 0; j < num_of_nodes - (i+1); j++)
			{
				read_node_ptr(node_list[i])->add_child(read_node_ptr(node_list[i+1+j]));
			}
		}
		for (int i = 0; i < num_of_nodes; i++) // Testing the addition of the child nodes:
		{
			if (read_node_ptr(node_list[i])->get_degree() != num_of_nodes - (i+1)) // Check node degree:
			{
				std::cerr << "2: n_arr[" << i << "]: Invalid degree.\n";
			}
			for (int j = 0; j < read_node_ptr(node_list[i])->get_degree(); j++) // Check node children:
			{
				if (read_node_ptr(node_list[i])->get_child(j) != read_node_ptr(node_list[i+1+j]))
				{
					std::cerr << "2: n_arr[" << i << "]: Invalid child.\n";
				}
			}
			// Check the node's parents:
			bool* used_flags = new bool[read_node_ptr(node_list[i])->max_num_of_parents];
			for (int j = 0; j < read_node_ptr(node_list[i])->max_num_of_parents; j++)
			{
				used_flags[j] = (read_node_ptr(node_list[i])->parents[j] == NULL);
			}
			for (int j = 0; j < num_of_nodes; j++) // For each possible parent:
			{
				// Is the node truely a parent?
				bool is_a_parent = (j < i);
				if (!is_a_parent)
				{
					continue;
				}

				node* expected_parent = read_node_ptr(node_list[j]);

				bool found_flag = false;
				for (int k = 0; !found_flag && (k < read_node_ptr(node_list[i])->max_num_of_parents); k++)
				{
					if (!used_flags[k] && read_node_ptr(node_list[i])->parents[k] == expected_parent)
					{
						found_flag = true;
						used_flags[k] = true;
					}
				}
				if (!found_flag)
				{
					std::cerr << "2: n_arr[" << i << "]: True parent not found.\n";
				}
			}
			for (int j = 0; j < read_node_ptr(node_list[i])->max_num_of_parents; j++)
			{
				if (!used_flags[j])
				{
					std::cerr << "2: n_arr[" << i << "]: Parent not used.\n";
				}
			}

			delete[] used_flags;
		}

		
		for (int i = 0; i < num_of_nodes; i++) // Alter and delete child nodes:
		{
			for (int j = 0; j < (num_of_nodes - (i+1))/2; j++)
			{
				read_node_ptr(node_list[i])->set_child(j,read_node_ptr(node_list[i+1+2*j]));
				read_node_ptr(node_list[i])->delete_child(j+1);
			}
			if ((num_of_nodes - (i+1)) % 2 != 0)
			{
				int j = (num_of_nodes - (i+1))/2;
				read_node_ptr(node_list[i])->set_child(j,read_node_ptr(node_list[i+1+2*j]));
			}
		}
		for (int i = 0; i < num_of_nodes; i++) // Testing the alteration and deletion of the child nodes:
		{
			if (read_node_ptr(node_list[i])->get_degree() != (num_of_nodes - (i+1) + 1)/2) // Check node degree:
			{
				std::cerr << "3: n_arr[" << i << "]: Invalid degree.\n";
			}
			for (int j = 0; j < read_node_ptr(node_list[i])->get_degree(); j++) // Check node children:
			{
				if (read_node_ptr(node_list[i])->get_child(j) != read_node_ptr(node_list[i+1+2*j]))
				{
					std::cerr << "3: n_arr[" << i << "]: Invalid child.\n";
				}
			}
			// Check the node's parents:
			bool* used_flags = new bool[read_node_ptr(node_list[i])->max_num_of_parents];
			for (int j = 0; j < read_node_ptr(node_list[i])->max_num_of_parents; j++)
			{
				used_flags[j] = (read_node_ptr(node_list[i])->parents[j] == NULL);
			}
			for (int j = 0; j < num_of_nodes; j++) // For each possible parent:
			{
				// Is the node truely a parent?
				bool is_a_parent = ((j < i) && ((i-j-1) % 2 == 0));
				if (!is_a_parent)
				{
					continue;
				}

				node* expected_parent = read_node_ptr(node_list[j]);

				bool found_flag = false;
				for (int k = 0; !found_flag && (k < read_node_ptr(node_list[i])->max_num_of_parents); k++)
				{
					if (!used_flags[k] && read_node_ptr(node_list[i])->parents[k] == expected_parent)
					{
						found_flag = true;
						used_flags[k] = true;
					}
				}
				if (!found_flag)
				{
					std::cerr << "3: n_arr[" << i << "]: True parent " << j << " not found.\n";
				}
			}
			for (int j = 0; j < read_node_ptr(node_list[i])->max_num_of_parents; j++)
			{
				if (!used_flags[j])
				{
					std::cerr << "3: n_arr[" << i << "]: Parent " << j << " not used.\n";
				}
			}

			delete[] used_flags;
		}
		

		for (int i = 0; i < num_of_nodes; i++) // Delete and replace the child nodes in preparation for tracing:
		{
			node* curr_node = read_node_ptr(node_list[i]);
			int new_degree = (num_of_nodes+i)/(i+1);
			for (int j = 0; j < new_degree; j++)
			{
				if (j < curr_node->get_degree())
				{
					curr_node->set_child(j,read_node_ptr(node_list[(i+1)*j]));
				}
				else
				{
					curr_node->add_child(read_node_ptr(node_list[(i+1)*j]));
				}
			}
			for (int j = curr_node->get_degree()-1; j >= new_degree; j--)
			{
				curr_node->delete_child(j);
			}
		}
		for (int i = 0; i < num_of_nodes; i++) // Testing the alteration and deletion of the child nodes:
		{
			node* curr_node = read_node_ptr(node_list[i]);
			if (curr_node->get_degree() != (num_of_nodes+i)/(i+1)) // Check node degree:
			{
				std::cerr << "4: n_arr[" << i << "]: Invalid degree.\n";
			}
			for (int j = 0; j < read_node_ptr(node_list[i])->get_degree(); j++) // Check node children:
			{
				if (read_node_ptr(node_list[i])->get_child(j) != read_node_ptr(node_list[(i+1)*j]))
				{
					std::cerr << "4: n_arr[" << i << "]: Invalid child.\n";
				}
			}
			// Check the node's parents:
			bool* used_flags = new bool[read_node_ptr(node_list[i])->max_num_of_parents];
			for (int j = 0; j < read_node_ptr(node_list[i])->max_num_of_parents; j++)
			{
				used_flags[j] = (read_node_ptr(node_list[i])->parents[j] == NULL);
			}
			for (int j = 0; j < num_of_nodes; j++) // For each possible parent:
			{
				// Is the node truely a parent?
				bool is_a_parent = (i % (j+1) == 0);
				if (!is_a_parent)
				{
					continue;
				}

				node* expected_parent = read_node_ptr(node_list[j]);

				bool found_flag = false;
				for (int k = 0; !found_flag && (k < read_node_ptr(node_list[i])->max_num_of_parents); k++)
				{
					if (!used_flags[k] && read_node_ptr(node_list[i])->parents[k] == expected_parent)
					{
						found_flag = true;
						used_flags[k] = true;
					}
				}
				if (!found_flag)
				{
					std::cerr << "4: n_arr[" << i << "]: True parent " << j << " not found.\n";
				}
			}
			for (int j = 0; j < read_node_ptr(node_list[i])->max_num_of_parents; j++)
			{
				if (!used_flags[j])
				{
					std::cerr << "4: n_arr[" << i << "]: Parent " << j << " not used.\n";
				}
			}

			delete[] used_flags;
		}


		// Testing the process of tracing out a subgraph:

		node* root_node = read_node_ptr(node_list[0]);

		node::set_node_tracker(root_node);
		while (!node::end_of_trace())
		{
			node* curr_tracker = node::get_node_tracker();

			std::cout << "[" << node_list.has_element(write_node_ptr(curr_tracker)) << "," << node_list.find(write_node_ptr(curr_tracker)) << "] ("
				<< curr_tracker->get_visitation_index() << ", "
				<< curr_tracker->get_depth() << ", "
				<< "[" << node_list.has_element(write_node_ptr(curr_tracker->get_prime_parent())) << "," << node_list.find(write_node_ptr(curr_tracker->get_prime_parent())) << "], "
				<< curr_tracker->get_prime_child_index() << ") "
				<< node::has_backtracked() << ' ' 
				<< node::is_backtracking() << ' '
				<< "[" << node_list.has_element(write_node_ptr(node::tracker_repetition())) << "," << node_list.find(write_node_ptr(node::tracker_repetition())) << "] "
				<< '\n';

			node::advance_node_tracker();
		}
		std::cout << '\n';

		// Testing copy:
		
		node* copied_root_node = node::copy_subgraph(root_node);
		list ordered_node_list;
		list copied_node_list;
		node::set_node_tracker(root_node);
		while (!node::end_of_trace())
		{
			if (!node::has_backtracked())
			{
				ordered_node_list.append(write_node_ptr(node::get_node_tracker()));
			}
			node::advance_node_tracker();
		}
		node::set_node_tracker(copied_root_node);
		while (!node::end_of_trace())
		{
			if (!node::has_backtracked())
			{
				copied_node_list.append(write_node_ptr(node::get_node_tracker()));
			}
			node::advance_node_tracker();
		}

		for (int i = 0; i < ordered_node_list.get_list_size(); i++) // Testing the copied graph:
		{
			node* curr_node = read_node_ptr(ordered_node_list[i]);
			node* copied_node = read_node_ptr(copied_node_list[i]);
			if (curr_node->get_the_data() != copied_node->get_the_data()) // Check the node data:
			{
				std::cerr << "copy: [" << i << "]: Data does not match.\n";
			}
			if (curr_node->get_degree() != copied_node->get_degree()) // Check node degree:
			{
				std::cerr << "copy: [" << i << "]: Degrees do not match.\n";
			}
			for (int j = 0; j < curr_node->get_degree(); j++) // Check node children:
			{
				if (ordered_node_list.find(write_node_ptr(curr_node->get_child(j))) != copied_node_list.find(write_node_ptr(copied_node->get_child(j))))
				{
					std::cerr << "copy: [" << i << "]: Children do not match.\n";
				}
			}
		}

		// Testing print:

		std::cout << "Tesing print: \n"
			<< "Printing the root node:\n" 
			<< node::print(root_node) << "\n\n"
			<< "Printing the copied root node:\n"
			<< node::print(copied_root_node) << "\n\n";

		// Testing delete:

		std::cout << "Testing delete: \n";

		node* copied_root_node_2 = node::copy_subgraph(root_node);
		node* new_root_node = new node(simple_data::write_double(3.14));
		new_root_node->add_child(copied_root_node_2);

		node::destroy_subgraph(copied_root_node_2);
		std::cout << node::print(new_root_node) << '\n';

		/*for (int i = 0; ; i++) // Check for memory leaks:
		{
			node::destroy_subgraph(new_root_node);
			copied_root_node_2 = node::copy_subgraph(root_node);
			new_root_node = new node(simple_data::write_double(3.14));
			new_root_node->add_child(copied_root_node_2);
		}*/
	}
	catch (char* error)
	{
		std::cerr << error;
	}
#endif

#ifdef __TESTING_NODE_2__
	try
	{
		ifstream input("Test Files/node_test.txt");

		int num_of_roots;
		input >> num_of_roots;
		node** root_nodes = new node*[num_of_roots];

		for (int i = 0; i < num_of_roots; i++)
		{
			root_nodes[i] = node::read_node_from_stream(input);
			std::cout << node::print(root_nodes[i]) << "\n\n";
		}
		
		std::cout << "\nTesting product:\n";

		node* root_product_1 = node::product_subgraph(root_nodes[1], root_nodes[2], true);
		std::cout << node::print(root_product_1) << '\n';

		std::cout << '\n';
		
		node* root_product_2 = node::product_subgraph(root_nodes[3], root_nodes[4], true);
		std::cout << node::print(root_product_2) << '\n';

		std::cout << '\n';
		
		node* root_product_3 = node::product_subgraph(root_nodes[4], root_nodes[7], true);
		std::cout << node::print(root_product_3) << '\n';

		std::cout << '\n';
		
		node* root_product_4 = node::product_subgraph(root_nodes[4], root_nodes[7], false);
		std::cout << node::print(root_product_4) << '\n';
		
		std::cout << "\nTesting compare:\n";

		std::cout << node::compare(root_nodes[0],root_nodes[0]) << ' ' << node::compare(root_nodes[2],root_nodes[1]) << ' ' << node::compare(root_nodes[3],root_nodes[4]) << '\n';
		
		std::cout << "\nTesting condense:\n";

		node* condensed_node_1 = node::condense(root_nodes[5]);
		std::cout << node::print(condensed_node_1) << '\n';

		node* condensed_node_2 = node::condense(root_nodes[6]);
		std::cout << node::print(condensed_node_2) << '\n';
		
		std::cout << "\nTesting expand:\n";

		node* expanded_node_1 = node::copy_subgraph(root_nodes[2]);
		std::cout << node::print(expanded_node_1) << '\n';
		expanded_node_1->expand(1);
		std::cout << node::print(expanded_node_1) << '\n';

	}
	catch (char* error)
	{
		std::cerr << error;
	}
#endif

#ifdef __TESTING_ARITHMETIC__
	try
	{
		ifstream input("Test Files/arithmetic_test.txt");
		int num_of_data; 
		input >> num_of_data;
		simple_data* e_arr = new simple_data[num_of_data];
		for (int i = 0; i < num_of_data; i++)
		{
			e_arr[i] = simple_data(input);
			std::cout << e_arr[i].print() << "\n\n";
			std::cout << "Negative: \n" << (-e_arr[i]).print() << "\n\n";
			std::cout << "Reciprocal: \n" << inv(e_arr[i]).print() << "\n\n\n";
			//system("PAUSE");
		}

		std::cout << "Addition Testing:\n";
		for (int i = 0; i < num_of_data; i++)
		{
			for (int j = 0; j < num_of_data; j++)
			{
				std::cout << (e_arr[i] + e_arr[j]).print() << '\n'; 
			}
		}
		
		std::cout << "Multiplication Testing:\n";
		for (int i = 0; i < num_of_data; i++)
		{
			for (int j = 0; j < num_of_data; j++)
			{
				std::cout << (e_arr[i] * e_arr[j]).print() << '\n'; 
			}
		}

	}
	catch (char* error)
	{
		std::cerr << error;
	}
#endif

#ifdef __TESTING_ARITHMETIC_2__
	try 
	{
		ifstream input("Test Files/arithmetic_test_2.txt");
		int num_of_roots; 
		input >> num_of_roots;
		node** n_arr = new node*[num_of_roots];
		for (int i = 0; i < num_of_roots; i++)
		{
			n_arr[i] = node::read_node_from_stream(input);
			std::cout << node::print(n_arr[i]) << "\n\n";
			//system("PAUSE");
		}

		std::cout << "Testing Multiplication:\n";
		node* prod_1 = node_binary_op(n_arr[0],n_arr[1],false,OP_MULTIPLICATION);
		//std::cout << node::print(prod_1) << "\n\n";
		node* prod_2 = node_binary_op(prod_1,n_arr[2],false,OP_MULTIPLICATION);
		//std::cout << node::print(prod_2) << "\n\n";
		node* prod_3 = node_binary_op(prod_2,n_arr[3],false,OP_MULTIPLICATION);
		std::cout << node::print(prod_3) << "\n\n";

		/*for (int R = 0; R < 3; R++)
		{
			for (int V = 0; V < 2; V++)
			{
				for (int S = 0; S < 4; S++)
				{
					for (int C = 0; C < 3; C++)
					{
						node* node_x = prod_3;
						node_x = node_x->get_child(R);
						node_x = node_x->get_child(V);
						node_x = node_x->get_child(S);
						node_x = node_x->get_child(C);
						std::cout << node_x->get_the_data().print() << ' ';
					}
				}
				std::cout << '\n';
			}
		}*/

		/*std::cout << "Testing Negation:\n";
		node* neg_1 = node_unary_op(prod_3,OP_NEGATIVE,simple_data());
		std::cout << node::print(neg_1) << "\n\n";*/

		std::cout << "Testing Condition:\n";
		node* cond_1 = condition(prod_3,0,2,false);
		node* cond_2 = condition(cond_1,3,0,false);
		std::cout << node::print(cond_2) << "\n\n";

		std::cout << "Testing Marginalization:\n";
		node* marg_1 = marginalize(cond_2,2,false);
		std::cout << node::print(marg_1) << "\n\n";

		std::cout << "Testing Inversion:\n";
		node* marg_2 = marginalize(marg_1,1,true);
		node* inv_1 = node_unary_op(marg_2,OP_INVERSE,simple_data());
		std::cout << node::print(inv_1) << "\n\n";
		node* prod_4 = node_binary_op(marg_1,inv_1,false,OP_MULTIPLICATION);
		std::cout << node::print(prod_4) << "\n\n";
	}
	catch (char* error)
	{
		std::cerr << error;
	}
#endif

#ifdef __NO_TESTING__
	int experiment_index;
	std::cout << "Enter experiment number: ";
	std::cin >> experiment_index;
	std::cout << '\n';

	string curr_token;
	// Read data:
	string data_input_file_name = "Test Files/" + to_string(experiment_index) + "_data.txt";
	ifstream data_input(data_input_file_name);
	if (data_input.fail())
	{
		std::cerr << "Test Files/" + to_string(experiment_index) + "_data.txt not found.\n";
		system("PAUSE");
		return EXIT_FAILURE;
	}
	int num_of_subgraphs;
	data_input >> num_of_subgraphs;

	list name_list;
	list node_list;
	for (int i = 0; i < num_of_subgraphs; i++)
	{
		try
		{
			name_list.append(simple_data::write_string(read_token(data_input)));
			node_list.append(write_node_ptr(node::read_node_from_stream(data_input)));
		}
		catch (const char* error)
		{
			std::cerr << "reading data file: " << error << '\n';
			system("PAUSE");
			return EXIT_FAILURE;
		}

		std::cout << name_list[i].read_string() << " = " << node::print(read_node_ptr(node_list[i])) << "\n\n";
	}
	std::cout << "\n***********************************\n";

	// Generate output file:
	string output_file_name = "Test Files/" + to_string(experiment_index) + "_output.txt";
	ofstream output(output_file_name);

	// Read instructions:
	string instructions_input_file_name = "Test Files/" + to_string(experiment_index) + "_instructions.txt";
	ifstream instructions_input(instructions_input_file_name);
	if (data_input.fail())
	{
		std::cerr << "Test Files/" + to_string(experiment_index) + "_instructions.txt not found.\n";
		system("PAUSE");
		return EXIT_FAILURE;
	}
	
	do // An entire instruction is processed each iteration.
	{
		enum command_type { COM_ASSIGN_NEW_SUBGRAPH, 
							COM_ASSIGN_NODE, 
							COM_COPY_NODE,
							COM_COPY_SUBGRAPH, 
							COM_CONDENSE, 
							COM_EXPAND,
							COM_SUBGRAPH_PRODUCT, 
							COM_BINARY_OPERATOR,
							COM_ADD_SUBGRAPHS,
							COM_MULTIPLY_SUBGRAPHS, 
							COM_UNARY_OPERATOR,
							COM_NEGATE_SUBGRAPH,
							COM_INVERT_SUBGRAPH,
							COM_MARGINALIZE,
							COM_CONDITION,
							COM_DS_BINARY_OPERATOR,
							COM_DS_COLLAPSE,
							COM_PRINT_STRING,
							COM_PRINT_DATA,
							COM_PRINT_SUBGRAPH, 
							COM_COMMENT} the_command;

		curr_token = read_token(instructions_input); 
		if (curr_token == "")
		{
			break;
		}

		if (curr_token == "assign_new_subgraph") 
		{
			the_command = COM_ASSIGN_NEW_SUBGRAPH;
		}
		else if (curr_token == "assign_node") 
		{
			the_command = COM_ASSIGN_NODE;
		}
		else if (curr_token == "copy_node") 
		{
			the_command = COM_COPY_NODE;
		}
		else if (curr_token == "copy_subgraph") 
		{
			the_command = COM_COPY_SUBGRAPH;
		}
		else if (curr_token == "condense") 
		{
			the_command = COM_CONDENSE;
		}
		else if (curr_token == "expand")
		{
			the_command = COM_EXPAND;
		}
		else if (curr_token == "subgraph_product") 
		{
			the_command = COM_SUBGRAPH_PRODUCT;
		}
		else if (curr_token == "binary_operator")
		{
			the_command = COM_BINARY_OPERATOR;
		}
		else if (curr_token == "add_subgraphs")
		{
			the_command = COM_ADD_SUBGRAPHS;
		}
		else if (curr_token == "multiply_subgraphs")
		{
			the_command = COM_MULTIPLY_SUBGRAPHS;
		}
		else if (curr_token == "unary_operator")
		{
			the_command = COM_UNARY_OPERATOR;
		}
		else if (curr_token == "negate_subgraph")
		{
			the_command = COM_NEGATE_SUBGRAPH;
		}
		else if (curr_token == "invert_subgraph")
		{
			the_command = COM_INVERT_SUBGRAPH;
		}
		else if (curr_token == "marginalize")
		{
			the_command = COM_MARGINALIZE;
		}
		else if (curr_token == "condition")
		{
			the_command = COM_CONDITION;
		}
		else if (curr_token == "DS_binary_operator")
		{
			the_command = COM_DS_BINARY_OPERATOR;
		}
		else if (curr_token == "DS_collapse")
		{
			the_command = COM_DS_COLLAPSE;
		}
		else if (curr_token == "print_string")
		{
			the_command = COM_PRINT_STRING;
		}
		else if (curr_token == "print_data")
		{
			the_command = COM_PRINT_DATA;
		}
		else if (curr_token == "print_subgraph")
		{
			the_command = COM_PRINT_SUBGRAPH;
		}
		else if (curr_token == "comment")
		{
			the_command = COM_COMMENT;
		}
		else
		{
			std::cerr << "command not found.\n";
			system("PAUSE");
			return EXIT_FAILURE;
		}

		if (the_command == COM_ASSIGN_NEW_SUBGRAPH)
		{ // ASSIGN_NEW_SUBGRAPH
			try
			{
				string dest_name = read_token(instructions_input);
				node* new_graph = node::read_node_from_stream(instructions_input);
				instruction_set_name(name_list,node_list,dest_name,new_graph,"assign_new_subgraph");
			}
			catch (const char* error)
			{
				std::cerr << "assign_new_subgraph " << error << '\n';
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_ASSIGN_NODE)
		{ // ASSIGN_NODE
			try
			{
				string dest_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"assign_node");
				int depth;
				instructions_input >> depth;

				node* resultant_node = source_node;
				for (int i = 0; i < depth; i++)
				{ // ASSIGN_NODE
					int child_index;
					instructions_input >> child_index;
					if (child_index >= resultant_node->get_degree())
					{
						std::cerr << "assign_node source_name child node not found.\n";
						system("PAUSE");
						return EXIT_FAILURE;
					}
					resultant_node = resultant_node->get_child(child_index);
				}

				instruction_set_name(name_list,node_list,dest_name,resultant_node,"assign_node");
			}
			catch (const char* error)
			{
				std::cerr << "assign_node " << error << '\n';
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_COPY_NODE)
		{ // COPY_NODE
			try
			{
				string dest_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"copy_node");
				node* copied_node = new node(source_node);
				instruction_set_name(name_list,node_list,dest_name,copied_node,"copy_node");
			}
			catch (const char* error)
			{
				std::cerr << "copy_node " << error << '\n';
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_COPY_SUBGRAPH)
		{ // COPY_SUBGRAPH
			try
			{
				string dest_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"copy_subgraph");
				node* copied_node = node::copy_subgraph(source_node);
				instruction_set_name(name_list,node_list,dest_name,copied_node,"copy_subgraph");
			}
			catch (const char* error)
			{
				std::cerr << "copy_subgraph " << error << '\n';
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_CONDENSE)
		{ // CONDENSE
			try
			{
				string dest_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"condense");
				node* condensed_root = node::condense(source_node);
				instruction_set_name(name_list,node_list,dest_name,condensed_root,"condense");
			}
			catch (const char* error)
			{
				std::cerr << "condense " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_EXPAND)
		{ // EXPAND
			try
			{
				string dest_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"expand");
				int depth;
				instructions_input >> depth;
				node* expanded_root = node::copy_subgraph(source_node);
				expanded_root->expand(depth);
				instruction_set_name(name_list,node_list,dest_name,expanded_root,"expand");
			}
			catch (const char* error)
			{
				std::cerr << "expand " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_SUBGRAPH_PRODUCT)
		{ // SUBGRAPH_PRODUCT
			try
			{
				string dest_name = read_token(instructions_input);
				bool max_degree_flag;
				instructions_input >> max_degree_flag;
				node* source_node_1 = instruction_read_source_node(name_list,node_list,instructions_input,"subgraph_product");
				node* source_node_2 = instruction_read_source_node(name_list,node_list,instructions_input,"subgraph_product");

				node* product_node = node::product_subgraph(source_node_1, source_node_2, max_degree_flag);
				instruction_set_name(name_list,node_list,dest_name,product_node,"subgraph_product");
			}
			catch (const char* error)
			{
				std::cerr << "subgraph_product " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_BINARY_OPERATOR)
		{ // BINARY_OPERATOR
			try
			{
				string dest_name = read_token(instructions_input);
				string op_name = read_token(instructions_input);
				bool max_degree_flag;
				instructions_input >> max_degree_flag;
				node* source_node_1 = instruction_read_source_node(name_list,node_list,instructions_input,"binary_operator");
				node* source_node_2 = instruction_read_source_node(name_list,node_list,instructions_input,"binary_operator");

				node* result_node = NULL;
				if (op_name == "+")
				{
					result_node = node_binary_op(source_node_1,source_node_2,max_degree_flag,OP_ADDITION);
				}
				else if (op_name == "*")
				{
					result_node = node_binary_op(source_node_1,source_node_2,max_degree_flag,OP_MULTIPLICATION);
				}
				else if (op_name == "-")
				{
					result_node = node_binary_op(source_node_1,source_node_2,max_degree_flag,OP_SUBTRACTION);
				}
				else if (op_name == "/")
				{
					result_node = node_binary_op(source_node_1,source_node_2,max_degree_flag,OP_DIVISION);
				}
				else if (op_name == "max")
				{
					result_node = node_binary_op(source_node_1,source_node_2,max_degree_flag,OP_MAX);
				}
				else if (op_name == "min")
				{
					result_node = node_binary_op(source_node_1,source_node_2,max_degree_flag,OP_MIN);
				}
				else
				{
					std::cerr << "binary_operator: operator not found.\n";
					system("PAUSE");
					return EXIT_FAILURE;
				}
				instruction_set_name(name_list,node_list,dest_name,result_node,"binary_operator");
			}
			catch (const char* error)
			{
				std::cerr << "binary_operator " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_ADD_SUBGRAPHS)
		{ // ADD_SUBGRAPHS
			try
			{
				string dest_name = read_token(instructions_input);
				bool max_degree_flag;
				instructions_input >> max_degree_flag;
				int n;
				instructions_input >> n;
				node** summand_array = new node*[n];
				for (int i = 0; i < n; i++)
				{
					summand_array[i] = instruction_read_source_node(name_list,node_list,instructions_input,"add_subgraphs");
				}
				node* sum_root = NULL;
				if (n == 0)
				{
					sum_root = new node();
				}
				else 
				{
					sum_root = node::copy_subgraph(summand_array[0]);
					for (int i = 1; i < n; i++)
					{
						node* old_sum = sum_root;
						sum_root = node_binary_op(old_sum,summand_array[i],max_degree_flag,OP_ADDITION);
						node::destroy_subgraph(old_sum);
					}
				}

				delete[] summand_array;
				instruction_set_name(name_list,node_list,dest_name,sum_root,"add_subgraphs");
			}
			catch (const char* error)
			{
				std::cerr << "add_subgraphs " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_MULTIPLY_SUBGRAPHS)
		{ // MULTIPLY_SUBGRAPHS
			try
			{
				string dest_name = read_token(instructions_input);
				bool max_degree_flag;
				instructions_input >> max_degree_flag;
				int n;
				instructions_input >> n;
				node** multplicand_array = new node*[n];
				for (int i = 0; i < n; i++)
				{
					multplicand_array[i] = instruction_read_source_node(name_list,node_list,instructions_input,"multiply_subgraphs");
				}
				node* product_root = NULL;
				if (n == 0)
				{
					product_root = new node();
				}
				else 
				{
					product_root = node::copy_subgraph(multplicand_array[0]);
					for (int i = 1; i < n; i++)
					{
						node* old_product = product_root;
						product_root = node_binary_op(old_product,multplicand_array[i],max_degree_flag,OP_MULTIPLICATION);
						node::destroy_subgraph(old_product);
					}
				}

				delete[] multplicand_array;
				instruction_set_name(name_list,node_list,dest_name,product_root,"multiply_subgraphs");
			}
			catch (const char* error)
			{
				std::cerr << "multiply_subgraphs " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_UNARY_OPERATOR)
		{ // UNARY_OPERATOR
			try
			{
				string dest_name = read_token(instructions_input);
				string op_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"unary_operator");

				node* result_node = NULL;
				if (op_name == "-")
				{
					result_node = node_unary_op(source_node,OP_NEGATIVE,simple_data());
				}
				else if (op_name == "/")
				{
					result_node = node_unary_op(source_node,OP_INVERSE,simple_data());
				}
				else
				{
					std::cerr << "unary_operator: operator not found.\n";
					system("PAUSE");
					return EXIT_FAILURE;
				}
				instruction_set_name(name_list,node_list,dest_name,result_node,"unary_operator");
			}
			catch (const char* error)
			{
				std::cerr << "unary_operator " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_NEGATE_SUBGRAPH)
		{ // NEGATE_SUBGRAPH
			try
			{
				string dest_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"negate_subgraph");
				node* negated_graph = node_unary_op(source_node,OP_NEGATIVE,simple_data());
				instruction_set_name(name_list,node_list,dest_name,negated_graph,"negate_subgraph");
			}
			catch (const char* error)
			{
				std::cerr << "negate_subgraph " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_INVERT_SUBGRAPH)
		{ // INVERT_SUBGRAPH
			try
			{
				string dest_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"invert_subgraph");
				node* inverted_graph = node_unary_op(source_node,OP_INVERSE,simple_data());
				instruction_set_name(name_list,node_list,dest_name,inverted_graph,"invert_subgraph");
			}
			catch (const char* error)
			{
				std::cerr << "invert_subgraph " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_MARGINALIZE)
		{ // MARGINALIZE
			try
			{
				string dest_name = read_token(instructions_input);
				bool keep_degree_flag;
				instructions_input >> keep_degree_flag;
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"marginalize");
				int level;
				instructions_input >> level;
				node* marginalized_graph = marginalize(source_node,level,keep_degree_flag);
				instruction_set_name(name_list,node_list,dest_name,marginalized_graph,"marginalize");
			}
			catch (const char* error)
			{
				std::cerr << "marginalize " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_CONDITION)
		{ // CONDITION
			try
			{
				string dest_name = read_token(instructions_input);
				bool keep_degree_flag;
				instructions_input >> keep_degree_flag;
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"condition");
				int level;
				instructions_input >> level;
				int child_index;
				instructions_input >> child_index;
				node* conditioned_graph = condition(source_node,level,child_index,keep_degree_flag);
				instruction_set_name(name_list,node_list,dest_name,conditioned_graph,"condition");
			}
			catch (const char* error)
			{
				std::cerr << "condition " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_DS_BINARY_OPERATOR)
		{ // DS_BINARY_OPERATOR
			try
			{
				string dest_name = read_token(instructions_input);
				string op_name = read_token(instructions_input);
				bool max_degree_flag;
				instructions_input >> max_degree_flag;
				node* source_node_1 = instruction_read_source_node(name_list,node_list,instructions_input,"DS_binary_operator");
				node* source_node_2 = instruction_read_source_node(name_list,node_list,instructions_input,"DS_binary_operator");

				node* result_node = NULL;
				if (op_name == "+")
				{
					result_node = DS_binary_op(source_node_1,source_node_2,max_degree_flag,OP_ADDITION);
				}
				else if (op_name == "*")
				{
					result_node = DS_binary_op(source_node_1,source_node_2,max_degree_flag,OP_MULTIPLICATION);
				}
				else if (op_name == "-")
				{
					result_node = DS_binary_op(source_node_1,source_node_2,max_degree_flag,OP_SUBTRACTION);
				}
				else if (op_name == "/")
				{
					result_node = DS_binary_op(source_node_1,source_node_2,max_degree_flag,OP_DIVISION);
				}
				else if (op_name == "max")
				{
					result_node = DS_binary_op(source_node_1,source_node_2,max_degree_flag,OP_MAX);
				}
				else if (op_name == "min")
				{
					result_node = DS_binary_op(source_node_1,source_node_2,max_degree_flag,OP_MIN);
				}
				else
				{
					std::cerr << "DS_binary_operator: operator not found.\n";
					system("PAUSE");
					return EXIT_FAILURE;
				}
				instruction_set_name(name_list,node_list,dest_name,result_node,"DS_binary_operator");
			}
			catch (const char* error)
			{
				std::cerr << "DS_binary_operator " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_DS_COLLAPSE)
		{ // DS_COLLAPSE
			try
			{
				string dest_name = read_token(instructions_input);
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"DS_collapse");
				node* condensed_root = DS_collapse(source_node);
				instruction_set_name(name_list,node_list,dest_name,condensed_root,"DS_collapse");
			}
			catch (const char* error)
			{
				std::cerr << "DS_collapse " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_PRINT_STRING)
		{ // PRINT_STRING
			try
			{
				string the_string = read_token(instructions_input);
				output << the_string << "\n\n";
				std::cout << the_string << "\n\n"; 
			}
			catch (const char* error)
			{
				std::cerr << "print_string " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_PRINT_DATA)
		{ // PRINT_DATA
			try
			{
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"print_data");
				output << source_node->get_the_data().print() << "\n\n";
				std::cout << source_node->get_the_data().print() << "\n\n";
			}
			catch (const char* error)
			{
				std::cerr << "print_data " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_PRINT_SUBGRAPH)
		{ // PRINT_SUBGRAPH
			try
			{
				node* source_node = instruction_read_source_node(name_list,node_list,instructions_input,"print_data");
				output << node::print(source_node) << "\n\n";
				std::cout << node::print(source_node) << "\n\n";
			}
			catch (const char* error)
			{
				std::cerr << "print_subgraph " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
		else if (the_command == COM_COMMENT)
		{ // COMMENT
			try
			{
				string curr_token;
				do
				{
					curr_token = read_token(instructions_input);
				}
				while ((curr_token != "comment_end") && (curr_token != ""));
			}
			catch (const char* error)
			{
				std::cerr << "comment " << error;
				system("PAUSE");
				return EXIT_FAILURE;
			}
		}
	} while (curr_token != "");

#endif

	system("PAUSE");
	return EXIT_SUCCESS;
}

