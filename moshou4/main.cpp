#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <functional>
#include <list>
#include <algorithm>
#include <cassert>

using namespace std;

int M, N, R, K, T;

int OriginHP[5];
int OriginSoliderATK[5];

char *soliderName[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
char *weaponName[3] = {"sword", "bomb", "arrow"};

int makeOrderRed[5] = {2, 3, 4, 1, 0}, makeOrderBlue[5] = {3, 0, 1, 2, 4};

class Weapon {
public:
    int ATK;
    int ATKself;
    bool useful = true;
    int usedTimes;
    int no;

    Weapon(int atk, int atkself = 0, int tim = 0) : ATK(atk), ATKself(atkself), usedTimes(tim) {
//        printf("Weapon with %d atk & %d atkself was built! Its usetime is %d\n", atk, atkself, tim);
    }

    virtual int use() {}

};

class Sword : public Weapon {
public:
    Sword(int SoliderATK) : Weapon(SoliderATK * 2 / 10) {
//        printf("Sword with %d atk was built!\n", SoliderATK * 2 / 10);
        no = 0;
    }

    int use() override {
//        printf("Use Sword with %d atk!\n", Weapon::ATK);
        int atk = ATK;
        ATK = atk * 8 / 10;
        if (ATK == 0)
            Weapon::useful = false;
        return atk;
    }

    static Sword *create(int SoliderATK) {
        return new Sword(SoliderATK);
    }

};

class Bomb : public Weapon {
public:
    Bomb(int SoliderATK) : Weapon(0) {
//        printf("Bomb was built!\n");
        no = 1;
    }

    int use() override {
        Weapon::useful = false;
//        printf("Use Bomb!\n");
        return Weapon::ATK;
    }

    static Bomb *create(int SoliderATK) {
        return new Bomb(SoliderATK);
    }
};

class Arrow : public Weapon {
public:
    Arrow(int SoliderATK) : Weapon(R) {
//        printf("Arrow with %d atk was built!\n", R);
        no = 2;
    }

    int use() override {
        Weapon::usedTimes++;
//        printf("Use Arrow with %d atk!\n", Weapon::ATK);
        if (Weapon::usedTimes == 3)
            Weapon::useful = false;
        return Weapon::ATK;
    }

    static Arrow *create(int SoliderATK) {
        return new Arrow(SoliderATK);
    }
};

typedef function<Weapon *(int)> CreateWeaponFunction;
map<int, CreateWeaponFunction> CreateWeapon;

//bool lostWeaponCompare(Weapon *weapon1, Weapon *weapon2) {
//    if (weapon1->no < weapon2->no)
//        return true;
//    else if (weapon1->no == weapon2->no) {
//        return weapon1->usedTimes < weapon2->usedTimes;
//    } else
//        return false;
//}
//
//bool warWeaponCompare(Weapon *weapon1, Weapon *weapon2) {
//    if (weapon1->no < weapon2->no)
//        return true;
//    else if (weapon1->no == weapon2->no) {
//        return weapon1->usedTimes > weapon2->usedTimes;
//    } else
//        return false;
//}

class Solider {
public:
//    Weapon *weapon[10];
    int position;
    int HP;
    int No;
    int type;
    int ATK;
    int team = 1;
    int loyalty;
    double morale;
//    int weaponIndex = 0;
//    int weaponNum[3] = {0, 0, 0};
//    int weaponSum = 0;
    Weapon *weaponList[3];

    Solider(int no, int hp, int atk, int pos, int typ) : No(no), HP(hp), ATK(atk), position(pos), type(typ) {
        //printf("Solider No.%d with %d HP was built at city %d! Its att is %d\n", no, hp, pos, atk);
        memset(weaponList, 0, sizeof(weaponList));
    }

    void setTeam() {
        team = -1;
    }

    virtual ~Solider() {
//        for (int i = 0; i < 10; i++) {
//            if (weapon[i]) {
//                printf("Solider No.%d 's weapon %d was delete!\n", Solider::No, i);
//                delete weapon[i];
//            }
//        }
//        printf("Solider No.%d with %d HP was delete!\n", No, HP);

    }

    virtual int setLoyalty(int headquarterLeftHP) {}

    virtual double setMorale(int headquarterLeftHP) {}

    virtual void goForward() {}

    virtual int escape() {
        return 0;
    }

    virtual void addMorale() {};

    virtual void decreaseMorale() {}

    virtual void decreaseLoyalty(){}

//    void lostSortWeapon() {
//        int num = 0;
//        while (weapon[num])
//            num++;
//        sort(weapon, weapon + num, lostWeaponCompare);
//    }

//    void sortWeapon() {
//        int num = 0;
//        while (weapon[num])
//            num++;
//        sort(weapon, weapon + num, warWeaponCompare);
//        weaponIndex = 0;
//        weaponSum = num;
//    }

//    void countWeapon() {
//        memset(weaponNum, 0, sizeof(weaponNum));
//        for (int i = 0; i < 10; i++) {
//            if (weapon[i]) {
//                weaponNum[weapon[i]->no]++;
//            }
//        }
//    }

    bool isalive() {
        return HP > 0;
    }

//    void delWeapon(int index) {
//        delete weapon[index];
//        weapon[index] = nullptr;
//
//        for (; index < weaponSum - 1; index++) {
//            weapon[index] = weapon[index + 1];
//            weapon[index + 1] = nullptr;
//        }
//
//        weaponSum--;
//
//    }

//    virtual int useWeapon() {
//        if (weapon[0] == nullptr) {
//            return 0;
//        }
//        weaponIndex = weaponIndex % weaponSum;
//        weapon[weaponIndex]->updateATK(ATK);
//        int type = weapon[weaponIndex]->no;
//        if (type == 1)
//            HP -= weapon[weaponIndex]->ATKself;
//        int atk = weapon[weaponIndex]->use();
//        if (!weapon[weaponIndex]->useful) {
//            delWeapon(weaponIndex);
//            return atk;
//        }
//        weaponIndex++;
//        return atk;
//    }

    virtual void checkWeaponUseful() {
        if (weaponList[0] && weaponList[0]->ATK == 0) {
            delete weaponList[0];
            weaponList[0] = nullptr;
        }
    }

    virtual int attack() {
        int atk = ATK + ((weaponList[0] != nullptr) ? weaponList[0]->use() : 0);
        if (weaponList[0]&&!weaponList[0]->useful) {
            delete weaponList[0];
            weaponList[0] = nullptr;
        }
        return atk;
    }

    virtual int attackInTurn() {
        int atk = ATK / 2 + ((weaponList[0] != nullptr) ? weaponList[0]->use() : 0);
        if (weaponList[0]&&!weaponList[0]->useful) {
            delete weaponList[0];
            weaponList[0] = nullptr;
        }
        return atk;
    }

    virtual bool useBomb(Solider *anotherSolider, int flag) {
        if (this->weaponList[1]) {
            if(flag==team) {
                if (
                        (anotherSolider->HP - this->ATK -
                         ((this->weaponList[0] != nullptr) ? this->weaponList[0]->ATK : 0) > 0)
                        &&(anotherSolider->type!=1)&&(this->HP - anotherSolider->ATK / 2 -
                            ((anotherSolider->weaponList[0] != nullptr) ? anotherSolider->weaponList[0]->ATK : 0) <= 0)
                        )
                    return true;
            }
            else {
                if(this->HP - anotherSolider->ATK -((anotherSolider->weaponList[0] != nullptr)? anotherSolider->weaponList[0]->ATK : 0) <= 0)
                    return true;
            }
            return false;

//            if (
//                    (
//                    (anotherSolider->HP - this->ATK - ((this->weaponList[0] != nullptr) ? this->weaponList[0]->ATK : 0) > 0)
//                    && (this->HP - anotherSolider->ATK / 2 - ((anotherSolider->weaponList[0] != nullptr)? anotherSolider->weaponList[0]->ATK : 0) <= 0)
//                    )
//            || (this->HP - anotherSolider->ATK -((anotherSolider->weaponList[0] != nullptr)? anotherSolider->weaponList[0]->ATK : 0) <= 0))
//                return true;
        }
        return false;
    }

    virtual void yep(int mytime) {}

    bool hasWeapon() {
        return (weaponList[0] != nullptr) || (weaponList[1] != nullptr) || (weaponList[2] != nullptr);
    }

};

class City {
public:
    Solider *cityredsolider;
    Solider *citybluesolider;

    int HP;
    int flag;
    int lastwarwinner;
    int thiswarwinner;


    City() {
        cityredsolider = citybluesolider = nullptr;
        HP = 0;
        flag = 0;
        lastwarwinner = 0;
        thiswarwinner = 0;
    }

    ~City() {
//        if (cityredsolider) {
//            delete cityredsolider;
//            cityredsolider = nullptr;
//        }
//        if (citybluesolider) {
//            delete citybluesolider;
//            citybluesolider = nullptr;
//        }
    }
};

City *city;

class Dragon : public Solider {
public:

    Dragon(int no, int pos) : Solider(no, OriginHP[0], OriginSoliderATK[0], pos, 0) {
        //printf("Dragon No.%d with %d HP was built! Its att is %d\n", no, OriginHP[0], OriginSoliderATK[0]);
        weaponList[no % 3] = CreateWeapon[no % 3](OriginSoliderATK[0]);
        Solider::checkWeaponUseful();
    }

    ~Dragon() override {
        for (int i = 0; i < 3; i++) {
            if (weaponList[i]) {
                //printf("Dragon No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weaponList[i];
                weaponList[i] = nullptr;
            }
        }
        //printf("Dragon No.%d with %d HP was delete at city %d!\n", Solider::No, Solider::HP, Solider::position);
    }

    double setMorale(int headquarterLeftHP) override {
        morale = ((double) headquarterLeftHP) / OriginHP[0];
        return morale;
    }

    void addMorale() override {
        morale += 0.2;
    }

    void decreaseMorale() override {
        morale -= 0.2;
    }

    static Dragon *create(int no, int pos) {
        return new Dragon(no, pos);
    }

    void goForward() override {
        Solider::position += Solider::team;
        //printf("Dragon No.%d with %d HP is in city %d now!\n", Solider::No, Solider::HP, Solider::position);
    }

    void yep(int mytime) {
        if (morale > 0.8) {
            if (team == 1)
                printf("%03d:40 red dragon %d yelled in city %d\n", mytime, No, position);
            else
                printf("%03d:40 blue dragon %d yelled in city %d\n", mytime, No, position);
        }
    }

};

class Ninja : public Solider {
public:

    Ninja(int no, int pos) : Solider(no, OriginHP[1], OriginSoliderATK[1], pos, 1) {
        //printf("Ninga No.%d with %d HP was built at city %d! Its att is %d\n", no, OriginHP[1], pos, OriginSoliderATK[1]);
        weaponList[no % 3] = CreateWeapon[no % 3](OriginSoliderATK[1]);
        weaponList[(no + 1) % 3] = CreateWeapon[(no + 1) % 3](OriginSoliderATK[1]);
        Solider::checkWeaponUseful();
    }

    ~Ninja() override {
        for (int i = 0; i < 3; i++) {
            if (weaponList[i]) {
                //printf("Ninja No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weaponList[i];
                weaponList[i] = nullptr;
            }
        }
        //printf("Ninja No.%d with %d HP was delete at city %d!\n", Solider::No, Solider::HP, Solider::position);
    }

    static Ninja *create(int no, int pos) {
        return new Ninja(no, pos);
    }

    void goForward() override {
        Solider::position += Solider::team;
        //printf("Ninja No.%d with %d HP is in city %d now!\n", Solider::No, Solider::HP, Solider::position);
    }

    int attackInTurn() override {
        return 0;
    }

    /*
    int useWeapon() {
        if (weapon[0] == nullptr) {
            return 0;
        }
        weaponIndex = weaponIndex % weaponSum;
        weapon[weaponIndex]->updateATK(ATK);
        int type = weapon[weaponIndex]->no;

        int atk = weapon[weaponIndex]->use();
        if (!weapon[weaponIndex]->useful) {
            Solider::delWeapon(weaponIndex);
            return atk;
        }
        weaponIndex++;
        return atk;
    }
     */

};

class Iceman : public Solider {
    int goTime = 0;
public:

    Iceman(int no, int pos) : Solider(no, OriginHP[2], OriginSoliderATK[2], pos, 2) {
        //printf("Iceman No.%d with %d HP was built at city %d! Its att is %d\n", no, OriginHP[2], pos, OriginSoliderATK[2]);
        weaponList[no % 3] = CreateWeapon[no % 3](OriginSoliderATK[2]);
        Solider::checkWeaponUseful();
    }

    ~Iceman() override {
        for (int i = 0; i < 3; i++) {
            if (weaponList[i]) {
                //printf("Iceman No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weaponList[i];
                weaponList[i] = nullptr;
            }
        }
        //printf("Iceman No.%d with %d HP was delete at city %d!\n", Solider::No, Solider::HP, Solider::position);
    }

    static Iceman *create(int no, int pos) {
        return new Iceman(no, pos);
    }

    void goForward() override {
        goTime++;
        Solider::position += Solider::team;
        if ((goTime % 2) == 0) {
            if (HP >= 10)
                HP -= 9;
            else
                HP = 1;
            ATK += 20;
        }
        //printf("Iceman No.%d with %d HP is in city %d now!\n", Solider::No, Solider::HP, Solider::position);
    }

};

class Lion : public Solider {

public:


    Lion(int no, int pos) : Solider(no, OriginHP[3], OriginSoliderATK[3], pos, 3) {
        //printf("Lion No.%d with %d HP was built at city %d! Its att is %d\n", no, OriginHP[3], pos, OriginSoliderATK[3]);
//        weaponList[no % 3] = CreateWeapon[no % 3](OriginSoliderATK[3]);
//        Solider::checkWeaponUseful();
    }

    ~Lion() override {
        for (int i = 0; i < 3; i++) {
            if (weaponList[i]) {
                //printf("Lion No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weaponList[i];
                weaponList[i] = nullptr;
            }
        }
        //printf("Lion No.%d with %d HP was delete at city %d!\n", Solider::No, Solider::HP, Solider::position);
    }

    int setLoyalty(int headquarterLeftHP) override {
        loyalty = headquarterLeftHP;
        return loyalty;
    }

    static Lion *create(int no, int pos) {
        return new Lion(no, pos);
    }

    void goForward() override {
        Solider::position += Solider::team;
        //loyalty -= K;
        //printf("Lion No.%d with %d HP & %d loyalty is in city %d now!\n", Solider::No, Solider::HP, loyalty, Solider::position);
    }

    int escape() override {
        if (position == N + 1 && team == 1 || position == 0 && team == -1)
            return 0;
        if (loyalty <= 0)
            return 1;
        return 0;
    }

    void decreaseLoyalty(){
        loyalty-=K;
    }

};

class Wolf : public Solider {
public:

    Wolf(int no, int pos) : Solider(no, OriginHP[4], OriginSoliderATK[4], pos, 4) {
        //printf("Wolf No.%d with %d HP was built at city %d! Its att is %d\n", no, OriginHP[4], pos, OriginSoliderATK[4]);
    }

    ~Wolf() override {
        for (int i = 0; i < 3; i++) {
            if (weaponList[i]) {
                //printf("Wolf No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weaponList[i];
                weaponList[i] = nullptr;
            }
        }
        //printf("Wolf No.%d with %d HP was delete at city!\n", Solider::No, Solider::HP);
    }

    static Wolf *create(int no, int pos) {
        return new Wolf(no, pos);
    }

    void goForward() override {
        Solider::position += Solider::team;
        //printf("Wolf No.%d with %d HP is in city %d now!\n", Solider::No, Solider::HP, Solider::position);
    }
};

typedef function<Solider *(int, int)> CreateSoliderFunction;
map<int, CreateSoliderFunction> CreateSolider;


class HeadQuarter {
public:
    list<Solider *> soliderList;
    int healthPoint;
    int position;
    int createIndex;
    int soliderIndex;


    HeadQuarter(int pos) : healthPoint(M), position(pos) {
        while (!soliderList.empty()) {
            delete soliderList.back();
            soliderList.pop_back();
        }
        createIndex = 0;
        soliderIndex = 0;
    }

    ~HeadQuarter() {

        list<Solider *>::iterator iter;
//        for(iter=soliderList.begin();iter!=soliderList.end();++iter){
//            cout<<(*iter)->No<<endl;
//        }

        while (!soliderList.empty()) {
            delete soliderList.back();
            soliderList.pop_back();
        }
    }

    int makeSolider(int time, const int *order, int flag = 0) {
        string str = position ? "blue" : "red";

        if (healthPoint >= OriginHP[order[createIndex % 5]]) {
            int soliderTypeIndex = order[createIndex % 5];
            healthPoint -= OriginHP[soliderTypeIndex];

            Solider *solider = CreateSolider[soliderTypeIndex](++soliderIndex, position);

            if (flag) {
                solider->setTeam();
                city[position].citybluesolider = solider;
            } else
                city[position].cityredsolider = solider;

            soliderList.push_back(solider);

            printf("%03d:00 %s %s %d born\n", time, str.c_str(), soliderName[soliderTypeIndex], soliderIndex);

            if (soliderTypeIndex == 3)
                printf("Its loyalty is %d\n", solider->setLoyalty(healthPoint));

            if (soliderTypeIndex == 0)
                printf("Its morale is %.2f\n", solider->setMorale(healthPoint));

            createIndex++;
            return 1;
        }
    }

};

HeadQuarter *RedTeam, *BlueTeam;

void make(int mytime) {
//    cout << mytime << "make\n";
    RedTeam->makeSolider(mytime, makeOrderRed);
    BlueTeam->makeSolider(mytime, makeOrderBlue, 1);
}

void escape(int mytime) {
//    cout << mytime << "escape\n";
    for (int i = 0; i <= N + 1; i++) {
        if (city[i].cityredsolider) {
            if (city[i].cityredsolider->escape()) {
                Solider *solider = city[i].cityredsolider;
                printf("%03d:05 red lion %d ran away\n", mytime, solider->No);

                city[i].cityredsolider = nullptr;
                RedTeam->soliderList.remove(solider);

                delete solider;
            }
        }
        if (city[i].citybluesolider) {
            if (city[i].citybluesolider->escape()) {
                Solider *solider = city[i].citybluesolider;
                printf("%03d:05 blue lion %d ran away\n", mytime, solider->No);

                city[i].citybluesolider = nullptr;
                BlueTeam->soliderList.remove(solider);

                delete solider;
            }
        }
    }
}

void reachEnemy(int mytime, int pos) {
    if (pos == N + 1) {
        Solider *solider = city[N + 1].cityredsolider;

        printf("%03d:10 red %s %d reached blue headquarter with %d elements and force %d\n",
               mytime, soliderName[makeOrderRed[(solider->No - 1) % 5]], solider->No, solider->HP, solider->ATK);


    } else if (pos == 0) {
        Solider *solider = city[0].citybluesolider;

        printf("%03d:10 blue %s %d reached red headquarter with %d elements and force %d\n",
               mytime, soliderName[makeOrderBlue[(solider->No - 1) % 5]], solider->No, solider->HP, solider->ATK);


    }
}

void victory(int mytime, int pos) {
    if (pos == N + 1)
        printf("%03d:10 blue headquarter was taken\n", mytime);
    else if (pos == 0)
        printf("%03d:10 red headquarter was taken\n", mytime);
}

bool goForward(int mytime) {
//    cout << mytime << "go forward\n";
    bool end1 = false, end2 = false;

    Solider *soliderredwest, *soliderredhere;

    if (city[1].citybluesolider) {
        if (city[0].citybluesolider) {
            end1 = true;
        }

        city[0].citybluesolider = city[1].citybluesolider;
        city[1].citybluesolider = nullptr;

        Solider *solider = city[0].citybluesolider;
        solider->goForward();
//        printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n", mytime,
//               soliderName[makeOrderBlue[(solider->No - 1) % 5]], solider->No, solider->position, solider->HP,
//               solider->ATK);
        reachEnemy(mytime, 0);

        if (end1)
            victory(mytime, 0);
    }

    soliderredwest = city[0].cityredsolider;
    city[0].cityredsolider = nullptr;

    for (int i = 1; i <= N; i++) {
        soliderredhere = city[i].cityredsolider;

        city[i].cityredsolider = soliderredwest;
        soliderredwest = soliderredhere;

        Solider *solider = city[i].cityredsolider;
        if (solider) {
            solider->goForward();
            printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n", mytime,
                   soliderName[makeOrderRed[(solider->No - 1) % 5]], solider->No, solider->position, solider->HP,
                   solider->ATK);
        }

        city[i].citybluesolider = city[i + 1].citybluesolider;
        city[i + 1].citybluesolider = nullptr;

        solider = city[i].citybluesolider;
        if (solider) {
            solider->goForward();
            printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n", mytime,
                   soliderName[makeOrderBlue[(solider->No - 1) % 5]], solider->No, solider->position, solider->HP,
                   solider->ATK);
        }
    }

    if (soliderredwest) {
        if (city[N + 1].cityredsolider) {
            end2 = true;
        }

        city[N + 1].cityredsolider = soliderredwest;

        Solider *solider = city[N + 1].cityredsolider;
        solider->goForward();

        reachEnemy(mytime, N + 1);

//        printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n", mytime,
//               soliderName[makeOrderBlue[(solider->No - 1) % 5]], solider->No, solider->position, solider->HP,
//               solider->ATK);

        if (end2)
            victory(mytime, N + 1);
    }

    if (end1 || end2) {
        return true;
    }
    return false;
}

