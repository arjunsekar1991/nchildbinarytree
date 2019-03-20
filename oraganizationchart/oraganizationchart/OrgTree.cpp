
#include "OrgTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Tokenize.h"
#include <sstream>
#include <stack> 
#include <iomanip>
using namespace std;

OrgTree::OrgTree()
{
	numElts = 0;
	root = nullptr;
	string filecontents = "";
	bool silentread = false;
}


OrgTree::~OrgTree()
{
//	delete currentRoot;
	delete root;
}

void OrgTree::addRoot(string title,string name) {
	TreeNode* currentTreeNode;
	if (numElts != 0) {
		currentTreeNode = new TreeNode(title, name);

		root->parent = currentTreeNode;
		numElts = numElts + 1;
		currentTreeNode->leftMostChild = root;
		root = currentTreeNode;
		//currentRoot = root;


	}
	if (numElts == 0) {
		this->root = new TreeNode(title, name);
		numElts = numElts + 1;
		//this->currentRoot = root;
	}


}

bool OrgTree::read(string filename) {
	string data, junk,previousjunk,secondtolastjunk;
	ifstream ifs;
	if(!ifs.is_open())
		ifs.open(filename);
	TreeNode *currentRoot=nullptr;
	bool isRootNeeded=true;
	while (!ifs.eof())
	{	
		
		while (ifs.peek() != ')' && !ifs.eof()&& isRootNeeded) {
			getline(ifs, data);
			vector <string> tokens;
			tokens = StringSplit(data, ",", false);
			junk = data;
			
			addRoot(tokens[0],tokens[1]);
			isRootNeeded = false;
			currentRoot = root;

		}

		
		if (ifs.peek() == ')') {
			isRootNeeded = false;
		//	secondtolastjunk = previousjunk;
		//	previousjunk = junk;
			getline(ifs, junk);
			
			if (currentRoot == root ) {
				//getline(ifs, junk);
				if (ifs.eof()) {
				//	cout << "valid file";
					
					return true;
				}
				else {
					//cout << "Invalid file sequence";
					cerr << "Invalid file";
					return false;
				}
				break;
			}
			currentRoot = currentRoot->parent;

			
			
		}
		while (ifs.peek() != ')'&& !isRootNeeded) {
			vector <string> tokens;
			getline(ifs, data);
			tokens = StringSplit(data, ",", false);
			
			hire(currentRoot, tokens[0],tokens[1]);
			currentRoot = find(tokens[0]);
			junk = data;
			

		//	isRootNeeded = true;
		
		}
		

		
	}
		
	return true;
}

