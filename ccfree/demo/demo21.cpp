/*
 *  ��������demo21.cpp���˳�����ʾfreecplus��ܵ�ͳ���ַ��������ĺ�����
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char buffer[301];  
  STRCPY(buffer,sizeof(buffer),"messi,10,true,30,68.5,2100000,Barcelona��");
  printf("words=%d\n",Words(buffer)); // ������:words=40

  STRCPY(buffer,sizeof(buffer),"÷��,10,true,30,68.5,2100000,Barcelona��");
  printf("words=%d\n",Words(buffer)); // ������:words=37
}

