#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(
T* start, T*end){
    T* ans=new T;
    for(int i=0;i<end-start;i++) {
//        cout<<*ans<<endl;
//        cout << *(start+i) << endl;
        *ans += *(start + i);
    }
    return *ans;
}
int main() {
    string array[4] = { "Tom","Jack","Mary","John"};
    cout << SumArray(array,array+4) << endl;
    int a[4] = { 1, 2, 3, 4};  //提示：1+2+3+4 = 10
    cout << SumArray(a,a+4) << endl;
    return 0;
}