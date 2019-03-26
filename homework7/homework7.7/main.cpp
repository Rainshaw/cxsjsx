#include <iostream>
using namespace std;
class MyCin
{
    int value=1;
    istream *in;
public:
    MyCin(){
        in=&cin;
    }
    MyCin& operator>>(int &x){
        if (!value)
            return *this;
        *in>>x;
        if(x==-1)
            value=0;
        //cout<<value<<endl;
        return *this;
    }
    operator bool(){
        return value;
    }
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2)
        cout  << n1 << " " << n2 << endl;
    return 0;
}