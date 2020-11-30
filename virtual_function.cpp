//封装,继承,多态
//基类析构函数默认不是virtual, 为了效率
//但是如果使用基类指针指向子类,释放时为了能调用基类析构函数,需要将基类析构函数定义为virtual
//构造函数和析构函数中调用的虚函数,其多态特性还未生成,调用自身实现的该函数
//如果类中含有虚函数或者纯虚函数,析构函数是public的,那么析构函数应该定义为virtual
//如果不希望外部使用者调用基类析构函数,用protected隐藏起来,这样就强制在派生类中调用基类析构函数
#include "utility.h"

class Parent{
    private:
        int m_id;
    public:
        Parent(int a): m_id(a){};
        //virtual ~Parent(){};
        virtual int getid(){return 0;};
        virtual void act(Parent& p){cout<<"P called\n";};
    protected:
        ~Parent(){};//Parent不能实例化,因为只有在其派生类中才能调用该基类的析构函数
};                  //也放弃了使用基类指针控制生命周期的行为 

class Son:public Parent{
    public:
        Son(int a):Parent(a){};
        ~Son(){};
        int getid() override {return 1;};//同名覆盖
        void act(Son& s){cout<<"S called\n";};
        void print();
};

void test(){

    Son* s = new Son(0);
    Parent* p = s;
    s->act(*s);
    p->act(*p);
    cout<<s->getid()<<endl;
    cout<<p->getid()<<endl;
    Son* ss = dynamic_cast<Son*>(p);
    cout<<ss->getid()<<endl;

}

int main(){
    test();
    return 0;
}