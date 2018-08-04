
#include "simple_data.h"
#include "box.h"
#include "pair.h"
#include "list.h"
#include "node.h"

#include "endless_array_i.h"
//#include "endless_array_p.h"

//#include "endless_hash_table_i.h"

#include "token_parsing.h"


void node::destroy_subgraph(node* root_node)
{
	tracker_index++;

	// DESTROY
	set_node_tracker(root_node);

	while (!end_of_trace())
	{ // DESTROY

		advance_node_tracker();
	}

	int num_of_visited_nodes = get_num_of_visited_nodes();

	// An array that tracks which nodes are untouchable, and which are not. 
	// Once an anchored flag is set to true, it stays true.
	bool* anchored_flags = new bool[num_of_visited_nodes]; 

	for (int i = 0; i < num_of_visited_nodes; i++) // Anchored flag array initialization:
	{ // DESTROY
		anchored_flags[i] = get_visited_node(i)->get_existance_lock_status(); 
	}

	// Iteratively update the array of anchored flags until no more changes are being made:
	bool complete_flag = false;
	while (!complete_flag)
	{ // DESTROY
		complete_flag = true;
		for (int i = 0; i < num_of_visited_nodes; i++)
		{ // DESTROY
			if (anchored_flags[i]) // Skip the iteration if the node is already known to be anchored.
			{
				continue;
			}
			node* curr_node = get_visited_node(i);
			for (int j = 0; j < curr_node->max_num_of_parents; j++)
			{ // DESTROY
				if (curr_node->parents[j] != NULL)
				{
					if (!has_visited_node(curr_node->parents[j])) // Is the parent outside of the set of visited nodes?
					{
						anchored_flags[i] = true;
						complete_flag = false;
						break;
					}
					else 
					{
						int parent_visitation_index = curr_node->parents[j]->get_visitation_index();
						if (anchored_flags[parent_visitation_index]) // Is the parent anchored?
						{
							anchored_flags[i] = true;
							complete_flag = false;
							break;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < num_of_visited_nodes; i++) // Destroy the unanchored nodes
	{ // DESTROY
		if (!anchored_flags[i])
		{
			delete get_visited_node(i);
		}
	}

	delete[] anchored_flags;

	tracker_index--;
}


node* node::copy_subgraph(node* root_node)
{
	tracker_index++;

	// COPY
	set_node_tracker(root_node);

	while (!end_of_trace())
	{ // COPY
		node* curr_node = get_node_tracker();

		if (!has_backtracked())
		{ // COPY First visit to the node, make a copy.
			node* copied_node = new node(curr_node->get_the_data());

			node* parent_node = curr_node->get_prime_parent();
			if (parent_node != NULL)
			{
				// Get the copy of the parent.
				node* copied_parent_node = read_node_ptr(parent_node->read_extra_data());
				// Add the copy to the parent copy's children.
				copied_parent_node->add_child(copied_node);
			}

			// Save a reference to the copy.
			curr_node->write_extra_data(write_node_ptr(copied_node));
		}

		if (!is_backtracking())
		{ // COPY Still children left.

			node* repeat_child = tracker_repetition();

			if (repeat_child != NULL)
			{ // COPY connect any existing copies.
				node* copied_node = read_node_ptr(curr_node->read_extra_data());
				node* copied_child_node = read_node_ptr(repeat_child->read_extra_data());

				copied_node->add_child(copied_child_node);
			}
		}

		// COPY
		advance_node_tracker();
	}

	node* copied_root_node = read_node_ptr(root_node->read_extra_data());

	tracker_index--;

	return copied_root_node;
}


node* node::product_subgraph(node* root_node_1, node* root_node_2, int outer_product_flag)
{
	tracker_index++;

	// PRODUCT

	if (visitation_lists[tracker_index].get_type_id() == TI_VOID) // Initialize the visitation list if necessary. 
	{
		visitation_lists.set_entry(tracker_index,write_list_ptr(new list()));
	}
	else
	{
		read_list_ptr(visitation_lists[tracker_index])->resize(0);
	}
	list* curr_visitation_list = read_list_ptr(visitation_lists[tracker_index]);

	simple_data data_1 = root_node_1->get_the_data();
	simple_data data_2 = root_node_2->get_the_data();
	node* product_root_node = new node(simple_data::write_pair(data_pair(data_1,data_2)));
	product_root_node->write_extra_data(simple_data::write_pair(data_pair(write_node_ptr(root_node_1),write_node_ptr(root_node_2))));
	product_root_node->visitation_indices.set_entry(tracker_index,simple_data::write_int(0));
	product_root_node->depths.set_entry(tracker_index,simple_data::write_int(0));
	product_root_node->prime_parents.set_entry(tracker_index,write_node_ptr(NULL));
	product_root_node->prime_child_indices.set_entry(tracker_index,simple_data::write_int(0));

	curr_visitation_list->append(write_node_ptr(product_root_node));

	node* curr_product_node = product_root_node;
	while (curr_product_node != NULL)
	{ // PRODUCT
		// Get the two nodes whose pair forms the current product node:
		node* curr_node_1 = read_node_ptr(curr_product_node->read_extra_data().read_pair().get_data_1());
		node* curr_node_2 = read_node_ptr(curr_product_node->read_extra_data().read_pair().get_data_2());

		// Get the current prime child index:
		int curr_prime_child_index = curr_product_node->prime_child_indices[tracker_index].read_int();

		bool backtrack_flag = true;
		if (outer_product_flag) // The backtracking conditions differ depending on the outer product status. 
		{
			if (curr_node_1 != NULL)
			{
				if (curr_prime_child_index < curr_node_1->the_degree)
				{
					backtrack_flag = false;
				}
			}
			if (curr_node_2 != NULL)
			{
				if (curr_prime_child_index < curr_node_2->the_degree)
				{
					backtrack_flag = false;
				}
			}
		}
		else
		{
			if ((curr_node_1 != NULL) && (curr_node_2 != NULL))
			{
				if ((curr_prime_child_index < curr_node_1->the_degree) && (curr_prime_child_index < curr_node_2->the_degree))
				{
					backtrack_flag = false;
				}
			}
		}
		if (backtrack_flag)
		{ // PRODUCT
			// Get the current prime parent:
			node* curr_prime_parent = read_node_ptr(curr_product_node->prime_parents[tracker_index]);

			// Move up to the parent:
			curr_product_node = curr_prime_parent;
		}
		else
		{ // PRODUCT

			// Get the current prime child for each component node:
			node* curr_prime_child_1 = NULL;
			if (curr_node_1 != NULL)
			{
				if (curr_prime_child_index < curr_node_1->the_degree)
				{
					curr_prime_child_1 = curr_node_1->children[curr_prime_child_index];
				}
			}
			node* curr_prime_child_2 = NULL;
			if (curr_node_2 != NULL)
			{
				if (curr_prime_child_index < curr_node_2->the_degree)
				{
					curr_prime_child_2 = curr_node_2->children[curr_prime_child_index];
				}
			}
			bool found_flag = false;
			node* found_node = NULL;
			for (int i = 0; !found_flag && (i < curr_visitation_list->get_list_size()); i++)
			{ // PRODUCT
				node* visited_node = read_node_ptr((*curr_visitation_list)[i]);
				node* visited_node_1 = read_node_ptr(visited_node->read_extra_data().read_pair().get_data_1());
				node* visited_node_2 = read_node_ptr(visited_node->read_extra_data().read_pair().get_data_2());
				if ((visited_node_1 == curr_prime_child_1) && (visited_node_2 == curr_prime_child_2))
				{
					found_flag = true;
					found_node = visited_node;
				}
			}
			
			// Advance the prime child index:
			curr_product_node->prime_child_indices.set_entry(tracker_index,simple_data::write_int(curr_prime_child_index+1));

			if (found_flag)
			{ // PRODUCT
				curr_product_node->add_child(found_node);
			}
			else
			{ // PRODUCT

				data_1 = simple_data();
				if (curr_prime_child_1 != NULL)
				{
					data_1 = curr_prime_child_1->get_the_data();
				}
				data_2 = simple_data();
				if (curr_prime_child_2 != NULL)
				{
					data_2 = curr_prime_child_2->get_the_data();
				}

				node* next_product_node = new node(simple_data::write_pair(data_pair(data_1,data_2)));
				next_product_node->write_extra_data(simple_data::write_pair(data_pair(write_node_ptr(curr_prime_child_1),write_node_ptr(curr_prime_child_2))));
				next_product_node->visitation_indices.set_entry(tracker_index,simple_data::write_int(curr_visitation_list->get_list_size()));
				next_product_node->depths.set_entry(tracker_index,simple_data::write_int(curr_product_node->depths[tracker_index].read_int()+1));
				next_product_node->prime_parents.set_entry(tracker_index,write_node_ptr(curr_product_node));
				next_product_node->prime_child_indices.set_entry(tracker_index,simple_data::write_int(0));

				curr_product_node->add_child(next_product_node);
				curr_visitation_list->append(write_node_ptr(next_product_node));

				curr_product_node = next_product_node;
			}
		}
	}

	tracker_index--;

	return product_root_node;
}


short node::compare(node* node_1, node* node_2)
{
	tracker_index++;

	// COMPARE

	node* product_root_node = product_subgraph(node_1, node_2, true);

	set_node_tracker(product_root_node);

	while (!end_of_trace())
	{ // COMPARE
		if (!has_backtracked())
		{
			node* curr_node = get_node_tracker();
			simple_data data_1 = curr_node->get_the_data().read_pair().get_data_1();
			simple_data data_2 = curr_node->get_the_data().read_pair().get_data_2();
			int c = data_1.compare(data_2);
			if (c != 0)
			{
				destroy_subgraph(product_root_node);
				tracker_index--;
				return c;
			}
		}

		// COMPARE
		advance_node_tracker();
	}
	
	destroy_subgraph(product_root_node);
	tracker_index--;
	return 0;
}


node* node::read_node_from_stream(istream& input)
{
	tracker_index++;

	// READ

	string curr_token;

	// Check if the root node is a molded table:
	curr_token = read_token(input);
	if (curr_token == "table")
	{
		tracker_index--;
		return read_table(input);
	}
	else if (curr_token != "new")
	{
		tracker_index--;
		throw "node::read_node_from_stream: expected \"new\" or \"table\".\n";
	}

	node* root_node = new node(simple_data(input));

	set_node_tracker(root_node);

	while (!end_of_trace())
	{ // READ
		node* curr_node = get_node_tracker();

		bool end_of_children_flag;
		bool manual_advance_tracker_flag = false; // The tracker is only manually advanced in the case of tables.

		curr_token = read_token(input);
		if (curr_token == "{") // Skip over any comment.
		{
			while (curr_token != "}")
			{
				curr_token = read_token(input);
				if (input.eof())
				{
					tracker_index--;
					throw "node::read_node_from_stream: \"}\" not found\n";
				}
			}
			curr_token = read_token(input);
		}

		if (!has_backtracked())
		{ // READ
			if (curr_token == "*")
			{
				end_of_children_flag = true;
			}
			else if (curr_token == "<")
			{
				end_of_children_flag = false;
			}
			else
			{
				tracker_index--;
				throw "node::read_node_from_stream: expected \"*\" or \"<\"\n";
			}
		}
		else
		{ // READ
			if (curr_token == ">")
			{
				end_of_children_flag = true;
			}
			else if (curr_token == ",")
			{
				end_of_children_flag = false;
			}
			else
			{
				tracker_index--;
				throw "node::read_node_from_stream: expected \">\" or \",\"\n";
			}
		}

		if (!end_of_children_flag)
		{
			curr_token = read_token(input);
			if (curr_token == "{") // Skip over any comment.
			{
				while (curr_token != "}")
				{
					curr_token = read_token(input);
					if (input.eof())
					{
						tracker_index--;
						throw "node::read_node_from_stream: \"}\" not found\n";
					}
				}
				curr_token = read_token(input);
			}

			if (curr_token == "new")
			{ // READ
				node* new_node = new node(simple_data(input));
				curr_node->add_child(new_node);
			}
			else if (curr_token == "ref")
			{ // READ
				int node_ref_index = stoi(read_token(input));
				if (node_ref_index >= get_num_of_visited_nodes())
				{
					tracker_index--;
					throw "node::read_node_from_stream: node ref index too high.\n";
				}
				node* the_node_ref = get_visited_node(node_ref_index);
				curr_node->add_child(the_node_ref);
			}	
			else if (curr_token == "addr")
			{ // READ
				node* the_node_ref = curr_node;
				do
				{
					curr_token = read_token(input);
					
					if (curr_token == "!") // Return to the root:
					{
						the_node_ref = root_node;
					}
					else if (curr_token == "^") // Pull up to the prime parent:
					{ // READ
						node* the_node_ref_prime_parent = the_node_ref->get_prime_parent();
						if (the_node_ref_prime_parent != NULL)
						{
							the_node_ref = the_node_ref_prime_parent;
						}
						else
						{
							tracker_index--;
							throw "node::read_node_from_stream: relative reference parent not found.\n";
						}
					}
					else if (curr_token == "@") // Remain at the current node and finish:
					{ // READ
						break;
					}
					else
					{ // READ
						bool is_number_flag = true;
						for (int i = 0; i < (int) curr_token.length(); i++)
						{
							if (!isdigit(curr_token[i]))
							{
								is_number_flag = false;
							}
						}
						if (is_number_flag) // Descend to the indicated child:
						{
							int child_index = stoi(curr_token);
							if (child_index < the_node_ref->get_degree())
							{
								the_node_ref = the_node_ref->get_child(child_index);
							}
							else
							{
								tracker_index--;
								throw "node::read_node_from_stream: relative reference child not found.\n";
							}
						}
						else
						{
							tracker_index--;
							throw "node::read_node_from_stream: expected \"!\", \"^\", \"@\", or a number.\n";
						}
					}
				} while (curr_token != "@");
				curr_node->add_child(the_node_ref);
			}
			else if (curr_token == "table")
			{
				curr_node->add_child(read_table(input));
				advance_node_tracker(); // Advance the node tracker through the newly created tree.
				while (get_node_tracker() != curr_node)
				{
					advance_node_tracker();
				}
				manual_advance_tracker_flag = true;
			}
			else
			{ // READ
				tracker_index--;
				throw "node::read_node_from_stream: expected \"new\", \"ref\", \"addr\", or \"table\".\n";
			}
		}

		if (!manual_advance_tracker_flag)
		{
			advance_node_tracker();
		}
	}

	tracker_index--;

	return root_node;
}


node* node::read_table(istream& input)
{
	// Read the number of variables:
	int num_of_variables;
	input >> num_of_variables;
	if (num_of_variables < 0)
	{
		throw "node::read_table: the number of variables cannot be negative.\n";
	}

	// Get the data related to each variable:
	enum variable_type {VT_NORMAL, VT_INACTIVE, VT_SPECIFIC};
	variable_type* the_variable_types = new variable_type[num_of_variables];
	simple_data* variable_names = new simple_data[num_of_variables];
	int* domain_sizes = new int[num_of_variables];
	int* specific_child_indices = new int[num_of_variables];
	for (int i = 0; i < num_of_variables; i++)
	{ // READ TABLE
		string curr_token = read_token(input);
		if (curr_token == "normal")
		{ // READ TABLE
			the_variable_types[i] = VT_NORMAL;
		}
		else if (curr_token == "inactive")
		{
			the_variable_types[i] = VT_INACTIVE;
		}
		else if (curr_token == "specific")
		{
			the_variable_types[i] = VT_SPECIFIC;
		}
		else
		{
			throw "node::read_table: invalid variable type.\n";
		}
		variable_names[i] = simple_data(input);
		domain_sizes[i] = stoi(read_token(input));
		if (the_variable_types[i] == VT_SPECIFIC)
		{ // READ TABLE
			specific_child_indices[i] = stoi(read_token(input));
		}
		else
		{
			specific_child_indices[i] = 0;
		}
	}

	// Get the default value:
	simple_data the_default_value = simple_data(input);
	node** default_nodes = new node*[num_of_variables+1];
	default_nodes[num_of_variables] = new node(the_default_value);
	for (int i = num_of_variables-1; i >= 0; i--)
	{ // READ TABLE
		default_nodes[i] = new node(variable_names[i]);
		for (int j = 0; j < domain_sizes[i]; j++)
		{
			default_nodes[i]->add_child(default_nodes[i+1]);
		}
	}

	// Start constructing the decision tree/diagram:
	node* root_node = new node();

	// Initialize the current assignment:
	int* curr_assignment = new int[num_of_variables];
	for (int i = 0; i < num_of_variables; i++)
	{ // READ TABLE
		if (the_variable_types[i] != VT_SPECIFIC)
		{
			curr_assignment[i] = 0;
		}
		else
		{
			curr_assignment[i] = specific_child_indices[i];
		}
	}

	// Iteratively construct the decision tree one leaf node at a time:
	bool complete_flag = false;
	do
	{ // READ TABLE
		// Poke through to the leaf node:
		node* leaf_node = root_node;
		for (int i = 0; i < num_of_variables; i++)
		{ // READ TABLE
			if (leaf_node->get_degree() == 0) // The first visit to a non-leaf node.
			{
				leaf_node->set_the_data(variable_names[i]); // Label the node with the variable name.

				// Create the necessary child nodes and child connections.
				if (the_variable_types[i] == VT_NORMAL)
				{ // READ TABLE
					for (int j = 0; j < domain_sizes[i]; j++)
					{
						leaf_node->add_child(new node());
					}
				}
				else if (the_variable_types[i] == VT_INACTIVE)
				{ // READ TABLE
					node* common_child = new node();
					for (int j = 0; j < domain_sizes[i]; j++)
					{
						leaf_node->add_child(common_child);
					}
				}
				else if (the_variable_types[i] == VT_SPECIFIC)
				{ // READ TABLE
					for (int j = 0; j < domain_sizes[i]; j++)
					{
						if (j == specific_child_indices[i])
						{
							leaf_node->add_child(new node());
						}
						else
						{
							leaf_node->add_child(default_nodes[i+1]);
						}
					}
				}
				else
				{
					throw "node::read_table: invalid variable type.\n";
				}
			}

			// Advance towards the desired leaf node:
			leaf_node = leaf_node->get_child(curr_assignment[i]);
		}

		// Read data to the leaf node:
		leaf_node->set_the_data(simple_data(input));

		// Advance the assignment:
		bool carry_flag = true;
		int variable_index = num_of_variables-1;
		while (carry_flag && variable_index >= 0)
		{ // READ TABLE
			if (the_variable_types[variable_index] == VT_NORMAL)
			{
				if (curr_assignment[variable_index] < domain_sizes[variable_index]-1)
				{
					curr_assignment[variable_index]++;
					carry_flag = false;
				}
				else
				{
					curr_assignment[variable_index] = 0;
					variable_index--;
				}
			}
			else
			{
				variable_index--;
			}
		}
		if (carry_flag)
		{
			complete_flag = true;
		}
	} while (!complete_flag);

	delete[] the_variable_types;
	delete[] variable_names;
	delete[] domain_sizes;
	delete[] specific_child_indices;

	node::destroy_subgraph(default_nodes[0]);
	delete[] default_nodes;
	delete[] curr_assignment;

	return root_node;
}


string node::print(node* root_node)
{
	tracker_index++;

	// PRINT

	endless_array_i::next_layer();

	int output_length = 0;
	string curr_string = ""; 

	endless_array_i::write_data(0,output_length,1,4,"new ");
	output_length += 4;

	set_node_tracker(root_node);

	while (!end_of_trace())
	{ // PRINT
		node* curr_node = get_node_tracker();

		int curr_prime_child_index = curr_node->get_prime_child_index();

		bool first_visit_flag = !has_backtracked();
		bool last_visit_flag = is_backtracking();

		if (first_visit_flag) // Is it the first visit to the node?
		{ // PRINT
			curr_string = curr_node->get_the_data().print();
			endless_array_i::write_data(0,output_length,1,curr_string.length(),curr_string.c_str());
			output_length += curr_string.length();
			if (last_visit_flag) // Is it also the last visit to the node?
			{
				endless_array_i::write_data(0,output_length,1,3," * ");
				output_length += 3;
			}
			else
			{
				endless_array_i::write_data(0,output_length,1,3," < ");
				output_length += 3;
			}
		}
		else 
		{ // PRINT
			if (last_visit_flag) // Is it the last visit to the node?
			{
				endless_array_i::write_data(0,output_length,1,3," > ");
				output_length += 3;
			}
			else
			{
				endless_array_i::write_data(0,output_length,1,3," , ");
				output_length += 3;
			}
		}

		if (!last_visit_flag) // Are there children left unprobed?
		{ // PRINT
			node* repeated_node = tracker_repetition();
			if (repeated_node == NULL)
			{
				endless_array_i::write_data(0,output_length,1,5," new ");
				output_length += 5;
			}
			else
			{
				int repeated_visitation_index = repeated_node->get_visitation_index();
				endless_array_i::write_data(0,output_length,1,5," ref ");
				output_length += 5;
				curr_string = to_string(repeated_visitation_index);
				endless_array_i::write_data(0,output_length,1,curr_string.length(),curr_string.c_str());
				output_length += curr_string.length();
				endless_array_i::write_data(0,output_length,1,1," ");
				output_length += 1;
			}
		}

		advance_node_tracker();
	}

	char* printed_c_string = new char[output_length];
	endless_array_i::read_data(0,0,1,output_length,printed_c_string);
	string printed_string = string(printed_c_string,output_length);
	delete[] printed_c_string;

	endless_array_i::previous_layer();

	tracker_index--;

	return printed_string;
	
}


node* node::condense(node* root_node)
{
	tracker_index++;

	// CONDENSE

	// First, find the set of all visited nodes

	set_node_tracker(root_node);

	while (!end_of_trace())
	{ // CONDENSE
		advance_node_tracker();
	}

	int num_of_visited_nodes = get_num_of_visited_nodes();

	// Second, initialize and iteratively refine the equivalence matrix:

	bool* equivalence_matrix = new bool[num_of_visited_nodes*num_of_visited_nodes];

	for (int i = 0; i < num_of_visited_nodes; i++)
	{ // CONDENSE
		for (int j = 0; j < num_of_visited_nodes; j++)
		{
			equivalence_matrix[num_of_visited_nodes*i+j] = true; // All equivalences will be assumed to be initially true.
		}
	}
	
	for (int i = 0; i < num_of_visited_nodes; i++) // Differentiate nodes based on their stored data or degree:
	{ // CONDENSE
		node* node_1 = get_visited_node(i);
		for (int j = 0; j < num_of_visited_nodes; j++)
		{
			node* node_2 = get_visited_node(j);
			if (node_1->the_data != node_2->the_data)
			{
				equivalence_matrix[num_of_visited_nodes*i+j] = false;
			}
			if (node_1->the_degree != node_2->the_degree)
			{
				equivalence_matrix[num_of_visited_nodes*i+j] = false;
			}
		}
	}

	bool complete_flag = false;
	while (!complete_flag)
	{ // CONDENSE
		complete_flag = true;
		for (int i = 0; i < num_of_visited_nodes; i++) // Differentiate the nodes based on the equivalence of their children
		{
			node* node_1 = get_visited_node(i);
			for (int j = 0; j < num_of_visited_nodes; j++)
			{
				node* node_2 = get_visited_node(j);
				if (equivalence_matrix[num_of_visited_nodes*i+j]) // Are the nodes currently believed to be equal?
				{
					for (int k = 0; k < node_1->the_degree; k++)
					{
						// Access the endless array block indices for each child:
						int node_1_child_index = node_1->children[k]->get_visitation_index();
						int node_2_child_index = node_2->children[k]->get_visitation_index();
						if (!equivalence_matrix[num_of_visited_nodes*node_1_child_index+node_2_child_index]) // Break the equivalence if the children are not also equivalent:
						{
							complete_flag = false; // Another sweep is needed.
							equivalence_matrix[num_of_visited_nodes*i+j] = false;
							break;
						}
					}
				}
			}
		}
	}

	// Third, establish the new condensed network:

	node** new_nodes = new node*[num_of_visited_nodes];

	for (int i = 0; i < num_of_visited_nodes; i++) // Create the new nodes:
	{ // CONDENSE
		bool found_flag = false; // Has a copy of an equivalent node already been created?
		for (int j = 0; j < i && !found_flag; j++)
		{
			if (equivalence_matrix[num_of_visited_nodes*i+j])
			{
				found_flag = true;
				new_nodes[i] = new_nodes[j];
			}
		}
		if (!found_flag) // If not, create a new copy.
		{
			new_nodes[i] = new node(get_visited_node(i)->get_the_data());
		}
	}

	for (int i = 0; i < num_of_visited_nodes; i++) // Connect the children:
	{ // CONDENSE
		bool found_flag = false; // Has the children already been connected?
		for (int j = 0; j < i && !found_flag; j++)
		{
			if (equivalence_matrix[num_of_visited_nodes*i+j])
			{
				found_flag = true;
			}
		}
		if (!found_flag) // If not, connect the appropriate children.
		{
			node* visited_node = get_visited_node(i);
			node* copied_node = new_nodes[i];
			for (int k = 0; k < visited_node->get_degree(); k++)
			{
				int child_visitation_index = visited_node->get_child(k)->get_visitation_index();
				copied_node->add_child(new_nodes[child_visitation_index]);
			}
		}
	}

	node* new_root_node = new_nodes[0];

	delete[] equivalence_matrix;
	delete[] new_nodes;

	tracker_index--;

	return new_root_node; 
}


void node::expand(int level)
{
	tracker_index++;

	// EXPAND
	set_node_tracker(this);

	while (!end_of_trace())
	{ // EXPAND
		node* curr_node = get_node_tracker();

		if ((curr_node->get_depth() == level) && !is_backtracking())
		{
			// Separate the child subgraphs:
			int curr_prime_child_index = curr_node->get_prime_child_index();

			node* old_child = curr_node->get_child(curr_prime_child_index);
			curr_node->set_child(curr_prime_child_index, copy_subgraph(old_child));
			destroy_subgraph(old_child);
		}

		advance_node_tracker();
	}

	tracker_index--;
}


void node::expand_2(int depth, bool full_expand_flag)
{
	tracker_index++;

	// EXPAND_2
	set_node_tracker(this);

	while (!end_of_trace())
	{ // EXPAND_2
		node* curr_node = get_node_tracker();

		int curr_prime_child_index = curr_node->get_prime_child_index();

		node* visited_node = tracker_repetition();
		if (visited_node != NULL)
		{
			if (!full_expand_flag)
			{
				if (((curr_node->get_depth() < depth)  && (visited_node->get_depth() != curr_node->get_depth()+1)) || // No shortcuts before "depth",
					((curr_node->get_depth() >= depth) && (visited_node->get_depth() < depth))) // No longcut returns to above "depth"
				{
					curr_node->set_child(curr_prime_child_index,new node(visited_node));
				}
			}
			else
			{
				if ((curr_node->get_depth() < depth) ||  
					((curr_node->get_depth() >= depth) && (visited_node->get_depth() < depth))) // No longcut returns to above "depth"
				{
					curr_node->set_child(curr_prime_child_index,new node(visited_node));
				}
			}
		}


		advance_node_tracker();
	}

	tracker_index--;
}

