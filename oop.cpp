#include "utility.h"

class Quote
{
public:
    Quote() = default;
    Quote(const string& name, double sales_price): bookNo(name), price(sales_price){}
    string isbn() const {return bookNo;}
    virtual double net_price(size_t n){return price*n;}
    int geta(){return 1;}
    virtual ~Quote() = default;
private:
    string bookNo;
protected:
    double price=1.0;
};

class Bulk_quote: public Quote
{
public:
    virtual double net_price(size_t n){
        return n>=atleast? n*(1-discount)*price : n*price;
    }
    virtual ~Bulk_quote() = default;
    int geta(){return 2;}
    Bulk_quote() = default;
    Bulk_quote(const string& name, double sales_price, size_t num, double cut):Quote(name,sales_price),discount(cut),atleast(num){}

private:
    double discount;
    size_t atleast;
};

void print_all(Quote& obj, size_t num)
{
    cout<<obj.isbn()<<": $"<<obj.net_price(num)<<endl;
}

int main(){
    Bulk_quote bq("isbn12345",10,100,0.1);
    Quote& qq = bq;
    print_all(bq,100);
    print_all(qq,100);
    return 0;
}

