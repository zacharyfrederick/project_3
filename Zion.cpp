/*
 * Zion.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: Zachary
 */

#include "Zion.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "Node2.h"
#include <string>
#include <stdio.h>
#include <cstring>
#include "NodeFactory.h"
#include "DirectoryNode.h"
#include "FileNode.h"
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

Zion::Zion() {
	root.path = "/";
	filesystem.insert(make_pair(root.path, &root));
	raw_data = nullptr;
}

Zion::~Zion() {
	if (raw_data != nullptr) {
		delete[] raw_data;
		raw_data = nullptr;
	}
}


bool Zion::detect_suffix(string base, string suffix) {
	int size = suffix.length();

	for (int i = size; i > 0; i--) {
		if (base[base.length()-i] != suffix[size-i]) {
			return false;
		}
	}

	return true;
}

bool Zion::detect_map_marker(string name) {
	if (name[0] != 'E')
		return false;

	if (!isdigit(name[1]))
		return false;

	if (name[2] != 'M')
		return false;

	if (!isdigit(name[3]))
		return false;

	return true;
}

bool Zion::is_dir_descriptor(string name) {
	if ((detect_suffix(name, "_START") == true) || (detect_suffix(name, "_END") == true) || (detect_map_marker(name) == true))
		return true;
	return false;
}

void Zion::initialize_indentation() {
	indentation.push(&root);
}

Node2* Zion::get_node_by_path(string path) {
	if (filesystem.find(path) == filesystem.end()) {
		return nullptr;
	}

	Node2* temp = filesystem[path];

	if (temp->type == DIR_NODE) {
		DirectoryNode* new_node = (DirectoryNode*) filesystem[path];
		return new_node;
	}

	if (temp->type == FILE_NODE) {
		FileNode* new_node = (FileNode*) filesystem[path];
		return new_node;
	}

	return nullptr;

}

vector<string> Zion::parse_tokens(string path) {
	vector<string> tokens;

	char* temp = new char[path.length() +1];
	strcpy(temp, path.c_str());

	char* pch = strtok(temp, "/");
	while(pch != NULL) {
		tokens.push_back(string(pch));
		pch = strtok(NULL, "/");
	}

	delete[] temp;
	return tokens;
}

bool Zion::insert_by_path(string path, Node2 new_node) {
	DirectoryNode* node = (DirectoryNode *) get_node_by_path(path);
	node->addChild(&new_node);
}

void Zion::print_file_sys() {
	for (auto itr = filesystem.begin(); itr != filesystem.end(); itr++) {
		cout << itr->first << "\n";
	}
}

string Zion::strip_suffix(string base, string suffix) {
	return base.substr(0, base.length() - suffix.length());
}

void Zion::add_child(Node2* parent, Node2* child) {
	DirectoryNode* parent_m = (DirectoryNode*) parent;
	parent_m->addChild(child);
}

bool Zion::is_content(const string& path) {
	return is_valid_and_type(path, FILE_NODE);
}

bool Zion::is_directory(const string& path) {
	return is_valid_and_type(path, DIR_NODE);
}

int Zion::get_size(const string& path) {
	return (is_valid_and_type(path, FILE_NODE)) ? ((FileNode*) filesystem[path])->descriptor.length : -1;
}

int Zion::get_contents(const string& path, char* buffer, int length, int offset) {
	return (is_valid_and_type(path, FILE_NODE) && (copy_data(buffer, length, offset))) ? length : -1;

}

int Zion::get_directory(const string& path, vector<string>* directory) {
	return (copy_directory(path, directory)) ? directory->size() : -1;
}

bool Zion::is_path_valid(string path) {
	return (filesystem.find(path) != filesystem.end());
}

enum Node_Type Zion::file_type_from_path(string path) {
	return (filesystem[path]->type == FILE_NODE) ? FILE_NODE : DIR_NODE;
}

bool Zion::create_file_sys(vector<struct descriptor_struct> descriptor_table, uint8_t* raw_data) {
	this->descriptor_table = descriptor_table;
	this->raw_data = raw_data;

	DirectoryNode *current = &root;
	vector<Node2*> children = current->getChildren();
	string current_path = current->path;

	stack<string> paths;
	stack<Node2*> levels;
	paths.push(current_path);
	levels.push(current);

	for (auto itr = descriptor_table.begin(); itr != descriptor_table.end(); itr++) {
		if (is_dir_descriptor((*itr).name) == true) {
			DirectoryNode* new_node = (DirectoryNode*) factory.create_node(DIR_NODE);
			new_node->set_descriptor((*itr));

			if (detect_suffix((*itr).name, "_START") == true) {
				(*itr).name = strip_suffix((*itr).name, "_START");
				current_path += (*itr).name + "/";
				paths.push((*itr).name);

				new_node->path = current_path;
				filesystem.insert(make_pair(new_node->path, new_node));
				levels.push(new_node);
				current->addChild(new_node);
				current = new_node;
			}

			if (detect_suffix((*itr).name, "_END") == true) {
				string old_token = paths.top();
				paths.pop();
				current_path = current_path.substr(0, current_path.size()-old_token.size()-1);
				levels.pop();
				current = (DirectoryNode*) levels.top();
			}

			if (detect_map_marker((*itr).name) == true) {
				current_path += (*itr).name + "/";
				paths.push((*itr).name);
				new_node = (DirectoryNode*) factory.create_node(DIR_NODE);
				new_node->path = current_path;
				current->addChild(new_node);
				current = new_node;
				filesystem.insert(make_pair(new_node->path, new_node));
				levels.push(current);

				for (int i=0; i < 10; i++) {
					itr++;
					FileNode* new_node = (FileNode*) factory.create_node(FILE_NODE);
					new_node->path = current_path + (*itr).name;
					new_node->set_descriptor((*itr));
					filesystem.insert(make_pair(new_node->path, new_node));
					current->addChild(new_node);
				}
				levels.pop();
				current = (DirectoryNode*) levels.top();

				string old_token = paths.top();
				paths.pop();

				current_path = current_path.substr(0, current_path.size()-old_token.size()-1);
			}

			current->addChild(new_node);
		} else {
			FileNode* new_node = (FileNode*) factory.create_node(FILE_NODE);
			new_node->path = current_path + (*itr).name;
			new_node->set_descriptor((*itr));
			filesystem.insert(make_pair(new_node->path, new_node));
			current->addChild(new_node);
		}
	}
	return true;
}

bool Zion::is_valid_and_type(string path, enum Node_Type enumNode_Type) {
	if (is_path_valid(path) && filesystem[path]->type == enumNode_Type) {
		return true;
	} else {
		return false;
	}
}

bool Zion::copy_data(char* buffer, int length, int offset) {
	for (int i = 0; i< length; i++) {
		buffer[i] = raw_data[offset+i];
	}

	return true;
}

bool Zion::copy_directory(const string path, vector<string>* directory) {
	if(is_valid_and_type(path, DIR_NODE)) {
		DirectoryNode* dir = (DirectoryNode*) filesystem[path];

		for (int i =0; i < dir->children.size(); i++) {
			directory->push_back(dir->children[i]->path);
		}
	} else {
		cout << "Not a directory";
		return false;
	}

	return true;
}

