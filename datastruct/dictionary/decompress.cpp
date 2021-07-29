/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-28 18:54:01
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-28 20:30:14
 */

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int   MAX_CODES = 4096,//2^12
            BYTE_SIZE = 8,
            EXCESS = 4,//12 - BYTE_SIZE
            ALPHA = 256,//2^BYTE_SIZE
            MASK = 15;//2^EXCESS - 1,余的四位

typedef pair<int,char> pairType;

//全局
pairType ht[MAX_CODES];//dic
char s[MAX_CODES];//用来重建文本
int size;//重建文本的大小
int leftOver;//带输出的代码位
bool bitsLeftOver = false;//false表示没有剩余位
ifstream in;//输入文件
ofstream out;//输出文件

/**
 * @description: 获取一个字节的低四位
 * @param {int&} code
 * @return {*}
 * @author: 
 */
bool getCode(int& code){
    //把压缩文件中的下一个代码存入code,如果不在有代码,则反回false
    int c,d;
    if((c = in.get()) == EOF){
        return false;
    }

    //检查前面是否有剩余的四位,如果有则与其连接
    if(bitsLeftOver){
        code = (leftOver << BYTE_SIZE) | c;
    }else{
        //没有,需要再加四位以凑足代码
        d = in.get();//另外8位
        code = (c << EXCESS) | (d >> EXCESS);
        leftOver = d & MASK;//存储四位
    }

    bitsLeftOver = !bitsLeftOver;
    return true;
}

/**
 * @description: 输出与代码对应的字符串
 * @param {int} code
 * @return {*}
 * @author: 
 */
void output(int code){
    size = -1;
    while(code >= ALPHA){
        //字典中的后缀
        s[++size] = ht[code].second;
        code = ht[code].first;
    }
    s[++size] = code; //code < ALPHA
    
    //解压的串是s[size] .. s[0]
    for(int i = size;i>=0;i--){
        out.put(s[i]);
    }
}

/**
 * @description: LZW解压器。压缩文件的第一个代码在while循环体外解码,方法是用一个类型转换，而其他代码则在循环体内解码。
 * 在while 循环的每一次迭代开始时，在s[size]中存有上次输出的解码文本的第一个字符。
 * 为了使第一个循环也满足此条件，可以把 size置为0且把 s[0]置为压缩文件中第一个代码所对应的唯一的一个字符。
 * @param {*}
 * @return {*}
 * @author: 
 */
void decompress(){
    int codeUsed = ALPHA; //当前代码codeUsed

    //输入和解压
    int pcode,//前面的代码
        ccode;//当前的代码
    
    if(getCode(pcode)){
        //文件不空
        
        s[0] = pcode;//取pcode的代码
        out.put(s[0]);
        size = 0;//s[size]是最后一个输出字符串的第一个字符

        while (getCode(ccode))
        {
            //又一个代码
            
            if(ccode < codeUsed){
                //确定ccode
                output(ccode);
                if(codeUsed < MAX_CODES){
                    //建立新代码
                    ht[codeUsed].first = pcode;
                    ht[codeUsed++].second = s[size];
                }
            }else{
                //特殊情况,没有定义的代码
                ht[codeUsed].first = pcode;
                ht[codeUsed++].second = s[size];
                output(ccode);
            }

            pcode = ccode;
        }
        
    }

    out.close();
    in.close();
}

void setFiles(int argc, char* argv[])
{// Determine file name.
   char outputFile[50], inputFile[54];

   // see if file name provided
   if (argc == 2)
      strcpy(outputFile,argv[1]);
   else
   {// name not provided, ask for it
         cout << "Enter name of file to decompress"
              << endl;
         cout << "Omit the extension .zzz"  << endl;
         cin >> outputFile;
   }

   strcpy(inputFile, outputFile);
   strcat(inputFile, ".zzz");

   // open files in binary mode
   in.open(inputFile, ios::binary);
   if (in.fail())
   {
      cerr << "Cannot open " << inputFile  << endl;
      exit(1);
   }
   out.open(outputFile, ios::binary);
}

int main(int argc, char* argv[]){
   setFiles(argc, argv);
   decompress();
}
