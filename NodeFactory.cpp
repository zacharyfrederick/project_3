/*
 * NodeFactory.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: Zachary
 */

#include "NodeFactory.h"
#include "DirectoryNode.h"
#include "FileNode.h"

NodeFactory::NodeFactory() {
	// TODO Auto-generated constructor stub

}

NodeFactory::~NodeFactory() {
	// TODO Auto-generated destructor stub
}


Node2 *NodeFactory::create_node(enum Node_Type type) {
	switch (type) {
	case DIR_NODE:
		return new DirectoryNode();
		break;

	case FILE_NODE:
		return new FileNode();
		break;

	default:
		return nullptr;
		break;
	}
}
