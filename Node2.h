#ifndef NODE2_H_
#define NODE2_H_

#include <string>

enum Node_Type {DIR_NODE=0, FILE_NODE};

using namespace std;

class Node2 {
public:
	Node2();
	virtual ~Node2();
	static int generateId();
	enum Node_Type type;
	Node_Type getType();
	string path;
	int id;

};

#endif /* NODE2_H_ */
