/**
 * 只加了插入和删除，属于二叉树必会操作，具体解释可以看 https://www.cnblogs.com/MrListening/p/5782752.html
 */
#ifndef __BINARY_H__
#define __BINARY_H__

#include <stdio.h>

template<class T>
class TreeNode{
public:
    T key;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode(T value):key(value),left(NULL),right(NULL){};
};

template<class T>
class BinaryTree{
public:
    BinaryTree();
    ~BinaryTree();
    bool treeEmpty();
    bool insert(T value);
    bool deleteValue(T value);
    void inorderTree(TreeNode<T>* value);
public:
    TreeNode<T>* root;
};

#endif

template<class T>
BinaryTree<T>::BinaryTree(){
    root = NULL;
}

template<class T>
BinaryTree<T>::~BinaryTree(){
    //destroy
}

template<class T>
bool BinaryTree<T>::treeEmpty(){
    return root == NULL;
}

template<class T>
bool BinaryTree<T>::insert(T value){
    if (root == NULL){
        root = new TreeNode<T>(value);
        return true;
    }
    TreeNode<T>* parent = NULL;
    TreeNode<T>* cur = root;
    while(cur){
        if (cur->key == value)return false;

        parent = cur;
        if (cur->key > value){
            cur = cur->left;
        }
        else{
            cur = cur->right;
        }
    }

    TreeNode<T>* tmp = new TreeNode<T>(value);

    if (parent->key < value)parent->right = tmp;
    else parent->left = tmp;
    return true;
}

template<class T>
bool BinaryTree<T>::deleteValue(T value){
    if (root == NULL)return false;

    TreeNode<T> *parent = NULL,*cur = root,*del = cur;
    while (cur != NULL && cur->key != value){
        if (cur->key > value){
            parent = cur;
            cur = cur->left;
        }
        else{
            parent = cur;
            cur = cur->right;
        }
    }
    if (cur == NULL)return false;
    if (cur->left == NULL){  //只有右孩子
        if (cur == root)root = cur->right;
        else if (cur == parent->left)parent->left = cur->right;
        else parent->right = cur->right;
        del = cur;
    }
    else if (cur->right == NULL){
        if (cur == root)root = cur->left;
        else if (cur == parent->left)parent->left = cur->left;
        else parent->right = cur->left;
        del = cur;
    }
    else{  //左右子树都不为空
        TreeNode<T>* left = cur->right;
        parent = cur;
        while (left->left){
            parent = left;
            left = left->left;
        }
        del = left;
        cur->key = left->key;
        if (parent->left == left){
            parent->left = left->right;
        }
        else{
            parent->right = left->right;
        }
    }
    delete del;
    return true;
}

template<class T>
void BinaryTree<T>::inorderTree(TreeNode<T>* value){
    if (value != NULL){
        inorderTree(value->left);
        printf("%d\n",value->key);
        inorderTree(value->right);
    }
}