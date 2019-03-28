#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <functional>
#include <list>
#include <algorithm>
#include <cassert>

using namespace std;

int M, N, K, T;

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
    int time;
    int no;

    Weapon(int atk, int atkself = 0, int tim = 0) : ATK(atk), ATKself(atkself), time(tim) {
        //printf("Weapon with %d atk & %d atkself was built! Its usetime is %d\n", atk, atkself, tim);
    }

    virtual void updateATK(int soliderATK) {}

    virtual int use() {}

};

class Sword : public Weapon {
public:
    Sword(int SoliderATK) : Weapon(SoliderATK * 2 / 10) {
        //printf("Sword with %d atk was built!\n", SoliderATK * 2 / 10);
        no = 0;
    }

    int use() override {
        //printf("Use Sword with %d atk!\n", Weapon::ATK);
        return Weapon::ATK;
    }

    void updateATK(int soliderATK) {
        ATK = soliderATK * 2 / 10;
    }

    static Sword *create(int SoliderATK) {
        return new Sword(SoliderATK);
    }

};

class Bomb : public Weapon {
public:
    Bomb(int SoliderATK) : Weapon(SoliderATK * 4 / 10, SoliderATK * 4 / 10 / 2) {
        //printf("Bomb with %d atk & %d atkself was built!\n", SoliderATK * 4 / 10, SoliderATK * 4 / 10 / 2);
        no = 1;
    }

    int use() override {
        Weapon::useful = false;
        //printf("Use Bomb with %d atk & %d atkself!\n", Weapon::ATK, Weapon::ATKself);
        return Weapon::ATK;
    }

    void updateATK(int soliderATK) {
        ATK = soliderATK * 4 / 10;
        ATKself = ATK / 2;
    }

    static Bomb *create(int SoliderATK) {
        return new Bomb(SoliderATK);
    }
};

class Arrow : public Weapon {
public:
    Arrow(int SoliderATK) : Weapon(SoliderATK * 3 / 10) {
        //printf("Arrow with %d atk was built!\n", SoliderATK * 3 / 10);
        no = 2;
    }

    int use() override {
        Weapon::time++;
        //printf("Use Arrow with %d atk!\n", Weapon::ATK);
        if (Weapon::time == 2)
            Weapon::useful = false;
        return Weapon::ATK;
    }

    void updateATK(int soliderATK) {
        ATK = soliderATK * 3 / 10;
    }

    static Arrow *create(int SoliderATK) {
        return new Arrow(SoliderATK);
    }
};

typedef function<Weapon *(int)> CreateWeaponFunction;
map<int, CreateWeaponFunction> CreateWeapon;

bool lostWeaponCompare(Weapon *weapon1, Weapon *weapon2) {
    if (weapon1->no < weapon2->no)
        return true;
    else if (weapon1->no == weapon2->no) {
        return weapon1->time < weapon2->time;
    } else
        return false;
}

bool warWeaponCompare(Weapon *weapon1, Weapon *weapon2) {
    if (weapon1->no < weapon2->no)
        return true;
    else if (weapon1->no == weapon2->no) {
        return weapon1->time > weapon2->time;
    } else
        return false;
}

class Solider {
public:
    Weapon *weapon[10];
    int position;
    int HP;
    int No;
    int ATK;
    int team = 1;
    int loyalty;
    int weaponIndex = 0;
    int weaponNum[3] = {0, 0, 0};
    int weaponSum = 0;

