//
// Created by 灰原 on 2017/9/3.
//
#include "AVLTreeNode.h"

template<typename T>
T AVLTreeNode::key(){
    return this->key;
}
AVLTreeNode* AVLTreeNode::left(){
    return this->left;
}
AVLTreeNode* AVLTreeNode::right(){
    return this->right;
}
AVLTreeNode* AVLTreeNode::height(){
    return this->height;
}
void AVLTreeNode::setLeft(AVLTreeNode<T> *ptr) {
    this->left = ptr;
}
void AVLTreeNode::setRight(AVLTreeNode<T> ptr) {
    this->right = ptr;
}
void AVLTreeNode::setHeight(int h) {
    this->height = h;
}
void AVLTreeNode::setKey(T tmp) {
    this->key = tmp;
}