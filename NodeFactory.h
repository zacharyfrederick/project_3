/*
 * NodeFactory.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Zachary
 */

#ifndef NODEFACTORY_H_
#define NODEFACTORY_H_

#include "Node2.h"

class NodeFactory {
public:
	NodeFactory();
	virtual ~NodeFactory();
	Node2 *create_node(enum Node_Type type);
};

#endif /* NODEFACTORY_H_ */
