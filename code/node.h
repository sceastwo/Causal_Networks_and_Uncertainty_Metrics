


#ifndef __NODE_H__
#define __NODE_H__

typedef unsigned char uchar;
typedef unsigned short uint16;
typedef unsigned long uint32;

//#define MAX(a,b) ((a >= b) ? a : b)
//#define MIN(a,b) ((a <= b) ? a : b)

#include <cstdlib>
#include <string>
using namespace std;

#include "simple_data.h"
#include "list.h"

class node;

node* read_node_ptr(const simple_data& the_data);
simple_data write_node_ptr(node* new_node_ptr);

class node
{
	friend int main(); // For testing purposes only.
private:
	simple_data the_data;

	// The children are stored in a list indexed by the child indices.
	// The same child may occur more than once.
	// The current degree is an articial bound on the array, beyond which are unused pointer slots.
	// The list is longer than the current degree to enable easy extensions. 
	// When a child in the middle of the list is removed, all children to the right shift left by 1.
	int max_degree;
	int the_degree;
	node** children;
	void append_to_child_list(node* new_child); // Crosslinking from the child is NOT done here.
	void remove_from_child_list(node* existing_child, bool remove_all_instances_flag); // Decrosslinking from the child is NOT done here.
	void remove_from_child_list(int index); // Decrosslinking from the child is NOT done here.

	// The parents are stored in an unindexed (unordered) list that may contain holes.
	// The number on parents is not maintained.
	// The same same parent may occur more than once.
	// When a parent is removed, a "hole" is left in the list that can be filled by another parent.
	int max_num_of_parents;
	node** parents;
	void append_to_parent_list(node* new_parent); // Crosslinking from the parent is NOT done here.
	void remove_from_parent_list(node* existing_parent, bool remove_all_instances_flag); // Decrosslinking from the parent is NOT done here.

	bool lock_existance_flag; 

public:

	node();
	node(simple_data new_data);
	node(simple_data new_data, int new_max_degree);
	node(simple_data new_data, int new_degree, node** new_children); 
private:
	void copy_node(node& existing_node);
public:
	node(node& existing_node);
	node(node* existing_node);
	node& operator=(node& existing_node);
	~node(); // Will forcefully delete the node breaking the child references from parent nodes also. The deletion will NOT propagate to the children.

	simple_data get_the_data();
	void set_the_data(const simple_data& new_data);
	int get_degree();
	node* get_child(int index);
	void add_child(node* new_child); 
	void set_child(int index, node* new_child);
	void delete_child(int index);
	bool is_loose();
	static void destroy_node(node* curr_node); // Will delete the current node if no parents are present.
	void lock_existance();
	void unlock_existance();
	bool get_existance_lock_status();

	// Important parameters for subroutines:
private:
	// Multiple traces can be active.
	static list node_trackers; // The current tracker.
	static list visitation_lists; // The list of visited nodes.
	list visitation_indices; // The node's position in the visitation list.
	list depths; // The node's depth in the visitation tree.
	list prime_parents; // The parent that is to be returned to.
	list prime_child_indices; // The child that is next to visit.
	list extra_data;

public:
	
	static int tracker_index; // An adjustable parameter for keeping track of which trace is active.

	static void set_node_tracker(node* target_node); 
	static node* get_node_tracker();
	static bool has_backtracked(); // Returns true if the node has been returned to. Is also true if the tracker was instantly reflected from an already visited child without leaving the current node.
	static bool is_backtracking(); // Returns true if the node has checked all children and is ready to backtrack.
	static node* tracker_repetition(); // If the next child has already been visited, return its pointer, otherwise return NULL. 
	static void advance_node_tracker();
	static bool end_of_trace();
	static int get_num_of_visited_nodes();
	static node* get_visited_node(int visitation_index);
	static bool has_visited_node(node* target_node);
	int get_visitation_index();
	int get_depth();
	node* get_prime_parent();
	int get_prime_child_index();
	void write_extra_data(const simple_data& new_extra_data);
	simple_data read_extra_data();
	// *************************************

	// Complex routines:
	static void destroy_subgraph(node* root_node); // From the subgraph rooted at "root_node", all nodes except those with ancestors outside of the subgraph will be deleted.
	static node* copy_subgraph(node* root_node);
	static node* product_subgraph(node* root_node_1, node* root_node_2, int outer_product_flag); // The outer_product_flag determins if children that are not common to both nodes are used or not.
	static short compare(node* node_1, node* node_2); // Returns +1 if element_1 > element_2; returns -1 if element_1 < element_2; and returns 0 if element_1 == element_2.
	static node* read_node_from_stream(istream& input);
	static node* read_table(istream& input);
	static string print(node* root_node);
	static node* condense(node* root_node); // Unify together all common elements.
	void expand(int level); // Opposite of condense, expands the subgraph at level "level".
	void expand_2(int depth, bool full_expand_flag); // Opposite of condense, expands the subgraph so that all nodes whose depth in the tracker tree is "<= depth" cannot be reached from the root by any shorter (or longer) path.

};


#endif

