
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
	/*if (numElts != 0) {
		currentTreeNode = new TreeNode(data);
		TreeNode* temp = root;
		while (temp->leftMostChild != nullptr)
		{
			temp = temp->leftMostChild;
			
		}
		temp->leftMostChild = currentTreeNode;
		numElts = numElts + 1;
		currentTreeNode->parent = temp;
		this->currentRoot = currentTreeNode;


	}*/
	if (numElts == 0) {
		this->root = new TreeNode(data);
		numElts = numElts + 1;
		this->currentRoot = root;
	}


}

bool OrgTree::read(string filename) {
	string data, junk;
	ifstream ifs;
	if(!ifs.is_open())
		ifs.open(filename);
	
	bool isRootNeeded=true;
	while (!ifs.eof())
	{	
		
		while (ifs.peek() != ')' && !ifs.eof()&& isRootNeeded) {
			getline(ifs, data);

			addRoot(data);
			isRootNeeded = false;

		}

		
		if (ifs.peek() == ')') {
			isRootNeeded = false;
			getline(ifs, junk);
			currentRoot = currentRoot->parent;
			
		}
		while (ifs.peek() != ')'&& !isRootNeeded) {
			getline(ifs, data);
			hire(currentRoot, data);
		//	isRootNeeded = true;
		
		}

		
	}
		
	return true;
}

void OrgTree::hire(TreeNode* treeNode, string data) {
	TreeNode* temp = new TreeNode(data);
	if (currentRoot->leftMostChild == nullptr) {
		currentRoot->leftMostChild = temp;
		temp->parent = currentRoot;
		currentRoot = currentRoot->leftMostChild;
	}
	else {
		currentRoot = currentRoot->leftMostChild;
		while (currentRoot->rightSibling!=nullptr)
		{
			currentRoot = currentRoot->rightSibling;
		}
		currentRoot->rightSibling = temp;	
		temp->parent = currentRoot->parent;
		currentRoot = temp;

	}
}

unsigned int OrgTree::getSize() {
	return numElts;
}
