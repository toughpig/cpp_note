#include "../utility.h"

class Quote
{
public:
    Quote() = default;
    Quote(const string& name, double sales_price): bookNo(name), price(sales_price){}
    string isbn() const {return bookNo;}
    virtual double net_price(size_t n){return price*n;}
    virtual auto func() -> int const {return 0;};
    int geta(){return 1;}
    virtual int getb(){return 1;}
    virtual void get(){cout<<geta()<<" "<<getb()<<endl;}
    virtual void test_default_var(int var=1){cout<<var<<endl;}
    virtual ~Quote() = default;
private:
    string bookNo;
protected:
    double price=1.0;
};

class Bulk_quote: public Quote
{
public:
    //virtual func must define before instantiation
    //virtual double net_price(size_t n){return n>=atleast? n*(1-discount)*price : n*price;}
    //put final/override after variable-table/decltype()/const 
    virtual auto func() -> int const final{return 1;};
    //non-vir-func overload
    int geta(){return 2;}
    //vir-func cverride
    virtual int getb(){return 2;}
    //virtual void get(){cout<<geta()<<" "<<getb()<<endl;};
    //given that virtual void get() did not override (succeed default base vir-func)
    //polymorphism behavior
        //derived d;
        //base& b = d;
        //b.get();
        //virtual func calls vir-func and non-vir(overloaded)-func behavior
        //if caller vir-func did not override, callee vir-func bind to derived, non-vir-func bind to base
        //if caller vir-func did override,     callee vir-func bind to derived, non-vir-func bind to derived
    //default variable-table polymorphism
    //use base's default variable-table
    virtual void test_default_var(int var=1){cout<<var<<endl;}
    friend ostream& operator<<(ostream& out, const Bulk_quote& bq)
    {
        out<<bq.isbn()<<endl;
        return out;
    }

    Bulk_quote() = default;
    //within derived class, can use base's protected possessions
    Bulk_quote(const string& name, double sales_price, size_t num, double cut):\
        Quote(name,sales_price),discount(cut),atleast(num){}
    virtual ~Bulk_quote() = default;

private:
    //base& can call derived private override vir-func
    //what the fuck
    virtual double net_price(size_t n){return n>=atleast? n*(1-discount)*price : n*price;}
    double discount;
    size_t atleast;
};

//polymorphism behavior
void print_all(Quote& obj, size_t num)
{
    cout<<obj.isbn()<<": $"<<obj.net_price(num)<<endl;
}

auto func() -> int const;

int main(){
    Bulk_quote bq("isbn12345",10,100,0.1);
    //cout<< bq.net_price(100);
    Quote& qq = bq;
    print_all(bq,100);
    print_all(qq,100);
    cout<<bq;
    return 0;
}

