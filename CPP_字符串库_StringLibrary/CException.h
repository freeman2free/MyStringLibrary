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
  string m_strErr; //�������Ϣ����
  string m_strFile;//��������ļ�
  int    m_nLineNum; //�������ʱ����һ��
  string m_strFuncName; //���ĸ���������
};