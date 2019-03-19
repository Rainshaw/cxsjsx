#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <functional>


using namespace std;

unsigned int mytime;

unsigned int healthPointList[5];
char *soliderTypeName[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};

unsigned int weapon[3];
char *weaponTypeName[3] = {"sword", "bomb", "arrow"};

int makeOrderA[5] = {2, 3, 4, 1, 0}, makeOrderB[5] = {3, 0, 1, 2, 4};


class Solider {
private:
    unsigned int healthPoint;
    unsigned int No;
public:
    explicit Solider(unsigned int HP, unsigned int No) : healthPoint(HP), No(No) {};

    virtual ~Solider() = default;;

    virtual void makeWeapon(int No){};

    virtual double getMorale(){};

    virtual vector<int> getWeaponList(){};

    virtual int getLoyalty(){};
};

class Dragon : public Solider {
private:
    vector<int> weaponList;
    double morale;
public:
    explicit Dragon(unsigned int No, unsigned int headquarterLeftHP) : Solider(healthPointList[0], No) {
        makeWeapon(No);
        morale = (double) headquarterLeftHP / (double) healthPointList[0];
    }

    static Dragon *create(unsigned int No, unsigned int headquarterLeftHP) {
        return new Dragon(No, headquarterLeftHP);
    }

    void makeWeapon(int No) override {
        weaponList.push_back(No % 3);
    }

    double getMorale() override {
        return morale;
    }

    vector<int> getWeaponList() override {
        return weaponList;
    }

};

class Ninja : public Solider {
private:
    vector<int> weaponList;
public:
    explicit Ninja(unsigned int No) : Solider(healthPointList[1], No) {
        makeWeapon(No);
    }

    static Ninja *create(unsigned int No, unsigned int headquarterLeftHP) {
        return new Ninja(No);
    }

    void makeWeapon(int No) override {
        weaponList.push_back(No % 3);
        weaponList.push_back((No + 1) % 3);
    }

    vector<int> getWeaponList() override {
        return weaponList;
    }

};

class Iceman : public Solider {
private:
    vector<int> weaponList;
public:
    explicit Iceman(unsigned int No) : Solider(healthPointList[2], No) {
        makeWeapon(No);
    }

    static Iceman *create(unsigned int No, unsigned int headquarterLeftHP) {
        return new Iceman(No);
    }

    void makeWeapon(int No) override {
        weaponList.push_back(No % 3);
    }

    vector<int> getWeaponList() override {
        return weaponList;
    }

};

class Lion : public Solider {
private:
    int loyalty;
public:
    explicit Lion(unsigned int No, unsigned int headquarterLeftHP) : Solider(healthPointList[3], No) {
        loyalty = headquarterLeftHP;
    }

    static Lion *create(unsigned int No, unsigned int headquarterLeftHP) {
        return new Lion(No, headquarterLeftHP);
    }

    int getLoyalty() override {
        return loyalty;
    }
};

class Wolf : public Solider {
private:

public:
    explicit Wolf(unsigned int No) : Solider(healthPointList[4], No) {

    }

    static Wolf *create(unsigned int No, unsigned int headquarterLeftHP) {
        return new Wolf(No);
    }
};

typedef function<Solider *(unsigned int, unsigned int)> SoliderCreateType;

map<unsigned int, SoliderCreateType> _SoliderCreate;


void myprint(Solider* solider, int tim, char *str, int soliderType, int soliderIndex, int soliderNum) {
    printf("%03d ", tim);
    printf("%s %s %d born with strength %d,%d %s in %s headquarter\n", str, soliderTypeName[soliderType], soliderIndex,
           healthPointList[soliderType], soliderNum, soliderTypeName[soliderType], str);
    switch (soliderType){
        case 0:
            printf("It has a %s,and it's morale is %.2f\n", weaponTypeName[solider->getWeaponList()[0]],solider->getMorale());
            break;
        case 1:
            printf("It has a %s and a %s\n", weaponTypeName[solider->getWeaponList()[0]], weaponTypeName[solider->getWeaponList()[1]]);
            break;
        case 2:
            printf("It has a %s\n", weaponTypeName[solider->getWeaponList()[0]]);
            break;
        case 3:
            printf("It's loyalty is %d\n", solider->getLoyalty());
            break;
        default:
            break;
    }
    return;
}

class Headquarter {
private:
    vector<Solider *> soliderList;
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

    int makeSolider(int time, const int *order, char *str, int count) {
        if (count == 5) {
            printf("%03d %s headquarter stops making warriors\n", time, str);
            return 0;
        }
        if (healthPoint >= healthPointList[order[createIndex % 5]]) {
            int soliderTypeIndex=order[createIndex%5];
            healthPoint -= healthPointList[soliderTypeIndex];

            Solider *solider = _SoliderCreate[soliderTypeIndex](++soliderIndex, healthPoint);
            soliderList.push_back(solider);

            soliderNumber[soliderTypeIndex]++;
            soliderTotalNumber++;


            myprint( solider, time, str, soliderTypeIndex, soliderIndex, soliderNumber[soliderTypeIndex]);

            createIndex++;
            createIndex %= 5;
            return 1;
        } else {
            createIndex++;
            createIndex %= 5;
            return makeSolider(time, order, str, count + 1);
        }
    }

};



int init() {
    mytime = 0;

    scanf("%d%d%d%d%d", &healthPointList[0], &healthPointList[1], &healthPointList[2], &healthPointList[3],
          &healthPointList[4]);
}


int deal() {
    int cycle;
    scanf("%d", &cycle);
    _SoliderCreate[0] = Dragon::create;
    _SoliderCreate[1] = Ninja::create;
    _SoliderCreate[2] = Iceman::create;
    _SoliderCreate[3] = Lion::create;
    _SoliderCreate[4] = Wolf::create;
    int casecount=0;
    while (casecount<cycle) {
        cout<<"Case:"<<++casecount<<endl;
        unsigned int HP;
        scanf("%d", &HP);
        init();
        Headquarter A(HP), B(HP);
        bool a = true, b = true;
        while (a || b) {
            //printf("%d\n", mytime);
            if (a) {
                if (!A.makeSolider(mytime, makeOrderA, "red", 0)) {
                    a = false;
                }
            }
            if (b) {
                if (!B.makeSolider(mytime, makeOrderB, "blue", 0)) {
                    b = false;
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