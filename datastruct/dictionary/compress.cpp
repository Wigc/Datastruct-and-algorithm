/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-28 15:55:01
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-28 20:19:38
 */


#include <iostream>
#include <fstream>
#include <cstring>
#include "hashChain.h"

using namespace std;

const int   DIVISOR = 4099,//hash的除数
            MAX_CODES = 4096,//2^12
            BYTE_SIZE = 8,
            EXCESS = 4,//12 - BYTE_SIZE
            ALPHA = 256,//2^BYTE_SIZE
            MASK1 = 255,//ALPHA - 1,前8位
            MASK2 = 15;//2^EXCESS - 1,余的四位

typedef pair<const long,int> pairType;

//全局变量
int leftOver;//待输出的代码位
bool bitsLeftOver = false;//false表示没有余下的位
ifstream in;//输入文件
ofstream out;//输出文件

/**
 * @description: 创建输入输出流
 * @param {int} argc
 * @param {char*} argv
 * @return {*}
 * @author: 
 */
void setFile(int argc,char* argv[]){
    char outputFile[50],inputFile[54];
    //是否提供文件名
    if(argc >= 2){
        strcpy(inputFile,argv[1]);
    }else{
        //未提供文件名，要求输入文件名
        cout<<"Enter name of file to compress:"<<endl;
        cin>>inputFile;
    }

    //以二进制方式打开
    in.open(inputFile,ios::binary);
    if(in.fail()){
        cerr<<"Cannot open"<<inputFile<<endl;
        exit(1);
    }

    strcpy(outputFile,inputFile);
    strcat(outputFile,".zzz");
    out.open(outputFile,ios::binary);
}

/**
 * @description: 因为每个代码是12位，每个字节是8位，所以输出的只能是代码的一部分，即一个字节。
 * 先输出代码的前8位，余下的4位留待其后输出。当要输出下一个代码时，加上前面余下的4位，共 16位，可以作为2字节输出。
 * MASK1为255，MASK2为15，EXCESS为4，BYTE_SIZE为8。当且仅当有余位待输出时，bitsLeftOver是 true。
 * 此时，余下的4位放在变量leftOver 中。
 * @param {long} code
 * @return {*}
 * @author: 
 */
void output(long code){
//输出8位，把剩余的保存
    int c,d;
    if(bitsLeftOver){
        //前面剩余的位
        
        d = int(code & MASK1);//右ByteSize位
        c = int((leftOver << EXCESS) | (code >> BYTE_SIZE));
        out.put(c);
        out.put(d);
        bitsLeftOver = false;
    }else{
        //前面没有剩余的位

        leftOver = code & MASK2;//右EXCESS位
        c = int(code >> EXCESS);
        out.put(c);
        bitsLeftOver = true;
    }
}

/**
 * @description: Lempel-Ziv-Welch 压缩.首先用256个ALPHA=256)8位ASCII字符和它们的代码对字典初始化。
 * 变量codeUsed记录目前已用的代码个数。因为每个代码为12位，则最多可分配 MAX_CODES=4096个代码。
 * 为了在字典中寻找最长的前缀，我们按前缀的长度1,2,3…的顺序查找，直到发现一个前缀在字典中不存在为止。
 * 这时就输出一个代码，并生成一个新代码（除非4096个代码全部用完)。
 * @param {*}
 * @return {*}
 * @author: 
 */
void compress(){
    //定义和初始化编码字典
    hashChain<long,int> h(DIVISOR);
    for(int i = 0;i < ALPHA;i++){
        h.insert(pairType(i,i));
    }
    int codesUsed = ALPHA;

    //输入和压缩
    int c = in.get();//输入文件的第一个字符
    if(c != EOF){
        //输入文件不为空
        long pcode = c;//前缀代码
        while ((c=in.get()) != EOF)
        {
            //处理字符c
            
            long theKey = (pcode << BYTE_SIZE) + c;
            //检查关键字theKey的代码是否在字典中
            pairType* thePair = h.find(theKey);
            if(thePair == NULL){
                //关键字不在表中

                output(pcode);
                if(codesUsed < MAX_CODES){
                    //建立新代码

                    h.insert(pairType((pcode << BYTE_SIZE)|c,codesUsed++));
                }
                pcode = c;
            }else{
                pcode = thePair->second;//关键字theKey在表中
            }
        }

        //输出最后的代码
        output(pcode);
        if(bitsLeftOver){
            output(leftOver<<EXCESS);
        }
        
    }
    out.close();
    in.close();
}

int main(int argc,char* argv[]){
    setFile(argc,argv);
    compress();
}