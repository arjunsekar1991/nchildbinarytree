
#include "OrgTree.h"
#include <string>
#include <iostream>
using namespace std;

// This is not the complete test harness/driver for project 2, but
// is a good starting point.  You should test your project completely
// by adding additional tests for each item in the grading rubric!

int main() {
	OrgTree o1, o2;

	// Adding roots should make a linear tree
	//o1.addRoot("R1", "R1");
	//o1.addRoot("R2", "R2");
	//o1.addRoot("R3", "R3");

	//o1.printSubTree(o1.getRoot()); //printSubTree from root


	//add two children to root
	//o1.hire(o1.getRoot(), "R3C1", "R3C1");
	//o1.hire(o1.getRoot(), "R3C2", "R3C2");


	//o1.hire(o1.find("R3C1"), "R3C1C1", "R3C1C1");//test find on leaf node and hire to it


	//cout << o1.getSize() << endl;
	//o1.printSubTree(o1.getRoot()); //printSubTree from root


	//o1.fire("R3C1"); //fire an internal node
	//cout << o1.getSize() << endl;
	//o1.printSubTree(o1.getRoot());

	// Write out a tree and read it back in to a new tree, then print
	//o1.write("output.txt");
	//o2.read("output.txt");
	//o2.printSubTree(o2.getRoot()); //printSubTree from root

	system("PAUSE");
	return 0;

}