#pragma once
#include <string>
#include <iostream>
#include <exception>


using namespace std;

class TreeNode {
public:
	string title;
	string name;
	TreeNode *parent;
	TreeNode *leftMostChild;
	TreeNode *rightSibling;

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
	TreeNode* getRoot();
	TreeNode* leftmostChild(TreeNode* node);
	TreeNode* rightSibling(TreeNode* node);
	void printSubTree(TreeNode* subTreeRoot);
	TreeNode* find(string);
	bool read(string);
	void write(string);
	void hire(TreeNode* node,string,string);
	bool fire(string);
private:
	TreeNode* root;
	unsigned int numElts;
	//TreeNode* currentRoot;
	string filecontents;
	bool silentRead;
	int counter=1;
};