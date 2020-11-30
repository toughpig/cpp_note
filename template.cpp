#include "utility.h"

//function template, compiler resolves parameter type 
template<typename U, typename S>
auto getid(U a, S b) -> decltype(a+b)
{
    return a+b;
}

//class template, user provides parameter type
template<class T>
class Node
{
public:
    Node(std::initializer_list<T> val):vec(std::make_shared<vector<T> >(val)){};
    void print(){
        for(auto a : *vec){
            cout<<a<<' ';
        }
    }
private:
    std::shared_ptr<vector<T> > vec;

};

int print(){
    return 0;
}

int main()
{
    double a=1.0;
    double b = -1.0;

    cout<<typeid(getid(a,b)).name()<<' '<<getid(b,a)<<' '<<a+b<<endl;

    Node<string> node({"hello","world"});
    node.print();
    return 0;
}