void cityProduceHP(int mytime) {
//    cout<<"cityProduceHP\n";
    for (int i = 1; i <= N; i++) {
        city[i].HP += 10;
        city[i].thiswarwinner = 100;
    }
}

void noWarCity(int mytime) {
//    cout<<"NoWarCity\n";
    for (int i = 1; i <= N; i++) {
        if (city[i].citybluesolider != nullptr && city[i].cityredsolider == nullptr) {
            BlueTeam->healthPoint += city[i].HP;
            printf("%03d:30 blue %s %d earned %d elements for his headquarter\n", mytime,
                   soliderName[city[i].citybluesolider->type], city[i].citybluesolider->No, city[i].HP);
            city[i].HP = 0;
            city[i].thiswarwinner = 100;
        } else if (city[i].citybluesolider == nullptr && city[i].cityredsolider != nullptr) {
            RedTeam->healthPoint += city[i].HP;
            printf("%03d:30 red %s %d earned %d elements for his headquarter\n", mytime,
                   soliderName[city[i].cityredsolider->type], city[i].cityredsolider->No, city[i].HP);
            city[i].HP = 0;
            city[i].thiswarwinner = 100;
        }
    }
}

void longSeeSoliderUseArrow(int mytime) {
//    cout<<"longSeeSoliderUseArrow\n";
    for (int i = 1; i <= N; i++) {
        Solider *solider1 = city[i].cityredsolider;
        if (solider1 && solider1->weaponList[2] && city[i + 1].citybluesolider) {
            Solider *solider2 = city[i + 1].citybluesolider;
            solider2->HP -= solider1->weaponList[2]->use();
            if (!solider1->weaponList[2]->useful) {
                delete solider1->weaponList[2];
                solider1->weaponList[2] = nullptr;
            }

            if (!solider2->isalive()) {
                printf("%03d:35 red %s %d shot and killed blue %s %d\n", mytime, soliderName[solider1->type],
                       solider1->No, soliderName[solider2->type], solider2->No);
            } else {
                printf("%03d:35 red %s %d shot\n", mytime, soliderName[solider1->type], solider1->No);
            }

        }
        solider1 = city[i].citybluesolider;
        if (solider1 && solider1->weaponList[2] && city[i - 1].cityredsolider) {
            Solider *solider2 = city[i - 1].cityredsolider;
            solider2->HP -= solider1->weaponList[2]->use();
            if (!solider1->weaponList[2]->useful) {
                delete solider1->weaponList[2];
                solider1->weaponList[2] = nullptr;
            }

            if (!solider2->isalive()) {
                printf("%03d:35 blue %s %d shot and killed red %s %d\n", mytime, soliderName[solider1->type],
                       solider1->No, soliderName[solider2->type], solider2->No);
            } else {
                printf("%03d:35 blue %s %d shot\n", mytime, soliderName[solider1->type], solider1->No);
            }

        }
    }
}

