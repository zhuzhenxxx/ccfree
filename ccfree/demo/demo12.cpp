/*
 *  ��������demo12.cpp���˳�����ʾfreecplus������ַ�����Сдת��������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char str1[31];   // C���Է����ַ�����

  STRCPY(str1,sizeof(str1),"12abz45ABz8��ʩ��");
  ToUpper(str1);      // ��str1�е�Сд��ĸת��Ϊ��д��
  printf("str1=%s=\n",str1);    // ��������str1=12ABZ45ABZ8��ʩ��=

  STRCPY(str1,sizeof(str1),"12abz45ABz8��ʩ��");
  ToLower(str1);      // ��str1�еĴ�д��ĸת��ΪСд��
  printf("str1=%s=\n",str1);    // ��������str1=12abz45abz8��ʩ��=

  string str2;    // C++���Է����ַ�����
  
  str2="12abz45ABz8��ʩ��";
  ToUpper(str2);      // ��str2�е�Сд��ĸת��Ϊ��д��
  printf("str2=%s=\n",str2.c_str());    // ��������str2=12ABZ45ABZ8��ʩ��=

  str2="12abz45ABz8��ʩ��";
  ToLower(str2);      // ��str2�еĴ�д��ĸת��ΪСд��
  printf("str2=%s=\n",str2.c_str());    // ��������str1=12abz45abz8��ʩ��=
}

