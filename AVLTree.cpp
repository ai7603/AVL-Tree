//
// Created by 灰原 on 2017/9/3.
//
#include <iostream>
#include "AVLTree.h"

AVLTree:AVLTree(AVLTreeNode<T>* ptr = nullptr){
    this->root = ptr;
};
template<typename T>
AVLTreeNode<T>* AVLTree::insert(T tmp){
    insert(root, tmp);
}
template<typename T>
void AVLTree::remove(T tmp){
    AVLTreeNode<T>* temp = query(root, tmp);
    if(temp != NULL) {
        remove(root, temp);
    }
}
template<typename T>
AVLTreeNode<T>* AVLTree::query(T tmp){
    return query(root, tmp);
}
int AVLTree::height(){
    return height(root);
}

template <typename T>
AVLTreeNode<T>* AVLTree::insert(AVLTreeNode<T>* ptr, T tmp){
    if(ptr == NULL){
        ptr = new AVLTreeNode(tmp, NULL,NULL);
        if(ptr == NULL){
            std::cerr << "ERROR WHEN CREATE NEW NODE" << std::endl;
            return NULL;
        }
    }
    else if(tmp < ptr->key()){
        ptr->setLeft(insert(ptr->left(), tmp));
        if(height(ptr->left()) - height(ptr->right()) == 2) {
            if(tmp > ptr->left()->key()){
                ptr = LRRotation(ptr);
            }
            else{
                ptr = LLRotation(ptr);
            }
        }
    }
    else if(tmp > ptr->key()){
        ptr->setRight(insert(ptr->right(), tmp));
        if(height(ptr->right()) - height(ptr->left()) == 2) {
            if (tmp > ptr->right()->key()) {
                ptr = RRRotation(ptr);
            } else {
                ptr = RLRotation(ptr);
            }
        }
    }
    else{
        std::cerr << "THERE IS A SAME VALUE IN THE AVL TREE" << std::endl;
    }
    ptr->setHeight(max(height(ptr->left()), height(ptr->right())) + 1);
    return ptr;
}
template<typename T>
AVLTreeNode<T>* AVLTree::remove(AVLTreeNode<T>*ptr, AVLTreeNode<T>* node) {
    if(ptr == NULL || node == NULL) {
        return NULL;
    }
    if(node->key() < ptr->key()){
        ptr->setLeft(remove(ptr->left(), node));
        if(height(ptr->right()) - height(ptr->left()) == 2){
            AVLTreeNode<T>* r = ptr->right();
            /*
             * If right subtree's left subtree is higher than the right, we can rotation the left,
             * or rotation the right, after the first rotation, make a right rotation
             */
            if(height(r->left()) > height(r->right()))
                ptr = RLRotation(ptr);
            else
                ptr = RRRotation(ptr);
        }
    }
    else if(node->key() > ptr->key()){
        ptr->setRight(remove(ptr->right(), node));
        if(height(ptr->left()) - height(ptr->right()) == 2){
            AVLTreeNode<T>* l = ptr->left();
            /*
             * similarity with delete in the left subtree
             */
            if(height(l->left()) > height(l->right()))
                ptr = LLRotation(ptr);
            else
                ptr = LRRotation(ptr);
        }
    }
    else{
        // If target node has both left subtree and right subtree
        if(ptr->left() != NULL && ptr->right() != NULL){
            if(height(ptr->left()) > height(ptr->right())){
                /*
                 *  If the left subtree is higher than right one
                 *  find the max node in the left subtree and use it to replace the current node
                 *  then delete the max node
                 *  with these operations we can delete the objective and at the same time we won't break the balance of tree
                 */
                AVLTreeNode<T>* MaxNode = getmax(ptr->left());
                if(MaxNode != NULL){
                    ptr->setKey(MaxNode->key());
                    ptr->setLeft(remove(ptr->left(), MaxNode));
                }
                else{
                    std::cerr << "ERROR WHEN DELETE" << std::endl;
                }
            }
            else{
                /*
                 * If the right ssubtree is not lower than left one
                 * find the min node in the right subtree and use it to replace the current node
                 * then delete the min node
                 * By these operations we can delete target node and keep the balance of tree
                 */
                AVLTreeNode<T>* MinNode = getmin(ptr->right());
                if(MinNode != NULL){
                    ptr->setKey(MinNode->key());
                    ptr->setRight(remove(ptr->right(), MinNode));
                }
                else{
                    std::cerr << "ERROR WHEN DELETE" << std::endl;
                }
            }
        }
        else{
            AVLTreeNode<T>* temp = ptr;
            if(ptr->left() == NULL){
                ptr = ptr->right();
            }
            else{
                ptr = ptr->left();
            }
            delete temp;
        }
    }
    return ptr;
}
template<typename T>
AVLTreeNode<T>* AVLTree::query(AVLTreeNode<T>* ptr, T tmp){
    AVLTreeNode<T>* k = ptr;
    while(tmp != k->key() && k != NULL){
        if(tmp < k->key()) k = k->left();
        else k = k->right();
    }
    return k;
}
template<typename T>
int AVLTree::height(AVLTreeNode<T>* ptr){
    if(ptr != NULL) return ptr->height();
    return 0;
}

