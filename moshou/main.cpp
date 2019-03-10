#include <iostream>
#include <map>
#include <vector>

using namespace std;

int mytime, maxtime;
unsigned int healthPointList[5];
char* soliderTypeName[5]={"dragon","ninja","iceman","lion","wolf"};

class Solider {
private:
    unsigned int healthPoint;
    unsigned int No;
public:
    explicit Solider(unsigned int HP, unsigned int No):healthPoint(HP), No(No) {
    //    cout << "A Solider with " << HP << "HP was built!\n";
    };

    virtual ~Solider() = default;;

    //virtual Solider *create(unsigned int No);
};

class Dragon : public Solider {
private:
    //int healthPoint;
public:
    Dragon(unsigned int No) : Solider(healthPointList[0], No) {
    //    cout << "A Dragon was built!\n";
    }

    static Dragon *create(unsigned int No){
        return new Dragon(No);
    }
};

class Ninja : public Solider {
private:
    //int healthPoint;
public:
    Ninja(unsigned int No) : Solider(healthPointList[1], No) {
    //    cout << "A Ninja was built!\n";
    }

    static Ninja *create(unsigned int No){
        return new Ninja(No);
    }
};

class Iceman : public Solider {
private:
    //int healthPoint;
public:
    Iceman(unsigned int No) : Solider(healthPointList[2], No) {
    //    cout << "A Iceman was built!\n";
    }

    static Iceman *create(unsigned int No){
        return new Iceman(No);
    }
};

class Lion : public Solider {
private:
    //int healthPoint;
public:
    Lion(unsigned int No) : Solider(healthPointList[3], No) {
    //    cout << "A Lion was built!\n";
    }

    static Lion *create(unsigned int No){
        return new Lion(No);
    }
};

class Wolf : public Solider {
private:
    //int healthPoint;
public:
    Wolf(unsigned int No) : Solider(healthPointList[4], No) {
    //    cout << "A Wolf was built!\n";
    }

    static Wolf *create(unsigned int No){
        return new Wolf(No);
    }
};

typedef function<Solider*(unsigned int)> SoliderCreateType;

map<unsigned int,SoliderCreateType> _SoliderCreate;



void myprint(int tim, char* str, int soliderType, int soliderIndex,int soliderNum){
    printf("%03d ",tim);
    printf("%s %s %d born with strength %d,%d %s in %s headquarter\n", str, soliderTypeName[soliderType], soliderIndex, healthPointList[soliderType], soliderNum, soliderTypeName[soliderType], str);
    return;
}

class Headquarter {
private:
    vector<Solider*> soliderList;
    unsigned int soliderNumber[5];
    unsigned int healthPoint;
    unsigned int soliderTotalNumber;
    unsigned int soliderIndex, createIndex;
public:

    Headquarter(unsigned int HP) : healthPoint(HP) {
        soliderList.clear();
        memset(soliderNumber, 0, sizeof(soliderNumber));
        soliderTotalNumber = soliderIndex = createIndex = 0;
    }

    int makeSolider(int time, const int *order, char* str, int count) {
        if(count==5) {
            printf("%03d %s headquarter stops making warriors\n", time, str);
            return 0;
        }
        if (healthPoint >= healthPointList[order[createIndex % 5]]) {
            Solider *solider = _SoliderCreate[order[createIndex % 5]](++soliderIndex);
            soliderList.push_back(solider);

            soliderNumber[order[createIndex % 5]]++;
            soliderTotalNumber++;
            healthPoint -= healthPointList[order[createIndex % 5]];

            myprint(time, str, order[createIndex % 5], soliderIndex, soliderNumber[order[createIndex % 5]]);
            createIndex++;
            createIndex%=5;
            return 1;
        }
        else {
            createIndex++;
            createIndex%=5;
            return makeSolider(time, order, str, count+1);
        }
    }

};

int makeOrderA[5] = {2, 3, 4, 1, 0}, makeOrderB[5] = {3, 0, 1, 2, 4};

int init(){
    mytime=0;
    //scanf("%d", &maxtime);
    scanf("%d%d%d%d%d", &healthPointList[0], &healthPointList[1], &healthPointList[2], &healthPointList[3],
          &healthPointList[4]);
}


int deal() {
    int cycle;
    scanf("%d", &cycle);
    _SoliderCreate[0]=Dragon::create;
    _SoliderCreate[1]=Ninja::create;
    _SoliderCreate[2]=Iceman::create;
    _SoliderCreate[3]=Lion::create;
    _SoliderCreate[4]=Wolf::create;
    int count=0;
    while (count<cycle) {
        count++;
        cout<<"Case:"<<count<<endl;
        unsigned int HP;
        scanf("%d", &HP);
        init();
        Headquarter A(HP), B(HP);
        bool a=true, b=true;
        while (a||b){
            //printf("%d\n", mytime);
            if(a){
                if(!A.makeSolider(mytime, makeOrderA, "red", 0)){
                    a=false;
                }
            }
            if(b){
                if(!B.makeSolider(mytime, makeOrderB, "blue", 0)){
                    b=false;
                }
            }
            mytime++;
        }
    }
}

int main() {
    deal();

    return 0;
}