void cleverSoliderUseBomb(int mytime) {
//    cout<<"cleverSoliderUseBomb\n";
    for (int i = 1; i <= N; i++) {
//        cout<<"UseBombJudge"<<i<<endl;
        if (city[i].citybluesolider && city[i].cityredsolider) {
            if (city[i].citybluesolider->isalive() && city[i].cityredsolider->isalive()) {
                Solider *solider1 = city[i].cityredsolider;
                Solider *solider2 = city[i].citybluesolider;

                int flag=((city[i].flag!=0)?city[i].flag:((i%2==0)?-1:1));

                if (solider1->useBomb(solider2, flag)) {
                    solider1->HP = -1;
                    solider2->HP = -1;
                    printf("%03d:38 red %s %d used a bomb and killed blue %s %d\n", mytime, soliderName[solider1->type],
                           solider1->No, soliderName[solider2->type], solider2->No);
                } else if (solider2->useBomb(solider1, flag)) {
                    solider1->HP = -1;
                    solider2->HP = -1;
                    printf("%03d:38 blue %s %d used a bomb and killed red %s %d\n", mytime, soliderName[solider2->type],
                           solider2->No, soliderName[solider1->type], solider1->No);
                }
            }
        }
    }
}


void afterWar(int mytime) {
//    cout<<"afterWar\n";
    //奖励生命元
    for (int i = 1; i <= N; i++) {
        if (city[i].thiswarwinner == -1) {
            if (BlueTeam->healthPoint >= 8) {
                BlueTeam->healthPoint -= 8;
                city[i].citybluesolider->HP += 8;
            }
        }
        if (city[N + 1 - i].thiswarwinner == 1) {
            if (RedTeam->healthPoint >= 8) {
                RedTeam->healthPoint -= 8;
                city[N + 1 - i].cityredsolider->HP += 8;
            }
        }
    }

    //回收生命元
    for (int i = 1; i <= N; i++) {
        if (city[i].thiswarwinner == 1) {
            RedTeam->healthPoint += city[i].HP;
            city[i].HP = 0;
        } else if (city[i].thiswarwinner == -1) {
            BlueTeam->healthPoint += city[i].HP;
            city[i].HP = 0;
        }
    }

    //改变旗子
//    for (int i = 1; i <= N; i++) {
//        if (city[i].thiswarwinner == 100) {
//            continue;
//        } else if (city[i].thiswarwinner == 0) {
//            city[i].lastwarwinner = 0;
//        } else if (city[i].thiswarwinner == 1) {
//            if (city[i].lastwarwinner == 1) {
//                city[i].flag = 1;
//                printf("%03d:40 red flag raised in city %d\n", mytime, i);
//            } else {
//                city[i].lastwarwinner = 1;
//            }
//        } else if (city[i].thiswarwinner == -1) {
//            if (city[i].lastwarwinner == -1) {
//                city[i].flag = -1;
//                printf("%03d:40 blue flag raised in city %d\n", mytime, i);
//            } else {
//                city[i].lastwarwinner = -1;
//            }
//        }
//    }


}

