#ifndef TOWERDEFENSEV2_TREENODE_H
#define TOWERDEFENSEV2_TREENODE_H
template <class Key, class Info>
class TreeNode
{
private:
    TreeNode* right; // указатель на правое поддерево
    TreeNode* left; // указатель на левое поддерево
    TreeNode* parent; // указатель на родителя
    Key key; // ключ ячейки контейнера
    Info value; // значение по ключю в ячейке контейнера
public:
    TreeNode():right(nullptr), left(nullptr), parent(nullptr){}; // пустой конструктор
    TreeNode(const Key& k, const Info& inf, TreeNode<Key, Info>* p):key(k), value(inf), right(nullptr), left(nullptr), parent(p){}; // иниц.конструктор
    TreeNode<Key, Info>* insert(TreeNode<Key, Info>* head, TreeNode<Key, Info>* p, const Key& k, const Info& inf)
    {
        if(head == nullptr)
        {
            auto* tmp = new TreeNode(k, inf, p);
            return tmp;
        }
        if(k > head->key)
        {
            head->right = insert(head->right, head, k, inf);
        }
        else if(k < head->key)
        {
            head->left = insert(head->left, head, k, inf);
        }
        return head;
    }
    TreeNode<Key, Info>* findByKey(TreeNode<Key, Info>* tmp, Key k) const
    {
        if(tmp == nullptr || tmp->key == k)
        {
            return tmp;
        }
        if(k > tmp->key)
        {
            return findByKey(tmp->right, k);
        }
        return findByKey(tmp->left, k);
    }
    void deleteNode(TreeNode<Key, Info>* tmp)
    {
        if(tmp == nullptr)
        {
            return;
        }
        deleteNode(tmp->right);
        deleteNode(tmp->left);
        delete tmp;
        tmp = nullptr;
    }
    TreeNode<Key, Info>* next (TreeNode<Key, Info>* tmp)
    {
        if(tmp->right != nullptr)
        {
            return findMinNode(tmp->right);
        }
        TreeNode<Key, Info>* dop = tmp->parent;
        while(dop != nullptr && tmp == dop->right)
        {
            tmp = dop;
            dop = dop->parent;
        }
        return dop;
    }
    TreeNode<Key, Info>* findMinNode(TreeNode<Key, Info>* tmp) const
    {
        if(tmp == nullptr)
        {
            return tmp;
        }
        while(tmp->left != nullptr)
        {
            tmp = tmp->left;
        }
        return tmp;
    }
    TreeNode<Key, Info>* findMaxNode(TreeNode<Key, Info>* tmp) const
    {
        if(tmp == nullptr)
        {
            return tmp;
        }
        while(tmp->right != nullptr)
        {
            tmp = tmp->right;
        }
        return tmp;
    }
    Key& getKey() {return this->key;}
    Info& getInfo() {return this->value;}
};

#endif //TOWERDEFENSEV2_TREENODE_H
