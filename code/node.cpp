
#include "simple_data.h"
#include "box.h"
#include "pair.h"
#include "list.h"
#include "node.h"

#include "endless_array_i.h"
//#include "endless_array_p.h"

//#include "endless_hash_table_i.h"

#include "token_parsing.h"


#define CHILD_BLOCK_SIZE 10
#define PARENT_BLOCK_SIZE 10

node* read_node_ptr(const simple_data& the_data)
{
	return *reinterpret_cast<node**>(the_data.get_the_data());
}

simple_data write_node_ptr(node* new_node_ptr)
{
	return simple_data(TI_MEM_BLOCK,sizeof(node*),&new_node_ptr);
}

void node::append_to_child_list(node* new_child)
{
	// Crosslinking from the child is not done here.
	if (the_degree >= max_degree)
	{
		int new_max_degree = max_degree + CHILD_BLOCK_SIZE;
		node** new_children = new node*[new_max_degree];
		for (int i = 0; i < max_degree; i++)
		{
			new_children[i] = children[i];
		}
		for (int i = max_degree; i < new_max_degree; i++)
		{
			new_children[i] = NULL;
		}
		delete[] children;
		max_degree = new_max_degree;
		children = new_children;
	}
	children[the_degree] = new_child;
	the_degree++;
}

void node::remove_from_child_list(node* existing_child, bool remove_all_instances_flag)
{
	// Decrosslinking from the child is not done here.
	// Identify the children slated for removal:
	bool found_flag = false;
	bool *removal_flags = new bool[the_degree];
	for (int i = 0; i < the_degree; i++)
	{
		if (children[i] == existing_child)
		{
			if (remove_all_instances_flag || !found_flag)
			{
				removal_flags[i] = true;
			}
			else
			{
				removal_flags[i] = false;
			}
			found_flag = true;
		}
		else
		{
			removal_flags[i] = false;
		}
	}
	// Remove the defunct children:
	int dest_index = 0;
	int source_index = 0;
	while (source_index < the_degree)
	{
		if (!removal_flags[source_index])
		{
			children[dest_index] = children[source_index];
			dest_index++;
		}
		source_index++;
	}
	the_degree = dest_index;
}

void node::remove_from_child_list(int index)
{
	// Decrosslinking from the child is not done here.
	if (index >= the_degree)
	{
		throw "node::remove_from_child_list(int index): invalid child index.\n";
	}
	// Bump child pointers to the left:
	for (int i = index; i < the_degree-1; i++)
	{
		children[i] = children[i+1];
	}
	the_degree--;
}

void node::append_to_parent_list(node* new_parent)
{
	// Crosslinking from the parent is not done here.
	bool found_flag = false;
	for (int i = 0; i < max_num_of_parents; i++)
	{
		if (parents[i] == NULL)
		{
			parents[i] = new_parent;
			found_flag = true;
			break;
		}
	}
	if (!found_flag)
	{
		int new_max_num_of_parents = max_num_of_parents + PARENT_BLOCK_SIZE;
		node** new_parents = new node*[new_max_num_of_parents];
		for (int i = 0; i < max_num_of_parents; i++)
		{
			new_parents[i] = parents[i];
		}
		new_parents[max_num_of_parents] = new_parent;
		for (int i = max_num_of_parents+1; i < new_max_num_of_parents; i++)
		{
			new_parents[i] = NULL;
		}
		delete[] parents;
		max_num_of_parents = new_max_num_of_parents;
		parents = new_parents;
	}
}

void node::remove_from_parent_list(node* existing_parent, bool remove_all_instances_flag)
{
	// Decrosslinking from the parent is not done here.
	for (int i = 0; i < max_num_of_parents; i++)
	{
		if (parents[i] == existing_parent)
		{
			parents[i] = NULL;
			if (!remove_all_instances_flag)
			{
				return;
			}
		}
	}
}

// ****************************************************************

node::node()
{
	the_data = simple_data();

	max_degree = 0;
	the_degree = 0;
	children = new node*[0];

	max_num_of_parents = 0;
	parents = new node*[0];

	lock_existance_flag = false;

	visitation_indices = list();
	depths = list();
	prime_parents = list();
	prime_child_indices = list();
	extra_data = list();
}

node::node(simple_data new_data)
{
	the_data = new_data;

	max_degree = 0;
	the_degree = 0;
	children = new node*[0];

	max_num_of_parents = 0;
	parents = new node*[0];

	lock_existance_flag = false;

	visitation_indices = list();
	depths = list();
	prime_parents = list();
	prime_child_indices = list();
	extra_data = list();
}

node::node(simple_data new_data, int new_max_degree)
{
	the_data = new_data;

	max_degree = (new_max_degree/CHILD_BLOCK_SIZE + 1) * CHILD_BLOCK_SIZE;
	the_degree = 0;
	children = new node*[max_degree];
	for (int i = 0; i < max_degree; i++)
	{
		children[i] = NULL;
	}

	max_num_of_parents = 0;
	parents = new node*[0];
	
	lock_existance_flag = false;

	visitation_indices = list();
	depths = list();
	prime_parents = list();
	prime_child_indices = list();
	extra_data = list();
}

