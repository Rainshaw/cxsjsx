#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
	char name[20];
	int age;
	int id;
	int grade[4];
	double ave;
public:
	Student(){};
	void input(){
        char first[20],last[20];
	    scanf("%[^,],%d,%d,%d,%d,%d,%d",name,&age,&id,&grade[0],&grade[1],&grade[2],&grade[3]);

	}

	void calculate(){
	    ave=((double)(grade[0]+grade[1]+grade[2]+grade[3]))/4;
	}

	void output(){
	    cout<<name<<","<<age<<","<<id<<","<<ave<<endl;
	    //printf("%s,%d,%d,%f\n",name,age,id,ave);
	}
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}