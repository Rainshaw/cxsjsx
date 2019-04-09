#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

template <class T>
class CArray3D
{
public:
    class CArray2D{
    public:
        T* arr;
        int n,k;
        CArray2D(){
            n=k=0;
            arr=nullptr;
        }
        CArray2D(int jj,int kk):n(jj),k(kk){
            arr=new T[jj*kk];
        }
        T* operator[](int j){
            return arr+j*k;
        }
        operator T*(){
            return arr;
        }

    };
    CArray2D *arr;
    int m;
    int n;
    int k;
    CArray3D(int ii,int jj, int kk):m(ii),n(jj),k(kk) {
        arr = new CArray2D[ii];
        for(int i=0;i<ii;i++){
            arr[i].n=n;
            arr[i].k=k;
            arr[i].arr=new T[n*k];
        }
    }
    CArray2D& operator[](int i){
        return arr[i];
    }
};


CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
    for(int i = 0;i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < 5; ++k)
                cout << a[i][j][k] << "," ;
            cout << endl;
        }
    }
}
void PrintB()
{
    for(int i = 0;i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for(int j = 0; j < 2; ++j) {
            for(int k = 0; k < 2; ++k)
                cout << b[i][j][k] << "," ;
            cout << endl;
        }
    }
}

int main()
{

    int No = 0;
    for( int i = 0; i < 3; ++ i ) {
        a[i];
        for( int j = 0; j < 4; ++j ) {
            a[j][i];
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
            a[j][i][i];
        }
    }
    PrintA();
    memset(a[1],-1 ,20*sizeof(int));
    memset(a[1],-1 ,20*sizeof(int));
    PrintA();
    memset(a[1][1],0 ,5*sizeof(int));
    PrintA();

    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 2; ++j )
            for( int k = 0; k < 2; ++k )
                b[i][j][k] = 10.0/(i+j+k+1);
    PrintB();
    int n = a[0][1][2];
    double f = b[0][1][1];
    cout << "****" << endl;
    cout << n << "," << f << endl;

    return 0;
}