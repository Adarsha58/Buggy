#include "intbst.h"

#include <iostream>
using namespace std;

void TEST_SUM(const IntBST& bst1){
	cout << "TEST_SUM" << endl;
	if(bst1.sum() == 50)
		cout << "PASSED" << endl;
	else
		cout << "FAILED" << endl;
}
void TEST_COUNT(const IntBST& bst1){
	cout << "TEST_COUNT" << endl;
	if(bst1.count() == 5)
		cout << "PASSED" << endl;
	else
		cout << "FAILED" << endl;
}
void TEST_CONTAINS(const IntBST& bst1){
	cout << "TEST_CONTAINS" << endl;
	if(bst1.contains(12) && !bst1.contains(11))
		cout << "PASSED" << endl;
	else
		cout << "FAILED" << endl;
}

void TEST_PRED(const IntBST& bst1){
	cout << "TEST_PRED" << endl;
	if(bst1.getPredecessor(12) == 10)
		cout << "PASSED" << endl;
	else
		cout << "FAILED" << endl;
}
void TEST_SUCC(const IntBST& bst1){
	cout << "TEST_SUCC" << endl;
	if(bst1.getSuccessor(12) == 15)
		cout << "PASSED" << endl;
	else
		cout << "FAILED" << endl;
}
void TEST_REMOVE(IntBST& bst1){
	cout << "TEST_REMOVE" << endl;
	bst1.remove(12);
	if(!bst1.contains(12) && bst1.getPredecessor(15) == 10)
		cout << "PASSED" << endl;
	else
		cout << "FAILED" << endl;
}

int main() {

    IntBST bst1;

    bst1.insert(10);
    bst1.insert(15);
    bst1.insert(5);
    bst1.insert(12);
    bst1.insert(8);

    TEST_SUM(bst1);
    TEST_COUNT(bst1);
    TEST_CONTAINS(bst1);
    TEST_PRED(bst1);
    TEST_SUCC(bst1);
    TEST_REMOVE(bst1);
    }

