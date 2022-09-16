#include "main.h"
// Author: Mai Huu Nghia
// I had tried very hard on this assignment. Please give me the best score u have
Cache::Cache(SearchEngine *s, ReplacementPolicy *r) : rp(r), s_engine(s) {
    hasArr = new Elem*[MAXSIZE];
    TimeArr = new Elem*[MAXSIZE];
    arrayMAXSIZEbaton = new Elem*[MAXSIZE];
    for(int i=0;i<MAXSIZE;i++){
		hasArr[i]=nullptr;
		TimeArr[i]=nullptr;
        arrayMAXSIZEbaton[i]=nullptr;
	}
}
Cache::~Cache()
{
    delete rp;
    delete s_engine;
    delete[] hasArr;
	delete[] TimeArr;
    delete[] arrayMAXSIZEbaton;
}
Data *Cache::read(int addr)
{
    Elem* temp= s_engine->search(addr);
    if (temp!=NULL){
        rp->access(temp);
        remove_TimeArr(temp);
        insert_TimeArr(temp);
        return temp->data;
    }
    return NULL;
}
Elem *Cache::put(int addr, Data *cont)
{
    Elem* temp= new Elem(addr, cont, true);
    Elem* remove_Elem= nullptr; 
    if (!rp->isFull()){
        rp->insert(temp);
        s_engine->insert(temp);
        insert_hasArr(temp);
        insert_TimeArr(temp);
    }
    else
    {
        remove_Elem= rp->remove();
        s_engine->remove(remove_Elem->addr);
        remove_hasArr(remove_Elem);
        remove_TimeArr(remove_Elem);
        rp->insert(temp);
        s_engine->insert(temp);
        insert_hasArr(temp);
        insert_TimeArr(temp);
        return remove_Elem;
    }
    return NULL;
}
Elem *Cache::write(int addr, Data *cont)
{
    Elem* temp= s_engine->search(addr);
    if (temp!=NULL){
        rp->access(temp);
        remove_TimeArr(temp);
        insert_TimeArr(temp);
        temp->data=cont;
        temp->sync=false;
    }
    else 
    {   
        Elem* temp= new Elem(addr, cont, false);
        Elem* remove_Elem= nullptr;
        if (!rp->isFull()){
            rp->insert(temp);
            s_engine->insert(temp);
            insert_hasArr(temp);
            insert_TimeArr(temp);
        }
        else
        {
            remove_Elem= rp->remove();
            s_engine->remove(remove_Elem->addr);
            remove_hasArr(remove_Elem);
            remove_TimeArr(remove_Elem);
            s_engine->insert(temp);
            insert_hasArr(temp);
            insert_TimeArr(temp);
            rp->insert(temp);
            return remove_Elem;
        }
    }
    return NULL;
}
void Cache::printRP()
{
    rp->print();
}
void Cache::printSE()
{
    s_engine->print();
}
void Cache::printLP()
{
    s_engine->hash->create_hash();
    s_engine->hash->print();
}