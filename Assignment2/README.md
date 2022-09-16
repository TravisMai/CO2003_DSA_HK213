# Assignment 2: Cache implement (Cont)
My assignment 2 in DSA semester 213  
More detail information about this assignment can be found in the pdf file.

## Student Outcomes
After completing this assignment, students will be able to
* get familiar with hash techniques
* select and manipulate data structures suitable to desired needs.

## Search Engine
The search engine is implemented as an abstract class SearchEngine declared
in file Cache.h but you are allowed to change everything in this class except its
name.
There is only one concrete subclass of this abstract class: BST. The BST class
which is from the previous assignment is used to search in BST.
BST class must have a print method which prints the elements in the buffer as
follows: prints the string "Print BST in inorder:/n" and then every elements in
the BST in in-order (LNR) and then prints the string "Print BST in preorder:/
n" and then every elements in the BST in pre-order (NLR)

## Cache replacement Policies
The replacement policy is implemented by an abstract class ReplacementPolicy
declared in file Cache.h. You are allowed to change everything in this class except
its name. There are 4 concrete subclasses to implement different replacement
policies:
* MFU (Most Frequently Used)
* LFU (Least Frequently Used)
* MFRU (Most Frequently Recently Used)
* LFRU (Most Frequently Recently Used)

## Run testcase

To run testcase
```C++
make all
```