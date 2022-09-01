// Mai Huu Nghia
// 2052612
#include "main.h"

// Cache MAXSIZE = 25 neu vuot qua MAXSIZE phai tien hanh remove 
// 2 ham overwrite:
//     put() (chi goi thong qua read)
//     write() (co the ghi de va tao data moi)

// addr is even, oldest out
// addr is odd, youngest out
/*
        0
         \
          1
           \
            3
           / \
          2   11
             /  \
            9   16
           / \
          4  10
           \
            5
             \
              7
               \
                8 
*/

// khi insert tree lay arr dau tien lam goc roi chen no vao
// ben trai nho hon parent
// ben phai lon hon parent
// BST nay chua balanced
// neu base = nullptr nghia la can tao nhanh moi r ghep vao voi cay
// tiep tuc de quy cho tơi khi nao tim dc nhanh trong aka base = nullptr
// cuoi cung return base  

Tree* insertTree(Tree* &root, Elem* elem) 
{ 
    bool flag = true;
    if (root == nullptr){
        Tree* new_leaf = new Tree();
        new_leaf->addr = elem->addr; 
        new_leaf->elem = elem;
        new_leaf->left = new_leaf->right = nullptr; 
        flag = false;
        return new_leaf; 
    }

    Tree* base = root;
    Tree* pre_base = nullptr;

    while (base != nullptr){
        pre_base = base;
        if (elem->addr >= base->addr){
            base = base->right;
        }
        else base = base->left;
    }
    if (flag == true){
        Tree* new_leaf = new Tree();
        new_leaf->addr = elem->addr; 
        new_leaf->elem = elem;
        new_leaf->left = new_leaf->right = nullptr; 
        if (elem->addr < pre_base->addr){
            pre_base->left = new_leaf;
        }
        else {
            pre_base->right = new_leaf;
        }
    }
    return root;
   
} 

Tree* deleteTree(Tree* head, int addr)
{
    
    Tree* lmeo;
    Tree* pre_base = nullptr;
    Tree* base = head;
    while (base != nullptr && base->addr != addr){
        if (addr < base->addr){
            pre_base = base;
            base = base->left;
        }
        else if (addr >= base->addr){
            pre_base = base;
            base = base->right;
        }
    }    
    if (base == nullptr){
        // delete base;
        return head;
    }
    // if (base->right != nullptr && base->left == nullptr) lmeo = base->right;
    // else if (base->right == nullptr && base->left != nullptr) lmeo = base->left;
    // else lmeo = nullptr;
    
    if (base->right != nullptr && base->left != nullptr){
        lmeo = nullptr;        
        Tree* dummyNode = base->right;

        while (dummyNode->left != nullptr){
            lmeo = dummyNode;
            dummyNode = dummyNode->left;
        }
        if (lmeo != nullptr) lmeo->left = dummyNode->right;
        else base->right = dummyNode->right;

        base->addr = dummyNode->addr;
        base->elem = dummyNode->elem;
        delete dummyNode;
    }
    else{
        if (base->left == nullptr) lmeo = base->right;
        else lmeo = base->left;

        if (pre_base == nullptr) return lmeo;

        if (base == pre_base->right) pre_base->right = lmeo;
        else pre_base->left = lmeo;

        // delete base;
    }
    // delete base;
    return head;
}

Data* Cache::read(int addr) {
    for (int i = 0; i < p; i++){
        if (arr[i] -> addr == addr){
            return arr[i] -> data;
        }
    }
    return NULL;
}

//sync auto true
Elem* Cache::put(int addr, Data* cont) {
    if (p == MAXSIZE && addr % 2 == 0){ // addr is even 
        // the oldest get out

        //xoa BST node
        this->base = deleteTree(base, arr[0]->addr);

        for (int i = 0; i < p - 1; i++){
            arr[i] = arr[i + 1];
        }
        arr[p-1] = new Elem(addr,cont,true); //new elem
                
        //them BST                
        this->base = insertTree(base, arr[p-1]);

        return arr[0];
    }
    else if (p == MAXSIZE && addr % 2 == 1){
        // the youngest get out
                
        //xoa BST
        this->base = deleteTree(base, arr[MAXSIZE-1]->addr);
                
        arr[MAXSIZE-1] = new Elem(addr,cont,true); //new elem
                
        //them BST
        this->base = insertTree(base, arr[MAXSIZE-1]);

        return arr[MAXSIZE-1];
    }
    else{
        arr[p] = new Elem(addr,cont,true);
        p++;
        //them BST
        this->base = insertTree(base, arr[p-1]);

        return NULL;
    }
}

//sync auto false
Elem* Cache::write(int addr, Data* cont) {
    int hehe = 0;
    for (int i = 0; i < p; i++){
        if (arr[i] -> addr == addr){
            arr[i] -> data = cont;
            arr[i] -> sync = false;
            hehe = 1;
            break;
        }
    }
    if (hehe == 0){
        if (p == MAXSIZE && addr % 2 == 0){ // addr is even 
            // the oldest get out

            //xoa BST node
            this->base = deleteTree(base, arr[0]->addr);

            for (int i = 0; i < p - 1; i++){
                arr[i] = arr[i + 1];
            }
            arr[p-1] = new Elem(addr,cont,false); //new elem
                
            //them BST                
            this->base = insertTree(base, arr[p-1]);

            return arr[0];
        }
        else if (p == MAXSIZE && addr % 2 == 1){
            // the youngest get out
                
            //xoa BST
            this->base = deleteTree(base, arr[MAXSIZE-1]->addr);
                
            arr[MAXSIZE-1] = new Elem(addr,cont,false); //new elem
                
            //them BST
            this->base = insertTree(base, arr[MAXSIZE-1]);

            return arr[MAXSIZE-1];
        }
        else{
            arr[p] = new Elem(addr,cont,false);
            p++;
            //them BST
            this->base = insertTree(base, arr[p-1]);

            return NULL;
        }
    }
    return NULL;
}

void Cache::print() {
	for (int i = p - 1; i >= 0; i--){
        arr[i]->print();
    }
}
void Cache::preOrder() {
	preOrderBST(base);
    
}
void Cache::inOrder() {
    if (this->base == nullptr) return;

    Tree* base1 = this->base;
    Tree* pre_base;

    while (base1 != nullptr)
    {
        if (base1->left == nullptr)
        {
            base1->elem->print();
            base1 = base1->right;
        }
        else{
            pre_base = base1->left;
            while (pre_base->right != nullptr && pre_base->right != base1){
                pre_base = pre_base->right;
            }
 
            if (pre_base->right == nullptr) {
                pre_base->right = base1;
                base1 = base1->left;
            }
            else {
                pre_base->right = nullptr;
                base1->elem->print();
                base1 = base1->right;
            } 
        }
    } 
}