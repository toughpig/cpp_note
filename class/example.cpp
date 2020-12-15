#include "../utility.h"

typedef const string::iterator It;

class Entity
{
public:
    Entity() = default;
    friend ostream& operator<<(ostream& out, const Entity& entity)
    {
        out<<entity.name<<":"<<endl;
        for(const auto& atom : entity.data)
        {
            out<<"  "<<atom.first<<' '<<atom.second<<endl;
        }
        cout<<endl;
        return out;
    }
    void process(string str);
private:
    string name = "unnamed";
    vector<pair<string,string> > data;
};

void Entity::process(string ss)
{
    size_t len = ss.length();
    size_t a,b;
    a=b=0;
    string first,second;
    while(a<len){
        while(a<len&&ss[a]==' ') a++;
        b=a;
        while(b<len&&ss[b]!=' ') b++;
        first = ss.substr(a,b-a);
        a=b;
        while(a<len&&ss[a]==' ') a++;
        b=a;
        while(b<len&&ss[b]!=' ') b++;
        second = ss.substr(a,b-a);
        a=b;
        data.emplace_back(make_pair(first,second));
    }
}


int main(int argc, char* argv[])
{
    vector<Entity> e;
    for(auto p = argv+1; p!=argv+argc; p++){
        ifstream ifst(*p, ifstream::in);
        string temp;
        if(ifst){
            while(getline(ifst,temp)){
                e.emplace_back(Entity());
                e.back().process(temp);
                cout<<e.back();
            }
        }
        else
        {
                cerr<<"couldn't open file "<<*p<<endl;
        }
    }
    return 0;
}
