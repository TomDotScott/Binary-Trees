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

	RedBlackNode* x = m_root;
	RedBlackNode* y = nullptr;

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

	// fix the tree
	FixInsert(newNode);
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

void RedBlackTree::RotateLeft(RedBlackNode* node)
{
	auto temp = node->m_rightNode;
	node->m_rightNode = temp->m_leftNode;
	
	if(temp->m_leftNode != TNULL)
	{
		temp->m_leftNode->m_parentNode = node;
	}

	temp->m_parentNode = node->m_parentNode;

	if(node->m_parentNode == nullptr)
	{
		m_root = temp;
	}else if(node == node->m_parentNode->m_leftNode)
	{
		node->m_parentNode->m_leftNode = temp;
	}else
	{
		node->m_parentNode->m_rightNode = temp;
	}

	temp->m_leftNode = node;
	node->m_parentNode = temp;
}

void RedBlackTree::RotateRight(RedBlackNode* node)
{
	auto* temp = node->m_leftNode;
	node->m_leftNode = temp->m_rightNode;

	if(temp->m_rightNode != TNULL)
	{
		temp->m_rightNode->m_parentNode = node;
	}

	temp->m_parentNode = node->m_parentNode;

	if(node->m_parentNode == nullptr)
	{
		m_root = temp;
	} else if (node == node->m_parentNode->m_rightNode)
	{
		node->m_parentNode->m_rightNode = temp;
	}else
	{
		node->m_parentNode->m_leftNode = temp;
	}

	temp->m_rightNode = node;
	node->m_parentNode = temp;
}


/// <summary>
/// Maintains the Red-Black Tree properties:
/// 1. Each node is either red or black.
/// 2. The root is black.This rule is sometimes omitted.Since the root can always be changed from red to black, but not necessarily vice versa, this rule has little effect on analysis.
/// 3. All leaves are black.
/// 4. If a node is red, then both its children are black.
/// 5. Every path from a given node to any of its descendant leaf nodes goes through the same number of black nodes.
/// </summary>
/// <param name="child">The newly inserted node</param>
void RedBlackTree::FixInsert(RedBlackNode* child)
{
	RedBlackNode* uncle;
	while(child->m_parentNode->m_colour == eTreeColour::e_Red)
	{
		if(child->m_parentNode == child->m_parentNode->m_rightNode)
		{
			uncle = child->m_parentNode->m_parentNode->m_leftNode;
			if(uncle->m_colour == eTreeColour::e_Red)
			{
				// If the parent and the uncle are red
				// Flip the colour of the nodes
				uncle->m_colour = eTreeColour::e_Black;
				child->m_parentNode->m_colour = eTreeColour::e_Black;
				child->m_parentNode->m_parentNode->m_colour = eTreeColour::e_Red;
				child = child->m_parentNode->m_parentNode;
			}else
			{
				if(child == child->m_parentNode->m_leftNode)
				{
					// If the Parent is the right child of the Grandparent and Kid is
					// the left child of the Parent, we need to do the right rotation
					// first to fix the tree
					child = child->m_parentNode;
					RotateRight(child);
				}

				// Now, the Parent is the right child of Grandparent and the Kid is the
				// right child of the Parent. We need to perform the left rotation
				// and change the colour of the Parent to black
				child->m_parentNode->m_colour = eTreeColour::e_Black;
				child->m_parentNode->m_parentNode->m_colour = eTreeColour::e_Red;
				RotateLeft(child->m_parentNode->m_parentNode);
			}
		}else
		{
			// Method is exactly the same as above, just mirrored
			
			uncle = child->m_parentNode->m_parentNode->m_rightNode;

			if(uncle->m_colour == eTreeColour::e_Red)
			{
				uncle->m_colour = eTreeColour::e_Black;
				child->m_parentNode->m_colour = eTreeColour::e_Black;
				child->m_parentNode->m_parentNode->m_colour = eTreeColour::e_Red;
				child = child->m_parentNode->m_parentNode;
			}else
			{
				if(child == child->m_parentNode->m_rightNode)
				{
					child = child->m_parentNode;
					RotateLeft(child);
				}

				child->m_parentNode->m_colour = eTreeColour::e_Black;
				child->m_parentNode->m_parentNode->m_colour = eTreeColour::e_Red;
				RotateRight(child->m_parentNode->m_parentNode);
			}
		}
		if(child == m_root)
		{
			break;
		}
	}
	m_root->m_colour = eTreeColour::e_Black;
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
