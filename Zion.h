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
#include <unordered_map>
#include "FuseManager.h"

using namespace std;

class Zion {
public:
	Zion();
	virtual ~Zion();
	DirectoryNode root;
	FuseManager fuse_manager;
	uint8_t *raw_data;
	vector<struct descriptor_struct> descriptor_table;
	bool detect_suffix(string base, string suffix);
	bool detect_map_marker(string name);
	bool is_dir_descriptor(string name);
	bool create_file_sys(vector<struct descriptor_struct> descriptor_table, uint8_t *raw_data);
	NodeFactory factory;
	void initialize_indentation();
	Node2 *get_node_by_path(string path);
	stack<Node2*> indentation;
	vector<string> parse_tokens(string path);
	bool insert_by_path(string path, Node2 new_node);
	void print_file_sys();
	unordered_map<string, Node2*> filesystem;
	string strip_suffix(string base, string suffix);
	void add_child(Node2* parent, Node2* child);
	bool is_content(const string &path);
	bool is_directory(const string &path);
	int get_size(const string &path);
	int get_contents(const string &path, char *buffer, int length, int offset=0);
	int get_directory(const string &path, vector<string> *directory);
	bool is_path_valid(string path);
	enum Node_Type file_type_from_path(string path);
	bool is_valid_and_type(string path, enum Node_Type);
	bool copy_data(char* buffer, int length, int offset);
	bool copy_directory(const string path, vector<string> *directory);
	int zion_get_attr(const char*, struct stat *);
	int zion_read(const char *path, char *buf, size_t size, off_t offset,struct fuse_file_info *fi);
};

#endif /* ZION_H_ */
