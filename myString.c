#include "myString.h"

/*
* 处理溢出问题的参考资料：
* 针对这种由于输入了一个很大的数字转换之后会超过能够表示的最大的整数而导致的溢出情况，我们有两种处理方式可以选择：

一个取巧的方式是把转换后返回的值n定义成long long，即long long n；

另外一种则是只比较n和MAX_INT / 10的大小，即：
若n > MAX_INT / 10，那么说明最后一步转换时，n*10必定大于MAX_INT，所以在得知n > MAX_INT / 10时，当即返回MAX_INT。
若n == MAX_INT / 10时，那么比较最后一个数字c跟MAX_INT % 10的大小，即如果n == MAX_INT / 10且c > MAX_INT % 10，则照样返回MAX_INT。
对于上面第一种方式，虽然我们把n定义了长整型，但最后返回时系统会自动转换成整型。咱们下面主要来看第二种处理方式。

对于上面第二种方式，先举两个例子说明下：

如果我们要转换的字符串是"2147483697"，那么当我扫描到字符'9'时，判断出214748369 > MAX_INT / 10 = 2147483647 / 10 = 214748364（C语言里，整数相除自动取整，不留小数），则返回MAX_INT；
如果我们要转换的字符串是"2147483648"，那么判断最后一个字符'8'所代表的数字8与MAX_INT % 10 = 7的大小，前者大，依然返回MAX_INT。
一直以来，我们努力的目的归根结底是为了更好的处理溢出，但上述第二种处理方式考虑到直接计算n *10 + c 可能会大于MAX_INT导致溢出，那么便两边同时除以10，只比较n和MAX_INT / 10的大小，
从而巧妙的规避了计算n*10这一乘法步骤，转换成计算除法MAX_INT/10代替，不能不说此法颇妙。
*/
int myAtoi(const char* sz)
{
  int nRet = 0;
  _Bool bFlag;
  static const int MAX_INT = (int)((unsigned)~0 >> 1);      //有符号4字节整型正数最大范围
  static const int MIN_INT = -(int)((unsigned)~0 >> 1) - 1; //有符号4字节整型负数最大范围

  //1.检查参数
  if (sz == NULL)
  {
    return nRet;
  }

  //2.判断是否有空格,有就移至下一位
  while (*sz == ' ')
  {
    sz++;
  }

  //3.判断是否是负号
  if (*sz == '-')
  {
    bFlag = true; //是负号赋值为true
    sz++;
  }

  while (*sz >= '0' && *sz <= '9')//如果当前字符是数字则计算数值
  {
    //从左(数字高位)至右(数字低位)扫描字符串，把之前得到的数字乘以10，再加上当前字符表示的数字。
    nRet = nRet * 10 + (int)(*sz - '0'); 
    sz++;

    //4.1处理整型正溢出
    if (bFlag == false && 
      (nRet > MAX_INT/10 || (nRet == MAX_INT /10 && (*sz-'0') > MAX_INT %10))
      )
    {
      nRet = MAX_INT; //赋最大值,中断循环
      break;
    }
    //4.2处理整型负溢出
    else if (bFlag == true && 
      (nRet > (unsigned)MIN_INT / 10 || (nRet == (unsigned)MIN_INT / 10 && (*sz - '0') > (unsigned)MIN_INT % 10))
      )
    {
      nRet = MIN_INT;
      break; 
    }
  }
  return nRet * (bFlag ? -1 : 1); //返回值还需要加上符号
}

char* myStrcat(char *dst, const char *src)
{
    /*1.数组方式
    unsigned long long len = strlen(dst); //定义一个长度变量(dst的长度,即被追加的字符串的长度)
    int idx = 0;
    while(src[idx] != '\0'){
        dst[len] = src[idx];
        idx++;
        len++;
    }
    dst[len] = '\0'; //在末尾加上\0表示该字符串已结束
    return dst;
    */
    //2.指针方式
    assert(dst != NULL && src != NULL);
    char *ret = dst; //把dst指针的初始位置保存一下
    int iLen = myStrlen(dst);
    int iSrcLen = myStrlen(src);
    if(iLen+1 <= iSrcLen) // 判断目标字符串的长度是否能容纳源字符串
    {
        return NULL;
    }
    //遍历dst所指向的字符数组,使其指向字符串的结尾
    while(*dst)
    {
        dst++;
    }
    //如果src不是空的,那么将src里的字符逐一放到dst的后面
    while(*src != '\0')
    {
        *dst = *src; //简写一下,dst和src++可以合并到该赋值语句中
         dst++;
         src++;
    }
    *dst = '\0'; //末尾记得加\0
    return ret; //返回ret,因为此时的dst已经指向字符串末尾了
}

