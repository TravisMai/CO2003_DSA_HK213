#ifndef CACHE_H
#define CACHE_H
// Author: Mai Huu Nghia
// I had tried very hard on this assignment. Please give me the best score u have
#include "main.h"

int *FRU_arr;
Elem** hasArr;
Elem** TimeArr;
Elem** arrayMAXSIZEbaton;
int parent(int i){ return (i-1)/2;}
int left(int i) { return (2*i + 1); }
int right(int i) { return (2*i + 2); }
int searchTime (int value){
	int i;
	for (i = 0; i < MAXSIZE; i++)
	{
		if (TimeArr[i]->addr==value){
			break;
		}
	}
	return i;
}
void insert_hasArr(Elem* &value){
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (hasArr[i] == nullptr){
			hasArr[i] = value;
			break;
		}
	}
}
void remove_hasArr(Elem* &value){
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (hasArr[i]==value){
			hasArr[i] = nullptr;
			break;
		}
	}
}
void insert_TimeArr(Elem* &value){
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (TimeArr[i] == nullptr){
			TimeArr[i] = value;
			break;
		}
	}
}
void remove_TimeArr(Elem* &value){
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (TimeArr[i]==value){
			for (int j = i; j < MAXSIZE-1; j++)
			{
				TimeArr[j] = TimeArr[j+1];
			}
			TimeArr[MAXSIZE - 1] = nullptr;
			break;
		}
	}
}
Elem* remove_LFRU(){
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			if (FRU_arr[j] == TimeArr[i]->addr)
			{
				return TimeArr[i];
			}			
		}		
	}
	return NULL;	
}
Elem* remove_MFRU(){
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			if (FRU_arr[j] == TimeArr[i]->addr)
			{
				return TimeArr[i];
			}			
		}		
	}
	return NULL;	
}
class Node
{
public:
	Elem *elem;
	Node* next{nullptr};
public:
	Node(Elem* e) : elem(e){};
	void print(){
		elem->print();
	}
};
class ReplacementPolicy
{
public:
	ReplacementPolicy(){};
	virtual ~ReplacementPolicy(){};
	int	size{0};
	Node* front{nullptr};
	Node* end{nullptr};
public:
	virtual void insert(Elem *e) = 0;
	virtual void access(Elem *e) = 0;
	virtual Elem* remove() = 0;
	virtual void print() = 0;
	bool isFull() { return size == MAXSIZE; }

};
struct arr{
	Elem* elem{nullptr};
	int count{0};
};
class LFU : public ReplacementPolicy{
	public:
	arr* myArr;
	public:
	LFU() {
		myArr = new arr[MAXSIZE];
		size=0;
	}
	~LFU() {delete[] myArr;}
	void insert(Elem* e) {
		size++;
		int i = size - 1;
		myArr[i].elem = e;
		myArr[i].count = 1;
		heapUp(i);
		heapDown(i);
	}
	void access(Elem *e){
		int i;
		for (i=0;i<size;i++){
			if (myArr[i].elem==e) break;
	 	}
		swap(&myArr[i], &myArr[size - 1]);
		size--;
		heapDown(i); // maybe i -1
		size++;
		myArr[size - 1].count++;
		int temp = size - 1;
		heapUp(temp);
	}
	virtual Elem* remove() { 
		Elem* root = myArr[0].elem;
		myArr[0] = myArr[size-1];
		size--;
		heapDown(0);
		// myArr[0].elem->addr
		return root;
	}
	virtual void print() {
		for(int i =0; i<size; i++){
			// cout<< "Access: " << myArr[i].count << " ";
			myArr[i].elem->print();
		}
	}
	void swap(arr* a, arr* b){
		int temp1 = a->count; 
		Elem* temp2= a->elem;
		a->count=b->count;
		a->elem=b->elem;
		b->count=temp1;
		b->elem=temp2;
	}
	void heapUp(int i)
	{
		while (i != 0 && myArr[parent(i)].count > myArr[i].count)
		{
			swap(&myArr[i], &myArr[parent(i)]);
			i = parent(i);
		}
	}
	void heapDown(int i)
	{
		int l = left(i);
		int r = right(i);
		int smallest = i;
		if (l < size && r < size && myArr[l].count == myArr[r].count && myArr[r].count <= myArr[smallest].count)
		{
			smallest = l;
		}
		else {			
			if (r < size && myArr[r].count <= myArr[i].count)
				smallest = r;
			if (l < size && myArr[l].count <= myArr[smallest].count)
				smallest = l;
		}
		if (smallest != i)
		{
			swap(&myArr[i], &myArr[smallest]);
			heapDown(smallest);
		}
	}
};
class MFU : public ReplacementPolicy{
	public:
	arr* myArr;
	public:
	MFU() {
		myArr = new arr[MAXSIZE];
		size=0;
	}
	~MFU() {delete[] myArr;}
	void insert(Elem* e) {
		size++;
		int i = size - 1;
		myArr[i].elem = e;
		myArr[i].count = 1;
		heapUp(i);
		heapDown(i);
	}
	void access(Elem *e){
		int i;
		for (i=0;i<size;i++){
			if (myArr[i].elem==e) break;
	 	}
		swap(&myArr[i], &myArr[size - 1]);
		size--;
		heapDown(i); // maybe i -1
		size++;
		myArr[size - 1].count++;
		int temp = size - 1;
		heapUp(temp);
	}
	virtual Elem* remove() { 
		Elem* root = myArr[0].elem;
		myArr[0] = myArr[size-1];
		size--;
		heapDown(0);
		return root;
	}
	virtual void print()
	{
		for(int i =size-1; i>=0; i--){
			// cout<< "Access: " << myArr[i].count << " ";
			myArr[i].elem->print();
		}
	}
	void swap(arr* a, arr* b){
		int temp1 = a->count; 
		Elem* temp2= a->elem;
		a->count=b->count;
		a->elem=b->elem;
		b->count=temp1;
		b->elem=temp2;
	}
	void heapUp(int i)
	{
		while (i != 0 && myArr[parent(i)].count < myArr[i].count)
		{
			swap(&myArr[i], &myArr[parent(i)]);
			i = parent(i);
		}
	}
	void heapDown(int i)
	{
		int l = left(i);
		int r = right(i);
		int largest = i;
		if (l < size && r < size && myArr[l].count == myArr[r].count && myArr[r].count >= myArr[largest].count)
		{
			largest = r;
		}
		else {			
			if (r < size && myArr[r].count >= myArr[i].count)
				largest = r;
			if (l < size && myArr[l].count >= myArr[largest].count)
				largest = l;
		}
		if (largest != i)
		{
			swap(&myArr[i], &myArr[largest]);
			heapDown(largest);
		}
	}
};
class LFRU: public LFU {
    Elem* remove() override 
	{ 
		int same_count = 0;
		FRU_arr = new int [MAXSIZE];
		FRU_arr[0] = myArr[0].elem->addr;	
		for (int i = 1; i < size; i++)
		{
			FRU_arr[i] = -1;
			if (myArr[i].count == myArr[0].count)
			{
				same_count++;
				FRU_arr[i] = myArr[i].elem->addr;
			}			
		}
		if (same_count != 0)
		{
			Elem* root = remove_LFRU();
			int i;
			for (i = 0; i < size; i++)
			{
				if (myArr[i].elem->addr == root->addr) break;
			}
			myArr[i] = myArr[size - 1];
			size--;
			heapDown(i);
			delete [] FRU_arr;
			return root;			
		}
		else
		{			
			Elem* root = myArr[0].elem;
			myArr[0] = myArr[size-1];
			size--;
			heapDown(0);
			delete [] FRU_arr;
			return root;
		}		
	}
	void sort_Time(int start, int end){
		for (int step = start; step <= end - 1; step++) {
			int min_idx = step;
			for (int i = step + 1; i <= end; i++) {
				if (searchTime(myArr[i].elem->addr) < searchTime(myArr[min_idx].elem->addr)) 
					min_idx = i;
			}
			swap(&myArr[min_idx], &myArr[step]);
		}
	}
	void Sort_Count() {
		for (int step = 0; step < size - 1; step++) {
			int min_idx = step;
			for (int i = step + 1; i < size; i++) {
				if (myArr[i].count < myArr[min_idx].count)
					min_idx = i;
			}
			swap(&myArr[min_idx], &myArr[step]);
		}
	}
	void print() override 
	{
		// int i = 0;
		// FRU_print = new Elem*[size];
		Sort_Count();
		for (int i = 0; i < size;)
		{
			int start = i;
			// int end;
			// FRU_print[start] = myArr[start].elem;
			for (int j = start+1; j < size-1; j++)
			{
				// if (myArr[j].count == myArr[start].count)
				// {
				// 	FRU_print[j] = myArr[j].elem;
				// }
				if (j == size-2){
					if (myArr[j+1].count != myArr[j].count)
					{
						sort_Time(i, j);
						i = size;
					}
					else
					{
						sort_Time(i, size-1);
						i = size;
					}					
				}
				else{
					if (myArr[j+1].count != myArr[j].count)
					{
						// end = j;
						sort_Time(i, j);
						i = j + 1;
					}
				}
				// if (i == size-1) 
				// {
				// 	FRU_print[i] = myArr[i].elem;
				// 	break;
				// }
				// if (i == size-2) 
				// {
				// 	FRU_print[i] = myArr[i].elem;
				// 	FRU_print[size-1] = myArr[size-1].elem;
				// 	break;
				// }
			}
			

			
		}
		// cout << i << endl<<endl;
		
		for(int k =0; k<size; k++){
			// cout<< "Access: " << myArr[i].count << " ";
			myArr[k].elem->print();
			// TimeArr[k]->print();
		}
	}
};
class MFRU: public MFU {
    Elem* remove() override 
	{ 
		int same_count = 0;
		FRU_arr = new int [MAXSIZE];
		FRU_arr[0] = myArr[0].elem->addr;	
		for (int i = 1; i < size; i++)
		{
			FRU_arr[i] = -1;
			if (myArr[i].count == myArr[0].count)
			{
				same_count++;
				FRU_arr[i] = myArr[i].elem->addr;
			}			
		}
		if (same_count != 0)
		{
			Elem* root = remove_MFRU();
			int i;
			for (i = 0; i < size; i++)
			{
				if (myArr[i].elem->addr == root->addr) break;
			}
			myArr[i] = myArr[size - 1];
			size--;
			heapUp(i);
			heapDown(i);
			delete [] FRU_arr;
			return root;			
		}
		else
		{			
			Elem* root = myArr[0].elem;
			myArr[0] = myArr[size-1];
			size--;
			heapUp(0);
			heapDown(0);
			delete [] FRU_arr;
			return root;
		}		
	}
	void sort_Time(int start, int end){
		for (int step = start; step <= end - 1; step++) {
			int min_idx = step;
			for (int i = step + 1; i <= end; i++) {
				if (searchTime(myArr[i].elem->addr) > searchTime(myArr[min_idx].elem->addr)) 
					min_idx = i;
			}
			swap(&myArr[min_idx], &myArr[step]);
		}
	}
	void Sort_Count() {
		for (int step = 0; step < size - 1; step++) {
			int min_idx = step;
			for (int i = step + 1; i < size; i++) {
				if (myArr[i].count > myArr[min_idx].count)
					min_idx = i;
			}
			swap(&myArr[min_idx], &myArr[step]);
		}
	}
	void print() override 
	{
		Sort_Count();
		for (int i = 0; i < size;)
		{
			int start = i;
			for (int j = start+1; j < size-1; j++)
			{
				if (j == size-2){
					if (myArr[j+1].count != myArr[j].count)
					{
						sort_Time(i, j);
						i = size;
					}
					else
					{
						sort_Time(i, size-1);
						i = size;
					}					
				}
				else{
					if (myArr[j+1].count != myArr[j].count)
					{
						// end = j;
						sort_Time(i, j);
						i = j + 1;
					}
				}
			}
		}
		for(int k =0; k<size; k++){
			myArr[k].elem->print();
		}
	}
};
class Hashing
{
public:
	Hashing() {}
	~Hashing() {}
	void create_hash(){
		for (int i = 0; i < MAXSIZE; i++)
		{
			if (hasArr[i]!=nullptr){
				for (int j = 0; j < MAXSIZE; j++)
				{
					int index = (hasArr[i]->addr + j) % MAXSIZE;
					if (arrayMAXSIZEbaton[index] == nullptr){
						arrayMAXSIZEbaton[index] = hasArr[i];
						break;
					}
				}	
			}
		}
	}
	void print() {
		cout << "Prime memory"<<endl;
		for (int i = 0; i < MAXSIZE; i++)
		{
			if (hasArr[i]!=nullptr){
				hasArr[i]->print();
			}
		}
		cout<<"Hash table memory"<<endl;
		for(int i=0;i<MAXSIZE;i++){
			if(arrayMAXSIZEbaton[i]!=nullptr){
				arrayMAXSIZEbaton[i]->print();
			}
		}
	}
};
class SearchEngine
{
public:
	SearchEngine(){}
	virtual ~SearchEngine(){};
	Hashing* hash = new Hashing();
	virtual bool insert(Elem* &value) = 0;
	virtual void remove(int addr) = 0;
	virtual void print() = 0;
	virtual Elem* search(int addr) = 0;
};
class Tree{
	public:
		class Node;
		Node* root{nullptr};
	public:
		class Node{
			protected:
				Node* left{nullptr}; 
				Node* right{nullptr};
				Elem* data;
				friend class Tree;
			public:
				Node(Elem* value) {data= value;}
				int getAdd(){return data->addr;}
		};
	public:
		Tree(){};
		~Tree(){}
		void insert(Node* &root, Elem* &value){
			if (root== nullptr){root= new Node(value);}
			else{
				if (value->addr < root->getAdd()) {this->insert(root->left, value);}
				else {this->insert(root->right, value);}
			}
		}
		void remove(Node*& root, int value) {
			if (root == nullptr) return;
			if (value < root->getAdd()) {remove(root->left, value);}
			else if (value > root->getAdd()) {remove(root->right, value);}
			else {
				if (root->left == nullptr) {
					Node* tmp = root;
					root = root->right;
					delete tmp;
					tmp = nullptr;
				} 
				else if (root->right == nullptr) {
					Node* tmp = root;
					root = root->left;
					delete tmp;
					tmp = nullptr;
				}
				else {
					Node* tmp = root->right;
					while (tmp->left != nullptr) {tmp = tmp->left;}
					root->data = tmp->data;
					remove(root->right, tmp->getAdd());
				}
			}
		}
		void insert(Elem* &value){insert(this->root, value);}
		void inorder(Node* root){
			if (root == nullptr) 
				return;
			Node* base1 = root;
			Node* pre_base =  nullptr;
			while (base1 != nullptr)
			{
				if (base1->left == nullptr)
				{
					base1->data->print();
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
						base1->data->print();
						base1 = base1->right;
					} 
				}
			}
		}
		void preorder(Node*root){
			if(root != nullptr){
                root->data->print();
                preorder(root->left);
                preorder(root->right);
            }
            else{return;}
		}
		void remove(int addr){remove(this->root, addr);}
		Elem* searchTree(Node* root, int addr){
			if (root==nullptr) return NULL;
			if (root->getAdd()==addr) return root->data;
			else if (root->getAdd()<addr)
				return searchTree(root->right, addr);
			else if (root->getAdd()>addr)
				return searchTree(root->left, addr);
			return NULL;
		}
};
class BST : public SearchEngine
{
public:
	Tree *newTree{nullptr};
public:
	BST() {newTree = new Tree();}
	~BST() {delete newTree;}
	bool insert(Elem* &value) {
		newTree->insert(value);
		return true;
	}
	void remove(int addr) {newTree->remove(addr);}
	void print() {
		cout << "Print BST in inorder:" <<endl;
		newTree->inorder(newTree->root);
		cout << "Print BST in preorder:" <<endl;
		newTree->preorder(newTree->root);
	}
	Elem* search(int addr){return newTree->searchTree(newTree->root,addr);}
};
#endif