#include <cstdlib>
#include <iostream>
using namespace std;

class MyString
{
    char str[200];
public:
    int strleen(const char * s)
    {	int i = 0;
        for(; s[i]; ++i);
        return i;
    }
    void strcppy(char * d,const char * s)
    {
        int i = 0;
        for( i = 0; s[i]; ++i)
            d[i] = s[i];
        d[i] = 0;

    }
    int strcmp(const char * s1,const char * s2)
    {
        for(int i = 0; s1[i] && s2[i] ; ++i) {
            if( s1[i] < s2[i] )
                return -1;
            else if( s1[i] > s2[i])
                return 1;
        }
        return 0;
    }
    void strcaat(char * d,const char * s)
    {
        int len = strlen(d);
        strcpy(d+len,s);
    }

    MyString(){
        str[0]='\0';
    }

    MyString(const char* sstr){
        strcppy(str, sstr);
    }

    MyString(const MyString &m){
        strcppy(str,m.str);
    }

    friend ostream& operator<<(ostream &out, MyString &m){
        out<<m.str;
        return out;
    }

    bool  operator==(MyString &m){
        int i=0;
        for(i=0;m.str[i];i++) {
            if (str[i] != m.str[i])
                return false;
        }
        if(m.str[i]==str[i])
            return true;
        return false;
    }

    bool operator<(MyString &m){
        if(*this==m)
            return false;
        int i=0;
        for(i=0;str[i];i++) {
            if(!m.str[i])
                return false;
            if (str[i] < m.str[i])
                return true;
            else if (str[i] > m.str[i])
                return false;
        }
        if(m.str[i])
            return true;
        else
            return false;
    }

    bool operator>(MyString &m){
        if(*this==m)
            return false;
        if(*this<m)
            return false;
        return true;
    }

    MyString operator+(MyString &m){
        MyString ans(*this);
        strcaat(ans.str,m.str);
        return ans;
    }

    MyString operator+(char* m){
        MyString ans(*this);
        strcaat(ans.str,m);
        return ans;
    }

    MyString& operator+=(MyString &m){
        strcaat(str, m.str);
        return *this;
    }

    MyString& operator+=(char* m){
        strcaat(str, m);
        return *this;
    }

    friend MyString operator+(const char* str, const MyString &m){
        MyString ans;
        strcat(ans.str,str);
        strcat(ans.str,m.str);
        return ans;
    }

    char& operator[](int index){
        return str[index];
    }

    char* operator()(int n, int m){
        char* ans=new char[m+1];
        for(int i=0;i<m;i++){
            ans[i]=str[n+i];
        }
        ans[m]='\0';
        return ans;
    }
};


int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}
int main()
{

	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}