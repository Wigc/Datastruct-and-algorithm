/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-27 20:53:28
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-27 20:54:38
 */

#include <iostream>
#include "../datastruct/dictionary/hashChain.h"

using namespace std;

int main()
{
   hashChain<int, int> z(11);
   pair<int, int> p;

   // test insert
   p.first = 2; p.second = 10;
   z.insert(p);
   p.first = 10; p.second = 50;
   z.insert(p);
   p.first = 24; p.second = 120;
   z.insert(p);
   p.first = 32; p.second = 160;
   z.insert(p);
   p.first = 3; p.second = 15;
   z.insert(p);
   p.first = 12; p.second = 60;
   z.insert(p);
   cout << "The dictionary is " << endl << z << endl;
   cout << "Its size is " << z.size() << endl;

   // test find
   cout << "Element associated with 2 is " << z.find(2)->second << endl;
   cout << "Element associated with 10 is " << z.find(10)->second << endl;
   cout << "Element associated with 12 is " << z.find(12)->second << endl;

}
