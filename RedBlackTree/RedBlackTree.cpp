//
// Created by Vinícius Araújo on 5/9/20.
//

#include "RedBlackTree.h"

/// Constructor
RedBlackTree::RedBlackTree(){
    this->_nil = new Node;
    this->_nil->left, this->_nil->right, this->_nil->p = this->_nil;
    this->_nil->color = BLACK;
    this->root = this->_nil;
    this->size = 0;
}


void RedBlackTree::smart_in_order(Node *x, std::vector<long> &res, float first, float last, Node *first_pointer, Node *last_pointer){
    if(x!=this->_nil){
        /* if x.key > last then we must only visit the left node, in a normal in order we would visit right and
         * and left node independently of a range we need*/
        if(x->key > last){
            smart_in_order(x->left, res, first, last, first_pointer, last_pointer);
        }
        // same as before but checking if x.key < first
        else if(x->key < first){
            smart_in_order(x->right, res, first, last, first_pointer, last_pointer);
        }
        // if those conditions dont check, we, then, have a node in which the key is within the range we want
        else{
            // we check if x is the node that has the last or the first so we do not call unnecessary recursions
            if(x!=last_pointer){
                smart_in_order(x->right, res, first, last, first_pointer, last_pointer);
            }
            if(x!=first_pointer){
                smart_in_order(x->left, res, first, last, first_pointer, last_pointer);
            }
            res.push_back(x->idx);
        }
    }
}

void RedBlackTree::find(std::vector<long> &res, float first, float last){
    Node *first_pointer, *last_pointer;
    first_pointer = search_first(first);
    last_pointer = search_last(last);
    smart_in_order(this->root, res, first, last, first_pointer, last_pointer);
}

// first node that is greater than first runs in O(h), RB_Tree has h = log(n)
Node *RedBlackTree::search_first(float first){
    float distance;
    float min_distance;
    Node* first_pointer;
    Node *x;
    min_distance = BIG_NUMBER;
    x = this->root;
    while(x!=this->_nil){
        distance = x->key - first;
        if(distance > 0 && distance < min_distance){
            min_distance = distance;
            first_pointer = x;
        }
        if(first < x->key){
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return first_pointer;
}

// Searchs for first node that does not exceeds last
Node* RedBlackTree::search_last(float last){
    float distance;
    float min_distance;
    Node* last_pointer;
    Node *x;
    min_distance = -BIG_NUMBER;
    x = this->root;
    while(x!=this->_nil){
        distance = x->key - last;
        if(distance < 0 && distance > min_distance){
            min_distance = distance;
            last_pointer = x;
        }
        if(last < x->key){
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return last_pointer;
}

void RedBlackTree::left_rotate(struct Node *x){
    Node *y;
    y = x->right;
    x->right = y->left;
    if (y->left != this->_nil ){
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == this->_nil) {
        this->root = y;
    }
    else if(x == x->p->left){
        x->p->left = y;
    }
    else{
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

void RedBlackTree::right_rotate(struct Node *y, int i, int z){
    Node *x;
    x = y->left;
    y->left = x->right;
    if (x->right != this->_nil){
        x->right->p = y;
    }
    x->p = y->p;
    if (y->p == this->_nil) {
        this->root = x;
    }
    else if(y == y->p->left){
        y->p->left = x; 
    }
    else{
        y->p->right = x;
    }
    x->right = y;
    y->p = x;
}

// fixes tree after insertion
void RedBlackTree::insert_fixup(Node *z, int i){
    Node *y;
    int x = 0;
    while(z->p->color == RED)
    {
        if(z->p == z->p->p->left) {
            y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->right) {
                    z = z->p;
                    this->left_rotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                this->right_rotate(z->p->p, i, x);
            }

        }
        else{
            y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }

            else {
                if (z == z->p->left) {
                    z = z->p;
                    this->right_rotate(z, i, x);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                this->left_rotate(z->p->p);
            }
        }
        x++;
    }
    this->root->color = BLACK;
}

void RedBlackTree::insert(float new_key, long new_idx){
    Node *z = new Node;
    Node *y, *x;
    z->key = new_key;
    z->idx = new_idx;
    int i = new_idx;
    y = this->_nil;
    x = this->root;
    // check where to insert z
    while(x!=this->_nil){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->p = y;
    if(y == this->_nil){
        this->root = z;
    }
    else {
        if(z->key < y->key){
            y->left = z;
        }
        else{
            y->right = z;
        }
    }
    z->left = this->_nil;
    z->right = this->_nil;
    z->color = RED;
    // probably z's insertion broke RB properties
    this->insert_fixup(z, i);
    this->size++;
}