#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
    Complex(){}
    Complex(char* str);
};

Complex::Complex(char* str) {
    int j=0;
    r=i=0;
    while(str[j]!='+') {
        r *= 10;
        r += str[j] - '0';
        j++;

    }
    j++;
    while(str[j]!='i'){
        i*=10;
        i+=str[j]-'0';
        j++;
    }

}

int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}