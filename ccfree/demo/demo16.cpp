/*
 *  ��������demo16.cpp���˳�����ʾfreecplus�����PickNumber������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char str[26];   // �ַ���str�Ĵ�С��11�ֽڡ�

  STRCPY(str,sizeof(str),"iab+12.3xy");
  PickNumber(str,str,false,false);
  printf("str=%s=\n",str);    // ��������str=123=

  STRCPY(str,sizeof(str),"iab+12.3xy");
  PickNumber(str,str,true,false);
  printf("str=%s=\n",str);    // ��������str=+123=

  STRCPY(str,sizeof(str),"iab+12.3xy");
  PickNumber(str,str,true,true);
  printf("str=%s=\n",str);    // ��������str=-12.3=
}

