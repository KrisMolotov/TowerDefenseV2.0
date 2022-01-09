#ifndef TOWERDEFENSEV2_BINARYTREE_H
#define TOWERDEFENSEV2_BINARYTREE_H
#include "TreeNode.h"

template <class Key, class Info>
class BinaryTree{
private:
    TreeNode<Key, Info>* head;
public:
    BinaryTree(): head(nullptr) {};
    ~BinaryTree() {head->deleteNode(head); head = nullptr;};
    TreeNode<Key, Info>* addNode(const Key& k, const Info& inf)
    {
        head = head->insert(head, head, k, inf);
        return head->findByKey(head, k);
    }
    const Info& getValue (const Key& k) const
    {
        TreeNode<Key, Info>* tmp = head->findByKey(head, k);
        return tmp->value;
    }
    TreeNode<Key, Info> * searchNode (const Key& k) const {return head->findByKey(head, k);}
    TreeNode<Key, Info>* nextNode (const Key& k)
    {
        TreeNode<Key, Info>* tmp = searchNode(k);
        return tmp->next(tmp);
    }
    TreeNode<Key, Info>* minNode () const {return head->findMinNode(head);}
    TreeNode<Key, Info> * maxNode () const {return head->findMaxNode(head);}
    void deleteTree() {head->deleteNode(head); head = nullptr;}
};
#endif //TOWERDEFENSEV2_BINARYTREE_H
