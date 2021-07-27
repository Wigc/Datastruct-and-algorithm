/*
 * @Description: 
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-07-27 12:02:45
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-07-27 14:32:10
 */
#ifndef utils_
#define utils_

#include <iostream>
#include <string>

using std::string;

/**
 * 把一个长度位3的字符串转换位一个长整型数
 */
long threeToLong(string s)
{
    //假设s.length() >= 3
    long answer = s.at(0);

    //左移8位，加入下一个字符
    answer = (answer << 8) + s.at(1);

    //左移8位，加入下一个字符
    return (answer << 8) + s.at(2);
}

/**
 * @description: 
 * @param {string} s    把s转换一个非负整数，这种转换依赖s的所有字符
 * @return {*}
 * @author: 
 */
int stringToInt(string s)
{
    //把s转换一个非负整数，这种转换依赖s的所有字符
    int length = (int)s.length(); //s中字符的个数
    int answer = 0;
    if (length % 2 == 1)
    {
        //长度为奇数
        answer = s.at(length - 1);
        length--;
    }

    //长度是偶数
    for (int i = 0; i < length; i += 2)
    {
        //同时转换两个字符
        answer += s.at(i);
        answer += ((int) s.at(i + 1)) << 8;
    }

    return (answer < 0) ? -answer : answer;
}


#endif