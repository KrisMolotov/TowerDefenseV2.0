#ifndef TOWERDEFENSEV2_MAP_H
#define TOWERDEFENSEV2_MAP_H
#include <stdexcept>
#include "BinaryTree.h"
#include "TreeNode.h"

template<class Key, class Info>
class MapIterator;

template<class Key, class Info>
class Map : public TreeNode<Key, Info>
{
private:
    BinaryTree<Key, Info> tree;
    int cnt;
public:
    Map():cnt(0) {};
    [[nodiscard]] int sizeMap() const {return cnt;}
    [[nodiscard]] bool isEmpty() const {return cnt == 0;}
    void clearMap() noexcept
    {
        tree.deleteTree();
        cnt = 0;
    }
    Info&& operator [] (const Key& key) const // r-value
    {
        auto a = find(key);
        if(a == end())
        {
            throw std::invalid_argument("Invalid key!");
        }
        return a->getInfo();
    }
    Info& operator [] (Key&& key)// l-value
    {
        auto a = find(key);
        if(a == end())
        {
            Info inf;
            auto dop = insert(key, inf);
            return dop->getInfo();
        }
        return a->getInfo();
    }
    friend class MapIterator<Key, Info>;
    typedef MapIterator<Key, Info> iterator;
    iterator begin() const
    {
        return iterator(tree.minNode());
    }
    iterator end() const
    {
        return iterator(nullptr);
    }
    iterator find(const Key& k) const
    {
        auto res = tree.searchNode(k);
        if(res == nullptr)
        {
            return end();
        }
        return iterator(res);
    }
    iterator insert(const Key& key, const Info& info)
    {
        auto tmp = find(key);
        if(tmp != end())
        {
            throw std::invalid_argument("This element is already inserted!");
        }
        iterator dop(tree.addNode(key, info));
        ++cnt;
        return dop;
    }
};

template <class Key, class Info>
class MapIterator
{
private:
    TreeNode<Key, Info>* cur;
public:
    MapIterator():cur(nullptr) {};
    explicit MapIterator(TreeNode<Key, Info>* a): cur(a) {};
    TreeNode<Key, Info>* getCur() const {return cur;}
    bool operator !=(const MapIterator<Key, Info>& it) const
    {
        return cur != it.cur;
    }
    bool operator == (const MapIterator<Key, Info>& it) const
    {
        return cur == it.cur;
    }
    TreeNode<Key, Info>& operator*()
    {
        return *cur;
    }
    TreeNode<Key, Info>* operator->()
    {
        return cur;
    }
    MapIterator<Key, Info>& operator ++()
    {
        cur = cur->next(cur);
        return *this;
    }
    const MapIterator<Key, Info>  operator ++(int)
    {
        const MapIterator res(*this);
        ++cur;
        return res;
    }
};
#endif //TOWERDEFENSEV2_MAP_H