//  Rotation of the structure of tree

/*
 *  The shape of the tree
 *             k2                    k1
 *            /  \                  /  \
 *           k1   A                B    K2
 *          /  \          ->      /    /  \
 *         B    C                N    C    A
 *        /
 *       N
 *  N is the new node that inserts into the tree
 */
template<typename T>
AVLTreeNode<T>* AVLTree::LLRotation(AVLTreeNode<T>* k2){
    AVLTreeNode<T>* k1 = k2->left();
    k2->setLeft(k1->right());
    k1->setRight(k2);
    // Update the height
    k2->setHeight(max(height(k2->left()), height(k2->right())) + 1);
    k1->setHeight(max(height(k1->left()), k2->height()) + 1);
    return k1;
}
/*
 * The shape of the tree
 *             k1                           K2
 *            /  \                         /  \
 *           A    k2                      K1   C
 *               /  \          ->        /  \   \
 *              B    C                  A    B   N
 *                    \
 *                     N
 *  N is the new node that inserts into the tree
 */
template<typename T>
AVLTreeNode<T>* AVLTree::RRRotation(AVLTreeNode<T>* k1){
    AVLTreeNode<T>* k2 = k1->right();
    k1->setRight(k2->left());
    k2->setLeft(k1);
    // Update the height
    k1->setHeight(max(height(k1->left()), height(k1->right())) + 1);
    k2->setHeight(max(height(k2->right()), k1->height()) + 1);
    return k2;
}
/*
 * The shape of the tree
 *             k3                           K3                       K2
 *            /  \                         /  \                     /  \
 *           K1    A                      K2   A                  K1    K3
 *          /  \              ->         /  \            ->      /  \  /  \
 *         B    K2                      K1  N2                  B  N1  N2  A
 *             /  \                    /  \
 *            N1   N2                 B   N1
 *  N is the new node that inserts into the tree
 */
template<typename T>
AVLTreeNode<T>* AVLTree::LRRotation(AVLTreeNode<T>* k3){
    k3->setLeft(RRRotation(k3->left()));
    return LLRotation(k3);
}
/*
 * The shape of the tree
 *             k1                           K1                           K3
 *            /  \                         /  \                         /  \
 *           A    k2                      A   K3                      K1    K2
 *               /  \         ->             /  \            ->      /  \  /  \
 *              K3   B                     N1   K2                  A  N1  N2  B
 *             /  \                            /  \
 *            N1   N2                         N2   B
 *  N is the new node that inserts into the tree
 */
template<typename T>
AVLTreeNode<T>* AVLTree::RLRotation(AVLTreeNode<T>* k1){
    k1->setRight(LLRotation(k1->right()));
    return RRRotation(k1);
}

/*
 *  Get the max node in the subtree then return the max node's pointer
 */
template <typename T>
AVLTreeNode<T>* AVLTree::getmax(AVLTreeNode<T>* ptr) {
    if(ptr == NULL) return NULL;
    if(ptr->right() == NULL) return ptr;
    else return getmax(ptr->right());
}
// Get the min node in the subtree then return the min node's pointer
template <typename T>
AVLTreeNode<T>* AVLTree::getmin(AVLTreeNode<T>* ptr){
    if(ptr == NULL) return NULL;
    if(ptr->left() == NULL) return ptr;
    else return getmin(ptr->left());
}
// Delete the max node and return the deleted nods's subtree's pointer
AVLTreeNode<T>* AVLTree::delmax(AVLTreeNode<T>* ptr) {
    if(ptr == NULL) return NULL;
    if(ptr->right() == NULL) return ptr->left();
    else{
        ptr->setRight(delmax(ptr->right()));
        return ptr;
    }
}
// Delete the Min node and return the deleted node;s subtree's pointer
template<typename T>
AVLTreeNode<T>* AVLTree::delmin(AVLTreeNode<T>* ptr){
    if(ptr == NULL) return NULL;
    if(ptr->left()) return ptr->right();
    else{
        ptr->setLeft(delmin(ptr->left()));
        return ptr;
    }
}