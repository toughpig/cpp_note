#include "../utility.h"


class Base
{
public:
    Base(int a):val(a){}
    Base(const Base& b){val=b.val;}
    const int getval(){return val;}
private:
    int val;
};


int main()
{

    Base b(1);
    Base c(2);
    Base d(c);
    cout<<b.getval()<<endl
        <<c.getval()<<endl
        <<d.getval()<<endl;


    return 0;
}