int myStrcmp(const char *str1, const char *str2)
{
     //1.数组的方式
//    int idx = 0;
    //只要满足该条件就进入循环idx+1,继续判断是否满足该条件,如不满足表示不相等,跳出循环
    //这个条件就是字符数组逐个元素的去对比看是否相等,且当前字符不是'\0'(如果是表示该字符串已经结束)
//    while (
    //str1[idx]==str2[idx] && 
    //(str1[idx] != '\0' || str2[idx] != '\0')
    //)
//    {
//        idx++;
//    }
//    return str1[idx]-str2[idx];
    //2.指针版本(使用指针遍历的方法)
    assert(str1 && str2);
    int ret = 0; //定义一个用于记录状态的变量,默认值为0表示情况2(src1==src2)
    while((*str1==*str2) && (*str1!='\0'))
    {
        str1++;
        str2++;
    }
    //如果第一个字符串的字符减去第二个字符串的字符不为0,说明不相等
    if((*str1 - *str2) != 0)
    {
        //情况1(str1>str2),将ret赋值为1
        if((*str1 - *str2)>0)
        {
            ret = 1;
        }
        else if((*str1 - *str2)<0)
        { 
            //情况3(str1<str2),将ret赋值为-1
            ret = -1;
        }
    }
    return ret;
}

