#include <iostream>

int main(int argc, char* argv[]) {
    int first=0;
    if(argc==1){
        printf("illegal numbers!\n");
        return 0;
    }
    int j=0;
    if(argv[1][0]=='-')
        j=1;
    for(int i=j; argv[1][i]; i++){
        first*=10;
        int x=argv[1][i]-'0';
        if(x>9||x<0) {
            printf("illegal numbers!\n");
            return 0;
        }
        first+=argv[1][i]-'0';
    }
    first=j?-first:first;

    int last=0;
    j=0;
    if(argv[argc-1][0]=='-')
        j=1;
    for(int i=j; argv[argc-1][i]; i++){
        last*=10;
        int x=argv[argc-1][i]-'0';
        if(x>9||x<0){
            printf("illegal numbers!\n");
            return 0;
        }
        last+=argv[argc-1][i]-'0';
    }
    last=j?-last:last;
    std::cout<<first+last<<std::endl;
    return 0;
}