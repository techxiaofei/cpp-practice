#include <stdio.h>
#include <iostream>
#include "binary_tree.h"

using namespace std;

int main(){
    BinaryTree<int> tree;
    tree.insert(15);
    tree.insert(5);
    tree.insert(3);
    tree.insert(23);
    tree.insert(33);
    tree.insert(6);
    tree.insert(6);
    tree.insert(2);
    tree.insert(0);
    tree.insert(28);
    tree.insert(7);
    tree.insert(24);
    tree.insert(11);
    tree.insert(2);
    tree.insert(232);
    tree.insert(17);
    tree.insert(8);
    tree.insert(9);
    tree.inorderTree(tree.root);
    tree.deleteValue(33);
    tree.deleteValue(8);
    printf("\n");
    tree.inorderTree(tree.root);

}

//g++ -o test main.cpp