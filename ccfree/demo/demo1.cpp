/*
 *  ��������demo1.cpp���˳�����ʾfreecplus�����STRCPY������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char str[11];   // �ַ���str�Ĵ�С��11�ֽڡ�

  STRCPY(str,sizeof(str),"freecplus");  // �����Ƶ�����û�г���str���Դ���ַ����Ĵ�С��
  printf("str=%s=\n",str);    // ��������str=freecplus=
  STRCPY(str,sizeof(str),"www.freecplus.net");  // �����Ƶ����ݳ�����str���Դ���ַ����Ĵ�С��
  printf("str=%s=\n",str);    // ��������str=www.freecp=
}