char* myStrcpy(char *dst, char const *src)
{
    // 1.数组版本
    //int idx = 0; //设置一个index变量用于遍历(以及作为下标)
//    for (idx = 0; idx < strlen(src)+1; idx++) { //for版本,就不需要最后再将结尾的\0加上
//        dst[idx] = src[idx];
//    }
//while版本
//    while(src[idx] != '\0'){
//        dst[idx] = src[idx];
//        idx++;
//    }
//    dst[idx] = '\0'; //在dst的末尾加上\0表示该字符串已结束
//    return dst;

    // 2.指针版本
    char *ret = dst; //记录一下dst最初的指向
    assert(dst && src); //为了安全(不能传入空指针),需要先检测传入的字符指针是否为空
    
    //如果源字符数组不是\0那么就进入循环,将src当前指向的地址处的值赋给dst指向的地址,
    //然后逐个+1指向下一个地址
    while(*src && *dst)
    {
        //*dst++ = *src++;
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0'; //记住末尾要补\0,此时dst指向的是该数组末尾
    return ret; //返回ret指针因为它指向的是这个字符数组的最起始的地址,即dst[0]
}

int myStrlen(const char* sz)
{
	int ret = 0;
	assert(sz != NULL);	
	if( sz == NULL)
	{
		ret = -1;
	}
	else if( *sz == '\0' )
	{
		ret = 0;
	}
	else
	{
		while(*sz != '\0')
		{
			//遇见中文(多字节编码系统下)只需要判断第一个字节是否大于127(无符号char)或小于0(有符号char),
			//那么当前字节+下一个字节就等于一个中文汉字
			if(*sz > 127 || *sz < 0) 
			{
				sz+=2;
				ret++;
				continue;
			}
			else
			{
				sz++;
				ret++;
			}
	 	}	
	}
	 return ret;
}

char* myStrlwr(char* sz)
{
  char* ret = NULL;
  int i = 0;
  //判断参数是否有问题
  if (sz != NULL && sz[i] != '\0')
  {
    //遍历该字符串
    while (sz[i] != '\0')
    {
      //判断当前字符是否是大写
      if (sz[i] >= 0x41 && sz[i] <= 0x5A)
      {
        sz[i] = sz[i] + ('a' - 'A'); //变成小写
      }
      i++;
    }
    ret = sz;
  }
  return ret;
}

char* myStrupr(char* sz)
{
  char* ret = NULL;
  int i = 0;
  //判断参数是否有问题
  if (sz != NULL && sz[i] != '\0')
  {
    //遍历该字符串
    while (sz[i] != '\0')
    {
      //发现当前字符是小写
      if (sz[i] >= 0x61 && sz[i] <= 0x7A)
      {
        sz[i] = sz[i] - ('a' - 'A'); //变成大写
      }
      i++;
    }
    ret = sz;
  }
  return ret;
}


bool myStrslice(char* szSrc, char* szDst, int iStart, int iEnd)
{
  int iSrcLen = myStrlen(szSrc); // 源字符串的长度
  int iDstLen = myStrlen(szDst); // 目标字符串的长度
  if(iStart > iSrcLen && (iEnd-iStart) > iSrcLen && (iEnd-iStart) > iDstLen)
  {
    return false;
  }
  int iSize = (iEnd-iStart);
  for(size_t i = 0; i < iSize; i++)
  {
    szDst[i] = szSrc[iStart+i];
  }
  szDst[iSize] = '\0';
  return true;
}

char* myStrstr(const char* szBuffer, const char* szSubBuffer)
{
  // 判断参数是否为空
  assert(szBuffer != NULL && szSubBuffer != NULL);
  // 创建三个指针,用于保存并操作参数
  char* szStr1 = NULL;
  char* szStr2 = NULL;
  char* szCurrent = (char*)szBuffer; // 用于记录上次是从哪个位置开始匹配的,充当游标
  //如果子串为空,无法比较返回空
  if(*szSubBuffer == '\0')
  {
    return szBuffer;
  }
  //开始查找
  while(*szCurrent)
  {
    szStr1= szCurrent; // 如果没匹配到,那么当前要查找的字符串都会更新到下一个位置(可回溯)
    szStr2 = (char*)szSubBuffer; // 如果没匹配到,那么子串就恢复到初始状态
    
    while((*szStr1 != '\0') && (*szStr2 != '\0') && (*szStr1 == *szStr2))
    {
      szStr1++;
      szStr2++;
    }
    if(*szStr2 == '\0')
    {
      //如果子串遍历完毕了,说明匹配到了,返回找到的子串的起始位置
      return szCurrent;
    }
    if(*szStr1 == '\0')
    {
       //如果子串大于要查找的字符串,表示不可能查找到,直接返回空
      return NULL;
    }
    szCurrent++; // 本次没查找到,szCurrent向后偏移
  }
  return NULL; //如果进行到这里表示没有找到,返回空
}

void myStrreverse(char *sz, int iLen)
{
  assert(sz);
  int iStart = 0;
  int iEnd = iLen-1;
  if(sz[iEnd] == '\0')
  {
    iEnd--;
  }
  while(iStart < iEnd)
  {
    char* szTemp = sz[iStart];
    sz[iStart] = sz[iEnd];
    sz[iEnd] = szTemp;
    iEnd--;
    iStart++;
  }
}

char *myItoa(int iValue, char *szBuffer, int iRadix)
{
  int i = 0;
  bool bNegative = false; // 判断是否为负数,默认不是

  // 如果传入的数值是0,那么要将他变为字符0,并以\0结尾
  if(iValue == 0)
  {
    szBuffer[i] = '0';
    i++;
    szBuffer[i] = '\0';
    return szBuffer;
  }

  //itoa函数除了以10进制为基数需要判断有无符号以外(如果是负数先将其变为正整数)
  //其余进制都默认为无符号整数
  if(iValue < 0 && iRadix == 10)
  {
    bNegative = true;
    iValue = -iValue;
  }
  //通过分解逐个分解数位的方式,逐个变为字符串
  while(iValue != 0)
  {
    int iRem = iValue % iRadix;
    szBuffer[i] = (iRem > 9) ? (iRem - 10) + 'A' : iRem + '0';
    i++;
    iValue = iValue / iRadix;
  }

  //如果是负数,最后需要加上-号
  if(bNegative)
  {
    szBuffer[i] = '-';
    i++;
  }
  szBuffer[i] = '\0'; // 字符串结束符加上
  //此时的字符串是倒序,需要反转一下
  myStrreverse(szBuffer, i);
  return szBuffer;
}

void XorCrypton(char* szBuffer, int iSize, char cKey)
{
  if (szBuffer != NULL)
  {
    for (size_t i = 0; i < iSize; i++)
    {
      szBuffer[i] ^= cKey;
    }
  }
}

void myFlush()
{
  while(1)
  {
    char ch = getchar(); //读取输入缓冲区中的字符(相当于利用一个字符变量进行吸收,丢掉了该字符)

    if(ch == '\n') //直到读取到回车(因为回车意味着一个字符串输入的结束)跳出循环,这样就达到了清空输入缓冲区的目的,不至于妨碍下一次的输入
    {
      break;
    }
  }
}