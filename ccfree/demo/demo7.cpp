/*
 *  ��������demo7.cpp���˳�����ʾfreecplus�����SPRINTF������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char str[21];   // �ַ���str�Ĵ�С��21�ֽڡ�

  SPRINTF(str,sizeof(str),"name:%s,no:%d","messi",10);
  printf("str=%s=\n",str);    // ��������str=name:messi,no:10=

  SPRINTF(str,sizeof(str),"name:%s,no:%d,job:%s","messi",10,"striker");
  printf("str=%s=\n",str);    // ��������str=name:messi,no:10,job=
}

