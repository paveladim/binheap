#ifndef ISET_H
#define ISET_H

#include <list>
#include "Node.h"

using namespace std;

Node* create_node(const int& key = 0);
void  delete_node(Node* node);
Node* link_trees(Node* r1, Node* r2);

Node* insert(Node* root_list, const int& key);
Node* heapify(Node* root_list);

int   get_min(Node* root_list);
int   delete_min(Node* root_list);

#endif
