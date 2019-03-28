/*
 * Node.h
 *
 *  Created on: Mar 24, 2019
 *      Author: Zachary
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "Wad.h"
#include <string>

using namespace std;

class Node {
public:
	Node();
	virtual ~Node();
	int id;
	string pathName;
	vector<Node> children;
	bool isDirectory;
	struct descriptor_struct descriptor;
	vector<Node> *getChildren();
	void setDirectory(bool isDirectory);
	bool getDirectory();
	string getPath();
	void setPath(string pathName);
	int getId();
	Node *getChild(int id);
	void addChild(Node node);
	int generateId();
};

#endif /* NODE_H_ */
