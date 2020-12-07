#pragma once

class TwoThreeNode
{
public:
	explicit TwoThreeNode(int data = -1);
	bool IsLeaf();
	int SiblingNumber();
	void Insert(TwoThreeNode* newChild, int newSmallest);
	
	TwoThreeNode* m_parent;
	TwoThreeNode* m_child[3];
	
	int m_key[2];

private:
	int GetSmallest();
	void Insert1Sibling(TwoThreeNode* newChild, int newSmallest);
	void Insert2Siblings(TwoThreeNode* newChild, int newSmallest);
	void Insert3Siblings(TwoThreeNode* newChild, int newSmallest);
	void UpdateParentSmallest(int data);
};