#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>

using namespace std;

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned int LONG;

#pragma pack(1)
typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;


int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout << "No enough parameters!\n";
        return 0;
    }

    string srcName = argv[1];
    string destName = argv[2];

    tagBITMAPFILEHEADER a;
    tagBITMAPINFOHEADER b;
    tagBITMAPINFOHEADER bori;

    fstream openpic, writepic;

    openpic.open(srcName, ios::in | ios::binary);
    writepic.open(destName, ios::out | ios::binary);

    openpic.read((char *) &a, sizeof(tagBITMAPFILEHEADER));
    openpic.read((char *) &b, sizeof(tagBITMAPINFOHEADER));

    bori=b;
    cout << "FILE " << sizeof(tagBITMAPFILEHEADER) << endl << "INFO " << sizeof(tagBITMAPINFOHEADER) << endl;

    int temp = b.biWidth;
    b.biWidth = b.biHeight;
    b.biHeight = temp;//交换宽和高

    temp = b.biXPelsPerMeter;
    b.biXPelsPerMeter = b.biYPelsPerMeter;
    b.biYPelsPerMeter = temp;

    int readnum = b.biBitCount / 8;//对于24位、32位图，每个像素点3、4字节

    writepic.write((char *) &a, sizeof(a));
    writepic.write((char *) &b, sizeof(b));//写入文件头

    printf("readnum: %d\n",readnum);

    char **s=new char*[bori.biHeight];

    printf("bitWidth*readnum mod 4=%d\n",readnum*bori.biWidth%4);
    printf("bitWidth*readnum=%d\n",readnum*bori.biWidth);

    int sWidth= readnum*bori.biWidth%4==0?readnum*bori.biWidth:(readnum*bori.biWidth/4+1)*4;

    printf("sWidth:%d\n",sWidth);

    for(int i=0; i<bori.biHeight;i++){
        *(s+i)=new char[sWidth];
    }

    for(int i=bori.biHeight-1;i>=0;i--){
        for(int j=0;j<sWidth;j++){
            openpic.read(*(s+i)+j,1);
        }
    }

    char zero[5]={0};
    for(int j=bori.biWidth-1;j>=0;j--){
        for(int i=bori.biHeight-1;i>=0;i--){
            writepic.write(*(s+i)+readnum*j,readnum);
        }
        if((b.biWidth*readnum)%4!=0){
            writepic.write(zero,4-(b.biWidth*readnum)%4);
        }
    }


//    char **s = new char *[b.biWidth];
//    for (int i = 0; i < b.biWidth; i++) {
//        *(s + i) = new char[(b.biHeight * b.biBitCount+31)/8];
//    }
//    for (int i = b.biWidth - 1; i >= 0; i--) {
//        for (int j = 0; j < b.biHeight; j++) {
//            openpic.read(*(s + i) + readnum * j, readnum);
//        }
//    }
//    char bu[10] = {0};
//    for (int j = b.biHeight - 1; j >= 0; j--) {
//        for (int i = b.biWidth - 1; i >= 0; i--) {
//            writepic.write(*(s + i) + readnum * j, readnum);
//        }
//        if ((b.biWidth * readnum) % 4 != 0) {
//            writepic.write(bu, 4 - (b.biWidth * readnum) % 4);
//        }
//    }
    openpic.close();
    writepic.close();
    return 0;

}