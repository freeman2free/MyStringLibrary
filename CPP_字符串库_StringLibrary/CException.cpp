#include <iostream>
#include "CException.h"
using namespace std;

string CException::GetErrInfo()
{
  return m_strErr;
}

string CException::GetFileInfo()
{
  return m_strFile;
}

int CException::GetLineNum()
{
  return m_nLineNum;
}

string CException::GetFuncInfo()
{
  return m_strFuncName;
}

void CException::Reason()
{
  //cout << "错误所在文件: " << m_strFile << endl;
  //cout << "错误所在行数: " << m_nLineNum << endl;
  //cout << "错误所在函数: " << m_strFuncName << endl;
  cout << "错误原因: " << m_strErr << endl;
}
