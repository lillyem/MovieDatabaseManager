# MovieDatabaseManager

This C++ application manages a collection of movies using both a hash table and a binary search tree. It reads initial movie data from a file, processes commands from another file, and allows efficient insertion, lookup, deletion, and traversal of movies based on their IDs.

# Files
main.cpp – Main application logic (your provided code).

Movies.txt – Input file containing the list of movies.

Commands.txt – File containing a sequence of commands to execute.

HashTable.h – Hash table implementation for storing movies.

BinaryTree.h – Generic binary tree utilities.

BinarySearchTree.h – BST-specific operations like insert, delete, traversal, etc.

Data.h – Movie structure and any supporting data definitions.

# Supported Commands (Commands.txt)
Code	Description
10	Insert a movie into both hash table and BST

11	Search for a movie in hash table and BST, display data and chain length

12	Delete a movie from both hash table and BST

13	Display statistics of both hash table and BST

20	Inorder traversal of the BST

21	Level-order traversal of the BST

22	Display all movies with IDs in a given range (BST)

23	Compare current BST with one loaded from a file and check isomorphism

99	Quit the program

# How to Compile and Run
Ensure all .h files, main.cpp, and the text files are in the same folder.


# Note: This program uses Windows-specific headers like <windows.h> and <conio.h>. If you're on a different OS, you may need to remove or replace them.

# Features
Dual data structure support: Hash Table and Binary Search Tree.

Fast insert, search, and delete using Hash Table.

Ordered and range-based queries via BST.

Check if two BSTs are isomorphic (same shape regardless of data).

View BST traversals (inorder and level-order).

Detailed hash table and BST statistics (e.g., chain lengths, tree height).

# Notes
Movie IDs are assumed to be unique.

Insertions are ignored if the movie already exists in both structures.

On command 23, a new BST is built from another file and compared with the main BST for structural similarity.

# Author
This project demonstrates intermediate-to-advanced C++ concepts including:

File I/O

Hashing

Binary Search Trees

Data structure synchronization

Command-driven program execution