node::node(simple_data new_data, int new_degree, node** new_children) 
{
	the_data = new_data;

	max_degree = (new_degree/CHILD_BLOCK_SIZE + 1) * CHILD_BLOCK_SIZE;
	the_degree = new_degree;
	children = new node*[max_degree];
	for (int i = 0; i < the_degree; i++)
	{
		children[i] = new_children[i];
		children[i]->append_to_parent_list(this); // Crosslink from the child.
	}
	for (int i = the_degree; i < max_degree; i++)
	{
		children[i] = NULL;
	}

	max_num_of_parents = 0;
	parents = new node*[0];
	
	lock_existance_flag = false;

	visitation_indices = list();
	depths = list();
	prime_parents = list();
	prime_child_indices = list();
	extra_data = list();
}

void node::copy_node(node& existing_node)
{
	the_data = existing_node.the_data;

	max_degree = existing_node.max_degree;
	the_degree = existing_node.the_degree;
	children = new node*[max_degree];
	for (int i = 0; i < the_degree; i++)
	{
		children[i] = existing_node.children[i];
		children[i]->append_to_parent_list(this); // Crosslink from the child.
	}
	for (int i = the_degree; i < max_degree; i++)
	{
		children[i] = NULL;
	}

	max_num_of_parents = 0;
	parents = new node*[0];
	
	lock_existance_flag = false;

	visitation_indices = list();
	depths = list();
	prime_parents = list();
	prime_child_indices = list();
	extra_data = list();
}

node::node(node& existing_node)
{
	copy_node(existing_node);
}

node::node(node* existing_node)
{
	copy_node(*existing_node);
}

node& node::operator=(node& existing_node)
{
	the_data = existing_node.the_data;
	return *this;
}

node::~node()
{
	for (int i = 0; i < max_num_of_parents; i++)
	{
		if (parents[i] != NULL)
		{
			parents[i]->remove_from_child_list(this,true); // Decrosslink with the parent.
		}
	}
	for (int i = 0; i < the_degree; i++)
	{
		children[i]->remove_from_parent_list(this,true); // Decrosslink with the child.
	}

	delete[] children;
	delete[] parents;
}

// *******************************************

simple_data node::get_the_data()
{
	return the_data;
}

void node::set_the_data(const simple_data& new_data)
{
	the_data = new_data;
}

int node::get_degree()
{
	return the_degree;
}

node* node::get_child(int index)
{
	return children[index];
}

void node::add_child(node* new_child)
{
	append_to_child_list(new_child);
	new_child->append_to_parent_list(this); // Crosslink with the child.
}

void node::set_child(int index, node* new_child)
{
	if (index >= the_degree)
	{
		throw "node::set_child(int index, node* new_child): invalid child index.\n";
	}
	children[index]->remove_from_parent_list(this,false); // Decrosslink with the child.
	children[index] = new_child;
	children[index]->append_to_parent_list(this); // Crosslink with the child.
}

void node::delete_child(int index)
{
	if (index >= the_degree)
	{
		throw "node::delete_child(int index): invalid child index.\n";
	}
	children[index]->remove_from_parent_list(this,false); // Decrosslink with the child.
	remove_from_child_list(index);
}

bool node::is_loose()
{
	if (lock_existance_flag)
	{
		return false;
	}
	for (int i = 0; i < max_num_of_parents; i++)
	{
		if (parents[i] != NULL)
		{
			return false;
		}
	}
	return true;
}

void node::destroy_node(node* curr_node)
{
	if (curr_node->is_loose())
	{
		delete curr_node;
	}
}

void node::lock_existance()
{
	lock_existance_flag = true;
}

void node::unlock_existance()
{
	lock_existance_flag = false;
}

bool node::get_existance_lock_status()
{
	return lock_existance_flag;
}

// ***********************************************************

list node::node_trackers;
list node::visitation_lists;

int node::tracker_index = 0;

void node::set_node_tracker(node* target_node)
{
	// Set the node tracker:
	node_trackers.set_entry(tracker_index,write_node_ptr(target_node));

	// Set the visitation list:
	if (visitation_lists[tracker_index].get_type_id() == TI_VOID)
	{
		visitation_lists.set_entry(tracker_index,write_list_ptr(new list()));
	}
	else
	{
		read_list_ptr(visitation_lists[tracker_index])->resize(0);
	}
	read_list_ptr(visitation_lists[tracker_index])->append(write_node_ptr(target_node));

	// Set the visitation index:
	target_node->visitation_indices.set_entry(tracker_index,simple_data::write_int(0));

	// Set the depth:
	target_node->depths.set_entry(tracker_index,simple_data::write_int(0));

	// Set the prime parent:
	target_node->prime_parents.set_entry(tracker_index,write_node_ptr(NULL));

	// Set the prime child index:
	target_node->prime_child_indices.set_entry(tracker_index,simple_data::write_int(0));
}

node* node::get_node_tracker()
{
	return read_node_ptr(node_trackers[tracker_index]);
}