/*
void wolfSteal(int mytime) {
    //cout << mytime << "wolfSteal\n";
    for (int i = 1; i <= N; i++) {
        if (city[i].cityredsolider && city[i].citybluesolider) {
            Solider *solider1, *solider2;
            solider1 = city[i].cityredsolider;
            solider2 = city[i].citybluesolider;

            if (makeOrderRed[(solider1->No - 1) % 5] == 4) {
                if (makeOrderBlue[(solider2->No - 1) % 5] == 4)
                    continue;

                int index = 0;
                while (solider1->weapon[index])
                    index++;
                solider2->lostSortWeapon();
                int count[3] = {0, 0, 0};

                //solider2->countWeapon();
                //printf("%d %d %d\n", solider2->weaponNum[0],solider2->weaponNum[1],solider2->weaponNum[2]);

                int no = (solider2->weapon[0]) ? solider2->weapon[0]->no : -1;

                while (index < 10 && solider2->weapon[0] && solider2->weapon[0]->no == no) {
                    solider1->weapon[index] = solider2->weapon[0];
                    count[solider1->weapon[index]->no]++;
                    int x;
                    for (x = 1; solider2->weapon[x]; x++)
                        solider2->weapon[x - 1] = solider2->weapon[x];
                    solider2->weapon[x - 1] = nullptr;
                    index++;
                }
                if (count[0] || count[1] || count[2]) {
                    printf("%03d:35 red wolf %d took ", mytime, solider1->No);
                    if (count[0]) {
                        printf("%d sword ", count[0]);
                    }
                    if (count[1]) {
                        printf("%d bomb ", count[1]);
                    }
                    if (count[2]) {
                        printf("%d arrow ", count[2]);
                    }
                    printf("from blue %s %d in city %d\n", soliderName[makeOrderBlue[(solider2->No - 1) % 5]],
                           solider2->No, solider1->position);
                }
            } else if (makeOrderBlue[(solider2->No - 1) % 5] == 4) {
                int index = 0;
                while (solider2->weapon[index])
                    index++;
                solider1->lostSortWeapon();
                int count[3] = {0, 0, 0};

                //solider1->countWeapon();
                //printf("%d %d %d\n", solider1->weaponNum[0],solider1->weaponNum[1],solider1->weaponNum[2]);

                int no = (solider1->weapon[0]) ? solider1->weapon[0]->no : -1;

                while (index < 10 && solider1->weapon[0] && solider1->weapon[0]->no == no) {
                    solider2->weapon[index] = solider1->weapon[0];
                    count[solider2->weapon[index]->no]++;
                    int x;
                    for (x = 1; solider1->weapon[x]; x++)
                        solider1->weapon[x - 1] = solider1->weapon[x];
                    solider1->weapon[x - 1] = nullptr;
                    index++;
                }
                if (count[0] || count[1] || count[2]) {
                    printf("%03d:35 blue wolf %d took ", mytime, solider2->No);
                    if (count[0]) {
                        printf("%d sword ", count[0]);
                    }
                    if (count[1]) {
                        printf("%d bomb ", count[1]);
                    }
                    if (count[2]) {
                        printf("%d arrow ", count[2]);
                    }
                    printf("from red %s %d in city %d\n", soliderName[makeOrderRed[(solider1->No - 1) % 5]],
                           solider1->No, solider1->position);
                }
            }
        }
    }
}
 */

