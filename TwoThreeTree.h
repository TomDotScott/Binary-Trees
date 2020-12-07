#pragma once
#include "TwoThreeNode.h"

class TwoThreeTree
{
public:
	TwoThreeTree();
	bool Insert(int data);
	void Print();
	
private:
	TwoThreeNode* m_root;

	TwoThreeNode* FindSpot(TwoThreeNode* node, int data);
	void PrintRecursive(TwoThreeNode* node, int indentLevel = 0);
};