bool node::has_backtracked()
{
	return (read_node_ptr(node_trackers[tracker_index])->prime_child_indices[tracker_index].read_int() != 0);
}

bool node::is_backtracking()
{
	node* curr_tracker = read_node_ptr(node_trackers[tracker_index]);
	return (curr_tracker->prime_child_indices[tracker_index].read_int() 
		>= curr_tracker->the_degree);
}

node* node::tracker_repetition()
{
	// Get the current tracker node:
	node* curr_tracker = read_node_ptr(node_trackers[tracker_index]);

	// Get the current prime child index:
	int curr_prime_child_index = curr_tracker->prime_child_indices[tracker_index].read_int();

	if (curr_prime_child_index >= curr_tracker->the_degree) // return NULL if there are node children left, and backtracking is occurring. 
	{
		return NULL;
	}

	// Get the current prime child:
	node* curr_prime_child = curr_tracker->children[curr_prime_child_index];

	// Get the current visitation list:
	list* curr_visitation_list = read_list_ptr(visitation_lists[tracker_index]);

	// Search the visitation list for the prime child:
	for (int i = 0; i < curr_visitation_list->get_list_size(); i++)
	{
		// Get the visited node:
		node* visited_node = read_node_ptr((*curr_visitation_list)[i]);
		if (visited_node == curr_prime_child)
		{
			return curr_prime_child;
		}
	}
	return NULL;
}

void node::advance_node_tracker()
{
	// Get the current tracker node:
	node* curr_tracker = read_node_ptr(node_trackers[tracker_index]);

	if (curr_tracker == NULL)
	{
		return;
	}

	// Get the current prime child index:
	int curr_prime_child_index = curr_tracker->prime_child_indices[tracker_index].read_int();

	if (curr_prime_child_index >= curr_tracker->the_degree)
	{
		// Get the current prime parent:
		node* curr_prime_parent = read_node_ptr(curr_tracker->prime_parents[tracker_index]);

		// Move up to the parent:
		node_trackers.set_entry(tracker_index,write_node_ptr(curr_prime_parent));
	}
	else
	{
		// Get the current prime child:
		node* curr_prime_child = curr_tracker->children[curr_prime_child_index];

		// Get the current visitation list:
		list* curr_visitation_list = read_list_ptr(visitation_lists[tracker_index]);

		// Search the visitation list for the prime child:
		bool found_flag = false;
		for (int i = 0; !found_flag && (i < curr_visitation_list->get_list_size()); i++)
		{
			// Get the visited node:
			node* visited_node = read_node_ptr((*curr_visitation_list)[i]);
			if (visited_node == curr_prime_child)
			{
				found_flag = true;
			}
		}

		curr_tracker->prime_child_indices.set_entry(tracker_index,simple_data::write_int(curr_prime_child_index+1)); // Advance the prime child_index.

		if (!found_flag)
		{
			int old_visitation_list_size = curr_visitation_list->get_list_size();

			node_trackers.set_entry(tracker_index,write_node_ptr(curr_prime_child));
			curr_visitation_list->append(write_node_ptr(curr_prime_child));

			curr_prime_child->visitation_indices.set_entry(tracker_index,simple_data::write_int(old_visitation_list_size));
			curr_prime_child->depths.set_entry(tracker_index,simple_data::write_int(curr_tracker->depths[tracker_index].read_int()+1));
			curr_prime_child->prime_parents.set_entry(tracker_index,write_node_ptr(curr_tracker));
			curr_prime_child->prime_child_indices.set_entry(tracker_index,simple_data::write_int(0));
		}
	}
}

bool node::end_of_trace()
{
	return (read_node_ptr(node_trackers[tracker_index]) == NULL);
}

int node::get_num_of_visited_nodes()
{
	return read_list_ptr(visitation_lists[tracker_index])->get_list_size();
}

node* node::get_visited_node(int visitation_index)
{
	return read_node_ptr((*read_list_ptr(visitation_lists[tracker_index]))[visitation_index]);
}

bool node::has_visited_node(node* target_node)
{
	// Get the current visitation list:
	list* curr_visitation_list = read_list_ptr(visitation_lists[tracker_index]);

	for (int i = 0; i < curr_visitation_list->get_list_size(); i++)
	{
		if (read_node_ptr((*curr_visitation_list)[i]) == target_node)
		{
			return true;
		}
	}
	return false;
}

int node::get_visitation_index()
{
	return visitation_indices[tracker_index].read_int();
}

int node::get_depth()
{
	return depths[tracker_index].read_int();
}

node* node::get_prime_parent()
{
	return read_node_ptr(prime_parents[tracker_index]);
}

int node::get_prime_child_index()
{
	return prime_child_indices[tracker_index].read_int();
}

void node::write_extra_data(const simple_data& new_extra_data)
{
	extra_data.set_entry(tracker_index,new_extra_data);
}

simple_data node::read_extra_data()
{
	return extra_data[tracker_index];
}

// Complex routines have been moved to: "node_2.cpp"

#undef CHILD_BLOCK_SIZE
#undef PARENT_BLOCK_SIZE 