void OrgTree::hire(TreeNode* treeNode, string newTitle, string name) {
	TreeNode* temp = new TreeNode(newTitle, name);
//	if(currentRoot==nullptr)
	TreeNode* currentRoot = find(treeNode->title);
	numElts++;
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

void OrgTree::write(string filename) {
	filecontents = "";
	if (root == nullptr){
		cout << "Tree is empty";
	}
	else {
		TreeNode* temproot = this->getRoot();
		silentRead = true;
		printSubTree(temproot);
		filecontents.pop_back();
		filecontents.pop_back();
		//cout << endl;
		//cout <<"printing file contents"<< filecontents;
		ofstream ofs;
		ofs.open(filename);



		vector <string> tokens;


	//	stringstream ss(filecontents);

		tokens = StringSplit(filecontents, "^", false);

		// Tokenizing w.r.t. space ' ' 
		//while (getline(ss, intermediate, '^'))
		//{
		//	myfile.write(intermediate);
			for (string i : tokens){
				ofs << i;
				ofs << endl;
			}
		ofs.close();
	}
	silentRead = false;
	//}
}

void OrgTree::printSubTree(TreeNode* subTreeRoot) {

	
	
	if (!silentRead) {
// a more comprehensive logic is required here
		//cout << "write your logic here";
		stack<TreeNode*> stack;
		if (subTreeRoot == nullptr) {
			return;
		}
		cout << subTreeRoot->title;
		
		if(subTreeRoot->leftMostChild!=nullptr)

		stack.push(subTreeRoot->leftMostChild);
		while (!stack.empty())
		{
			
			
			TreeNode* currentNode = stack.top();
			cout << currentNode->title;		
			stack.pop();
	
			if (currentNode->rightSibling!=nullptr){
				stack.push(currentNode->rightSibling);
//			
			}
			// push left child of popped node to the stack
			if (currentNode->leftMostChild!=nullptr){
				stack.push(currentNode->leftMostChild);
		
			}
		}
	}
	
	
	
	if (silentRead) {
		if (subTreeRoot == nullptr) {
			filecontents = filecontents + ")" + "^";
			return;
		}
		filecontents = filecontents + subTreeRoot->title+","+ subTreeRoot->name + "^";
		printSubTree(subTreeRoot->leftMostChild);
		
		printSubTree(subTreeRoot->rightSibling);
	}

	
}

unsigned int OrgTree::getSize() {
	return numElts;
}

TreeNode* OrgTree::getRoot() {
	return root;
}
TreeNode* OrgTree::leftmostChild(TreeNode* node) {
	if (node == nullptr) {
		return nullptr;
	}
	if (node->leftMostChild != nullptr)	
	return node->leftMostChild;
	else
		return nullptr;
}

TreeNode* OrgTree::rightSibling(TreeNode* node) {
	if (node == nullptr) {
		return nullptr;
	}
	if (node->rightSibling != nullptr)
		return node->rightSibling;
	else
		return nullptr;

}
TreeNode* OrgTree::find(string title) {

	if (root == nullptr)
		return nullptr;


	stack<TreeNode*> stack;
	stack.push(root);
	TreeNode* returnValue=nullptr;
	// run till stack is not empty
	while (!stack.empty())
	{
		// pop a node from the stack and print it
		TreeNode* currentNode = stack.top();
		stack.pop();
		if (currentNode->title == title)
		{
			returnValue = currentNode;
			return currentNode;
		}
		else {
			//cout << currentNode->data << " ";

			// push right child of popped node to the stack
			if (currentNode->rightSibling!=nullptr)
				stack.push(currentNode->rightSibling);

			// push left child of popped node to the stack
			if (currentNode->leftMostChild!=nullptr)
				stack.push(currentNode->leftMostChild);
		}

		returnValue = nullptr;


	}
	return returnValue;
}

bool OrgTree::fire(string formerTitle) {
	TreeNode* foundNode = this->find(formerTitle);
	if (foundNode == nullptr) {
		//cout << "Node not found";
		return false;

	}
	if (root == foundNode) {
		//cout << "Root cannot be fired";
		return false;
	}
	if (foundNode->leftMostChild == nullptr&&foundNode->rightSibling == nullptr) {
		//cout << "leaf node";if(
		TreeNode* tempParent = foundNode->parent;
		TreeNode* left = tempParent->leftMostChild;
		if (left->title == foundNode->title&&foundNode->parent==tempParent) {
			tempParent->leftMostChild = nullptr;
			delete foundNode;
			numElts--;
			return true;
		}else{
		while (left->rightSibling->title != foundNode->title) {
			left = left->rightSibling;
			//delete foundNode;
		}
		delete foundNode;

		left->rightSibling = nullptr;
		numElts--;
		return true;
		}
	}
	if (foundNode->leftMostChild == nullptr&&foundNode->rightSibling != nullptr) {
		//cout << "one side empyty node";
		TreeNode* tempParent = foundNode->parent;
		TreeNode* left = tempParent->leftMostChild;
		if (left->title == foundNode->title) {
			tempParent->leftMostChild = foundNode->rightSibling;
			delete foundNode;
			numElts--;
			return true;
		}
		else{
		while (left->rightSibling->title != foundNode->title) {
			left = left->rightSibling;
		}
		left->rightSibling = foundNode->rightSibling;
		delete foundNode;
		numElts--;
		}
		return true;
	}
	if (foundNode->leftMostChild != nullptr&&foundNode->rightSibling != nullptr) {
		TreeNode* tempParent = foundNode->parent;
		TreeNode* fixingchilds = foundNode->leftMostChild;
		TreeNode* left = foundNode->parent->leftMostChild;

		if (left->title == foundNode->title) {
			foundNode->leftMostChild->parent = tempParent;
			tempParent->leftMostChild = foundNode->leftMostChild;
			while (fixingchilds->rightSibling != nullptr) {
				
				fixingchilds = fixingchilds->rightSibling;
				fixingchilds->parent = tempParent;
			}
			fixingchilds ->rightSibling = foundNode->rightSibling;
			fixingchilds->rightSibling->parent = foundNode->parent;
			delete foundNode;
			numElts--;

		}else{
		while (fixingchilds->rightSibling != nullptr) {
			
			fixingchilds->parent = left->parent;

			fixingchilds = fixingchilds->rightSibling;

		}
		fixingchilds->parent = left->parent;
		if (foundNode->rightSibling != nullptr)
			fixingchilds->rightSibling = foundNode->rightSibling;
		left->rightSibling = foundNode->leftMostChild;
		
		delete foundNode;
		numElts--;
		//TreeNode* left = tempParent->leftMostChild;
		//foundNode->leftMostChild=
		return true;
		}
	}

	if (foundNode->leftMostChild != nullptr&&foundNode->rightSibling == nullptr) {
		TreeNode* tempParent = foundNode->parent;
		TreeNode* left = foundNode->parent->leftMostChild;
		TreeNode* fixingChilds = foundNode->leftMostChild;
		if (foundNode->title == left->title) {
			foundNode->leftMostChild->parent = foundNode->parent;
			tempParent->leftMostChild = foundNode->leftMostChild;
			delete foundNode;
			numElts--;
		}else{
		
		while (left->rightSibling->title != foundNode->title) {
			left = left->rightSibling;
		}
		
	//	foundNode->leftMostChild->parent = left->parent;
		left->rightSibling = foundNode->leftMostChild;

		while (fixingChilds->rightSibling != nullptr) {
			fixingChilds->parent = nullptr;
			fixingChilds->parent = tempParent;
			fixingChilds = fixingChilds->rightSibling;
		}
		fixingChilds->parent = tempParent;
		

		delete foundNode;
		numElts--;
		return true;
	
	}}
	return false;
}