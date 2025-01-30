#include "vector.h"
#include "string.h"
#include <bits/stdc++.h>
#include "haha"
using namespace kad;

#define  cout std::cout
#define cin std::cin
#define endl std::endl

int main(int argc, char const *argv[])
{
    #if 0 //测试vector
    srand(unsigned(time(NULL)));
    vector<int> a;
    for(int i=0;i<20;i++){
        a.push_back(rand()%100);
    }


    for(auto i:a){
        std::cout<<i<<" ";
    }

    std::cout<<std::endl;
    std::sort(a.begin(),a.end());
    for(auto i:a){
        std::cout<<i<<" ";
    }

    std::cout<<std::endl;
    #endif


    #if 1

    string a;
    cin>>a;
    cout<<a<<endl;

    cout<<a.size()<<endl;


    #endif



    return 0;
}




