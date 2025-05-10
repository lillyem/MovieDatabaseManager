#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "HashTable.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Data.h"
using namespace std;
#define MAX_ITEMS 23
#define QUIT 99


int main () {

	char fileName [25] = "Movies.txt";
	
	char commandsFile [25] = "Commands.txt";
	ifstream inputFile;

	
	int command;
	string movieString; 
	Movie movieRead;
	
	HashTable * ht;
	
	cout << "Creating hash table ... " << endl;
	ht = initHashTableFromFile(MAX_ITEMS, fileName);
	
	
	BTNode * moviesBST = initBSTFromFile(fileName);
	
	cout << "Processing commands from commands file ..." << endl << endl;
	
	ifstream inCommand;
	inCommand.open(commandsFile);
	
	if (!inCommand.is_open()) {
		cout << "Commands file " << commandsFile << " could not be opened. Aborting ..." << endl;
		exit(1);
	}

	inCommand >> command;
	
	while(command!=QUIT){
		
		cout << "COMMAND " << command << ":" << endl << endl;
		
		if(command==10){
			
			inCommand >> movieRead.ID >>movieRead.yearReleased >> movieRead.duration >> movieRead.genre;
			inCommand >> ws;
			getline (inCommand, movieRead.title);
			
			displayMovie(movieRead);
			
			BTNode * bstContains = containsBST(moviesBST,movieRead.ID );
			
			if(containsHT(ht,movieRead.ID)==-1 && bstContains==NULL){ //checking if the movie is the HT and BST, inserting if it isn't
				insertHT(ht, movieRead);
				insertBST(moviesBST, movieRead);
				cout << "--> Movie " << movieRead.ID << " inserted in hash table and BST." << endl; 
			}
			
			else{
				cout << "--> The movie is already in the hash table and BST" << endl;
			}
		
		
		
		} 
		
		if(command==11){
			
			inCommand >> movieString;
			
			int loc = containsHT(ht, movieString);
			
			// if the movie is in the HT, display and find the length of the linked list it is stored in
			
			if(loc!=-1){
				cout << "--> The movie " << movieString << " is in the hash table." << endl << endl;
				displayMovieHT(ht, movieString);
				int lengthChainHT= lengthChain(ht, loc);
				cout << "--> The length of the chain is " << lengthChainHT << endl << endl;
			}
			else{
				cout << "The movie " << movieString << " is NOT in the hashtable." << endl;
			}
			
			//checking if it is in the BST by assigning it to a node and checking if it is null
			
			BTNode * bstContains = containsBST(moviesBST, movieString);
			
			if(bstContains!=NULL){
				cout << "The movie " << movieString << " is in the BST." << endl << endl;
				displayMovie(bstContains->data);
			}
			else{
				cout << "The movie " << movieString << " is NOT in the BST." << endl;
			}
		}
	
		if (command==12){
			inCommand >> movieString;
			
			//if the HT contains the movie, delete it 
			
			if(containsHT(ht, movieString)!=-1){
				deleteHT(ht, movieString);
				cout << "Movie " << movieString << " deleted from hash table." << endl;
			}
			else{
				cout << "The movie " << movieString << " is NOT in the hashtable." << endl;
			}
			
			// same logic here, if the BST contains the movie, delete it
			
			BTNode * bstContains = containsBST(moviesBST, movieString);
			
			if(bstContains!=NULL){
				deleteBST(moviesBST, movieString);
				cout << "Movie " << movieString << " deleted from BST." << endl;	
			}
			
			
		}
		
		if(command==13){
			
			// call to functions to display HT and BST statistics
			
			statisticsHT(ht);
			cout << endl;
			statisticsBST(moviesBST);
			cout << endl;
		}
		
		if(command==20){
			
			// call to inOrder function
			
			cout << "Inorder traversal of BST: " << endl << endl;
			inOrder(moviesBST);
			cout << endl;
		}
		
		if(command==21){
			
			// call to level order function
			
			cout << "Level order traversal of BST: " << endl << endl;
			levelOrder(moviesBST);
			cout << endl;
		}
		
		if(command==22){
			string lowerID, upperID;
			
			inCommand >> lowerID >> upperID;
			
			cout << "Displaying all keys in the BST between " << lowerID << " and " << upperID << ": " << endl << endl;
			rangeBST(moviesBST, lowerID, upperID);
			cout << endl;
		}
		
		if(command==23){
			string filename;
			inCommand >> filename;
			
			//filename is a string, convert to c-string then use it in the initBSTFromFile function to create the BST
			
			char filenameChar[filename.length() + 1]; 

			strcpy(filenameChar, filename.c_str()); 
    	
			BTNode * bstFile = initBSTFromFile(filenameChar);
			
			// level order traversal
			
			levelOrder(bstFile);
			
			//checking if the bst from the file and the original BST we created are isomorphic
			
			bool isomorphic = isIsomorphic (bstFile, moviesBST);
			
			if (isomorphic==true){
				cout << "--> BSTs are isomorphic." << endl;
			}
			else{
				cout << "--> BSTs are NOT isomorphic." << endl;
			}
			
			//releasing memory from the BST created 
			
			clearBT(bstFile);
		}
		
		cout << endl << endl;
		inCommand >> command;
	}
	
	inCommand.close();
	return 0;
}
