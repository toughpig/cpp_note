#include "../utility.h"

//-----------三种基本容器-------------
//1.序列式容器 array/vector/list/deque/forward_list 数组,链表实现
//2.关联式容器 set/map/multiset/multimap 红黑树实现
//3.无顺序容器 unordered_map/unordered_set/unordered_multiset/unordered_multimap 哈希表实现

//4.上述的封装 stack/queue/priority_queue/string/bitset

//容器内元素的条件
//1.必须可以复制或搬移(copy/move的过程中没有副作用)  引用/函数 不行
//2.可以被赋值操作,(非基本类型)要重载operator=
//3.元素可以被销毁,析构函数不能是private

//序列式容器,元素要有默认构造函数
//某些操作元素须定义 ==
//关联式容器,排序默认<
//无顺序容器必须提供一个hash函数
//stl容器内存的是元素值而不是引用

//自定义的类放到container里面,要怎么放????

//--------container的共同接口----------
template<typename T>
void containerAllInterface(T& a,T& b){
    T c;
    T d(a);//copy
    T e = a;//copy
    T f(std::move(a));//move
    //std::move(a)产生a的亡值表达式,等价于static_cast<右值引用>
    auto iterb = b.begin();
    auto itere = b.end();
    T g(iterb,itere);//copy
    b.size();//除了forward_list不包含此接口
    b.empty();
    b.max_size();//该容器最大容量
    if(b == c){} //比较容器内的值
    if(b != c){}
    if(b < c){} //对于序列容器
    e = b;
    e = std::move(b);
    e.swap(g); //std::array 线性的, 其他O(1)
    swap(e,g); //全局效率O(1),除了array
    e.cbegin(); // -> const_iterator
    e.cend();
    e.clear(); //内容全部调用析构函数,除了array
}

void test(){
    vector<int> a;
    vector<int> b;
    containerAllInterface(a,b);
}

void arraypart(){//原生数组的封装
    //template<typename T,typename size>
    //class array;
    array<int,10> a;//内存分配在栈上,一旦分配不再重新分配
    array<int,5> b = {};//初始化0
    array<int,5> c{1,2,3};//初始化,后面补0
    b[0]=1;
    b[1]=2;
    b[2]=3;
    cout<<(b==c)<<endl;//true比较的是容器内的值,不是容器的地址
    a[1];//返回的都是引用
    //a.at(10);//等价于a[1],但是会检查并抛出数组越界异常std::out_of_range
    a.front();
    a.back();

    a.rbegin();//返回迭代器,从尾到头
    a.rend();

    //和C接口互用
    array<char,100> str;
    strcpy(&str[0],"hello world\n");
    printf("%s",&str[0]);
    printf("%s",str.data());
    //printf("%s",str.begin())错误
    auto info = std::get<1>(str);
    cout<<typeid(info).name()<<' '<<info<<endl;
    str.fill(0);

    //异常
    //a.at(pos);
    //使用场景:
    //大小固定,要与C接口交互
}

void newpart(){
    typedef int pp[10];
    int a=1;
    int* ap = new int(10);
    int* bp = new pp;
    int* cp = new int[10];
    int* dp = (int*)malloc(10*sizeof(int));
    int ep[10];
    cout<<sizeof(ap)<<' '<<sizeof(bp)<<' '<<sizeof(cp)<<' '<<sizeof(dp)<<' '<<sizeof(ep)<<endl;
    cout<<ap[0]<<' '<<bp[0]<<' '<<cp[0]<<' '<<dp[0]<<' '<<ep[1]<<endl;
}

