#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;
class CHugeInt {
    char str[210];
public:
    CHugeInt(int x){
        int i;
        for(i=1;x!=0;x/=10,i++){
            int c=x%10;
            str[210-i]='0'+c;
        }
        while(i<=210){
            str[210-i]='\0';
            i++;
        }
    }
    CHugeInt(char* s){
        int j=1;
        for(int i=strlen(s)-1;i>=0; i--,j++)
            str[210-j]=s[i];
        //cout<<j<<endl;
        while(j<=210){
            str[210-j]='\0';
            j++;
        }
    }



    CHugeInt(){
        int i=0;
        while(i<210)
            str[i++]='\0';
    }
    CHugeInt(const CHugeInt &c){
        int i=0;
        while(i<210) {
            str[i] = c.str[i];
            i++;
        }
    }
    friend ostream &operator <<(ostream &out, const CHugeInt &c){
        int i=0;
        while(!c.str[i])
            i++;
        while(i<210)
            out<<c.str[i++];
        return out;
    }

    CHugeInt operator+(const CHugeInt &x){
        CHugeInt ans;
        int jinwei=0;
        int i;
        for(i=210-1; str[i]&&x.str[i];i--){
            int res=jinwei+str[i]+x.str[i]-'0'-'0';
            ans.str[i]=res%10+'0';
            jinwei=res/10;
        }
        while(str[i]){
            int res=jinwei+str[i]-'0';
            ans.str[i]=res%10+'0';
            jinwei=res/10;
            i--;
        }
        while(x.str[i]){
            int res=jinwei+x.str[i]-'0';
            ans.str[i]=res%10+'0';
            jinwei=res/10;
            i--;
        }
        if(jinwei)
            ans.str[i]=jinwei+'0';
        return  ans;
    }

    friend CHugeInt operator+(const int a, const CHugeInt &x){
        CHugeInt ans;
        CHugeInt xx(a);
        int jinwei=0;
        int i;
        for(i=210-1; xx.str[i]&&x.str[i];i--){
            int res=jinwei+xx.str[i]+x.str[i]-'0'-'0';
            ans.str[i]=res%10+'0';
            jinwei=res/10;
        }
        while(xx.str[i]){
            int res=jinwei+xx.str[i]-'0';
            ans.str[i]=res%10+'0';
            jinwei=res/10;
            i--;
        }
        while(x.str[i]){
            int res=jinwei+x.str[i]-'0';
            ans.str[i]=res%10+'0';
            jinwei=res/10;
            i--;
        }
        if(jinwei)
            ans.str[i]=jinwei+'0';
        return  ans;
    }

    CHugeInt& operator++(){
        int jinwei=1;
        int i;
        for(i=210-1; str[i]&&jinwei;i--){
            int res=jinwei+str[i]-'0';
            str[i]=res%10+'0';
            jinwei=res/10;
        }
        jinwei?str[i]=jinwei+'0':1;
        return *this;
    }

    CHugeInt operator++(int){
        CHugeInt ans(*this);
        int jinwei=1;
        int i;
        for(i=210-1; str[i]&&jinwei;i--){
            int res=jinwei+str[i]-'0';
            str[i]=res%10+'0';
            jinwei=res/10;
        }
        jinwei?str[i]=jinwei+'0':1;
        return ans;
    }

    CHugeInt& operator+=(const CHugeInt &c){
        *this=*this+c;
        return *this;
    }
};
int  main()
{
	char s[210];
	int n;

	while (cin >> s >> n) {
	    //cout<<s<<endl<<n<<endl<<1<<endl;

		CHugeInt a(s);
		CHugeInt b(n);
        //cout<<a<<endl<<b<<endl<<2<<endl;
		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}