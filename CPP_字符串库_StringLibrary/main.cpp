// CMyString: 创建一个自己的字符串操作类
#include <iostream>
#include "CMyStringAchieve.h"
//#include <string>
//#include <string.h>
using namespace std;


int main()
{

  //CMyString str{ R"(D:\c++work\CMyString\CMyString\CMyString.sln)" };
  char* strSz = (char*)"你好中国";
  CMyString strN{ strSz };
  CMyString strF{ strN };
  cout << strF(0,8) << endl;
  cout << strN << endl;
  cout << strF << endl;
  /*size_t nLen = 0;
  int nIdx = 0;

  //找到盘符
  nIdx = str.StringFind("\\");//先找到盘符
  CMyString str2 = str.LeftSubString(nIdx); //盘符已找到
  cout << str2 << endl;
  //找到文件后缀名
  nIdx = str.StringReverseFind(".sln");
  CMyString str3 = str.RightSubString(nIdx);

  //找到文件名
  nIdx = str.StringReverseFind("CMyString");
  CMyString str4 = str.RightSubString(nIdx+1);

  //格式化字符串
  CMyString& str5 =  str4.StringFormat("%d %d %d", 3, 1, 5);

  //
  CMyString str6 = CMyString::ValueOf(12.3);
  CMyString str7 = CMyString::ValueOf(true);

  CMyString str8("Helloworld");
  CMyString str9("Test");
  CMyString str10("Helloworld3");
  str10 = str8 + str9;
  str9 += str8;
  bool bRet = (str9 == str8);
  cout << bRet << endl;
  bRet = (str9 != str8);
  cout << bRet << endl;

  bRet = (str10 > str8);
  cout << bRet << endl;
  bRet = (str10 < str8);
  cout << bRet << endl;

  cout << str10 << endl;*/
}