/*
 *  ��������demo29.cpp���˳�����ʾfreecplus����е�CTimer�ࣨ��ʱ�������÷���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  CTimer Timer;

  printf("elapsed=%lf\n",Timer.Elapsed());
  sleep(1);
  printf("elapsed=%lf\n",Timer.Elapsed());
  sleep(1);
  printf("elapsed=%lf\n",Timer.Elapsed());
  usleep(1000);
  printf("elapsed=%lf\n",Timer.Elapsed());
  usleep(100);
  printf("elapsed=%lf\n",Timer.Elapsed());
  sleep(10);
  printf("elapsed=%lf\n",Timer.Elapsed());
}

