#pragma once
#ifndef CMYSTRING_H
#define CMYSTRING_H
#include <iostream>
#include "CException.h"
using namespace std;

class CMyString
{
public:
  CMyString(const char* sz = nullptr);//���캯����Ĭ�ϲ�
  CMyString(const CMyString& obj); //�������캯��
  CMyString(CMyString&& obj)noexcept;//�ƶ�����
  ~CMyString(); //��������

  //��ȡ�ַ�������
  size_t GetLength();
  CMyString& GetString();
  //��ȡ�ַ�����ָ���±괦���ַ�����������Ϊ�ַ����͵�����,���������޸�ָ���±괦���ַ���
  char& At(size_t nIdx);

  //�ַ���������ͬʱ��һ����������,���������͵�,ʹ�������Ժ�һЩ��
  void StringCopy(const CMyString& str);
  void StringCopy(const char* str);

  //�ַ���ƴ��
  CMyString& StringAppend(const char* str);
  CMyString& StringAppend(const CMyString& str);

  //�ַ�������(��Ϊ��ǰ����ҺʹӺ���ǰ������)�������ַ�����ĸ�ַ����е�һ�γ��ֵ�λ����
  int StringFind(const char* str);
  int StringFind(const CMyString& str);
  int StringReverseFind(const char* str); //��β��Ϊ�����в���
  int StringReverseFind(const CMyString& str);

  //�ַ�����ȡ�Ӵ�����Ϊ�����ȡ �Ҳ���ȡ һ����ȡ��ָ���±�λ����ȡ������������Ϊ�ַ��������,Ϊ�˱���ƴ�ӵȲ�����
  CMyString LeftSubString(size_t nLen);
  CMyString RightSubString(size_t nLen);
  CMyString MidSubString(size_t nIdx, size_t nLen);

  //��ʽ���ַ���
  CMyString& StringFormat(const char* szFmt, ...);

  //���볣��Ա�������������¾�̬����
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

  //�����������������
  CMyString& operator= (const CMyString& obj); //��ֵ
  CMyString& operator= (CMyString && obj)noexcept; //��ֵ
  friend CMyString operator+(const CMyString& obj1, const CMyString& obj2);
  CMyString& operator+= (const CMyString& obj);
  const char& operator[](size_t nIndex); //��������ǰ�������żӸ�const����ֻ�ܶ������޸�
  friend bool operator== (const CMyString& obj1, const CMyString& obj2);
  friend bool operator!= (const CMyString& obj1, const CMyString& obj2);
  friend bool operator> (const CMyString& obj1, const CMyString& obj2);
  friend bool operator< (const CMyString& obj1, const CMyString& obj2);
  explicit operator const char* ();
  explicit operator void* () const;
  CMyString operator() (size_t nIdx, size_t nLen); //��ȡָ�������ַ���,�º���
  friend ostream& operator<<(ostream& out, const CMyString& obj);
  friend istream& operator>>(istream& in, CMyString& obj);

private:
  void Init(const char* sz); //�ú����������ڲ�����.��ʼ��ʱ��ʹ��
  void Init(const CMyString& obj); //�ú����������ڲ�����.��ʼ��ʱ��ʹ��
  void FreeSpace();          //�ͷſռ�
private:          
  char* m_sz; //���ݳ�Ա:�ַ���������
  size_t m_nBufSize; //���ݳ�Ա:�ڴ��ܴ�С.������Ҫ��̬�����ַ����ĳ���
  //size_t* m_nReferenceCnt; //���ü���(ȫ����Ϊ�����,���ò��Ҳ�Ͳ���Ҫ��һ����)
};
#endif