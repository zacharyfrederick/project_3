/*
 * Node.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: Zachary
 */

#include "Node.h"
#include <vector>

void Node::setDirectory(bool isDirectory) {
	this->isDirectory = isDirectory;
}

bool Node::getDirectory() {
	return isDirectory;
}

vector<Node> *Node::getChildren() {
	return &children;
}

int Node::getId() {
	return id;
}

string Node::getPath() {
	return pathName;
}

void Node::setPath(string pathName) {
	this->pathName = pathName;
}

Node::Node() {
	id = generateId();
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

int Node::generateId() {
	static int current_id = 0;
	current_id++;
	return current_id;
}
Node* Node::getChild(int id) {
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		if ((*itr).id == id) {
			return &(*itr);
		}
	}

	return nullptr;
}

void Node::addChild(Node node) {
	children.push_back(node);
}