//void warGetWeapon(Solider *solider1, Solider *solider2) {
//    solider2->lostSortWeapon();
//
//    int index = solider1->weaponSum;
//    for (int i = 0; index < 10; index++) {
//        solider1->weapon[index] = solider2->weapon[i];
//        solider2->weapon[i] = nullptr;
//        i++;
//    }
//}


void war(int mytime) {
//    cout << mytime << "war\n";
    for (int i = 1; i <= N; ++i) {
//        cout<<i<<endl;
        if (city[i].citybluesolider && city[i].cityredsolider) {
            Solider *solider1 = city[i].cityredsolider;
            Solider *solider2 = city[i].citybluesolider;
            if (!solider1->isalive() && !solider2->isalive()) {
                RedTeam->soliderList.remove(solider1);
                city[i].cityredsolider = nullptr;
                delete solider1;
                solider1 = nullptr;

                BlueTeam->soliderList.remove(solider2);
                city[i].citybluesolider = nullptr;
                delete solider2;
                solider2 = nullptr;

                city[i].thiswarwinner = 100;

            } else if (!solider1->isalive() && solider2->isalive()) {
                if (city[i].flag == -1 || (city[i].flag == 0 && i % 2 == 0)) {
                    solider2->addMorale();
                    solider2->yep(mytime);
                }
                if (solider2->type == 4)
                    for (int j = 0; j < 3; j++) {
                        if (!solider2->weaponList[j]) {
                            solider2->weaponList[j] = solider1->weaponList[j];
                            solider1->weaponList[j] = nullptr;
                        }
                    }

                printf("%03d:40 blue %s %d earned %d elements for his headquarter\n", mytime, soliderName[solider2->type],
                       solider2->No, city[i].HP);

                RedTeam->soliderList.remove(solider1);
                city[i].cityredsolider = nullptr;
                delete solider1;
                solider1 = nullptr;

                city[i].thiswarwinner = -1;
            } else if (!solider2->isalive() && solider1->isalive()) {
                if (city[i].flag == 1 || (city[i].flag == 0 && i % 2 == 1)) {
                    solider1->addMorale();
                    solider1->yep(mytime);
                }
                if (solider1->type == 4) {
                    for (int j = 0; j < 3; j++) {
                        if (!solider1->weaponList[j]) {
                            solider1->weaponList[j] = solider2->weaponList[j];
                            solider2->weaponList[j] = nullptr;
                        }
                    }
                }

                printf("%03d:40 red %s %d earned %d elements for his headquarter\n", mytime, soliderName[solider1->type],
                       solider1->No, city[i].HP);

                BlueTeam->soliderList.remove(solider2);
                city[i].citybluesolider = nullptr;
                delete solider2;
                solider2 = nullptr;

                city[i].thiswarwinner = 1;
            } else {
                int HPreturnRedLion = solider1->type == 3 ? solider1->HP : 0;
                int HPreturnBlueLion = solider2->type == 3 ? solider2->HP : 0;
                if (city[i].flag == 0) {
                    if (i % 2 == 1) {
                        int atkf1t2 = solider1->attack();
                        solider2->HP -= atkf1t2;
                        printf("%03d:40 red %s %d attacked blue %s %d in city %d with %d elements and force %d\n",
                               mytime, soliderName[solider1->type], solider1->No, soliderName[solider2->type],
                               solider2->No, i, solider1->HP, solider1->ATK);
                        if (solider2->isalive()) {
                            if(solider2->type!=1) {
                                int atkf2t1 = solider2->attackInTurn();
                                solider1->HP -= atkf2t1;
                                //cout<<1<<endl;
                                printf("%03d:40 blue %s %d fought back against red %s %d in city %d\n",
                                       mytime, soliderName[solider2->type], solider2->No, soliderName[solider1->type],
                                       solider1->No, i);
                            }
                            if (!solider1->isalive()) {
                                printf("%03d:40 red %s %d was killed in city %d\n", mytime, soliderName[solider1->type],
                                       solider1->No, i);
                                solider2->addMorale();
                                if (solider2->type == 4) {
                                    for (int j = 0; j < 3; j++) {
                                        if (!solider2->weaponList[j]) {
                                            solider2->weaponList[j] = solider1->weaponList[j];
                                            solider1->weaponList[j] = nullptr;
                                        }
                                    }
                                }
                                solider2->HP += HPreturnRedLion;

                                printf("%03d:40 blue %s %d earned %d elements for his headquarter\n", mytime,
                                       soliderName[solider2->type],
                                       solider2->No, city[i].HP);

                                RedTeam->soliderList.remove(solider1);
                                city[i].cityredsolider = nullptr;
                                delete solider1;
                                solider1 = nullptr;

                                city[i].thiswarwinner = -1;
                            } else {
                                solider1->decreaseMorale();
                                solider2->decreaseMorale();
                                solider1->yep(mytime);

                                city[i].thiswarwinner = 0;
                            }
                        } else {
                            printf("%03d:40 blue %s %d was killed in city %d\n", mytime, soliderName[solider2->type],
                                   solider2->No, i);
                            solider1->addMorale();
                            if (solider1->type == 4) {
                                for (int j = 0; j < 3; j++) {
                                    if (!solider1->weaponList[j]) {
                                        solider1->weaponList[j] = solider2->weaponList[j];
                                        solider2->weaponList[j] = nullptr;
                                    }
                                }
                            }
                            solider1->HP += HPreturnBlueLion;
                            solider1->yep(mytime);

                            printf("%03d:40 red %s %d earned %d elements for his headquarter\n", mytime,
                                   soliderName[solider1->type],
                                   solider1->No, city[i].HP);

                            BlueTeam->soliderList.remove(solider2);
                            city[i].citybluesolider = nullptr;
                            delete solider2;
                            solider2 = nullptr;

                            city[i].thiswarwinner = 1;
                        }
                    } else {
                        int atkf2t1 = solider2->attack();
                        solider1->HP -= atkf2t1;
                        printf("%03d:40 blue %s %d attacked red %s %d in city %d with %d elements and force %d\n",
                               mytime, soliderName[solider2->type], solider2->No, soliderName[solider1->type],
                               solider1->No, i, solider2->HP, solider2->ATK);
                        if (solider1->isalive()) {
                            if(solider1->type!=1) {
                                int atkf1t2 = solider1->attackInTurn();
                                solider2->HP -= atkf1t2;
                                //cout<<2<<endl;
                                printf("%03d:40 red %s %d fought back against blue %s %d in city %d\n",
                                       mytime, soliderName[solider1->type], solider1->No, soliderName[solider2->type],
                                       solider2->No, i);
                            }
                            if (!solider2->isalive()) {
                                printf("%03d:40 blue %s %d was killed in city %d\n", mytime,
                                       soliderName[solider2->type],
                                       solider2->No, i);
                                solider1->addMorale();

                                if (solider1->type == 4) {
                                    for (int j = 0; j < 3; j++) {
                                        if (!solider1->weaponList[j]) {
                                            solider1->weaponList[j] = solider2->weaponList[j];
                                            solider2->weaponList[j] = nullptr;
                                        }
                                    }
                                }
                                solider1->HP += HPreturnBlueLion;

                                printf("%03d:40 red %s %d earned %d elements for his headquarter\n", mytime,
                                       soliderName[solider1->type],
                                       solider1->No, city[i].HP);

                                BlueTeam->soliderList.remove(solider2);
                                city[i].citybluesolider = nullptr;
                                delete solider2;
                                solider2 = nullptr;

                                city[i].thiswarwinner = 1;
                            } else {
                                solider1->decreaseMorale();
                                solider2->decreaseMorale();
                                solider2->yep(mytime);

                                city[i].thiswarwinner = 0;
                            }
                        } else {
                            printf("%03d:40 red %s %d was killed in city %d\n", mytime, soliderName[solider1->type],
                                   solider1->No, i);
                            solider2->addMorale();

                            if (solider2->type == 4) {
                                for (int j = 0; j < 3; j++) {
                                    if (!solider2->weaponList[j]) {
                                        solider2->weaponList[j] = solider1->weaponList[j];
                                        solider1->weaponList[j] = nullptr;
                                    }
                                }
                            }
                            solider2->HP += HPreturnRedLion;
                            solider2->yep(mytime);

                            printf("%03d:40 blue %s %d earned %d elements for his headquarter\n", mytime,
                                   soliderName[solider2->type],
                                   solider2->No, city[i].HP);

                            RedTeam->soliderList.remove(solider1);
                            city[i].cityredsolider = nullptr;
                            delete solider1;
                            solider1 = nullptr;

                            city[i].thiswarwinner = -1;
                        }
                    }
                } else if (city[i].flag == 1) {
                    int atkf1t2 = solider1->attack();
                    solider2->HP -= atkf1t2;
                    printf("%03d:40 red %s %d attacked blue %s %d in city %d with %d elements and force %d\n",
                           mytime, soliderName[solider1->type], solider1->No, soliderName[solider2->type],
                           solider2->No, i, solider1->HP, solider1->ATK);
                    if (solider2->isalive()) {
                        if(solider2->type!=1) {
                            int atkf2t1 = solider2->attackInTurn();
                            solider1->HP -= atkf2t1;
                            //cout<<3<<endl;
                            printf("%03d:40 blue %s %d fought back against red %s %d in city %d\n",
                                   mytime, soliderName[solider2->type], solider2->No, soliderName[solider1->type],
                                   solider1->No, i);
                        }
                        if (!solider1->isalive()) {
                            printf("%03d:40 red %s %d was killed in city %d\n", mytime, soliderName[solider1->type],
                                   solider1->No, i);
                            solider2->addMorale();

                            if (solider2->type == 4) {
                                for (int j = 0; j < 3; j++) {
                                    if (!solider2->weaponList[j]) {
                                        solider2->weaponList[j] = solider1->weaponList[j];
                                        solider1->weaponList[j] = nullptr;
                                    }
                                }
                            }
                            solider2->HP += HPreturnRedLion;

                            printf("%03d:40 blue %s %d earned %d elements for his headquarter\n", mytime,
                                   soliderName[solider2->type],
                                   solider2->No, city[i].HP);

                            RedTeam->soliderList.remove(solider1);
                            city[i].cityredsolider = nullptr;
                            delete solider1;
                            solider1 = nullptr;

                            city[i].thiswarwinner = -1;
                        } else {
                            solider1->decreaseMorale();
                            solider2->decreaseMorale();
                            solider1->yep(mytime);

                            city[i].thiswarwinner = 0;
                        }
                    } else {
                        printf("%03d:40 blue %s %d was killed in city %d\n", mytime, soliderName[solider2->type],
                               solider2->No, i);
                        solider1->addMorale();
                        solider1->yep(mytime);
                        if (solider1->type == 4) {
                            for (int j = 0; j < 3; j++) {
                                if (!solider1->weaponList[j]) {
                                    solider1->weaponList[j] = solider2->weaponList[j];
                                    solider2->weaponList[j] = nullptr;
                                }
                            }
                        }
                        solider1->HP += HPreturnBlueLion;


                        printf("%03d:40 red %s %d earned %d elements for his headquarter\n", mytime,
                               soliderName[solider1->type],
                               solider1->No, city[i].HP);

                        BlueTeam->soliderList.remove(solider2);
                        city[i].citybluesolider = nullptr;
                        delete solider2;
                        solider2 = nullptr;

                        city[i].thiswarwinner = 1;
                    }
                } else if (city[i].flag == -1) {
                    int atkf2t1 = solider2->attack();
                    solider1->HP -= atkf2t1;
                    printf("%03d:40 blue %s %d attacked red %s %d in city %d with %d elements and force %d\n",
                           mytime, soliderName[solider2->type], solider2->No, soliderName[solider1->type],
                           solider1->No, i, solider2->HP, solider2->ATK);
                    if (solider1->isalive()) {
                        if(solider1->type!=1) {
                            int atkf1t2 = solider1->attackInTurn();
                            solider2->HP -= atkf1t2;
                            //cout<<4<<endl;
                            printf("%03d:40 red %s %d fought back against blue %s %d in city %d\n",
                                   mytime, soliderName[solider1->type], solider1->No, soliderName[solider2->type],
                                   solider2->No, i);
                        }
                        if (!solider2->isalive()) {
                            printf("%03d:40 blue %s %d was killed in city %d\n", mytime,
                                   soliderName[solider2->type],
                                   solider2->No, i);
                            solider1->addMorale();

                            if (solider1->type == 4) {
                                for (int j = 0; j < 3; j++) {
                                    if (!solider1->weaponList[j]) {
                                        solider1->weaponList[j] = solider2->weaponList[j];
                                        solider2->weaponList[j] = nullptr;
                                    }
                                }
                            }
                            solider1->HP += HPreturnBlueLion;

                            printf("%03d:40 red %s %d earned %d elements for his headquarter\n", mytime,
                                   soliderName[solider1->type],
                                   solider1->No, city[i].HP);

                            BlueTeam->soliderList.remove(solider2);
                            city[i].citybluesolider = nullptr;
                            delete solider2;
                            solider2 = nullptr;

                            city[i].thiswarwinner = 1;
                        } else {
                            solider1->decreaseMorale();
                            solider2->decreaseMorale();
                            solider2->yep(mytime);

                            city[i].thiswarwinner = 0;
                        }
                    } else {
                        printf("%03d:40 red %s %d was killed in city %d\n", mytime, soliderName[solider1->type],
                               solider1->No, i);
                        solider2->addMorale();
                        if (solider2->type == 4) {
                            for (int j = 0; j < 3; j++) {
                                if (!solider2->weaponList[j]) {
                                    solider2->weaponList[j] = solider1->weaponList[j];
                                    solider1->weaponList[j] = nullptr;
                                }
                            }
                        }
                        solider2->HP += HPreturnRedLion;
                        solider2->yep(mytime);

                        printf("%03d:40 blue %s %d earned %d elements for his headquarter\n", mytime,
                               soliderName[solider2->type],
                               solider2->No, city[i].HP);

                        RedTeam->soliderList.remove(solider1);
                        city[i].cityredsolider = nullptr;
                        delete solider1;
                        solider1 = nullptr;

                        city[i].thiswarwinner = -1;
                    }
                }
            }
            if(solider1&&solider2){
                solider1->decreaseLoyalty();
                solider2->decreaseLoyalty();
            }
        } else if (city[i].citybluesolider && !city[i].citybluesolider->isalive()) {
            BlueTeam->soliderList.remove(city[i].citybluesolider);
            delete city[i].citybluesolider;
            city[i].citybluesolider = nullptr;

            city[i].thiswarwinner = 100;
        } else if (city[i].cityredsolider && !city[i].cityredsolider->isalive()) {
            RedTeam->soliderList.remove(city[i].cityredsolider);
            delete city[i].cityredsolider;
            city[i].cityredsolider = nullptr;

            city[i].thiswarwinner = 100;
        } else if (!city[i].cityredsolider && !city[i].citybluesolider) {
            city[i].thiswarwinner = 100;
        }

        if (city[i].thiswarwinner == 100) {
            continue;
        } else if (city[i].thiswarwinner == 0) {
            city[i].lastwarwinner = 0;
        } else if (city[i].thiswarwinner == 1) {
            if (city[i].lastwarwinner == 1) {
                if(city[i].flag!=1) {
                    city[i].flag = 1;
                    printf("%03d:40 red flag raised in city %d\n", mytime, i);
                }
            } else {
                city[i].lastwarwinner = 1;
            }
        } else if (city[i].thiswarwinner == -1) {
            if (city[i].lastwarwinner == -1) {
                if(city[i].flag!=-1) {
                    city[i].flag = -1;
                    printf("%03d:40 blue flag raised in city %d\n", mytime, i);
                }
            } else {
                city[i].lastwarwinner = -1;
            }
        }

    }
}