void vectorpart(){//动态数组
    //template<typename T,typename Allocator = allocator<T>>
    //class vector;
    //std默认的allocator(new/delete), TCMalloc
    using vf = vector<float>;
    vf a;
    vf b = a;
    vf c(a);
    vf d(10);//size,默认0
    vf e(10,1.0f);
    vf f(e.begin(),e.end());
    vf g({1.0,2.0});//C++11
    vf h = {1.1,2.2,3.3};//initialize list

    cout<<d.capacity()<<endl;//当前能装多少不会发生重分配
    d.reserve(100);//预先分配100个float的空间

    b.assign(3,1.0f);//size变成3,值都是1.0
    b.assign(h.begin(),h.end());
    b.resize(10);
    b.resize(10,1.0f);
    b.swap(a);
    swap(a,b);
    if(!b.empty()){//多线程下是错的
        b.front();//若b.empty(),undefined
        b.back();
    }

    b.erase(b.begin());
    b.erase(b.begin(),b.end());//不做检查

    b.push_back(1.0);
    b.pop_back();//void
    b.insert(b.end(),e.begin(),e.end());
    b.emplace(b.end(),10.0f);
    //使用push_back()向容器中加入一个右值元素(临时对象)时，
    //首先会调用构造函数构造这个临时对象
    //然后需要调用拷贝构造函数将这个临时对象放入容器中。原来的临时变量释放。
    //这样造成的问题就是临时变量申请资源的浪费。
    //引入了右值引用，转移构造函数(转移赋值运算符)后,push_back()右值时,
    //就会调用构造函数和转移构造函数A(A&& a)
    //如果可以在插入的时候直接构造，就只需要构造一次即可
    //这就是c++11新加的emplace_back
    b.emplace_back(10.0f);//C++11 &&
    d.shrink_to_fit();//C++11

    vf aa(10);//size=10
    aa.push_back(2.2f);//size=11
    cout<<aa.capacity()<<' '<<aa.size()<<endl;
    aa.shrink_to_fit();
    cout<<aa.capacity()<<' '<<aa.size()<<endl;

    //尾部添加删除快,内存紧凑
}

void dequepart(){
    //template<typename T,typename Allocator = allocator<T>>
    //class deque;
    //尾部和头部添加删除快
    //迭代器不能是普通指针
    //迭代比vector慢
    //接口与vector类似
    using dq = deque<int>;
    dq a;
    dq b(10,1);
    //不提供以下函数
    //d.capacity();
    //d.reserve(100);

    auto iterafter = b.erase(b.begin());
    b.push_back(2);
    b.push_front(3);
    b.emplace(b.end(),4);
    b.emplace_front(5);
}

void listpart(){//双向链表
    //template<typename T,typename Allocator = allocator<T>>
    //class list;
    //不支持随机访问,头尾可以
    //任意位置(获知该位置指针)插入删除方便
    //插入删除不会造成迭代器失效
    using lst = list<int>;
    //构造方式与vector类似
    //不提供以下函数
    //capacity()
    //reserve()
    //shrink_to_fit()
    //lst[pos]不能随机访问,通过迭代器访问

    lst a(10);
    //迭代器的移动
    auto iter = a.begin();
    std::advance(iter,4);
    auto iter5 = std::next(iter,4);

    //不能使用STL的sort排序list,因为list的迭代器不是随机迭代器,不能瞬移,只能一步一步后移
    //std::sort(a.begin(),a.end());
    //算法接口
    a.remove(1);//全部删除列表中值为1的结点
    a.remove_if([](auto v){return v>100;});//lambda
    a.reverse();
    a.sort();// <
    lst b(a);
    a.merge(b);//有序列表转移到a,b空
    a.unique();//去连续重复值, 11223144 -> 12314
    a.splice(a.begin(),b);//把b插到a迭代器位置
}

void forward_listpart(){//单向链表
    //template<typename T,typename Allocator = allocator<T>>
    //class forward_list;
    //接口与list基本一致
    //不提供以下接口
    //a.back()   只能指向头节点
    //a.rbegin()   不提供反向迭代器
    //a.pop_back()
    using flst = forward_list<int>;
    flst a(10);
    //使用头指针进行操作
    a.before_begin();//解引用undefined
    if(!a.empty()) a.pop_front();
    a.erase_after(a.before_begin());//删除头节点
    flst b(a);
    a.insert_after(a.before_begin(),b.begin(),b.end());

    flst aa = {1,2,3,4,5,6};
    auto iter = aa.before_begin();
    for(int i=0;i<2;i++) iter++;//要在第三位插入
    aa.insert_after(iter,10);
    for(auto a : aa){
        cout<<a<<' ';
    }
}

struct CompareAge{
    template<typename T>
    bool operator()(T& a,T& b) const {
        return a.getage()<b.getage();
    }
};

class node{
    public:
        node(int a,string str): age(a),name(std::move(str)){};
        ~node(){};
        void print() const {
            cout<<age<<' '<<name<<endl;
        };
        int getage() const {return age;}
        bool operator==(const node& a) const {
            return age==a.age&&name==a.name;
        }
    private:
        int age;
        string name;

};


//set/map内部实际使用红黑树存储,左/右/父节点,前驱/后继结点,40bytes

