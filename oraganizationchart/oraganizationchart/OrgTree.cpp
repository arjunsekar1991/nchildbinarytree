
#include "OrgTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Tokenize.h"
#include <sstream>
#include <stack> 
using namespace std;

OrgTree::OrgTree()
{
	numElts = 0;
	root = nullptr;
	string filecontents = "";
}


OrgTree::~OrgTree()
{
}

void OrgTree::addRoot(string data) {
	TreeNode* currentTreeNode;
	if (numElts != 0) {
		currentTreeNode = new TreeNode(data);

		root->parent = currentTreeNode;
		numElts = numElts + 1;
		currentTreeNode->leftMostChild = root;
		root = currentTreeNode;


	}
	if (numElts == 0) {
		this->root = new TreeNode(data);
		numElts = numElts + 1;
		this->currentRoot = root;
	}


}

bool OrgTree::read(string filename) {
	string data, junk,previousjunk,secondtolastjunk;
	ifstream ifs;
	if(!ifs.is_open())
		ifs.open(filename);
	
	bool isRootNeeded=true;
	while (!ifs.eof())
	{	
		
		while (ifs.peek() != ')' && !ifs.eof()&& isRootNeeded) {
			getline(ifs, data);
			junk = data;
			addRoot(data);
			isRootNeeded = false;

		}

		
		if (ifs.peek() == ')') {
			isRootNeeded = false;
			secondtolastjunk = previousjunk;
			previousjunk = junk;
			getline(ifs, junk);
			
			if (currentRoot == root && previousjunk == junk&&junk==secondtolastjunk) {
				//getline(ifs, junk);
				if (ifs.eof()) {
					//cout << "valid file";
					return true;
				}
				else {
					//cout << "Invalid file sequence";
					return false;
				}
				break;
			}
			currentRoot = currentRoot->parent;

			
			
		}
		while (ifs.peek() != ')'&& !isRootNeeded) {
			getline(ifs, data);
			hire(currentRoot, data);
			junk = data;

		//	isRootNeeded = true;
		
		}
		

		
	}
		
	return true;
}

void OrgTree::hire(TreeNode* treeNode, string data) {
	TreeNode* temp = new TreeNode(data);
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
		printSubTree(temproot);
		cout << endl;
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

	//}
}

void OrgTree::printSubTree(TreeNode* subTreeRoot) {
	if (subTreeRoot == nullptr) {
		return;
	}
	cout << subTreeRoot->data;
	filecontents= filecontents+ subTreeRoot->data+"^";
	printSubTree(subTreeRoot->leftMostChild);
	cout << ")";
	filecontents = filecontents + ")" + "^";
	printSubTree(subTreeRoot->rightSibling);
}

unsigned int OrgTree::getSize() {
	return numElts;
}

TreeNode* OrgTree::getRoot() {
	return root;
}

TreeNode* OrgTree::find(string searchdata) {

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
		if (currentNode->data == searchdata)
		{
			returnValue = currentNode;
			return currentNode;
		}
		else {
			cout << currentNode->data << " ";

			// push right child of popped node to the stack
			if (currentNode->rightSibling)
				stack.push(currentNode->rightSibling);

			// push left child of popped node to the stack
			if (currentNode->leftMostChild)
				stack.push(currentNode->leftMostChild);
		}

		returnValue = nullptr;

		// important note - right child is pushed first so that left child
		// is processed first (FIFO order)
	}
	return returnValue;
}