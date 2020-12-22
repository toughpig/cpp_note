#include "utility.h"

int main()
{

    fmt::print("the answer is {}\n",100);
    string a(fmt::format("i choose {1} rather than {0}\n","eat", "sleep"));
    fmt::print("{}",a);

    vector<int> v{1,2,3};
    fmt::print("{}\n",v);

    //string s = fmt::format(FMT_STRING("{:d}"),"i am not a number");
    //fmt::print("{}",s);

    auto of = fmt::output_file("test.out");
    of.print("Don't be {}\n","Panic");
    return 0;
}