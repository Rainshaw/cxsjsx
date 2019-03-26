#include <iostream>
#include <string>
#include <fstream>

using namespace std;
template <class T>
class CMyistream_iterator
{
    T* value;
    istream &instream;

public:
    CMyistream_iterator(istream &in):instream(in){
        value= nullptr;
    }

    T&operator *(){
        if(value)
            return *value;
        value=new T;
        instream>>*value;
        return *value;
    }

    void operator ++(int){
        if(value)
            delete value;
        value=nullptr;
    }

};



int main()
{
    int t;
    cin >> t;
    while( t -- ) {
        CMyistream_iterator<int> inputInt(cin);
        int n1,n2,n3;
        n1 = * inputInt; //读入 n1
        int tmp = * inputInt;
        cout << tmp << endl;
        inputInt ++;
        n2 = * inputInt; //读入 n2
        inputInt ++;
        n3 = * inputInt; //读入 n3
        cout << n1 << " " << n2<< " " << n3 << " ";
        CMyistream_iterator<string> inputStr(cin);
        string s1,s2;
        s1 = * inputStr;
        inputStr ++;
        s2 = * inputStr;
        cout << s1 << " " << s2 << endl;
    }
    return 0;
}
