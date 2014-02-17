#ifndef TREEMAP_H
#define TREEMAP_H

#include <vector>

struct TreeNode;
template<typename _Tp> class TreeMap;
//typedef std::vector<char>::const_iterator KeyIterator;
typedef const char* KeyIterator;

template<>
class TreeMap<int>
{
    public:
        TreeMap();
        ~TreeMap();
        int Insert(KeyIterator first, KeyIterator last, int value); // returns value
        std::vector<int> GetIdSet(KeyIterator first, KeyIterator last) const;
        int GetValue(int id) const; // returns id
    private:
        TreeNode* m_Root;
};

template<typename _Tp>
class TreeMap
{
    public:
        // returns the id of the value inserted
        int Insert(KeyIterator first, KeyIterator last, const _Tp& value)
        {
            m_Data.push_back(value);
            return m_Tree.Insert(first, last, m_Data.size() - 1);
        }

        std::vector<int> GetIdSet(KeyIterator first, KeyIterator last) const
        {
            return m_Tree.GetIdSet(first, last);
        }

        _Tp& GetValue(int id)
        {
            return m_Data[id];
        }

    private:
        TreeMap<int> m_Tree;
        std::vector<_Tp> m_Data;
};

#endif // TREEMAP_H
