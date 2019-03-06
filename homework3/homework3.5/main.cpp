#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }

	MyString& operator=(MyString & m){
        Copy(m);
        return *this;
    }

    MyString& operator=(char*  m){
        p = new char[strlen(m) + 1];
        strcpy(p,m);
        return *this;
    }

	void Copy(const MyString &m){
	    p=new char[strlen(m.p)];
        strcpy(p,m.p);
	}

	friend ostream & operator << (ostream &out, MyString &m){
        out<<m.p;
        return out;
	}
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;

		MyString s3(NULL);
		s3.Copy(w1);

		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;

		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;

	}
}