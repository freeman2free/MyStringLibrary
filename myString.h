#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//atoi函数将字符串转有符号4字节整型
int myAtoi(const char* sz);

/*strcat函数,用于在一个字符串后面再追加一个字符串(本质上还是一个复制字符串的函数)*/
char* myStrcat(char *dst, const char *src);

/*strcmp函数,用于比较字符串大小
情况1.如果第一个字符串大于第二个字符串，则返回大于0的数字
情况2.如果第一个字符串等于第二个字符串，则返回0
情况3.如果第一个字符串小于第二个字符串，则返回小于0的数字
*/
int myStrcmp(const char *str1, const char *str2);

/*strcpy函数,用于复制字符串*/
char* myStrcpy(char *dst, char const *src);

/*strlen函数,用于返回字符串长度(不包含'\0')*/
int myStrlen(const char* sz);

/*strlwr函数,用于将字符串中的字母大写转小写*/
char* myStrlwr(char* sz);

/*strupr函数,用于将字符串中的字母小写转大写*/
char* myStrupr(char* sz);

/*strslice函数,用于分割字符串*/
bool myStrslice(char* szSrc, char* szDst, int iStart, int iEnd);

/*strstr函数,用于搜索子串*/
char* myStrstr(const char* szBuffer, const char* szSubBuffer);

/*strreverse函数,反转字符串*/
void myStrreverse(char* sz, int iLen);

/*itoa函数,用于将有符号整数转换为字符串
  iValue: 需要转换为字符的数字
  szBuffer: 转换为字符串后将其保存的位置
  iRadix: 转换数字的进制(基数),例如按照2/8/10/16进制来转换数字
*/
char* myItoa(int iValue, char* szBuffer, int iRadix);

/*XorCrypton函数,异或加密指定字符串*/
void XorCrypton(char* szBuffer, int iSize, char cKey);

/*flush函数,用于清空缓存区的的函数*/
void myFlush();

#endif