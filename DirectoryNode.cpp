/*
 * DirectoryNode.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: Zachary
 */

#include "DirectoryNode.h"
#include "Node2.h"
#include <vector>
#include "Wad.h"

DirectoryNode::DirectoryNode() {
	type = DIR_NODE;
	//path = "/";
}

DirectoryNode::~DirectoryNode() {
	// TODO Auto-generated destructor stub
}

vector<Node2*> DirectoryNode::getChildren() {
	return children;
}

void DirectoryNode::addChild(Node2 *new_node) {
	children.push_back(new_node);

}

Node2 *DirectoryNode::getChild(int id) {
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		if ((*itr)->id == id) {
			return (*itr);
		}
	}
	return nullptr;
}

string DirectoryNode::get_name() {
	return descriptor.name;
}

uint32_t DirectoryNode::get_location() {
	return descriptor.offset;
}

uint32_t DirectoryNode::get_offset() {
	return descriptor.offset;
}

void DirectoryNode::set_descriptor(struct descriptor_struct descriptor){
	this->descriptor = descriptor;
	//path = descriptor.name;
}

