//
// Created by Vinicius Araújo on 5/9/20.
//

#ifndef LABTREE_REDBLACKTREE_H
#define LABTREE_REDBLACKTREE_H

#define BIG_NUMBER 1000000
#define EPSOLON 0.0001
#include <vector>
#include <iostream>


enum Color {BLACK, RED};

// Node is the nodes of our Red Black Tree
struct Node {
    float key;
    long idx;
    Node *p, *left, *right;
    Color color;
};


class RedBlackTree {

public:

    // how many keys the tree stores
    int size;

    Node *root;

    RedBlackTree();

    //insert new node
    void insert(float new_key, long new_idx);

    void find(std::vector<long> &res, float first, float last);

private:

    // a sentinel node
    Node *_nil;

    // RB-Tree operation to use when keeping RB properties
    void left_rotate(Node *x);

    Node* search_first(float first);

    Node* search_last(float last);

    // gets to the vector res only the values in the tree between first and last
    void smart_in_order(Node* x, std::vector<long> &res, float first, float last, Node *first_pointer, Node *last_pointer);

    // same as left_rotate
    void right_rotate(Node *y, int i, int z);

    // Fix RB-Tree after an insertion
    void insert_fixup(Node *z, int i);

};


#endif //LABTREE_REDBLACKTREE_H
