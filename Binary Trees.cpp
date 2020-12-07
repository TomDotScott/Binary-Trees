#include <ctime>
#include <iostream>
#include "RedBlackTree.h"
#include "TwoThreeTree.h"

int random_range(const int min, const int max)
{
	static bool first = true;
	if (first)
	{
		//seeding for the first time only!
		srand(static_cast<unsigned>(time(nullptr)));
		first = false;
	}
	return min + rand() % ((max)-min);
}

int main()
{	
	TwoThreeTree tree;

	// Generate 20 random numbers and insert them into the 2-3 tree
	for(int i = 0; i < 20; ++i)
	{
		const auto randNum = random_range(0, 100);
		std::cout << "Inserting: " << randNum << std::endl;
		tree.Insert(randNum);
	}

	tree.Print();
}