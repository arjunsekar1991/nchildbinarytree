#pragma once
#include <string>
#include <iostream>
#include <exception>
#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

using namespace std;

class TreeNode {
public:
	string title;
	string name;
	TREENODEPTR parent;
	TREENODEPTR leftMostChild;
	TREENODEPTR rightSibling;

	TreeNode(string datainput,string inputname) {
		parent = nullptr;
		leftMostChild = nullptr;
		rightSibling = nullptr;
		title = datainput;
		name = inputname;

	}
	~TreeNode() {

	};
};


class OrgTree{ 
public:
	
	
	OrgTree();
	~OrgTree();           // Destructor
	void addRoot(string,string);
	unsigned int getSize();
	TREENODEPTR getRoot();
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);
	void printSubTree(TREENODEPTR subTreeRoot);
	TREENODEPTR find(string);
	bool read(string);
	void write(string);
	void hire(TREENODEPTR node,string,string);
	bool fire(string);
private:
	TREENODEPTR root;
	unsigned int numElts;
	//TreeNode* currentRoot;
	string filecontents;
	bool silentRead;
	//int counter=1;
};