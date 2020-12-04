#pragma once
#include <string>

enum class eTreeColour
{
	e_Black, e_Red
};

struct RedBlackNode
{
	int m_data;
	RedBlackNode* m_parentNode;
	RedBlackNode* m_leftNode;
	RedBlackNode* m_rightNode;
	eTreeColour m_colour;
};

class RedBlackTree
{
public:
	RedBlackTree();
	void Insert(int key);
	void PrintTree() const;
private:
	RedBlackNode* m_root;
	RedBlackNode* TNULL;

	void RecursivePrint(RedBlackNode* root, std::string& indent, bool leaf) const;
};

