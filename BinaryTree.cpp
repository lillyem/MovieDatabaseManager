#include <iostream>
#include <cstdlib>
#include "BinaryTree.h"
#include "Queue.h"
#define MAX_ITEMS 23
#include "Data.h"

using namespace std;



BTNode * createBTNode (Movie data) {
	
	//creating a BT node for the Movie struct
	BTNode * newNode; 
   
	newNode = new BTNode;
   
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
   
	return newNode;
}



void preOrder (BTNode * root) {
	
	if (root == NULL)
		return;
		
	cout << root->data.ID << " ";

	preOrder (root->left);
	preOrder (root->right);
}



void inOrder (BTNode * root) {
	
	if (root == NULL)
		return;

	inOrder (root->left);
	
	cout << root->data.ID << " ";
	
	inOrder (root->right);
}



void postOrder (BTNode * root) {
	
	if (root == NULL)
		return;

	postOrder (root->left);
	postOrder (root->right);
	
	cout << root->data.ID << " ";
}



int moment (BTNode * root) {

	if (root == NULL)
		return 0;
		
	return (1 + moment (root->left) + moment (root->right));
}



int numOneChild (BTNode * root) {

	if (root == NULL)
		return 0;
		
	if (root->left == NULL && root->right == NULL)
		return 0;

	if (root->left == NULL)
		return 1 + numOneChild (root->right);
	else
	if (root->right == NULL)
		return 1 + numOneChild (root->left);
	else
		return (numOneChild (root->left) + numOneChild (root->right));
}



int numTerminal (BTNode * root) {

	if (root == NULL)
		return 0;
		
	if (root->left == NULL && root->right == NULL)
		return 1;
		
	return (numTerminal (root->left) + numTerminal (root->right));
}



int nodeDepth (BTNode * node) {
	int branch;
	
	branch = 0;
	
	if (node == NULL)
		return -1;
		
	while (node->parent != NULL) {
		node = node->parent;
		branch++;
	}
	
	return branch;
}



int height (BTNode * root) {
	
	//finds the height of the tree from the root, go down
	if(root==NULL){
		return 0;
	}
	
	int heightLeft=height(root->left);
	int heightRight=height(root->right);
	
	return max(heightLeft, heightRight)+1;

}



void levelOrder (BTNode * root) {  

	if (root==NULL){
		return;
	}
	Queue * q = initQueue(MAX_ELEMENTS); //initialize queue
	int levelNum=0;
	int numNodes;
	
	enqueue(q,root); //enqueue root 
	
	while(!isEmptyQueue(q)){
		//set the number of nodes in the level to the size of the queue from the iteration before when we used enqueue
		numNodes=sizeQueue(q); 
		cout << numNodes << " nodes at Level " << levelNum << ": ";
		for(int i=1; i<=numNodes; i++){
			BTNode * p = dequeue (q);	//dequeuing to display the nodes on a particular level
			cout << p->data.ID << " ";
			if(p->left!=NULL){
				enqueue(q,p->left);
			}
			if(p->right!=NULL){
				enqueue(q,p->right);
			}
		}
		cout << endl;
		levelNum++; //iterate the number of levels
	}
}



void clearBT (BTNode * root) {
	
	//recursively deletes a binary tree
	
	if (root==NULL){
		return;
	}
	
	clearBT(root->left);
	clearBT(root->right);
	
	delete root;
	root=NULL;
}