void setpart(){
    //template<typename T,typename Compare=less<T>,typename Allocator=allocator<T>>
    //class set;

    //template<typename T,typename Compare=less<T>,typename Allocator=allocator<T>>
    //class multiset;

    //元素自动排序
    //插入和删除O(lgn)
    //元素满足严格的弱顺序
    // x<y -> y<x==false
    // x<x==false
    // x<y, y<z -> x<z
    using st = set<int>;
    //构造类似

    st a{1,2,4,3};
    st b = {4,3,1,2};
    cout<<(a==b)<<endl;

    //算法接口
    auto cnt = a.count(1);//set中count只可能是0/1,multiset中可能>1
    auto iter = a.find(2);//返回第一个查找到的迭代器
    if(iter!=a.end()) ;//查找成功
    a={1,2,4,5};
    auto lower = a.lower_bound(3);//返回可插入3的最左位置迭代器 4
    if(lower != a.end()){
        if(*lower == 3){
            //1已经存在在该set中
        }
    }
    auto upper = a.upper_bound(3);//返回可插入3的最右位置迭代器 4
    auto equal = a.equal_range(5);//返回可插入5的区间位置迭代器pair <5,6>

    auto state = a.insert(3);//返回pair<Iterator, bool>

    node x(12,"Bob");
    node y(15,"Acely");
    node z(11,"vince");
    set<node,CompareAge> c;
    c.insert(x);
    c.insert(y);
    c.insert(z);
    // vector<node> c;
    // c.push_back(x);
    // c.push_back(y);
    // c.push_back(z);
    for(auto& k:c){//set的for(auto& k:c),k不能改变值,所以只能调用定义为const的函数
        k.print();
    }
    auto iter0 = c.find(x);//通过allocator的比较方式寻找
    auto iter2 = std::find(c.begin(),c.end(),x);//******需要重载operator==***********

    auto iter1 = c.begin();//只能调用const属性
    (*iter1).print();
}

void mappart(){
    //template<typename Key,typename T,typename Compare=less<Key>,typename Allocator=allocator<pair<const Kry,T>>>

    //算法接口
    using mp = map<int,string>;
    mp a = {{1,"Acely"},{2,"Vince"}};

    //插入三种方法
    auto state = a.insert(make_pair(2,"Bob"));//返回pair<iter,bool>,当前键已经存在则返回false
    cout<<state.second<<endl;//false
    auto newstate = a.emplace(11,"hello");
    cout<<newstate.second<<endl;
    a.emplace(make_pair(4,"hello"));
    a[10]="world";//value要有默认构造函数
    a[20];//等价于auto state = a.insert(make_pair(20,"")); return state.second;
    auto iter = a.find(2);//Key
    if(iter!=a.end()){
        cout<<(*iter).second<<endl;
    }
}

class position{
    public:
        position(int x,int y):mx(x),my(y){};
        int getx() const {return mx;}
        int gety() const {return my;}
    private:
        int mx;
        int my;
};

class person{
    public:
        person(int a,string str):age(a),name(str){}
        void print(){cout<<name<<' '<<age<<endl;}
        int getage() const {return age;}
        const string getname() const {return name;}
        void changeage(int newage){age=newage;}
        bool operator==(const person& per){return age==per.age&&name==per.name;}
    private:
        int age;
        string name;
};


//boost中的实现
template<class T> inline void hash_combine(size_t &seed,const T &v){
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

//*****模板类特化*****,已定义的模板,应用到自定义类上
namespace std{

    // template<typename T> struct hash{
    //      ........
    // };

    template<> struct hash<position>{
        size_t operator()(const position& p) const {
            auto key = hash<int>()(p.getx());
            hash_combine(key,p.gety());
            return key;
        }
    };
}

void unorderedpart(){//hashtable O(1)
    //template<typename Key,typename T,typename Hash=hash<Key>,
    //typename EqPred=equal_to<Key>,typename Allocator=allocator<pair<const Key,T>>>
    //查找平摊效率常数
    //使用hash有hash的缺点,遍历,空间效率,数据量超级大(千万级)的时候,使用红黑树的set/map效率较高
    //equal_to处理hash冲突
    using uodmp = unordered_map<position,person>;//hash已经模板特化应用到position
}


//辅助类pair
// template<typename T1,typename T2>
// struct pair{
//     T1 first;
//     T2 second;
// };

//set/map内部的值实际上是pair存储

template<typename T, unsigned S>
unsigned constexpr num(const T (&a)[S]){
    return S; 
}