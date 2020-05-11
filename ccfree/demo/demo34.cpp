/*
 *  ��������demo34.cpp���˳�����ʾfreecplus��ܵ��ļ������������÷�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  // ɾ���ļ���
  if (REMOVE("/tmp/root/_freecplus.h")==false)
  {
    printf("REMOVE(/tmp/root/_freecplus.h) %d:%s\n",errno,strerror(errno));
  }

  // �������ļ���
  if (RENAME("/tmp/root/freecplus.cpp","/tmp/root/aaa/bbb/ccc/freecplus.cpp")==false)
  {
    printf("RENAME(/tmp/root/freecplus.cpp) %d:%s\n",errno,strerror(errno));
  }
  
  // �����ļ���
  if (COPY("/freecplus/_freecplus.h","/tmp/root/aaa/bbb/ccc/_freecplus.h")==false)
  {
    printf("COPY(/freecplus/_freecplus.h) %d:%s\n",errno,strerror(errno));
  }

  // ��ȡ�ļ��Ĵ�С��
  printf("size=%d\n",FileSize("/freecplus/_freecplus.h"));

  // �����ļ���ʱ�䡣
  UTime("/freecplus/_freecplus.h","2020-01-05 13:37:29");

  // ��ȡ�ļ���ʱ�䡣
  char mtime[21]; memset(mtime,0,sizeof(mtime));
  FileMTime("/freecplus/_freecplus.h",mtime,"yyyy-mm-dd hh24:mi:ss");
  printf("mtime=%s\n",mtime);   // ���mtime=2020-01-05 13:37:29
}

