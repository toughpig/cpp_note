#include "tools/container.hpp"

class B
{
    public:
        B(int _a):a(_a){}
        int geta(){return a;}
    private:
        int a=1;
};

class D:public B
{
    public:
        D(int _a, int _b):B(_a),b(_b){}
        D(const D& d): B(d),b(d.b){}
        int getb(){return b;}
    private:
        int b=1;
};


int main(){
    vectorpart();
    mappart();
    listpart();
    D d(2,2);
    D dd(d);
    cout<<dd.geta()<<' '<<dd.getb()<<endl;
    int* int_ptr = new int;
    cout<<int_ptr<<endl;
    shared_ptr<vector<string> > sp = make_shared<vector<string> >();

}

