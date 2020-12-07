#include "TwoThreeNode.h"
TwoThreeNode::TwoThreeNode(const int data) :
	m_parent(nullptr),
	m_child{ nullptr, nullptr, nullptr },
	m_key{ data, -1 }
{
}

bool TwoThreeNode::IsLeaf()
{
	return m_child[0] == nullptr;
}

int TwoThreeNode::SiblingNumber()
{
	for (int i = 0; i < 3; ++i)
	{
		if (this == m_parent->m_child[i])
		{
			return i;
		}
	}
	return -1;
}

void TwoThreeNode::Insert(TwoThreeNode* newChild, int newSmallest)
{
	if (m_child[1] == nullptr)
	{
		Insert1Sibling(newChild, newSmallest);
	} else if (m_child[2] == nullptr)
	{
		Insert2Siblings(newChild, newSmallest);
	} else
	{
		Insert3Siblings(newChild, newSmallest);
	}
}

/// <returns>The value of the smallest data item in the subtree rooted by this node</returns>
int TwoThreeNode::GetSmallest()
{
	TwoThreeNode* node = this;
	while (!node->IsLeaf())
	{
		node = node->m_child[0];
	}
	return node->m_key[0];
}

void TwoThreeNode::Insert1Sibling(TwoThreeNode* newChild, const int newSmallest)
{
	const auto newKey = newChild->m_key[0];
	newChild->m_parent = this;

	if (newKey < m_child[0]->m_key[0])
	{
		// insert the child as the first child of the root
		m_child[1] = m_child[0];
		m_child[0] = newChild;
		m_key[0] = m_child[1]->GetSmallest();
	} else
	{
		// the new node is inserted as a second child of the root
		m_child[1] = newChild;
		m_key[0] = newSmallest;
	}
}

void TwoThreeNode::Insert2Siblings(TwoThreeNode* newChild, int newSmallest)
{
	const auto newKey = newChild->m_key[0];
	newChild->m_parent = this;

	if (newKey < m_child[0]->m_key[0])
	{
		m_child[2] = m_child[1];
		m_child[1] = m_child[0];
		m_child[0] = newChild;

		m_key[1] = m_key[0];
		m_key[0] = m_child[1]->GetSmallest();
		UpdateParentSmallest(newSmallest);
	} else if (newKey < m_child[1]->m_key[0])
	{
		m_child[2] = m_child[1];
		m_child[1] = newChild;

		m_key[1] = m_key[0];
		m_key[0] = newSmallest;
	} else
	{
		m_child[2] = newChild;

		m_key[1] = newSmallest;
	}
}

void TwoThreeNode::Insert3Siblings(TwoThreeNode* newChild, int newSmallest)
{
	const auto newKey = newChild->m_key[0];

	int splitSmallest = -1;
	auto* splitNode = new TwoThreeNode();
	splitNode->m_parent = m_parent;

	if (newKey < m_child[0]->m_key[0] || newKey < m_child[1]->m_key[0])
	{
		// the new child is inserted into the current node
		splitSmallest = m_key[0];
		splitNode->m_child[0] = m_child[1];
		splitNode->m_child[1] = m_child[2];
		splitNode->m_key[0] = m_key[1];

		m_child[1]->m_parent = splitNode;
		m_child[2]->m_parent = splitNode;
		newChild->m_parent = this;

		if (newKey < m_child[0]->m_key[0])
		{
			// the new child is inserted as the first child
			m_child[1] = m_child[0];
			m_child[0] = newChild;

			m_key[0] = m_child[1]->GetSmallest();
			UpdateParentSmallest(newSmallest);
		} else
		{
			// the new child is inserted as the second child
			m_child[1] = newChild;
			m_key[0] = newSmallest;
		}
	} else
	{
		// the new child is inserted in the split node
		m_child[2]->m_parent = splitNode;
		newChild->m_parent = splitNode;

		if (newKey < m_child[2]->m_key[0])
		{
			// insert new child as the first child
			splitSmallest = newSmallest;
			splitNode->m_child[0] = newChild;
			splitNode->m_child[1] = m_child[2];
			splitNode->m_key[0] = m_key[1];
		} else
		{
			// the new child is the second child
			splitSmallest = m_key[1];
			splitNode->m_child[0] = m_child[2];
			splitNode->m_child[1] = newChild;
			splitNode->m_key[0] = newSmallest;
		}
	}

	m_child[2] = nullptr;
	m_key[1] = -1;

	if (m_parent->m_parent == nullptr)
	{
		// we are at the root, so a new root needs to be created
		auto newRoot = new TwoThreeNode();

		m_parent->m_child[0] = newRoot;
		newRoot->m_parent = m_parent;
		newRoot->m_child[0] = this;
		m_parent = newRoot;
	}

	m_parent->Insert(splitNode, splitSmallest);
}

void TwoThreeNode::UpdateParentSmallest(int data)
{
	switch (SiblingNumber())
	{
	case 0:
		if (m_parent->m_parent != nullptr)
		{
			m_parent->UpdateParentSmallest(data);
		}
		break;

	case 1:
		m_parent->m_key[0] = data;
		break;

	case 2:
		m_parent->m_key[1] = data;
		break;
	default: break;
	}
}