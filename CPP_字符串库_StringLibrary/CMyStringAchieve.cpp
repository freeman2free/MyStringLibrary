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
  // 获取传入参数的长度
  size_t nLen = _vscprintf(szFmt, arglist);
  //用长度开辟一段空间
  szFormat = new char[nLen + 1];

  if (szFormat == nullptr)
  {
    return str;
  }
  //格式化后的字符串传给开辟的空间
  vsprintf_s(szFormat, nLen + 1, szFmt, arglist);

  va_end(arglist);
  //copy给新建的对象
  str.StringCopy(szFormat);
  //释放空间
  delete[] szFormat;
  return str;
}

//=运算符重载(左值)
CMyString& CMyString::operator= (const CMyString& obj)
{
  this->StringCopy(obj.m_sz);
  return *this;
}

//=运算符重载(右值)
CMyString& CMyString::operator=(CMyString&& obj) noexcept
{
  FreeSpace(); //先释放自己
  m_sz = obj.m_sz;
  obj.m_sz = nullptr;
  return *this;
}

//+运算符重载(右值)
CMyString operator+(const CMyString& obj1, const CMyString& obj2)
{
  CMyString cmTmp = obj1;
  CMyString cmTmp2 = obj2 ;
  cmTmp = cmTmp.StringAppend(cmTmp2);
  return cmTmp;
}

//+=运算符重载(左值)
CMyString& CMyString::operator+= (const CMyString& obj)
{
  this->StringAppend(obj.m_sz);
  return *this;
}

//[]运算符重载
const char& CMyString::operator[](size_t nIndex)
{
  //判断下标是否越界
  if (nIndex > strlen(m_sz) || nIndex <= 0)
  {
    throw CException("数组下标越界", __FILE__, __FUNCTION__, __LINE__);
  }
  return At(nIndex);
}

//==运算符重载
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

//!=运算符重载
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

//>运算符重载
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

//<运算符重载
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

//<<运算符重载
ostream& operator<<(ostream& out, const CMyString& obj)
{
  out << obj.m_sz;
  return out;
}

//支持输入
istream& operator>>(istream& in, CMyString& obj)
{
  char* strBuf = new char[0x32]; //输入的缓冲区
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

//初始化函数（内部使用）
void CMyString::Init(const char* sz)
{
  //检查参数（在此处检查,就不用在构造和拷贝构造中重复检查了）
  if (sz == nullptr)
  {
    m_sz = nullptr;
    m_nBufSize = 0;
    return;
  }

  //申请内存，保存字符串
  m_nBufSize = strlen(sz) + 1; //获取要申请的内存空间长度
  m_sz = new char[m_nBufSize];//申请内存

  if (m_sz == nullptr)//如果申请失败就return
  {
    m_nBufSize = 0;
    return;
  }
  else
  {
    strcpy_s(m_sz, m_nBufSize, sz); //申请成功拷贝字符串到数据成员
  }

}
//为拷贝构造专门创建一个初始化函数
void CMyString::Init(const CMyString& obj)
{
  //检查参数（在此处检查,就不用在构造和拷贝构造中重复检查了）
  if (obj.m_sz == nullptr)
  {
    m_sz = nullptr;
    m_nBufSize = 0;
    return;
  }

  //申请内存，保存字符串
  m_nBufSize = strlen(obj.m_sz) + 1; //获取要申请的内存空间长度
  m_sz = new char[m_nBufSize];//申请内存

  if (m_sz == nullptr)//如果申请失败就return
  {
    m_nBufSize = 0;
    return;
  }
  else
  {
    strcpy_s(m_sz, m_nBufSize, obj.m_sz); //申请成功拷贝字符串到数据成员
  }

}

//释放函数
void CMyString::FreeSpace()
{
    if (m_sz != nullptr)
    {
      delete[] m_sz;

      m_sz = nullptr;
      m_nBufSize = 0;
    }
}

//有默认参的构造函数
CMyString::CMyString(const char* sz) 
{
  Init(sz);
}

//拷贝构造函数
CMyString::CMyString(const CMyString& obj)
{
  //申请内存,存储字符串给新对象
  Init(obj);
  
}

//移动构造函数
CMyString::CMyString(CMyString&& obj)noexcept
{
  m_sz = obj.m_sz;
  m_nBufSize = obj.m_nBufSize;
  obj.m_sz = nullptr;
  obj.m_nBufSize = 0;
}

//析构函数
CMyString::~CMyString()
{
  FreeSpace();
}

//判断长度(不含\0)
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
  assert(!(m_sz == nullptr || nIdx >= GetLength())); //通过断言来判断是否是非空参数以及下标是否合法
  return m_sz[nIdx];
}

//复制字符串
void CMyString::StringCopy(const char* str)
{
  //先判断参数是否合法
  if (str == nullptr)
  {
    FreeSpace();//释放原来的
    return;
  }

  //判断缓冲区是否能够放下
  if (m_nBufSize > strlen(str))
  {
    //内存足够,直接放入
    strcpy_s(m_sz, m_nBufSize, str);
    return;
  }
  else
  {
    //内存不够,重新申请
    FreeSpace();//先释放
    Init(str); //再申请新的内存存储字符串
  }
}

