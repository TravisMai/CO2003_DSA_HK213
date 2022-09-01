#ifndef CACHE_H
#define CACHE_H
// Mai Huu Nghia
// 2052612
#include "main.h"

// khai 1 class có pointer:
//     1 trai (brand ben trai)
//     1 phai (brand ben phai)
// addr dia chi cua node tren tree
// Elem co 3 thanh phan
// addr: dia chi cua Cache
// data
// sync:
//     ham put() sync = true
//     ham write() sync = false
class Tree{
    public:
        int addr;
        Elem* elem;
        Tree *left = nullptr;
        Tree *right = nullptr;
        
};

// tao them 2 ham print in/pre order do khong cho phep chinh trong main.cpp & main.h
class Cache {
        Elem** arr;
        int p;
        Tree* base;
	public:
        friend class Tree;
        Cache(int s);
        ~Cache();
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();
        void preOrderBST(Tree* base){
            if(base != nullptr){
                base->elem->print();
                preOrderBST(base->left);
                preOrderBST(base->right);
            }
            else{
                // delete base;
                return;
            }
        }
};

Cache::Cache(int s){
    arr = new Elem*[s];
    p = 0;
    base = nullptr;
}

Cache::~Cache() {
    delete[] arr;
    // delete base;
}
#endif