#include "TwoThreeTree.h"

#include <iostream>

TwoThreeTree::TwoThreeTree()
{
	m_root = new TwoThreeNode();
	m_root->m_child[0] = new TwoThreeNode();
	m_root->m_child[0]->m_parent = m_root;
}

bool TwoThreeTree::Insert(int data)
{
	auto* newNode = new TwoThreeNode();
	auto* spot = m_root->m_child[0];

	if (spot->m_child[0] == nullptr)
	{
		// First insertion
		newNode->m_parent = spot;
		spot->m_child[0] = newNode;
	} else
	{
		spot = FindSpot(spot, data);
		if (spot == nullptr)
		{
			return false;
		}
		spot->Insert(new TwoThreeNode(data), data);
	}
	return true;
}

void TwoThreeTree::Print()
{
	PrintRecursive(m_root->m_child[0]);
	std::cout << std::endl;
}

TwoThreeNode* TwoThreeTree::FindSpot(TwoThreeNode* node, int data)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	while (!node->IsLeaf())
	{
		if (node->m_key[0] == data || node->m_key[1] == data)
		{
			return nullptr;
		}
		if (node->m_key[0] == -1 || data < node->m_key[0])
		{
			node = node->m_child[0];
		} else if (node->m_key[1] == -1 || data < node->m_key[1])
		{
			node = node->m_child[1];
		} else
		{
			node = node->m_child[2];
		}
	}

	if (node->m_key[0] == data)
	{
		return nullptr;
	} else
	{
		return node->m_parent;
	}
}

void TwoThreeTree::PrintRecursive(TwoThreeNode* node, int indentLevel)
{
	for (int i = 0; i < indentLevel; ++i)
	{
		std::cout << "    ";
	}

	if (node == nullptr)
	{
		std::cout << "---> NULL" << std::endl;
		return;
	}

	std::cout << "---> " << node->SiblingNumber() << ":  ( " << node->m_key[0]
		<< ", " << node->m_key[1] << ")" << std::endl;

	if(!node->IsLeaf())
	{
		++indentLevel;
		PrintRecursive(node->m_child[0], indentLevel);
		PrintRecursive(node->m_child[1], indentLevel);
		PrintRecursive(node->m_child[2], indentLevel);
	}
}
