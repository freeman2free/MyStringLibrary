#pragma once
#include <string>
using namespace std;
class CException
{
public:
  CException(string strErr = 0, string strFile = 0, string strFuncName = 0, int nLine = 0) :
    m_strErr(strErr),
    m_strFile(strFile),
    m_strFuncName(strFuncName),
    m_nLineNum(nLine)
  {}

  string GetErrInfo();
  string GetFileInfo();
  int GetLineNum();
  string GetFuncInfo();

  void Reason();
private:
  string m_strErr; //错误的信息描述
  string m_strFile;//出错误的文件
  int    m_nLineNum; //捕获错误时在哪一行
  string m_strFuncName; //在哪个函数出错
};