    Solider(int no, int hp, int atk, int pos) : No(no), HP(hp), ATK(atk), position(pos) {
        //printf("Solider No.%d with %d HP was built at city %d! Its att is %d\n", no, hp, pos, atk);
        memset(weapon, 0, sizeof(weapon));
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

    virtual void goForward() {}

    virtual int escape() {
        return 0;
    }

    void lostSortWeapon() {
        int num = 0;
        while (weapon[num])
            num++;
        sort(weapon, weapon + num, lostWeaponCompare);
    }

    void sortWeapon() {
        int num = 0;
        while (weapon[num])
            num++;
        sort(weapon, weapon + num, warWeaponCompare);
        weaponIndex = 0;
        weaponSum = num;
    }

    void countWeapon() {
        memset(weaponNum, 0, sizeof(weaponNum));
        for (int i = 0; i < 10; i++) {
            if (weapon[i]) {
                weaponNum[weapon[i]->no]++;
            }
        }
    }

    bool isalive() {
        return HP > 0;
    }

    void delWeapon(int index) {
        delete weapon[index];
        weapon[index] = nullptr;

        for (; index < weaponSum - 1; index++) {
            weapon[index] = weapon[index + 1];
            weapon[index + 1] = nullptr;
        }

        weaponSum--;

    }

    virtual int useWeapon() {
        if (weapon[0] == nullptr) {
            return 0;
        }
        weaponIndex = weaponIndex % weaponSum;
        weapon[weaponIndex]->updateATK(ATK);
        int type = weapon[weaponIndex]->no;
        if (type == 1)
            HP -= weapon[weaponIndex]->ATKself;
        int atk = weapon[weaponIndex]->use();
        if (!weapon[weaponIndex]->useful) {
            delWeapon(weaponIndex);
            return atk;
        }
        weaponIndex++;
        return atk;
    }

    virtual void yep(int mytime) {}

};

class City {
public:
    Solider *cityredsolider;
    Solider *citybluesolider;

    City() {
        cityredsolider = citybluesolider = nullptr;
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

    Dragon(int no, int pos) : Solider(no, OriginHP[0], OriginSoliderATK[0], pos) {
        //printf("Dragon No.%d with %d HP was built! Its att is %d\n", no, OriginHP[0], OriginSoliderATK[0]);
        weapon[0] = CreateWeapon[no % 3](OriginSoliderATK[0]);
    }

    ~Dragon() override {
        for (int i = 0; i < 10; i++) {
            if (weapon[i]) {
                //printf("Dragon No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weapon[i];
            }
        }
        //printf("Dragon No.%d with %d HP was delete at city %d!\n", Solider::No, Solider::HP, Solider::position);
    }

    static Dragon *create(int no, int pos) {
        return new Dragon(no, pos);
    }

    void goForward() override {
        Solider::position += Solider::team;
        //printf("Dragon No.%d with %d HP is in city %d now!\n", Solider::No, Solider::HP, Solider::position);
    }

    void yep(int mytime) {
        if (team == 1)
            printf("%03d:40 red dragon %d yelled in city %d\n", mytime, No, position);
        else
            printf("%03d:40 blue dragon %d yelled in city %d\n", mytime, No, position);
    }

};

class Ninja : public Solider {
public:

    Ninja(int no, int pos) : Solider(no, OriginHP[1], OriginSoliderATK[1], pos) {
        //printf("Ninga No.%d with %d HP was built at city %d! Its att is %d\n", no, OriginHP[1], pos, OriginSoliderATK[1]);
        weapon[0] = CreateWeapon[no % 3](OriginSoliderATK[1]);
        weapon[1] = CreateWeapon[(no + 1) % 3](OriginSoliderATK[1]);
    }

