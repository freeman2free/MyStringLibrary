#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "CMyStringAchieve.h"
using namespace std;

CMyString CMyString::StringFromFormat(const char* szFmt, ...)
{
  CMyString str;
  char* szFormat = nullptr;
  va_list arglist;
  va_start(arglist, szFmt);
  // ��ȡ��������ĳ���
  size_t nLen = _vscprintf(szFmt, arglist);
  //�ó��ȿ���һ�οռ�
  szFormat = new char[nLen + 1];

  if (szFormat == nullptr)
  {
    return str;
  }
  //��ʽ������ַ����������ٵĿռ�
  vsprintf_s(szFormat, nLen + 1, szFmt, arglist);

  va_end(arglist);
  //copy���½��Ķ���
  str.StringCopy(szFormat);
  //�ͷſռ�
  delete[] szFormat;
  return str;
}

//=���������(��ֵ)
CMyString& CMyString::operator= (const CMyString& obj)
{
  this->StringCopy(obj.m_sz);
  return *this;
}

//=���������(��ֵ)
CMyString& CMyString::operator=(CMyString&& obj) noexcept
{
  FreeSpace(); //���ͷ��Լ�
  m_sz = obj.m_sz;
  obj.m_sz = nullptr;
  return *this;
}

//+���������(��ֵ)
CMyString operator+(const CMyString& obj1, const CMyString& obj2)
{
  CMyString cmTmp = obj1;
  CMyString cmTmp2 = obj2 ;
  cmTmp = cmTmp.StringAppend(cmTmp2);
  return cmTmp;
}

//+=���������(��ֵ)
CMyString& CMyString::operator+= (const CMyString& obj)
{
  this->StringAppend(obj.m_sz);
  return *this;
}

//[]���������
const char& CMyString::operator[](size_t nIndex)
{
  //�ж��±��Ƿ�Խ��
  if (nIndex > strlen(m_sz) || nIndex <= 0)
  {
    throw CException("�����±�Խ��", __FILE__, __FUNCTION__, __LINE__);
  }
  return At(nIndex);
}

//==���������
bool operator== (const CMyString& obj1, const CMyString& obj2)
{
  bool bRet = true;
  int nRet = strcmp(obj1.m_sz, obj2.m_sz);
  if (nRet > 0 || nRet < 0)
  {
    bRet = false;
  }
  return bRet;
}

//!=���������
bool operator!=(const CMyString& obj1, const CMyString& obj2)
{
  bool bRet = true;
  int nRet = strcmp(obj1.m_sz, obj2.m_sz);
  if (nRet == 0)
  {
    bRet = false;
  }
  return bRet;
}

//>���������
bool operator>(const CMyString& obj1, const CMyString& obj2)
{
  bool bRet = true;
  int nRet = strcmp(obj1.m_sz, obj2.m_sz);
  if (nRet == 0 || nRet < 0)
  {
    bRet = false;
  }
  return bRet;
}

//<���������
bool operator<(const CMyString& obj1, const CMyString& obj2)
{
  bool bRet = true;
  int nRet = strcmp(obj1.m_sz, obj2.m_sz);
  if (nRet == 0 || nRet > 0)
  {
    bRet = false;
  }
  return bRet;
}

//<<���������
ostream& operator<<(ostream& out, const CMyString& obj)
{
  out << obj.m_sz;
  return out;
}

//֧������
istream& operator>>(istream& in, CMyString& obj)
{
  char* strBuf = new char[0x32]; //����Ļ�����
  if (strBuf != nullptr)
  {
    in >> strBuf;
    obj.StringCopy(strBuf);

    delete[] strBuf;
  }
  
  return in;
}


CMyString::operator const char* ()
{
  return m_sz;
}

CMyString::operator void* () const
{
  return m_sz;
}

CMyString CMyString::operator()(size_t nIdx, size_t nLen)
{
  return MidSubString(nIdx, nLen);
}

