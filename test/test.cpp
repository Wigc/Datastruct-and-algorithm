/*
 * @Author: your name
 * @Date: 2021-07-27 13:40:59
 * @LastEditTime: 2021-07-28 20:02:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Datastruct-and-algorithm\test\test.cpp
 */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "../datastruct/utils.h"

using namespace std;



int main(){
    
    // cout<<threeToLong("abc")<<endl;
    // int a = 1<<8;
    // cout<< a << endl;
    ifstream in("1.txt.zzz",ios::binary);
    char c;
    while((c = in.get()) != EOF){
        int a = c;
        cout<<a<<" ";
    }
}
