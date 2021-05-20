#include "alg.hpp"

#ifndef _UTILITY_H
#define _UTILITY_H

#include "../utility.h"

#endif

//-------------------list--------------------
void showList(mylist* root)
{
    if(!root) cout<<"null";
    while(root)
    {
        cout<<root->data;
        if(root->next)
            cout<<" -> ";
        root = root->next;
    }
    cout<<endl;
}

mylist* reverse(mylist* root)
{
    mylist* ans = nullptr;
    mylist* tmp = nullptr;
    while(root)
    {
        tmp = root->next;
        root->next = ans;
        ans = root;
        root = tmp;
    }
    return ans;
}

mylist* erase(mylist* root, int a)
{
    while(root && root->data==a)
    {
        return erase(root->next,a);
        free(root);
    }
    if(!root) return nullptr;
    root->next = erase(root->next,a);
    return root;
}

//-----------------heap-sort--------------------
void Heap::showHeap()
{
    for(int i = 1; i<=count; i++)
        cout<<heap[i]<<" ";
    cout<<endl;
}

bool Heap::insert(int a)
{
    if(count==capacity) return false;
    heap[++count] = a;
    uphandle(count);
    return true;
};

void Heap::uphandle(int pos)
{
    if(pos<=1) return;
    if(heap[pos/2]>heap[pos])
    {
        swap(heap[pos],heap[pos/2]);
        uphandle(pos/2);
    }
}

void Heap::downhandle(int pos, int end)
{
    if(pos*2>end) return;
    int ll = pos*2, rr = pos*2+1;
    int newpos;
    if(rr>end)
        newpos = ll;
    else if(heap[ll]<heap[rr])
        newpos = ll;
    else
        newpos = rr;
    if(heap[pos]>heap[newpos])
    {
        swap(heap[pos],heap[newpos]);
        downhandle(newpos,end);
    }
}