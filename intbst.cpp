// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
	if(!n)
		return;
	printInOrder(n->left);
	cout << n->info << " ";
	printInOrder(n->right);
}


// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n) {
	printPostOrder(n->left);
	printPostOrder(n->right);
	cout << n->info << " ";
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
	if(!n)
		return 0;
	return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
	if(!n)
		return 0;
	return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
	if(!n)
		return nullptr;
	if(n->info < value)
		return getNodeFor(value, n->right);
	if(n->info > value)
		return getNodeFor(value, n->left);
	return n;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
	if(getNodeFor(value, root) != nullptr)
		return true;
	return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
	Node* p = getNodeFor(value, root);
	if(!p)
		return nullptr;
	if(p->left){
		p = p->left;
		while(p->right)
			p = p->right;
		return p;
	}
	while(p->parent){
		if(p->parent->right == p){
			p = p->parent;
			return p;
			}
		p = p->parent;
		}
	return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
	Node* p = getPredecessorNode(value);
	if(!p)
		return 0;
	return p->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
	Node* p = getNodeFor(value, root);
	if(!p)
		return nullptr;
	if(p->right){
		p = p->right;
		while(p->left)
			p = p->left;
		return p;
	}
	while(p->parent){
		if(p->parent->left == p){
			p = p->parent;
			return p;
			}
		p = p->parent;
		}
	return nullptr;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
	Node* p = getSuccessorNode(value);
	if(!p)
		return 0;
	return p->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
	Node* p = getNodeFor(value,root);
	if(!p)
		return false;
	if(count(root) == 1){
		delete p;
		root = nullptr;
		return true;
	}
	if(!p->left && !p->right){
		if(p->parent->right == p){
			p->parent->right = nullptr;
			delete p;
			return true;
		}
		if(p->parent->left == p){
			p->parent->left = nullptr;
			delete p;
			return true;
		}
	}
	if(!p->left != !p->right){
		if(p->left){
			if(p->parent->right == p){
				p->parent->right = p->left;
				delete p;
				return true;
			}
			if(p->parent->left == p){
				p->parent->left = p->left;
				delete p;
				return true;
			}
		}
		if(p->right){
			if(p->parent->right == p){
				p->parent->right = p->right;
				delete p;
				return true;
			}
			if(p->parent->left == p){
				p->parent->left = p->right;
				delete p;
				return true;
			}
		}
	}
        //one of the student student had a buggy code something like this
        int tmp = p->info;
        p->info = getPredecessor(value);
        getPredecessorNode(value)->info = tmp;
        remove(tmp);
        // so the student had the right idea that for the node with two children, you swap the predecessor and node’s value and delete the predecessor spot correctly with recursion. 
        // but the problem was the following: suppose you had to remove root node 64 with two children and it’s predecessor 32. So you basically swap 32 and 64 values and call remove(64);—predecessor spot.
        // when this happens, getNodeFor(64) is called in the next recursive function call. The way how this function getNodeFor works is that it assumes Bst property is always preserved such as smaller values are to the left and vice versa
        // however when we swapped 64 and 32 for some time for remove function, after the swap 64 is to the left of 32. So getNodeFor(64) is gonna return null even though it’s there.
        // So I proposed some solutions to the student(I don’t know if it worked, this is not the exact code, so I can’t try):
        // implement getNodeFor(value) in such a way that it checks every node using traversal  not depending upon Bst properties. Or
        // remove and fix the predecessor spot and then swap the value to the node to get removed as below. 

/*—-Correct Version
	int replacement = getPredecessor(value);
	remove(replacement);
	p->info = replacement;
*/
	return true;
}