//��ʼ���������ڲ�ʹ�ã�
void CMyString::Init(const char* sz)
{
  //���������ڴ˴����,�Ͳ����ڹ���Ϳ����������ظ�����ˣ�
  if (sz == nullptr)
  {
    m_sz = nullptr;
    m_nBufSize = 0;
    return;
  }

  //�����ڴ棬�����ַ���
  m_nBufSize = strlen(sz) + 1; //��ȡҪ������ڴ�ռ䳤��
  m_sz = new char[m_nBufSize];//�����ڴ�

  if (m_sz == nullptr)//�������ʧ�ܾ�return
  {
    m_nBufSize = 0;
    return;
  }
  else
  {
    strcpy_s(m_sz, m_nBufSize, sz); //����ɹ������ַ��������ݳ�Ա
  }

}
//Ϊ��������ר�Ŵ���һ����ʼ������
void CMyString::Init(const CMyString& obj)
{
  //���������ڴ˴����,�Ͳ����ڹ���Ϳ����������ظ�����ˣ�
  if (obj.m_sz == nullptr)
  {
    m_sz = nullptr;
    m_nBufSize = 0;
    return;
  }

  //�����ڴ棬�����ַ���
  m_nBufSize = strlen(obj.m_sz) + 1; //��ȡҪ������ڴ�ռ䳤��
  m_sz = new char[m_nBufSize];//�����ڴ�

  if (m_sz == nullptr)//�������ʧ�ܾ�return
  {
    m_nBufSize = 0;
    return;
  }
  else
  {
    strcpy_s(m_sz, m_nBufSize, obj.m_sz); //����ɹ������ַ��������ݳ�Ա
  }

}

//�ͷź���
void CMyString::FreeSpace()
{
    if (m_sz != nullptr)
    {
      delete[] m_sz;

      m_sz = nullptr;
      m_nBufSize = 0;
    }
}

//��Ĭ�ϲεĹ��캯��
CMyString::CMyString(const char* sz) 
{
  Init(sz);
}

//�������캯��
CMyString::CMyString(const CMyString& obj)
{
  //�����ڴ�,�洢�ַ������¶���
  Init(obj);
  
}

//�ƶ����캯��
CMyString::CMyString(CMyString&& obj)noexcept
{
  m_sz = obj.m_sz;
  m_nBufSize = obj.m_nBufSize;
  obj.m_sz = nullptr;
  obj.m_nBufSize = 0;
}

//��������
CMyString::~CMyString()
{
  FreeSpace();
}

//�жϳ���(����\0)
size_t CMyString::GetLength()
{
  return m_sz!=nullptr ? strlen(m_sz) : 0;
}


CMyString& CMyString::GetString()
{
  return *this;
}

char& CMyString::At(size_t nIdx)
{
  assert(!(m_sz == nullptr || nIdx >= GetLength())); //ͨ���������ж��Ƿ��Ƿǿղ����Լ��±��Ƿ�Ϸ�
  return m_sz[nIdx];
}

//�����ַ���
void CMyString::StringCopy(const char* str)
{
  //���жϲ����Ƿ�Ϸ�
  if (str == nullptr)
  {
    FreeSpace();//�ͷ�ԭ����
    return;
  }

  //�жϻ������Ƿ��ܹ�����
  if (m_nBufSize > strlen(str))
  {
    //�ڴ��㹻,ֱ�ӷ���
    strcpy_s(m_sz, m_nBufSize, str);
    return;
  }
  else
  {
    //�ڴ治��,��������
    FreeSpace();//���ͷ�
    Init(str); //�������µ��ڴ�洢�ַ���
  }
}

//�����ַ���
void CMyString::StringCopy(const CMyString& str)
{
  return StringCopy(str.m_sz); //����ֱ��ʹ���Ѿ�ʵ�ֵĺ���
}

