/*
 *  ��������demo5.cpp���˳�����ʾfreecplus�����STRNCAT������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char str[11];   // �ַ���str�Ĵ�С��11�ֽڡ�

  STRCPY(str,sizeof(str),"www");  
  STRNCAT(str,sizeof(str),".free",10);  // strԭ�е����ݼ��ϴ�׷�ӵ�����û�г���str���Դ�ŵĴ�С��
  printf("str=%s=\n",str);              // ��������str=www.free=

  STRCPY(str,sizeof(str),"www");  
  STRNCAT(str,sizeof(str),".freecplus.net",6);  // strԭ�е����ݼ��ϴ�׷�ӵ�����û�г���str���Դ�ŵĴ�С��
  printf("str=%s=\n",str);                      // ��������str=www.freec=

  STRCPY(str,sizeof(str),"www");  
  STRNCAT(str,sizeof(str),".freecplus.net",10); // strԭ�е����ݼ��ϴ�׷�ӵ����ݳ�����str���Դ�ŵĴ�С��
  printf("str=%s=\n",str);                      // ��������str=www.freecp=
}

