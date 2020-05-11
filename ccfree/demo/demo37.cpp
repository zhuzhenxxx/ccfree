/*
 *  ��������demo37.cpp���˳�����ʾfreecplus�����FGETS�������÷���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  FILE *fp=0;

  if ( (fp=FOPEN("/tmp/aaa/bbb/ccc/tmp.xml","r"))==0)
  {
    printf("FOPEN(/tmp/aaa/bbb/ccc/tmp.xml) %d:%s\n",errno,strerror(errno)); return -1;
  }

  char strBuffer[301];

  while (true)
  {
    memset(strBuffer,0,sizeof(strBuffer));
    if (FGETS(fp,strBuffer,300)==false) break;     // ��������"\n"������
    //if (FGETS(fp,strBuffer,300,"<endl/>")==false) break; // ��������"<endl/>"������

    printf("strBuffer=%s",strBuffer);
  }

  fclose(fp);
}