void headQuarterReport(int mytime) {
//    cout << mytime << "headQuarterReport\n";
    printf("%03d:50 %d elements in red headquarter\n", mytime, RedTeam->healthPoint);
    printf("%03d:50 %d elements in blue headquarter\n", mytime, BlueTeam->healthPoint);
}

void soliderReport(int mytime) {
//    cout << mytime << "soliderReport\n";
    for (int i = 0; i <= N + 1; i++) {
        if (city[i].cityredsolider) {
            Solider *solider1 = city[i].cityredsolider;

            printf("%03d:55 red %s %d has ", mytime, soliderName[solider1->type], solider1->No);
            if (solider1->hasWeapon()) {
                if (solider1->weaponList[2]) {
                    printf("arrow(%d)", 3 - solider1->weaponList[2]->usedTimes);
                    if (solider1->weaponList[1]) {
                        printf(",bomb");
                        if (solider1->weaponList[0]) {
                            printf(",sword(%d)\n", solider1->weaponList[0]->ATK);
                        } else {
                            printf("\n");
                        }
                    } else {
                        if (solider1->weaponList[0]) {
                            printf(",sword(%d)\n", solider1->weaponList[0]->ATK);
                        } else {
                            printf("\n");
                        }
                    }
                } else {
                    if (solider1->weaponList[1]) {
                        printf("bomb");
                        if (solider1->weaponList[0]) {
                            printf(",sword(%d)\n", solider1->weaponList[0]->ATK);
                        } else {
                            printf("\n");
                        }
                    } else {
                        if (solider1->weaponList[0]) {
                            printf("sword(%d)\n", solider1->weaponList[0]->ATK);
                        }
                    }
                }

            } else {
                printf("no weapon\n");
            }
        }
    }
    for (int i = 0; i <= N + 1; i++) {
        if (city[i].citybluesolider) {
            Solider *solider1 = city[i].citybluesolider;

            printf("%03d:55 blue %s %d has ", mytime, soliderName[solider1->type], solider1->No);
            if (solider1->hasWeapon()) {
                if (solider1->weaponList[2]) {
                    printf("arrow(%d)", 3 - solider1->weaponList[2]->usedTimes);
                    if (solider1->weaponList[1]) {
                        printf(",bomb");
                        if (solider1->weaponList[0]) {
                            printf(",sword(%d)\n", solider1->weaponList[0]->ATK);
                        } else {
                            printf("\n");
                        }
                    } else {
                        if (solider1->weaponList[0]) {
                            printf(",sword(%d)\n", solider1->weaponList[0]->ATK);
                        } else {
                            printf("\n");
                        }
                    }
                } else {
                    if (solider1->weaponList[1]) {
                        printf("bomb");
                        if (solider1->weaponList[0]) {
                            printf(",sword(%d)\n", solider1->weaponList[0]->ATK);
                        } else {
                            printf("\n");
                        }
                    } else {
                        if (solider1->weaponList[0]) {
                            printf("sword(%d)\n", solider1->weaponList[0]->ATK);
                        }
                    }
                }

            } else {
                printf("no weapon\n");
            }
        }
    }
}

