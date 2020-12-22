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
    if(a<len){
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
        if(first == "key")
            name = second;
        else
            data.emplace_back(make_pair(first,second));
    }
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

/*
**********database************
*/
vector<Entity> database;

void printall(const vector<Entity>& e)
{
    for(const auto& a : e)
    {
        cout<<a;
    }
}

void build_date(string filename)
{
    ifstream ifst(filename, ifstream::in);
    string temp;
    if(ifst){
        while(getline(ifst,temp)){
            database.emplace_back(Entity());
            database.back().process(temp);
        }
    }
    else
    {
            cerr<<"couldn't open file "<<filename<<endl;
    }
}

int main(int argc, char* argv[])
{
    string cmd;
    while(getline(cin,cmd))
    {
        if(cmd=="print")
        {
            printall(database);
        }
        else if(cmd=="build")
        {
            cout<<"input filename\n";
            string filename;
            getline(cin,filename);
            build_date(filename);
        }
        else if(cmd=="insert")
        {
            cout<<"input filename\n";
            string filename;
            getline(cin,filename);
            string temp;
            getline(cin,temp);
            ofstream ofst(filename,fstream::app);
            ofst.write((temp+'\n').c_str(),temp.size()+1);
            ofst.close();
        }
        else if(cmd=="quit")
        {
            break;
        }
        else
        {
            cout<<"invalid input format\n";
        }
        
    }
    return 0;
}
