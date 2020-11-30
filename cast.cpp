#include "utility.h"

int main(){

//类型转换  static_cast, dynamic_cast, const_cast, reinterpret_cast

/*static_cast任何编写程序时能够明确的类型转换都可以使用static_cast
static_cast不能转换掉底层const，volatile和__unaligned属性。
由于不提供运行时的检查，所以叫static_cast，因此，需要在编写程序时确认转换的安全性。
主要在以下几种场合中使用：
    1.用于类层次结构中，父类和子类之间指针和引用的转换；
    2.进行上行转换，把子类对象的指针/引用转换为父类指针/引用，这种转换是安全的；
    3.进行下行转换，把父类对象的指针/引用转换成子类指针/引用，这种转换是不安全的，需要编写程序时来确认；
    4.用于基本数据类型之间的转换，例如把int转char，int转enum等，需要编写程序时来确认安全性；
    5.把void指针转换成目标类型的指针（这是极其不安全的）；
*/


//dynamic_cast会在运行时检查类型转换是否合法，具有一定的安全性。仅适用于指针或引用
//将父类指针cast成子类指针(危险)
//Base b = new Base;
//Derived *d = dynamic_cast<Derived *>(b); 转换失败返回空指针
//Base bb;
//Derived &dd = dynamic_cast<Derived&>(bb); 转换失败抛出异常
/*
class A { virtual void f() {}; };
class B :public A { void f() {}; };
class C :public A { void f() {}; };
class D :public B, public C { void f() {}; };

void main()
{
    D *pD = new D;
    B *pB = dynamic_cast<B *>(pD);
    A *pA = dynamic_cast<A *>(pB);
}
*/

//const_cast用于移除类型的const、volatile和__unaligned属性,指向同一片内存
const char *pc;
char *p = const_cast<char*>(pc);

//reinterpret_cast非常激进的指针类型转换，在编译期完成，可以转换任何类型的指针，所以极不安全。

}