//复制字符串
void CMyString::StringCopy(const CMyString& str)
{
  return StringCopy(str.m_sz); //可以直接使用已经实现的函数
}

CMyString& CMyString::StringAppend(const char* str)
{
  //判断参数是否合法
  if (str == nullptr)
  {
    return *this;
  }

  //如果自己本身就为空
  if (m_sz == nullptr)
  {
    StringCopy(str); //相当于Copy了一份
    return *this;
  }

  //如果都不为空
  if (m_nBufSize > (strlen(str) + strlen(m_sz))) //先判断缓冲区是否足够(拼接是两个字符串相加的长度)
  {
    //内存足够直接追加
    strcat_s(m_sz, m_nBufSize,str);
  }
  else //目标内存不够
  {
    //用一个新的缓冲区进行拼接
    size_t nNewSize = strlen(str) + strlen(m_sz) + 1; //拼接后的总长度
    char* pNew = new char[nNewSize]; //申请新的缓冲区
    if (pNew == nullptr)
    {
      return *this;
    }

    strcpy_s(pNew, nNewSize, m_sz); //先将原来的字符串放入
    strcat_s(pNew, nNewSize, str);  //追加新的字符串完成拼接

    FreeSpace(); //释放掉原来的内存
    //赋值新的
    StringCopy(pNew); //利用copy函数传给该对象的m_sz,这样就可以释放指针了
    //m_sz = pNew; //将拼接好的字符串传给该对象
    //m_nBufSize = nNewSize;

    //释放掉免得出现内存泄露
    delete[]pNew;
    nNewSize = 0;
  }
  return *this;
}


CMyString& CMyString::StringAppend(const CMyString& str)
{
  return StringAppend(str.m_sz);
}

//寻找
int CMyString::StringFind(const char* str)
{
  char* pFind = nullptr; //用于接收查找到的首地址
  int nIdx = -1; //要返回的下标

  //判断参数是否合法
  if (str == nullptr)
  {
    goto END_FUNC;
  }

  //要查找的源字符串不能为空
  if (m_sz == nullptr)
  {
    goto END_FUNC;
  }

  //要查找的内容不能大于母串的长度
  if (m_nBufSize > strlen(str)+1)
  {
    pFind = strstr(m_sz, str); //找到子串在母串中出现的首地址
    if (pFind != NULL) //如果找到了
    {
      nIdx = (int)(pFind - m_sz); //与母串首地址相减得到的就是该子串首次出现的下标了
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

//字符串反向查找
int CMyString::StringReverseFind(const char* str)
{
  const char* pSearch = nullptr; //用于接收查找到的首地址
  int nIdx = -1; //要返回的下标
  int i = GetLength() - 1; //得到源字符串长度

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
    //从尾部遍历源字符串,并逐一比对
    while (i >= 0)
    {
      if (m_sz[i] != *pSearch) //如果不匹配
      {
        nIdx++; //nIdx+1
      }
      else if (m_sz[i] == *pSearch) //如果当前字符匹配
      {
        nIdx++; //nIdx+1
        pSearch--; //要搜索的子串-1
        if (*pSearch == NULL) //判断是否已经搜索完毕
        {
          pSearch = nullptr;
          break;//完毕就退出
        }
      }
      i--;
    }//end while

    if (i < 0 && *pSearch != NULL) //如果遍历完毕,而子串没有被搜索完的话表示没有找到
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

//从左侧开始提取
CMyString CMyString::LeftSubString(size_t nLen)
{
  return MidSubString(0, nLen);
}

//从右侧开始提取
CMyString CMyString::RightSubString(size_t nLen)
{
  return MidSubString(GetLength() - nLen, nLen);
}

//从指定下标处寻找指定长度字符串并返回
CMyString CMyString::MidSubString(size_t nIdx, size_t nLen)
{
  CMyString cStr;
  char* pStr = nullptr;
  int i = 0;
  size_t j = 0;

  if (nIdx < 0 || nIdx > GetLength()) //下标是否合法
  {
    goto END_SUB;
  }

  if (m_sz == nullptr)
  {
    goto END_SUB;
  }

  if (nLen > GetLength() - nIdx) //判断要获取的长度是否合法
  {
    goto END_SUB;
  }

  pStr = new char[nLen + 1]; //申请一个空间用于存放找到的字符串
  if (pStr != nullptr) //申请成功
  {
    for (i = nIdx, j = 0; j < nLen; i++, j++) //循环遍历指定长度,并从指定位置处将指定长度的字符串赋值给所开辟的空间
    {
      pStr[j] = m_sz[i];
    }
    pStr[j] = '\0'; //将字符串闭合
    cStr.StringCopy(pStr); //得到的字符串传给数据成员
  }
  //释放空间
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
  // 获取传入参数的长度
  size_t nLen = _vscprintf(szFmt, arglist);
  //用长度开辟一段空间
  szFormat = new char[nLen + 1];
  
  if (szFormat == nullptr)
  {
    return str;
  }
  //格式化后的字符串传给开辟的空间
  vsprintf_s(szFormat, nLen + 1, szFmt, arglist);

  va_end(arglist);
  //copy给新建的对象
  str.StringCopy(szFormat);
  //释放空间
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