CMyString& CMyString::StringAppend(const char* str)
{
  //�жϲ����Ƿ�Ϸ�
  if (str == nullptr)
  {
    return *this;
  }

  //����Լ������Ϊ��
  if (m_sz == nullptr)
  {
    StringCopy(str); //�൱��Copy��һ��
    return *this;
  }

  //�������Ϊ��
  if (m_nBufSize > (strlen(str) + strlen(m_sz))) //���жϻ������Ƿ��㹻(ƴ���������ַ�����ӵĳ���)
  {
    //�ڴ��㹻ֱ��׷��
    strcat_s(m_sz, m_nBufSize,str);
  }
  else //Ŀ���ڴ治��
  {
    //��һ���µĻ���������ƴ��
    size_t nNewSize = strlen(str) + strlen(m_sz) + 1; //ƴ�Ӻ���ܳ���
    char* pNew = new char[nNewSize]; //�����µĻ�����
    if (pNew == nullptr)
    {
      return *this;
    }

    strcpy_s(pNew, nNewSize, m_sz); //�Ƚ�ԭ�����ַ�������
    strcat_s(pNew, nNewSize, str);  //׷���µ��ַ������ƴ��

    FreeSpace(); //�ͷŵ�ԭ�����ڴ�
    //��ֵ�µ�
    StringCopy(pNew); //����copy���������ö����m_sz,�����Ϳ����ͷ�ָ����
    //m_sz = pNew; //��ƴ�Ӻõ��ַ��������ö���
    //m_nBufSize = nNewSize;

    //�ͷŵ���ó����ڴ�й¶
    delete[]pNew;
    nNewSize = 0;
  }
  return *this;
}


CMyString& CMyString::StringAppend(const CMyString& str)
{
  return StringAppend(str.m_sz);
}

//Ѱ��
int CMyString::StringFind(const char* str)
{
  char* pFind = nullptr; //���ڽ��ղ��ҵ����׵�ַ
  int nIdx = -1; //Ҫ���ص��±�

  //�жϲ����Ƿ�Ϸ�
  if (str == nullptr)
  {
    goto END_FUNC;
  }

  //Ҫ���ҵ�Դ�ַ�������Ϊ��
  if (m_sz == nullptr)
  {
    goto END_FUNC;
  }

  //Ҫ���ҵ����ݲ��ܴ���ĸ���ĳ���
  if (m_nBufSize > strlen(str)+1)
  {
    pFind = strstr(m_sz, str); //�ҵ��Ӵ���ĸ���г��ֵ��׵�ַ
    if (pFind != NULL) //����ҵ���
    {
      nIdx = (int)(pFind - m_sz); //��ĸ���׵�ַ����õ��ľ��Ǹ��Ӵ��״γ��ֵ��±���
    }
    else
    {
      pFind = nullptr;
    }
  }

END_FUNC:
  return nIdx;
}

int CMyString::StringFind(const CMyString& str)
{
  return StringFind(str.m_sz);
}

//�ַ����������
int CMyString::StringReverseFind(const char* str)
{
  const char* pSearch = nullptr; //���ڽ��ղ��ҵ����׵�ַ
  int nIdx = -1; //Ҫ���ص��±�
  int i = GetLength() - 1; //�õ�Դ�ַ�������

  if (str == nullptr)
  {
    goto END_FUNC;
  }
  if (m_sz == nullptr)
  {
    goto END_FUNC;
  }

  while (*str != '\0')
  {
    str++;
  }
  str--;

  pSearch = str;
  if (pSearch != nullptr)
  {
    //��β������Դ�ַ���,����һ�ȶ�
    while (i >= 0)
    {
      if (m_sz[i] != *pSearch) //�����ƥ��
      {
        nIdx++; //nIdx+1
      }
      else if (m_sz[i] == *pSearch) //�����ǰ�ַ�ƥ��
      {
        nIdx++; //nIdx+1
        pSearch--; //Ҫ�������Ӵ�-1
        if (*pSearch == NULL) //�ж��Ƿ��Ѿ��������
        {
          pSearch = nullptr;
          break;//��Ͼ��˳�
        }
      }
      i--;
    }//end while

    if (i < 0 && *pSearch != NULL) //����������,���Ӵ�û�б�������Ļ���ʾû���ҵ�
    {
      nIdx = -1;
    }
  }


END_FUNC:
  return nIdx;
}


