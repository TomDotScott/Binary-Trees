#include "RedBlackTree.h"

#include <iostream>

RedBlackTree::RedBlackTree()
{
	TNULL = new RedBlackNode();
	TNULL->m_colour = eTreeColour::e_Black;
	TNULL->m_leftNode = nullptr;
	TNULL->m_rightNode = nullptr;
	m_root = TNULL;
}


/// <summary>
/// Inserts a key into the tree in its appropriate position and fixes the tree
/// </summary>
/// <param name="key">The data key to be inserted into the tree</param>
void RedBlackTree::Insert(const int key)
{
	// Normal binary search insertion
	auto* newNode = new RedBlackNode();
	newNode->m_parentNode = nullptr;
	newNode->m_data = key;
	newNode->m_leftNode = TNULL;
	newNode->m_rightNode = TNULL;
	newNode->m_colour = eTreeColour::e_Red; // Every new node in a Red Black Tree must be red

	RedBlackNode* y = nullptr;
	RedBlackNode* x = m_root;

	while (x != TNULL)
	{
		y = x;
		if(newNode->m_data < x->m_data)
		{
			x = x->m_leftNode;
		}else
		{
			x = x->m_rightNode;
		}
	}

	newNode->m_parentNode = y;
	if(y == nullptr)
	{
		m_root = newNode;
	}else if(newNode->m_data < y->m_data)
	{
		y->m_leftNode = newNode;
	}else
	{
		y->m_rightNode = newNode;
	}

	// if the new node is a root node, return
	if(newNode->m_parentNode == nullptr)
	{
		newNode->m_colour = eTreeColour::e_Black;
		return;
	}

	// if the grandparent is null, return
	if(newNode->m_parentNode->m_parentNode == nullptr)
	{
		return;
	}
	// TODO: FIX THE TREE
}

/// <summary>
/// Displays the tree in the console
/// </summary>
void RedBlackTree::PrintTree() const
{
	if(m_root)
	{
		std::string indent;
		RecursivePrint(m_root, indent, false);
	}
}

/// <summary>
/// Recursively prints out the RB Tree to the console
/// </summary>
/// <param name="root">The current node</param>
/// <param name="indent">The string indent between nodes (helps everything look pretty)</param>
/// <param name="leaf">Whether it is a leaf node</param>
void RedBlackTree::RecursivePrint(RedBlackNode* root, std::string& indent, const bool leaf) const
{
	if(root)
	{
		std::cout << indent;
		if(leaf)
		{
			std::cout << "R-----";
			indent += "     ";
		}else
		{
			std::cout << "L-----";
			indent += "|    ";
		}

		const std::string colour = root->m_colour == eTreeColour::e_Red ? "RED" : "BLACK";

		std::cout << root->m_data << "(" << colour << ")" << std::endl;
		RecursivePrint(root->m_leftNode, indent, false);
		RecursivePrint(root->m_rightNode, indent, true);
	}
}
