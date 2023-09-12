#pragma once
#ifndef CMYSTRING_H
#define CMYSTRING_H
#include <iostream>
#include "CException.h"
using namespace std;

class CMyString
{
public:
  CMyString(const char* sz = nullptr);//构造函数带默认参
  CMyString(const CMyString& obj); //拷贝构造函数
  CMyString(CMyString&& obj)noexcept;//移动构造
  ~CMyString(); //析构函数

  //获取字符串长度
  size_t GetLength();
  CMyString& GetString();
  //获取字符串中指定下标处的字符（返回类型为字符类型的引用,可以用于修改指定下标处的字符）
  char& At(size_t nIdx);

  //字符串拷贝（同时给一个函数重载,给两种类型的,使类的灵活性好一些）
  void StringCopy(const CMyString& str);
  void StringCopy(const char* str);

  //字符串拼接
  CMyString& StringAppend(const char* str);
  CMyString& StringAppend(const CMyString& str);

  //字符串查找(分为从前向后找和从后向前找两种)返回子字符串在母字符串中第一次出现的位置数
  int StringFind(const char* str);
  int StringFind(const CMyString& str);
  int StringReverseFind(const char* str); //以尾部为起点进行查找
  int StringReverseFind(const CMyString& str);

  //字符串提取子串（分为左侧提取 右侧提取 一般提取即指定下标位置提取）（返回类型为字符串类对象,为了便于拼接等操作）
  CMyString LeftSubString(size_t nLen);
  CMyString RightSubString(size_t nLen);
  CMyString MidSubString(size_t nIdx, size_t nLen);

  //格式化字符串
  CMyString& StringFormat(const char* szFmt, ...);

  //加入常成员函数，增加以下静态方法
  static CMyString ValueOf(bool b);  //true ==> "true"
  static CMyString ValueOf(char c);  //a ==> "a" 
  static CMyString ValueOf(double lf);  //3.5 ==>  "3.5" 
  static CMyString ValueOf(float f);  //4.5f ==> "4.5" 
  static CMyString ValueOf(int i);  //123 ==> "123" 
  static CMyString ValueOf(long li);  //123 ==> "123" 
  static CMyString ValueOf(short i);  //123 ==> "123" 
  static CMyString ValueOf(const char* data); //char[] = "123" ==> string "123" 
  static CMyString CopyValueOf(const char* data, int offset, int count); //char[] = "123" ==> string "123" 
  static CMyString StringFromFormat(const char* fmt, ...);  //("%d", 123) ==> string "123" 

  //增加以下运算符重载
  CMyString& operator= (const CMyString& obj); //左值
  CMyString& operator= (CMyString && obj)noexcept; //右值
  friend CMyString operator+(const CMyString& obj1, const CMyString& obj2);
  CMyString& operator+= (const CMyString& obj);
  const char& operator[](size_t nIndex); //返回类型前可以试着加个const让其只能读不能修改
  friend bool operator== (const CMyString& obj1, const CMyString& obj2);
  friend bool operator!= (const CMyString& obj1, const CMyString& obj2);
  friend bool operator> (const CMyString& obj1, const CMyString& obj2);
  friend bool operator< (const CMyString& obj1, const CMyString& obj2);
  explicit operator const char* ();
  explicit operator void* () const;
  CMyString operator() (size_t nIdx, size_t nLen); //截取指定长度字符串,仿函数
  friend ostream& operator<<(ostream& out, const CMyString& obj);
  friend istream& operator>>(istream& in, CMyString& obj);

private:
  void Init(const char* sz); //该函数仅用于内部调用.初始化时候使用
  void Init(const CMyString& obj); //该函数仅用于内部调用.初始化时候使用
  void FreeSpace();          //释放空间
private:          
  char* m_sz; //数据成员:字符串缓冲区
  size_t m_nBufSize; //数据成员:内存总大小.可能需要动态申请字符串的长度
  //size_t* m_nReferenceCnt; //引用计数(全部改为了深拷贝,因此貌似也就不需要这一项了)
};
#endif