int CMyString::StringReverseFind(const CMyString& str)
{
  return StringReverseFind(str.m_sz);
}

//����࿪ʼ��ȡ
CMyString CMyString::LeftSubString(size_t nLen)
{
  return MidSubString(0, nLen);
}

//���Ҳ࿪ʼ��ȡ
CMyString CMyString::RightSubString(size_t nLen)
{
  return MidSubString(GetLength() - nLen, nLen);
}

//��ָ���±괦Ѱ��ָ�������ַ���������
CMyString CMyString::MidSubString(size_t nIdx, size_t nLen)
{
  CMyString cStr;
  char* pStr = nullptr;
  int i = 0;
  size_t j = 0;

  if (nIdx < 0 || nIdx > GetLength()) //�±��Ƿ�Ϸ�
  {
    goto END_SUB;
  }

  if (m_sz == nullptr)
  {
    goto END_SUB;
  }

  if (nLen > GetLength() - nIdx) //�ж�Ҫ��ȡ�ĳ����Ƿ�Ϸ�
  {
    goto END_SUB;
  }

  pStr = new char[nLen + 1]; //����һ���ռ����ڴ���ҵ����ַ���
  if (pStr != nullptr) //����ɹ�
  {
    for (i = nIdx, j = 0; j < nLen; i++, j++) //ѭ������ָ������,����ָ��λ�ô���ָ�����ȵ��ַ�����ֵ�������ٵĿռ�
    {
      pStr[j] = m_sz[i];
    }
    pStr[j] = '\0'; //���ַ����պ�
    cStr.StringCopy(pStr); //�õ����ַ����������ݳ�Ա
  }
  //�ͷſռ�
  delete [] pStr; 
  pStr = nullptr;
END_SUB:
  return cStr;
}

CMyString& CMyString::StringFormat(const char* szFmt, ...)
{
  CMyString str;
  char* szFormat = nullptr;
  va_list arglist;
  va_start(arglist, szFmt);
  // ��ȡ��������ĳ���
  size_t nLen = _vscprintf(szFmt, arglist);
  //�ó��ȿ���һ�οռ�
  szFormat = new char[nLen + 1];
  
  if (szFormat == nullptr)
  {
    return str;
  }
  //��ʽ������ַ����������ٵĿռ�
  vsprintf_s(szFormat, nLen + 1, szFmt, arglist);

  va_end(arglist);
  //copy���½��Ķ���
  str.StringCopy(szFormat);
  //�ͷſռ�
  delete[] szFormat;
  return str;
}

CMyString CMyString::ValueOf(bool b)
{
  return StringFromFormat("%s", b ? "true" : "false");
}

CMyString CMyString::ValueOf(char c)
{
  return StringFromFormat("%c", c);
}

CMyString CMyString::ValueOf(double lf)
{
  return StringFromFormat("%.2lf", lf);
}

CMyString CMyString::ValueOf(float f)
{
  return StringFromFormat("%.2f", f);
}

CMyString CMyString::ValueOf(int i)
{
  return StringFromFormat("%d", i);
}

CMyString CMyString::ValueOf(long li)
{
  return StringFromFormat("%ld", li);
}

CMyString CMyString::ValueOf(short hi)
{
  return StringFromFormat("%hd", hi);
}

CMyString CMyString::ValueOf(const char* data)
{
  return StringFromFormat("%s", data);
}

CMyString CMyString::CopyValueOf(const char* data, int offset, int count)
{
  return StringFromFormat("%s %d %d", data, offset, count);
}

