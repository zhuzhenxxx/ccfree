/*
 *  ��������demo2.cpp���˳�����ʾfreecplus�����STRNCPY������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char str[11];   // �ַ���str�Ĵ�С��11�ֽڡ�

  STRNCPY(str,sizeof(str),"freecplus",5);  // �����Ƶ�����û�г���str���Դ���ַ����Ĵ�С��
  printf("str=%s=\n",str);    // ��������str=freec=
  STRNCPY(str,sizeof(str),"www.freecplus.net",8);  // �����Ƶ�����û�г���str���Դ���ַ����Ĵ�С��
  printf("str=%s=\n",str);    // ��������str=www.free=
  STRNCPY(str,sizeof(str),"www.freecplus.net",17);  // �����Ƶ����ݳ�����str���Դ���ַ����Ĵ�С��
  printf("str=%s=\n",str);    // ��������str=www.freecp=
}

