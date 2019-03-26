
#include "OrgTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Tokenize.h"
#include <sstream>
#include <stack> 
#include <iomanip>
//#define TREENULLPTR NULL
using namespace std;

OrgTree::OrgTree()
{
	numElts = 0;
	root = TREENULLPTR;
	string filecontents = "";
	bool silentread = false;
}


OrgTree::~OrgTree()
{
//	delete currentRoot;
	delete root;
}

void OrgTree::addRoot(string title,string name) {
	TREENODEPTR currentTreeNode;
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
	TREENODEPTR currentRoot= TREENULLPTR;
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
					//cerr << "Invalid file";
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

void OrgTree::hire(TREENODEPTR treeNode, string newTitle, string name) {
	TREENODEPTR temp = new TreeNode(newTitle, name);
//	if(currentRoot==nullptr)
	TREENODEPTR currentRoot = find(treeNode->title);
	numElts++;
	if (currentRoot->leftMostChild == TREENULLPTR) {
		currentRoot->leftMostChild = temp;
		temp->parent = currentRoot;
		currentRoot = currentRoot->leftMostChild;
	}
	else {
		currentRoot = currentRoot->leftMostChild;
		while (currentRoot->rightSibling!= TREENULLPTR)
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
	if (root == TREENULLPTR){
		cout << "Tree is empty";
	}
	else {
		TREENODEPTR temproot = this->getRoot();
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

void OrgTree::printSubTree(TREENODEPTR subTreeRoot) {

	int intendation = 4;
	
	if (!silentRead) {
// a more comprehensive logic is required here
		//cout << "write your logic here";
		stack<TREENODEPTR> stack;
		if (subTreeRoot == TREENULLPTR) {
			return;
		}
		cout << subTreeRoot->title<<":"<<subTreeRoot->name<<endl;
		
		if(subTreeRoot->leftMostChild!= TREENULLPTR)

		stack.push(subTreeRoot->leftMostChild);
		while (!stack.empty())
		{
			
			
			TREENODEPTR currentNode = stack.top();
			cout << setw(intendation)<<"";;
			cout << currentNode->title <<":"<<currentNode->name<<endl;
			stack.pop();
	
			if (currentNode->rightSibling!= TREENULLPTR){
				stack.push(currentNode->rightSibling);
				intendation = intendation + 4;
				
			}
			intendation = intendation - 4;

			// push left child of popped node to the stack
			if (currentNode->leftMostChild!= TREENULLPTR){
				stack.push(currentNode->leftMostChild);
				intendation = intendation + 4;
				
			}
		}
	}
	
	
	
	if (silentRead) {
		if (subTreeRoot == TREENULLPTR) {
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

TREENODEPTR OrgTree::getRoot() {
	return root;
}
TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node) {
	if (node == TREENULLPTR) {
		return TREENULLPTR;
	}
	if (node->leftMostChild != TREENULLPTR)
	return node->leftMostChild;
	else
		return TREENULLPTR;
}

TREENODEPTR OrgTree::rightSibling(TREENODEPTR node) {
	if (node == TREENULLPTR) {
		return TREENULLPTR;
	}
	if (node->rightSibling != TREENULLPTR) 
		return node->rightSibling;
	else
		return TREENULLPTR;

}
TREENODEPTR OrgTree::find(string title) {

	if (root == TREENULLPTR)
		return TREENULLPTR;


	stack<TREENODEPTR> stack;
	stack.push(root);
	TREENODEPTR returnValue= TREENULLPTR;
	// run till stack is not empty
	while (!stack.empty())
	{
		// pop a node from the stack and print it
		TREENODEPTR currentNode = stack.top();
		stack.pop();
		if (currentNode->title == title)
		{
			returnValue = currentNode;
			return currentNode;
		}
		else {
			//cout << currentNode->data << " ";

			// push right child of popped node to the stack
			if (currentNode->rightSibling!= TREENULLPTR)
				stack.push(currentNode->rightSibling);

			// push left child of popped node to the stack
			if (currentNode->leftMostChild!= TREENULLPTR)
				stack.push(currentNode->leftMostChild);
		}

		returnValue = TREENULLPTR;


	}
	return returnValue;
}

bool OrgTree::fire(string formerTitle) {
	TREENODEPTR foundNode = this->find(formerTitle);
	if (foundNode == TREENULLPTR) {
		//cout << "Node not found";
		return false;

	}
	if (root == foundNode) {
		//cout << "Root cannot be fired";
		return false;
	}
	if (foundNode->leftMostChild == TREENULLPTR &&foundNode->rightSibling == TREENULLPTR) {
		//cout << "leaf node";if(
		TREENODEPTR tempParent = foundNode->parent;
		TREENODEPTR left = tempParent->leftMostChild;
		if (left->title == foundNode->title&&foundNode->parent==tempParent) {
			tempParent->leftMostChild = TREENULLPTR;
			delete foundNode;
			numElts--;
			return true;
		}else{
		while (left->rightSibling->title != foundNode->title) {
			left = left->rightSibling;
			//delete foundNode;
		}
		delete foundNode;

		left->rightSibling = TREENULLPTR;
		numElts--;
		return true;
		}
	}
	if (foundNode->leftMostChild == TREENULLPTR &&foundNode->rightSibling != TREENULLPTR) {
		//cout << "one side empyty node";
		TREENODEPTR tempParent = foundNode->parent;
		TREENODEPTR left = tempParent->leftMostChild;
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
	if (foundNode->leftMostChild != TREENULLPTR &&foundNode->rightSibling != TREENULLPTR) {
		TREENODEPTR tempParent = foundNode->parent;
		TREENODEPTR fixingchilds = foundNode->leftMostChild;
		TREENODEPTR left = foundNode->parent->leftMostChild;

		if (left->title == foundNode->title) {
			foundNode->leftMostChild->parent = tempParent;
			tempParent->leftMostChild = foundNode->leftMostChild;
			while (fixingchilds->rightSibling != TREENULLPTR) {
				
				fixingchilds = fixingchilds->rightSibling;
				fixingchilds->parent = tempParent;
			}
			fixingchilds ->rightSibling = foundNode->rightSibling;
			fixingchilds->rightSibling->parent = foundNode->parent;
			delete foundNode;
			numElts--;

		}else{
		while (fixingchilds->rightSibling != TREENULLPTR) {
			
			fixingchilds->parent = left->parent;

			fixingchilds = fixingchilds->rightSibling;

		}
		fixingchilds->parent = left->parent;
		if (foundNode->rightSibling != TREENULLPTR)
			fixingchilds->rightSibling = foundNode->rightSibling;
		left->rightSibling = foundNode->leftMostChild;
		
		delete foundNode;
		numElts--;
		//TreeNode* left = tempParent->leftMostChild;
		//foundNode->leftMostChild=
		return true;
		}
	}

	if (foundNode->leftMostChild != TREENULLPTR &&foundNode->rightSibling == TREENULLPTR) {
		TREENODEPTR tempParent = foundNode->parent;
		TREENODEPTR left = foundNode->parent->leftMostChild;
		TREENODEPTR fixingChilds = foundNode->leftMostChild;
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

		while (fixingChilds->rightSibling != TREENULLPTR) {
			fixingChilds->parent = TREENULLPTR;
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