#pragma once
#include <string>
#include <iostream>
#include <exception>


using namespace std;


class OrgTree{ 
private:
	class TreeNode {
	public:
		string title;
		string name;
		TreeNode* parent;
		TreeNode* leftMostChild;
		TreeNode* rightSibling;

		TreeNode(string titleOrganization, string fullName) {
			parent = nullptr;
			leftMostChild = nullptr;
			rightSibling = nullptr;
			title = titleOrganization;
			name = fullName;
			
		}
		~TreeNode() {

		};
	};

public:
	
	OrgTree();
	~OrgTree();           // Destructor
//	void addRoot(string, string);
//	unsigned int getSize();
//	TreeNode* getRoot();
//	TreeNode* leftmostChild(TreeNode* node);
//	TreeNode* rightSibling(TreeNode* node);
//	void printSubTree(TreeNode* subTreeRoot);
//	TreeNode* find(string);
//	bool read(string);
//	void write(string);
//	void hire(TreeNode*, string, string);
//	bool fire(string)
	

};