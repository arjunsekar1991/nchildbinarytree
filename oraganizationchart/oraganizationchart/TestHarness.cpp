
#include "OrgTree.h"
#include <string>
#include <iostream>
using namespace std;

// This is not the complete test harness/driver for project 2, but
// is a good starting point.  You should test your project completely
// by adding additional tests for each item in the grading rubric!

int main() {
	//OrgTree o1, o2;
	
	// Adding roots should make a linear tree
	//o1.addRoot("R1", "R1");
	//o1.addRoot("R2", "R2");
	//o1.addRoot("R3", "R3");
	//o1.addRoot("R1");
	//o1.addRoot("R2");
	//o1.addRoot("R3");

	//o1.printSubTree(o1.getRoot()); //printSubTree from root


	//add two children to root
	//o1.hire(o1.getRoot(), "R3C1");
	//o1.hire(o1.getRoot(), "R3C2");


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
	OrgTree o1,o2,o3;
	o1.read("input.txt");
	o1.printSubTree(o1.find("VP Sales"));

	//TreeNode* rootAddress = o1.getRoot();
	//TreeNode* dataFinder;
	o1.write("output.txt");
	//cout << "size of organization" << o1.getSize();
	//dataFinder = o1.find("VM");
	//TreeNode* lefchild= o1.leftmostChild(dataFinder);

	//TreeNode* rightchild = o1.rightSibling(dataFinder);

	//o1.fire("DK");
	//o1.fire("VB");
	//o1.fire("DA");
	//o1.fire("MW");
	//o1.printSubTree(dataFinder);
	//o1.write("output.txt");

	/*o2.addRoot("DA");
	o2.addRoot("DG");
	o2.addRoot("VM");
	o2.addRoot("PG");
	o2.hire(o2.find("DG"), "HG");
	o2.hire(o2.find("VM"), "DK");
	o2.hire(o2.find("PG"), "VB");
	o2.hire(o2.find("PG"), "VA");
	o2.hire(o2.find("VA"), "MW");
	o2.hire(o2.find("VA"), "CB");
	o2.hire(o2.find("MW"), "SD");
	o2.hire(o2.find("MW"), "SM");
	o2.fire("DK");
	o2.fire("VB");
	o2.fire("DA");
	o2.fire("MW");
	o2.write("ouput2.txt");*/
	
	o3.addRoot("Digital Media Specialist","Al Gore");
	o3.addRoot("Director of Marketing","George Lucas");
	o3.addRoot("VP Sales","Mark Zuckerberg");
	o3.addRoot("President", "George Orwell");
	
	o3.hire(o3.find("Director of Marketing"), "Head of Television and Print Advertising", "George Martin");
	o3.hire(o3.find("VP Sales"), "Director of Public Relations", "Kurt Vonnegut");
	o3.hire(o3.find("President"), "VP Operations", "Bill Gates");
	o3.hire(o3.find("President"), "VP Software Development", "Ayn Rand");
	o3.hire(o3.find("VP Software Development"), "MagicBag Team Leader", "Wil Wheaton");
	o3.hire(o3.find("VP Software Development"), "Cloud Development", "Bob Ross");
	o3.hire(o3.find("MagicBag Team Leader"), "Software Engineer I", "Donald Knuth");
	o3.hire(o3.find("MagicBag Team Leader"), "Software Engineer II", "Marvin Minsky");
	//
	TREENODEPTR mynode = o3.find("President");	
	TREENODEPTR mynoderight = o3.leftmostChild(o3.find("President"));

	o3.fire("Head of Television and Print Advertising");
	o3.fire("VP Operations");
	o3.fire("VP Sales");
	//o3.fire("PG");
	//o3.fire("HG");
	o3.fire("Director of Public Relations");
	//o3.fire("VB");
	o3.fire("VP Software Development");
	o3.fire("MagicBag Team Leader");
	o3.fire("Cloud Development");
	o3.fire("Software Engineer I");
	o3.fire("Software Engineer II");
	o3.fire("Director of Marketing");
//	o3.fire("Digital Media Specialist");
	o3.rightSibling(o3.find("VP Sales"));
	o3.write("ouput3.txt");
	TREENODEPTR mynodeleft  = o3.leftmostChild(o3.find("President"));

	system("PAUSE");
	return 0;

}