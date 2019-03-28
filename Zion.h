/*
 * Zion is the filesystem name and I thought it sounded cool
 */

#ifndef ZION_H_
#define ZION_H_

#include "Node2.h"
#include "Wad.h"
#include "NodeFactory.h"
#include <stack>
#include <string>
#include "DirectoryNode.h";
using namespace std;

class Zion {
public:
	Zion();
	virtual ~Zion();
	DirectoryNode root;
	vector<struct descriptor_struct> descriptor_table;
	bool detect_suffix(string base, string suffix);
	bool detect_map_marker(string name);
	bool is_dir_descriptor(string name);
	bool create_file_sys(vector<struct descriptor_struct> descriptor_table);
	NodeFactory factory;
	void initialize_indentation();
	Node2 *get_node_by_path(string path);
	stack<Node2*> indentation;
	vector<string> parse_tokens(string path);
	bool insert_by_path(string path, Node2 new_node);
	void print_file_sys();

};

#endif /* ZION_H_ */
