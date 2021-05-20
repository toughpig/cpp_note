#include "tools/container.hpp"

class B
{
    public:
        B(int _a):a(_a){}
        
        ~B(){
            cout<<"~B()"<<endl;
        }
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

void process(ofstream& ofs){
    ofs<<"hello\nworld\nmain\n";
    ofs.flush();
}

int main(int argc, char* argv[]){
    vectorpart();
    mappart();
    listpart();
    D d(2,2);
    D dd(d);
    cout<<dd.geta()<<' '<<dd.getb()<<endl;
    int* int_ptr = new int;
    cout<<int_ptr<<endl;
    shared_ptr<vector<string> > sp = make_shared<vector<string> >();
    string str;
    //getline(cin,str);
    ofstream ofs;
    ofs.open("test.in");
    assert(ofs);
    ofs<<"hello\nworld\n";
    ofs.close();
    ifstream ifs("test.in");
    //ofs.open("test.out");
    //assert(ofs);
    //string temp;
    //while(getline(ifs,temp))
    //    ofs<<temp+"\n";
    ifs.close();
    //ofs.close();
    for(auto p = argv+1; p!=argv+argc; p++){
        ofstream ofst(*p, ofstream::app | ofstream::out);
        if(ofst){
            process(ofst);
        }
        else
        {
                cerr<<"couldn't open file "<<*p<<endl;
        }
        
    }
    {
        B* bb = new B(1);

    }
    cout<<"B released"<<endl;

}

