/*
 *  ��������demo24.cpp���˳�����ʾfreecplus�����LocalTimeʱ�亯����ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char strtime[20];
  memset(strtime,0,sizeof(strtime));

  LocalTime(strtime,"yyyy-mm-dd hh24:mi:ss",-30);  // ��ȡ30��ǰ��ʱ�䡣
  printf("strtime1=%s\n",strtime);

  LocalTime(strtime,"yyyy-mm-dd hh24:mi:ss");      // ��ȡ��ǰʱ�䡣
  printf("strtime2=%s\n",strtime);

  LocalTime(strtime,"yyyy-mm-dd hh24:mi:ss",30);   // ��ȡ30����ʱ�䡣
  printf("strtime3=%s\n",strtime);
}

