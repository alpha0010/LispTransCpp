/*
 * Data structure for reasonably fast and memory efficient key/value pairs.
 * Intended for use with large sets of (overlapping) string keys.
 */

#include "treemap.h"

#include <algorithm>

struct TreeNode
{
    TreeNode(char ch) : value(ch) {};

    void AddLeaf(KeyIterator first, KeyIterator last, int leaf);

    std::vector<int> GetLeaves(KeyIterator first, KeyIterator last) const;

    char value;
    std::vector<TreeNode> children;
    std::vector<int> leaves;
};

struct TreeNodeLess
{
    bool operator() (const TreeNode& a, const TreeNode& b)
    {
        return (a.value < b.value);
    }
};

void TreeNode::AddLeaf(KeyIterator first, KeyIterator last, int leaf)
{
    if (first == last)
    {
        std::vector<int>::iterator itr = std::lower_bound(leaves.begin(), leaves.end(), leaf);
        if (itr == leaves.end() || *itr != leaf)
            leaves.insert(itr, leaf);
    }
    else
    {
        std::vector<TreeNode>::iterator itr = std::lower_bound(children.begin(), children.end(), TreeNode(*first), TreeNodeLess());
        if (itr == children.end() || itr->value != *first)
            itr = children.insert(itr, TreeNode(*first));
        itr->AddLeaf(first + 1, last, leaf);
    }
}

std::vector<int> TreeNode::GetLeaves(KeyIterator first, KeyIterator last) const
{
    if (first == last)
        return leaves;
    std::vector<TreeNode>::const_iterator itr = std::lower_bound(children.begin(), children.end(), TreeNode(*first), TreeNodeLess());
    if (itr == children.end() || itr->value != *first)
        return std::vector<int>();
    return itr->GetLeaves(first + 1, last);
}



TreeMap<int>::TreeMap() :
    m_Root(new TreeNode('\0'))
{
}

TreeMap<int>::~TreeMap()
{
    delete m_Root;
}

int TreeMap<int>::Insert(KeyIterator first, KeyIterator last, int value)
{
    m_Root->AddLeaf(first, last, value);
    return value;
}

std::vector<int> TreeMap<int>::GetIdSet(KeyIterator first, KeyIterator last) const
{
    return m_Root->GetLeaves(first, last);
}

int TreeMap<int>::GetValue(int id) const
{
    return id;
}
