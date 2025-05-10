#include <iostream>
#include <cstdlib>
#include <fstream>

#include "NodeTypes.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Data.h"

using namespace std;


BTNode * initBSTFromFile (char fileName[]) {
	
	BTNode * root = NULL;
	
	ifstream inputFile;
	Movie movie;
	int numMovies;
	
	inputFile.open(fileName);
	
	if (!inputFile.is_open()) {
		cout << "Input file " << fileName << " could not be opened. Aborting ..." << endl;
		return root;
	}

	numMovies = 0;
	inputFile >> movie.ID;
	
	cout << "Root of BST created with " << movie.ID << endl;
	
	while (movie.ID != "END") {
		inputFile >> movie.yearReleased >> movie.duration >> movie.genre >> ws;
		getline (inputFile, movie.title);
		numMovies++;

		root = insertBST (root, movie);
		inputFile >> movie.ID;
	}

	inputFile.close();
	
	cout << "-->" << numMovies << " movies read from " << fileName << " and stored in BST." << endl << endl;
	
	return root;
}



BTNode* insertBST(BTNode* root, Movie data) {
    BTNode* newNode;

    
    if (root == NULL) { 
		// tree is empty
        newNode = createBTNode(data);
        return newNode;
    }

    if (data.ID < root->data.ID) {
		//go to left subtree
        BTNode* inserted = insertBST(root->left, data);
        root->left = inserted;
        inserted->parent = root;
    }
    
    else { 
		// go to right subtree
        BTNode* inserted = insertBST(root->right, data);
        root->right = inserted;
        inserted->parent = root;
    }
    return root;
}




BTNode * containsBST (BTNode * root, string key) {
	if(root==NULL){
			return NULL;
		}
		if(root->data.ID==key){
			return root;
		}
		if(key<root->data.ID){ 
			//search left subtree
			return (containsBST(root->left, key));
		}
		else{
			//search right subtree
			return (containsBST(root->right, key));
		}

}



BTNode * minimumBST (BTNode * root) {
	if(root==NULL){
		return NULL;
	}
	
	//find leftmost, leftmost=smallest 
	if(root->left==NULL){
		return root;
	}
	return minimumBST(root->left);
	
}



BTNode * maximumBST (BTNode * root) {
	if(root==NULL){
		return NULL;
	}
	//find rightmost, rightmost=largest 
	if(root->right==NULL){
		return root;
	}
	return maximumBST(root->right);
}



BTNode * inOrderSuccessor (BTNode * node) {

	if(node==NULL){
		return NULL;
	}
	if(node->right!=NULL){
		return minimumBST(node->right);
	}
	
	BTNode * parent;
	parent=node->parent;
	
	while(parent!=NULL && node==parent->right){
		node=parent;
		parent=parent->parent;
	}
	return parent;	
}



void rangeBST (BTNode * root, string lowerID, string upperID) {
		
	if (root==NULL){
		return;
	}
	//if the root data is larger than the lowerID, search the left subtree (smaller keys here)
	if(root->data.ID > lowerID){
		rangeBST(root->left, lowerID, upperID);
	}
	
	//if the root data is within the given range, output 
	if (root->data.ID>=lowerID && root->data.ID<=upperID){
		cout << root->data.ID << " ";
	}
	
	//if the root data is smaller than the upperID, search the right subtree(larger keys here)
	if(root->data.ID < upperID){
		rangeBST(root->right, lowerID, upperID);
	}
	
}
	


void statisticsBST (BTNode * root) {
	
	int heightTree = height(root);
	int numTerminalOneChild = numOneChild(root);
	BTNode * minimumKey = minimumBST(root);
	BTNode * maximumKey = maximumBST(root);
	
	//displaying the required values after calling the respective functions
	
	cout << "Statistics on BST: " << endl;
	cout << "Height of binary tree " << heightTree << endl;
	cout << "Number of non-terminal nodes one child: " << numTerminalOneChild << endl;
	cout << "Smallest key: " << minimumKey->data.ID << endl;
	cout << "Biggest key: " << maximumKey->data.ID << endl;
	cout << endl;
		
}


void inOrderTraversal(BTNode* root, Queue* q) {
    
	//this function traverses the BST inOrder and enqueues the keys in the queue
	
	if (!root) {
        return;
    }
    
    inOrderTraversal(root->left, q);
    
    enqueue(q, root);
    
    inOrderTraversal(root->right, q);
}


bool isIsomorphic(BTNode* root1, BTNode* root2) {
	
	//storing both bsts in separate queues (using the inorder logic) with the helper
	//function above then dequeueing and comparing values
	
    Queue* q1 = initQueue(100); 
    Queue* q2 = initQueue(100); 

    inOrderTraversal(root1, q1);
    inOrderTraversal(root2, q2);

    while (!isEmptyQueue(q1) && !isEmptyQueue(q2)) {
        BTNode* node1 = dequeue(q1);
        BTNode* node2 = dequeue(q2);

        if (node1->data.ID != node2->data.ID) {
            return false;
        }
    }
    return isEmptyQueue(q1) && isEmptyQueue(q2);
}
BTNode * deleteBST(BTNode * root, string key) {
    
    BTNode* toDelete = containsBST(root, key); 
    
    if (toDelete == NULL) {
        return root; 
    }
	
	if (root==NULL){
		return root; //if the BST contains the key, assign the node to a BTNode
	}
	
	if (key <root->data.ID){  //searching left subtree if the key is smaller than the root data
		root->left=deleteBST(root->left, key);
	}
	
	else if(key > root->data.ID){ //searching right subtree if the key is larger than the root data
		root->right=deleteBST(root->right, key);
	}
	
	// Current root is the node to be deleted
	else{
		if(root->left == NULL && root->right==NULL){ // leaf
			delete root;
			return NULL;
		}
		else if(root->left==NULL){	// one right child
			BTNode * node = root->right;
			delete root;
			return node;
		}
		else if(root->right==NULL){ // one left child 
			BTNode * node = root->left;
			delete root;
			return node;
		}
		
		//two children
		else{
			// find the in-order successor 
			BTNode * successor = inOrderSuccessor(root); 
			// replace the current root's data with the inOrder successor's data
			root->data = successor ->data;
			// delete the in-order successor from the right subtree
			root->right = deleteBST(root->right, successor->data.ID);
		}
	}
    return root;
}


