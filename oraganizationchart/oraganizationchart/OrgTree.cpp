
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
			
		}
		temp->leftMostChild = currentTreeNode;
		numElts = numElts + 1;
		currentTreeNode->parent = temp;
		this->currentRoot = currentTreeNode;


	}
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

		}

		
		if (ifs.peek() == ')') {
			isRootNeeded = false;
			getline(ifs, junk);
			
			getline(ifs, data);
			//	currentRoot = currentRoot->parent;
			if (data == junk) {
				currentRoot = currentRoot->parent;
				if (currentRoot == root) {
					getline(ifs, data);
					if (ifs.eof()) {
						cout << "valid file";
						return true;
					}
					else {
						cout << "Invalid file sequence";
						return false;
					}
					break;
				}
				getline(ifs, data);

			}
			if(data != ")"){
		//		currentRoot = currentRoot->parent;
			hire(currentRoot,data);
			}
		}
		while (ifs.peek() != ')'&& !isRootNeeded) {
			getline(ifs, data);
			hire(currentRoot, data);
		//	isRootNeeded = true;
		
		}

		
	}
		
	
}

void OrgTree::hire(TreeNode* treeNode, string data) {
	TreeNode* temp = new TreeNode(data);
	/*if (currentRoot->leftMostChild == nullptr) {
		currentRoot->leftMostChild = temp;
		temp->parent = currentRoot->parent;
		currentRoot = currentRoot->leftMostChild;
	}*/
	if(currentRoot->rightSibling == nullptr) 
	{
		currentRoot->rightSibling = temp;
		temp->parent = currentRoot->parent;
		currentRoot = currentRoot->rightSibling;
	}
	else {
		while (currentRoot->rightSibling!=nullptr)
		{
			currentRoot = currentRoot->rightSibling;
		}
		currentRoot->rightSibling = temp;
		temp->parent = currentRoot;
		currentRoot = currentRoot->rightSibling;
	}
}

unsigned int OrgTree::getSize() {
	return numElts;
}
