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
#include "FileNode.h";

using namespace std;

Zion::Zion() {
	root.path = "/";
}

Zion::~Zion() {
	// TODO Auto-generated destructor stub
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

bool Zion::create_file_sys(vector<struct descriptor_struct> descriptor_table) {
	initialize_indentation();

	this->descriptor_table = descriptor_table;

	DirectoryNode *current = &root;
	indentation.push(current);

	for (auto itr = descriptor_table.begin(); itr != descriptor_table.end(); itr++) {
		if (is_dir_descriptor((*itr).name) == true) {
			DirectoryNode* new_node = (DirectoryNode*) factory.create_node(DIR_NODE);
			new_node->set_descriptor((*itr));
			current->addChild(new_node);

			if (detect_suffix((*itr).name, "_START")) {
				current = new_node;
				indentation.push(current);
			}

			if (detect_suffix((*itr).name, "_END")) {
				indentation.pop();
				current = (DirectoryNode*) indentation.top();
			}

			if (detect_map_marker((*itr).name) == true) {
				current = new_node;
				for (int i =0; i < 10; i++) {
					itr++;
					DirectoryNode* new_node = (DirectoryNode*) factory.create_node(DIR_NODE);
					current->addChild(new_node);
				}
				cout << current->children.size() << "\n";
				current = (DirectoryNode*) indentation.top();
			}

		} else {
			FileNode* new_node = (FileNode *) factory.create_node(FILE_NODE);
			new_node->set_descriptor((*itr));
			current->addChild(new_node);
		}
	}

	print_file_sys();
}

void Zion::initialize_indentation() {
	indentation.push(&root);
}

Node2* Zion::get_node_by_path(string path) {
	vector<string> tokens = parse_tokens(path);

	if (path == "/") {
		return &root;
	}

	DirectoryNode *temp = &root;
	vector<Node2*> *children = root.getChildren();
	Node2* node = nullptr;

	for (int i=0; i < tokens.size(); i++) {
		for (auto itr = children->begin(); itr != children->end(); itr++) {
			if (tokens[i] == (*itr)->path) {
				temp = (DirectoryNode* ) &(*itr);
				children = temp->getChildren();
			}
		}
	}

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
	Node2* test = get_node_by_path("/E1M1");
	if (test == nullptr) {
		cout << "something went wrong\n";
	}
}
