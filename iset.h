#ifndef ISET_H
#define ISET_H

#include <vector>
#include "Node.h"

using namespace std;

Node* create_node(const int& key = 0);
void  delete_node(Node* node);
Node* link_trees(Node* r1, Node* r2);

Node* insert(Node* root_list, const int& key);
Node* merge(Node* rl1, Node* rl2);

int   get_min(Node* root_list);
int   delete_min(Node** root_list);

void  clear_heap(Node* root_list);
void  recursive_clear(Node* node);

void  grow(Node* to_grow);
void  add_to_merged(vector<Node*>& merged, Node* node);

Node* create_heap(const vector<int> src);

#endif
