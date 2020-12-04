#include <iostream>
#include "RedBlackTree.h"

int main()
{
	RedBlackTree redBlack;
	redBlack.Insert(8);
	redBlack.Insert(18);
	redBlack.Insert(5);
	redBlack.Insert(15);
	redBlack.Insert(17);
	redBlack.Insert(6);
	redBlack.PrintTree();
}