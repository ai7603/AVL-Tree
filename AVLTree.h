//
// Created by 灰原 on 2017/9/3.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H
#include "AVLTreeNode.h"

template<typename T>
class AVLTree{
private:
    AVLTreeNode<T>* root;
public:
    AVLTree() {}
    AVLTree(AVLTreeNode<T>* ptr = nullptr);
    ~AVLTree();
    AVLTreeNode<T>* insert(T tmp);
    void remove(T tmp);
    AVLTreeNode<T>* query(T tmp);
    int height();
    //void preorder();
    //void inorder();
    //void postorder();
    //void print();
private:
    // Return the root of tree
    AVLTreeNode<T>* insert(AVLTreeNode<T>* ptr, T tmp);
    AVLTreeNode<T>* remove(AVLTreeNode<T>* ptr, AVLTreeNode<T>* node);
    AVLTreeNode<T>* query(AVLTreeNode<T>* ptr, T tmp);
    int height(AVLTreeNode<T>* ptr);
    // Single Rotation
    AVLTreeNode<T>* LLRotation(AVLTreeNode<T>* k2);
    // return the new root
    AVLTreeNode<T>* RRRotation(AVLTreeNode<T>* k1);
    // return the new root

    AVLTreeNode<T>* LRRotation(AVLTreeNode<T>* k3);
    AVLTreeNode<T>* RLRotation(AVLTreeNode<T>* k1);

    AVLTreeNode<T>* getmax(AVLTreeNode<T>* ptr);
    AVLTreeNode<T>* getmin(AVLTreeNode<T>* ptr);

    AVLTreeNode<T>* delmax(AVLTreeNode<T>* ptr);
    AVLTreeNode<T>* delmin(AVLTreeNode<T>* ptr);
};
#endif //AVLTREE_AVLTREE_H
