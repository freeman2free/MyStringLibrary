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
  //cout << "���������ļ�: " << m_strFile << endl;
  //cout << "������������: " << m_nLineNum << endl;
  //cout << "�������ں���: " << m_strFuncName << endl;
  cout << "����ԭ��: " << m_strErr << endl;
}