    ~Ninja() override {
        for (int i = 0; i < 10; i++) {
            if (weapon[i]) {
                //printf("Ninja No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weapon[i];
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

};

class Iceman : public Solider {
public:

    Iceman(int no, int pos) : Solider(no, OriginHP[2], OriginSoliderATK[2], pos) {
        //printf("Iceman No.%d with %d HP was built at city %d! Its att is %d\n", no, OriginHP[2], pos, OriginSoliderATK[2]);
        weapon[0] = CreateWeapon[no % 3](OriginSoliderATK[2]);
    }

    ~Iceman() override {
        for (int i = 0; i < 10; i++) {
            if (weapon[i]) {
                //printf("Iceman No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weapon[i];
            }
        }
        //printf("Iceman No.%d with %d HP was delete at city %d!\n", Solider::No, Solider::HP, Solider::position);
    }

    static Iceman *create(int no, int pos) {
        return new Iceman(no, pos);
    }

    void goForward() override {
        Solider::position += Solider::team;
        Solider::HP -= Solider::HP / 10;
        //printf("Iceman No.%d with %d HP is in city %d now!\n", Solider::No, Solider::HP, Solider::position);
    }

};

class Lion : public Solider {
public:


    Lion(int no, int pos) : Solider(no, OriginHP[3], OriginSoliderATK[3], pos) {
        //printf("Lion No.%d with %d HP was built at city %d! Its att is %d\n", no, OriginHP[3], pos, OriginSoliderATK[3]);
        weapon[0] = CreateWeapon[no % 3](OriginSoliderATK[3]);
    }

    ~Lion() override {
        for (int i = 0; i < 10; i++) {
            if (weapon[i]) {
                //printf("Lion No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weapon[i];
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
        loyalty -= K;
        //printf("Lion No.%d with %d HP & %d loyalty is in city %d now!\n", Solider::No, Solider::HP, loyalty, Solider::position);
    }

    int escape() override {
        if (position == N + 1 || position == 0)
            return 0;
        if (loyalty <= 0)
            return 1;
        return 0;
    }

};

class Wolf : public Solider {
public:

    Wolf(int no, int pos) : Solider(no, OriginHP[4], OriginSoliderATK[4], pos) {
        //printf("Wolf No.%d with %d HP was built at city %d! Its att is %d\n", no, OriginHP[4], pos, OriginSoliderATK[4]);
    }

    ~Wolf() override {
        for (int i = 0; i < 10; i++) {
            if (weapon[i]) {
                //printf("Wolf No.%d 's weapon %d was delete!\n", Solider::No, i);
                delete weapon[i];
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

            createIndex++;
            return 1;
        }
    }

};

HeadQuarter *RedTeam, *BlueTeam;

void make(int mytime) {
    //cout << mytime << "make\n";
    RedTeam->makeSolider(mytime, makeOrderRed);
    BlueTeam->makeSolider(mytime, makeOrderBlue, 1);
}

void escape(int mytime) {
    //cout << mytime << "escape\n";
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
    //cout << mytime << "go forward\n";
    bool end = false;

    Solider *soliderredwest, *soliderredhere;

    if (city[1].citybluesolider) {
        if (city[0].citybluesolider) {}
        end = true;

        city[0].citybluesolider = city[1].citybluesolider;
        city[1].citybluesolider = nullptr;

        Solider *solider = city[0].citybluesolider;
        solider->goForward();
//        printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n", mytime,
//               soliderName[makeOrderBlue[(solider->No - 1) % 5]], solider->No, solider->position, solider->HP,
//               solider->ATK);
        reachEnemy(mytime, 0);

        if (end)
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
        if (city[N + 1].cityredsolider) {}
        end = true;

        city[N + 1].cityredsolider = soliderredwest;

        Solider *solider = city[N + 1].cityredsolider;
        solider->goForward();

        reachEnemy(mytime, N + 1);

//        printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n", mytime,
//               soliderName[makeOrderBlue[(solider->No - 1) % 5]], solider->No, solider->position, solider->HP,
//               solider->ATK);

        if (end)
            victory(mytime, N + 1);
    }

    if (end) {
        return true;
    }
    return false;
}

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


void warGetWeapon(Solider *solider1, Solider *solider2) {
    solider2->lostSortWeapon();

    int index = solider1->weaponSum;
    for (int i = 0; index < 10; index++) {
        solider1->weapon[index] = solider2->weapon[i];
        solider2->weapon[i] = nullptr;
        i++;
    }

}

void war(int mytime) {
    //cout << mytime << "war\n";
    for (int i = 1; i <= N; ++i) {
        if (city[i].citybluesolider && city[i].cityredsolider) {
//            if(city[i].cityredsolider==city[i].citybluesolider){
//                cout<<"Illegel!\n";
//            }
            //cout<<i%2<<endl;
            Solider *solider1 = ((i % 2) == 0) ? city[i].citybluesolider : city[i].cityredsolider;
            Solider *solider2 = ((i % 2) == 1) ? city[i].citybluesolider : city[i].cityredsolider;

            solider1->sortWeapon();
            solider2->sortWeapon();

            solider1->countWeapon();
            solider2->countWeapon();

            //printf("%d %d %d %d %d %d\n", solider1->team, solider1->No, solider1->HP, solider1->weaponNum[0], solider1->weaponNum[1], solider1->weaponNum[2]);
            //printf("%d %d %d %d %d %d\n", solider2->team, solider2->No, solider2->HP, solider2->weaponNum[0], solider2->weaponNum[1], solider2->weaponNum[2]);


            while (true) {
                solider1->countWeapon();
                int bomb1 = solider1->weaponNum[1], bomb2;
                int arrow1 = solider1->weaponNum[2], arrow2;

                int atkf1t2 = solider1->useWeapon();
                solider2->HP -= atkf1t2;
                //printf("solider1HP: %d, solider2HP: %d\n", solider1->HP, solider2->HP);
                int atkf2t1;
                if (solider1->isalive() && solider2->isalive()) {
                    solider2->countWeapon();
                    bomb2 = solider2->weaponNum[1];
                    arrow2 = solider2->weaponNum[2];

                    atkf2t1 = solider2->useWeapon();
                    solider1->HP -= atkf2t1;
                    //printf("solider1HP: %d, solider2HP: %d\n", solider1->HP, solider2->HP);
                }
                //cout<<bomb1<<" "<<arrow1<<" "<<bomb2<<" "<<arrow2<<" "<<atkf1t2<<" "<<atkf2t1<<endl;

                if (!solider1->isalive() && !solider2->isalive()) {

                    printf("%03d:40 both red %s %d and blue %s %d died in city %d\n", mytime,
                           soliderName[makeOrderRed[(city[i].cityredsolider->No - 1) % 5]],
                           city[i].cityredsolider->No,
                           soliderName[makeOrderBlue[(city[i].citybluesolider->No - 1) % 5]],
                           city[i].citybluesolider->No, solider1->position);

                    BlueTeam->soliderList.remove(city[i].citybluesolider);
                    RedTeam->soliderList.remove(city[i].cityredsolider);

                    city[i].cityredsolider = nullptr;
                    city[i].citybluesolider = nullptr;

                    delete solider1;
                    delete solider2;

                    solider1 = nullptr;
                    solider2 = nullptr;

                    break;

                } else if (!solider1->isalive()) {
                    //solider1挂了
                    warGetWeapon(solider2, solider1);

                    if (solider1 == city[i].citybluesolider) {
                        printf("%03d:40 red %s %d killed blue %s %d in city %d remaining %d elements\n", mytime,
                               soliderName[makeOrderRed[(city[i].cityredsolider->No - 1) % 5]],
                               city[i].cityredsolider->No,
                               soliderName[makeOrderBlue[(city[i].citybluesolider->No - 1) % 5]],
                               city[i].citybluesolider->No, solider1->position, solider2->HP);

                        city[i].citybluesolider = nullptr;
                        BlueTeam->soliderList.remove(solider1);
                    } else {
                        printf("%03d:40 blue %s %d killed red %s %d in city %d remaining %d elements\n", mytime,
                               soliderName[makeOrderBlue[(city[i].citybluesolider->No - 1) % 5]],
                               city[i].citybluesolider->No,
                               soliderName[makeOrderRed[(city[i].cityredsolider->No - 1) % 5]],
                               city[i].cityredsolider->No, solider1->position, solider2->HP);

                        city[i].cityredsolider = nullptr;
                        RedTeam->soliderList.remove(solider1);
                    }
                    delete solider1;
                    solider1 = nullptr;
                    break;
                } else if (!solider2->isalive()) {
                    //solider2挂了
                    warGetWeapon(solider1, solider2);

                    if (solider2 == city[i].citybluesolider) {
                        printf("%03d:40 red %s %d killed blue %s %d in city %d remaining %d elements\n", mytime,
                               soliderName[makeOrderRed[(city[i].cityredsolider->No - 1) % 5]],
                               city[i].cityredsolider->No,
                               soliderName[makeOrderBlue[(city[i].citybluesolider->No - 1) % 5]],
                               city[i].citybluesolider->No, solider1->position, solider1->HP);

                        city[i].citybluesolider = nullptr;
                        BlueTeam->soliderList.remove(solider2);

                    } else {
                        printf("%03d:40 blue %s %d killed red %s %d in city %d remaining %d elements\n", mytime,
                               soliderName[makeOrderBlue[(city[i].citybluesolider->No - 1) % 5]],
                               city[i].citybluesolider->No,
                               soliderName[makeOrderRed[(city[i].cityredsolider->No - 1) % 5]],
                               city[i].cityredsolider->No, solider1->position, solider1->HP);

                        city[i].cityredsolider = nullptr;
                        RedTeam->soliderList.remove(solider2);
                    }

                    delete solider2;
                    solider2 = nullptr;
                    break;

                } else {
                    if (atkf1t2 == 0 && atkf2t1 == 0 && arrow1 == 0 && arrow2 == 0 && bomb1 == 0 && bomb2 == 0) {
                        printf("%03d:40 both red %s %d and blue %s %d were alive in city %d\n", mytime,
                               soliderName[makeOrderRed[(city[i].cityredsolider->No - 1) % 5]],
                               city[i].cityredsolider->No,
                               soliderName[makeOrderBlue[(city[i].citybluesolider->No - 1) % 5]],
                               city[i].citybluesolider->No, solider1->position);
                        break;
                    }
                }
            }
            if (city[i].cityredsolider) {
                city[i].cityredsolider->yep(mytime);
            }
            if (city[i].citybluesolider) {
                city[i].citybluesolider->yep(mytime);
            }
        }
    }
}

void headQuarterReport(int mytime) {
    //cout << mytime << "headQuarterReport\n";
    printf("%03d:50 %d elements in red headquarter\n", mytime, RedTeam->healthPoint);
    printf("%03d:50 %d elements in blue headquarter\n", mytime, BlueTeam->healthPoint);
}

void soliderReport(int mytime) {
    //cout << mytime << "soliderReport\n";
    for (int i = 0; i <= N + 1; i++) {
        if (city[i].cityredsolider) {
            Solider *solider1 = city[i].cityredsolider;
            solider1->countWeapon();

            printf("%03d:55 red %s %d has %d sword %d bomb %d arrow and %d elements\n", mytime,
                   soliderName[makeOrderRed[(solider1->No - 1) % 5]], solider1->No, solider1->weaponNum[0],
                   solider1->weaponNum[1], solider1->weaponNum[2], solider1->HP);

        }
        if (city[i].citybluesolider) {
            Solider *solider1 = city[i].citybluesolider;
            solider1->countWeapon();

            printf("%03d:55 blue %s %d has %d sword %d bomb %d arrow and %d elements\n", mytime,
                   soliderName[makeOrderBlue[(solider1->No - 1) % 5]], solider1->No, solider1->weaponNum[0],
                   solider1->weaponNum[1], solider1->weaponNum[2], solider1->HP);
        }
    }
}


void init() {
    scanf("%d%d%d%d", &M, &N, &K, &T);
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
        if (60 * mytime + 35 > T)
            break;
        wolfSteal(mytime);
        if (60 * mytime + 40 > T)
            break;
        war(mytime);
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