/*
 *  ��������demo4.cpp���˳�����ʾfreecplus�����STRCAT������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char str[11];   // �ַ���str�Ĵ�С��11�ֽڡ�
  STRCPY(str,sizeof(str),"www");  

  STRCAT(str,sizeof(str),".fr");  // strԭ�е����ݼ��ϴ�׷�ӵ�����û�г���str���Դ�ŵĴ�С��
  printf("str=%s=\n",str);        // ��������str=www.fr=

  STRCAT(str,sizeof(str),"eecplus.net");  // strԭ�е����ݼ��ϴ�׷�ӵ����ݳ�����str���Դ�ŵĴ�С��
  printf("str=%s=\n",str);                // ��������str=www.freecp=
}