void init() {
    scanf("%d%d%d%d%d", &M, &N, &R, &K, &T);
    scanf("%d%d%d%d%d", &OriginHP[0], &OriginHP[1], &OriginHP[2], &OriginHP[3], &OriginHP[4]);
    scanf("%d%d%d%d%d", &OriginSoliderATK[0], &OriginSoliderATK[1], &OriginSoliderATK[2], &OriginSoliderATK[3],
          &OriginSoliderATK[4]);

    RedTeam = new HeadQuarter(0);
    BlueTeam = new HeadQuarter(N + 1);
    city = new City[N + 2];
}

void deal() {
    int mytime = 0;
    while (60 * mytime <= T) {
        make(mytime);

        if (60 * mytime + 5 > T)
            break;
        escape(mytime);

        if (60 * mytime + 10 > T)
            break;
        if (goForward(mytime)) {
            break;
        }

        if (60 * mytime + 20 > T)
            break;
        cityProduceHP(mytime);

        if (60 * mytime + 30 > T)
            break;
        noWarCity(mytime);

        if (60 * mytime + 35 > T)
            break;
        //wolfSteal(mytime);
        longSeeSoliderUseArrow(mytime);

        if (60 * mytime + 38 > T)
            break;
        cleverSoliderUseBomb(mytime);

        if (60 * mytime + 40 > T)
            break;
        war(mytime);
        afterWar(mytime);

        if (60 * mytime + 50 > T)
            break;
        headQuarterReport(mytime);

        if (60 * mytime + 55 > T)
            break;
        soliderReport(mytime);

        mytime++;
    }
}

void release() {
    delete RedTeam;
    delete BlueTeam;
    delete[] city;
}

int main() {
    //stdout = freopen("out.txt", "w", stdout);
    CreateWeapon[0] = Sword::create;
    CreateWeapon[1] = Bomb::create;
    CreateWeapon[2] = Arrow::create;

    CreateSolider[0] = Dragon::create;
    CreateSolider[1] = Ninja::create;
    CreateSolider[2] = Iceman::create;
    CreateSolider[3] = Lion::create;
    CreateSolider[4] = Wolf::create;

    int loop;
    scanf("%d", &loop);
    int caseout = 0;
    while (caseout < loop) {
        printf("Case %d:\n", ++caseout);
        init();
        deal();
        release();
    }
}