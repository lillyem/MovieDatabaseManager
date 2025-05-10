#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include "Data.h"
#include "HashTable.h"
using namespace std;


HashTable * initHashTable (int sizeTable) {
	
	//initializes the hashtable 
	
	HashTable * ht = new HashTable;
	
	for(int i=1; i<=sizeTable; i++){
		ht->elements[i]=NULL;
	}
	ht->sizeTable=sizeTable;
	
	return ht;
}



HashTable * initHashTableFromFile (int sizeTable, char fileName[]) {

	ifstream inputFile;
	ofstream outputFile;

	Movie movie;
	int numMovies;
	
	HashTable * ht = initHashTable(sizeTable);	
	
	inputFile.open(fileName);
	
	if (!inputFile.is_open()) {
		cout << "Input file " << fileName << " could not be opened. Aborting ..." << endl;
		return ht;
	}
	
	numMovies = 0;
	inputFile >> movie.ID;
	
	while (movie.ID != "END") {
		inputFile >> movie.yearReleased >> movie.duration >> movie.genre >> ws;
		getline (inputFile, movie.title);
		numMovies++;

		insertHT (ht, movie);
		inputFile >> movie.ID;
	}

	inputFile.close();
	
	cout << "--> " << numMovies << " movies read from " << fileName << " and stored in hash table." << endl << endl;
	
	return ht;
}


int toHash(string code, int sizeTable){
	
	//function used to hash each movieID, returning the location in the HT
	
	int value = 0;
	int i = 2;
	int location;
	
	while (code[i]!='\0'){
		value=value*10+(code[i]-'0');
		i++;
	}
	location=value%sizeTable+1;
	
	return location;
}

int containsHT (HashTable * ht, string key) {
	int loc;
	LLNode * curr;
	
	loc=toHash(key, ht->sizeTable); //calls the hashing function to find the potential location in the HT
	
	curr=ht->elements[loc]; //sets the top of the linked list using the location found 
	
	//search linked list until the data is found or until the list ends (not present)
	while(curr!=NULL){
		if(curr->data.ID==key){
			return loc;
		}
		curr=curr->next;
	}
	
	return -1;
}



void displayMovie (Movie movie) {
	
	cout << "ID:              " << movie.ID << endl;
	cout << "TITLE:           " << movie.title << endl;
	cout << "YEAR RELEASED:   " << movie.yearReleased << endl;
	cout << "DURATION:        " << movie.duration << endl;
	cout << "GENRE:           " << movie.genre << endl;
	cout << endl;	
}



void displayMovieHT (HashTable * ht, string key) {
	
	int location= containsHT(ht,key); //checking to see if the movie exists in the HT
	LLNode * curr = ht->elements[location];
	
	if(location!=-1){
		while(curr!=NULL){
			if(curr->data.ID==key){
				displayMovie(curr->data); //displaying if it exists
			}
			curr=curr->next;
		}
	}
}


	
int lengthChain (HashTable * ht, int location) {
	
	//if the top of the linked list is NULL, length is 0
	if(ht->elements[location]==NULL){
		return 0;
	}
	//linked list > 0, so set curr to the head of the list
	LLNode * curr = ht->elements[location];
	int num=0;
	
	//finding the size of the linked list
	while(curr!=NULL){
		num++;
		curr=curr->next;
	}
	return num;
}



LLNode * createNode (Movie movie) {
	LLNode * newNode;
	
	newNode = new LLNode;
	
	newNode->data = movie;
	newNode->next = NULL;
	
	return newNode;
}

void insertHT (HashTable * ht, Movie movie) {
	
	int loc;
	LLNode * newNode;
	string key=movie.ID;
	
	loc=toHash(key, ht->sizeTable); //find location it would hash to 
	
	if(containsHT(ht,movie.ID)==-1){ // if the the HT doesn't contain the movie, create a newNode and insert in linked list
		newNode = createNode(movie);
		newNode->next = ht->elements[loc];
		ht->elements[loc]= newNode;
	}
}



void statisticsHT (HashTable * ht) {
	
	int empty, notEmpty;
	empty=0;
	notEmpty=0;
	int maxChain=INT_MIN;
	
	for(int i=1; i<=ht->sizeTable; i++){
		if(ht->elements[i]==NULL){
			empty++; //counting the empty locations in HT (if the head is NULL)
		}
		else{
			notEmpty++; //counting filled location
			string key=ht->elements[i]->data.ID;
			
			//finding the length of the chain and then find the max chain in HT
			int length=lengthChain(ht,i);
		
			if(length>maxChain){
				maxChain=length;
			}
		}
		
	}
	
	//output the results after performing the necessary operations
	cout << "Statistics on hash table: " << endl;
	cout << "There are " << notEmpty << " filled locations." << endl;
	cout << "There are " << empty << " empty locations. " << endl;
	cout << "The length of the longest chain is: " << maxChain << endl;
	
}




void deleteHT (HashTable * ht, string key) {
	
	//finding which linked list the key exists in, if it exists
	int location= containsHT(ht,key);
	LLNode * curr = ht->elements[location];
	LLNode * pred = NULL;
	
	//movie doesn't exist in HT
	if(location==-1){
		cout << "This movie does not exist." << endl;
	}
	
	//deleting the movie
	else{
		while(curr!=NULL){
			if(curr->data.ID==key){
				if(pred==NULL){
					ht->elements[location]=ht->elements[location]->next;
				}
				else{
					pred->next=curr->next;
				}
				delete curr;
				return;
			}
			pred=curr;
			curr=curr->next;
		}
	}
	
	cout << "Movie has been deleted successfully." << endl;
}


