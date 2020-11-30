#include "utility.h"

//在构造函数中try catch,一旦实例化完成,不用再去检查是否损坏
//swap()中也不要抛出异常

class Ruleofthree{//C++98
    private:
        char* str;

    public:
        Ruleofthree(const char* str){//动态分配需要写析构函数释放,系统基本类型的默认析构函数啥也不做
            this->str = new char(strlen(str)+1);
        }
        ~Ruleofthree(){
            delete[] str;
        }
        Ruleofthree(const Ruleofthree& obj){//定义拷贝构造函数需要重载赋值=,不然拷贝指针有bug
            str = new char(strlen(obj.str)+1);
            strcpy(str,obj.str);
        }
        Ruleofthree& operator=(const Ruleofthree& obj){
            char* newstr = new char(strlen(obj.str)+1);
            strcpy(newstr,obj.str);
            delete[] str;
            str=newstr;
            return *this;
        }
};

//左值可以取地址,引用
//右值不能取地址,引用,但是可以取const引用
/*
返回临时变量,右值引用
返回类型为vector<int>&&
vector<int> func(){
    vector<int> ans(10,0);
    return ans;
}
*/


//使用std::move()主要是在传递形参过程中避免拷贝,传入的是右值引用
//形参如果是const&,那么形参传递内存拷贝的过程,函数内部变量拷贝是有的
//但是如果需要拷贝的东西是在堆上的,传入右值引用,函数内部拷贝都不需要,
//直接使用该右值引用的内存空间


class Ruleoffive{//针对C++11右值进行重载
    private:
        char* str;

    public:
        Ruleoffive(const char* str){//动态分配需要写析构函数释放,系统基本类型的默认析构函数啥也不做
            this->str = new char(strlen(str)+1);
        }
        ~Ruleoffive(){
            delete[] str;
        }
        Ruleoffive(const Ruleoffive& obj){//可以传左值,右值,引用,const引用
            str = new char(strlen(obj.str)+1);//传右值,也要动态分配内存再拷贝
            strcpy(str,obj.str);
        }
        
        Ruleoffive& operator=(const Ruleoffive& obj){
            char* newstr = new char(strlen(obj.str)+1);
            strcpy(newstr,obj.str);
            delete[] str;
            str=newstr;
            return *this;
        }
        Ruleoffive(Ruleoffive&& obj){//传入右值
            str = obj.str;//不用申请空间,直接将右值空间给左值,即临时变量不用浪费.
            obj.str=nullptr;
        }
        Ruleoffive& operator=(Ruleoffive&& obj){
            if(&obj==this) return *this;
            delete[] str;//防止内存泄漏
            str = obj.str;
            obj.str=nullptr;
            return *this;
        }
};


int main(){
    //same constructor
    Ruleofthree test("hello");
    Ruleoffive a("hello");
    //都调用拷贝构造函数,一个传左值,一个传右值
    Ruleoffive b = a;//first declearation using operator=,will still apply to default copy constructor
    b = std::move(b);//this time use override operator=
    Ruleoffive c(b);
    Ruleoffive d = std::move(a);//调用右值的拷贝构造函数
    //此时a还是Ruleoffive类型,但是不能再使用了,因为其资源已经转移给c了
    Ruleoffive e(c);

    return 0;
}