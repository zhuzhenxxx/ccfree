/*
 *  ��������demo26.cpp���˳�����ʾfreecplus�����������ʾ��ʱ����ַ�����ʾ��ʱ��֮���ת����
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  time_t ltime;
  char strtime[20];

  memset(strtime,0,sizeof(strtime));
  strcpy(strtime,"2020-01-01 12:35:22");

  ltime=strtotime(strtime);    // ת��Ϊ������ʱ��
  printf("ltime=%ld\n",ltime); // ���ltime=1577853322
  
  memset(strtime,0,sizeof(strtime));
  timetostr(ltime,strtime,"yyyy-mm-dd hh24:mi:ss");  // ת��Ϊ�ַ�����ʱ��
  printf("strtime=%s\n",strtime);     // ���strtime=2020-01-01 12:35:22
}

