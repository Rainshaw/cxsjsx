#include <iostream>

int bin2bcd(char val)
{
	int x=0;
	for(int i=7;i>=0;i--){
		if((x&0xf)>=5){
			std::cout<<1<<std::endl;
			x+=3;
		}
		if(((x&0xf0)>>4)>=5){
			std::cout<<1<<std::endl;
			x+=(3<<4);
		}
		x<<=1;
		x= (((val&(1<<i))>>i) | x&(~1));
		std::cout<<i<<" : "<<std::bitset<32>(x)<<std::endl;
	}
	return x;
}

int main() {
    char bin=255;
    std::cout << std::bitset<8>(bin)<< std::endl;
	std::cout << std::bitset<32>(bin2bcd(bin)) << std::endl;
    return 0;
}