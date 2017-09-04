//
// Created by 灰原 on 2017/9/3.
//

#ifndef AVLTREE_AVLTREENODE_H
#define AVLTREE_AVLTREENODE_H

template<typename T>
class AVLTreeNode{
private:
    T Key;
    int Height;
    AVLTreeNode *Left;
    AVLTreeNode *Right;
public:
    AVLTreeNode(T val, AVLTreeNode* l, AVLTreeNode* r): Key(val), Height(0), Left(l), Right(r){}
    int height();
    T key();
    AVLTreeNode* left();
    AVLTreeNode* right();
    void setLeft(AVLTreeNode<T>* ptr);
    void setRight(AVLTreeNode<T> ptr);
    void setHeight(int h);
    void setKey(T tmp);
};
#endif //AVLTREE_AVLTREENODE_H
