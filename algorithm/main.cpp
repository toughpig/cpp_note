#include "alg.hpp"

#ifndef _UTILITY_H
#define _UTILITY_H

#include "../utility.h"

#endif

void mylist_test()
{
    mylist a(0);
    mylist b(1,&a);
    mylist c(2,&b);
    mylist d(3,&c);
    mylist e(4,&d);
    mylist f(5,&e);
    mylist g(6,&f);
    showList(&g);
    mylist* root = reverse(&g);
    showList(root);
    root = erase(root,1);
    showList(root);
}

void myheap_test(){
    Heap myheap(5);
    assert(myheap.insert(5));
    assert(myheap.insert(4));
    assert(myheap.insert(3));
    assert(myheap.insert(2));
    assert(myheap.insert(1));
    myheap.showHeap();
}

void heap_find_top_k(){
    int n,k,tmp;
    cin>>n>>k;
    Heap myheap(k);
    while(n--)
    {
        cin>>tmp;
        if(myheap.getCount()<k) assert(myheap.insert(tmp));
        else
        {
            if(myheap.getTop()<tmp)
            {
                myheap.changeTop(tmp);
                myheap.downhandle(1,myheap.getCount());
            }
        }
        myheap.showHeap();
    }

}

// int32_t array sum all no overflow, but partial sum can overflow, compute sum.
#define int32_t __INT32_TYPE__
int32_t fix(vector<int32_t>& num)
{
    int ll=0, rr=0;
    int len = num.size();
    while(ll<len&&num[ll]>=0) ll++;
    while(rr<len&&num[rr]<=0) rr++;
    while(ll<len&&rr<len)
    {
        int32_t tmp = num[ll] + num[rr];
        if(tmp<0)
        {
            num[rr] = 0;
            num[ll] = tmp;
            while(rr<len&&num[rr]<=0) rr++;
        }
        else if(tmp>0)
        {
            num[ll] = 0;
            num[rr] = tmp;
            while(ll<len&&num[ll]>=0) ll++;
        }
        else{
            num[ll] = num[rr] = 0;
            while(ll<len&&num[ll]>=0) ll++;
            while(rr<len&&num[rr]<=0) rr++;
        }
    }
    int32_t ans = 0;
    while(ll<len) ans += num[ll++];
    while(rr<len) ans += num[rr++];
    return ans;
}
void test_00()
{
    vector<int32_t> num{1<<31,~(1<<31),1<<30,(int32_t)0xc0000000,1,2,3,4,-1,-10,2};
    cout<<fix(num)<<endl;
}




int main()
{
    // mylist_test();
    // myheap_test();
    // heap_find_top_k();
    // test_00();
    int a = 1;
    pid_t pid;
    if(pid=fork() == 0){
        cout<<"child pid: "<<getpid()<<endl;
        a++;
        cout<<a<<endl;
        exit(0);
    }
    int statusp;
    pid_t child_pid = waitpid(pid,&statusp,0);
    cout<<"wait pid: "<<child_pid<<endl;
    cout<<"father pid: "<<getpid()<<endl;
    cout<<a<<endl;
    vector<int> aa;
    aa.push_back(0);
    assert(aa.size()>0);
    return 0;
}