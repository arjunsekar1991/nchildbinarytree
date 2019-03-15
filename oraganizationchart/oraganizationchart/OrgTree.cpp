
#include "OrgTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Tokenize.h"
using namespace std;

OrgTree::OrgTree()
{
	numElts = 0;
	root = NULL;
}


OrgTree::~OrgTree()
{
}

void OrgTree::addRoot(string data) {
	TreeNode* currentTreeNode;
	if (numElts != 0) {
		currentTreeNode = new TreeNode(data);
		TreeNode* temp = root;
		while (temp->leftMostChild != nullptr)
		{
			temp = temp->leftMostChild;
			this->currentRoot = temp;
		}
		temp->leftMostChild = currentTreeNode;
		numElts = numElts + 1;
		currentTreeNode->parent = temp;
		
	}
	if (numElts == 0) {
		this->root = new TreeNode(data);
		numElts = numElts + 1;
	}
	

}

bool OrgTree::read(string filename) {
	string data, junk;
	ifstream ifs;
	if(!ifs.is_open())
		ifs.open(filename);
	
	
	while (!ifs.eof())
	{
		
		while (ifs.peek() != ')'&& !ifs.eof()) {
			getline(ifs, data);
			addRoot(data);
			
		}
		while (ifs.peek() == ')') {
			
			getline(ifs, junk);
			
			getline(ifs, data);
			if (data == junk) {
				currentRoot = currentRoot->parent;
				getline(ifs, data);
			}
			hire(currentRoot,data);
				
		}
	}
		
	
	return true;
}

void OrgTree::hire(TreeNode* treeNode, string data) {
	TreeNode* temp = new TreeNode(data);
	if(treeNode->rightSibling == nullptr) 
	{
		treeNode->rightSibling = temp;
		temp->parent = treeNode;
		
	}
	else {
		while (treeNode->rightSibling!=nullptr)
		{
			treeNode = treeNode->rightSibling;
		}
		treeNode->rightSibling = temp;
		temp->parent = currentRoot;
	}
}

unsigned int OrgTree::getSize() {
	return numElts;
}
