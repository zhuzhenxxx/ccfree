/*
 *  ��������demo36.cpp���˳�����ʾfreecplus�����FOPEN�������÷���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  FILE *fp=0;

  // ��FOPEN��������fopen�⺯�������Ŀ¼/tmp/aaa/bbb/ccc�����ڣ��ᴴ������
  if ( (fp=FOPEN("/tmp/aaa/bbb/ccc/tmp.xml","w"))==0)   
  {
    printf("FOPEN(/tmp/aaa/bbb/ccc/tmp.xml) %d:%s\n",errno,strerror(errno)); return -1;
  }

  // ���ļ���д�����г�Ů���ݡ�
  fprintf(fp,"<data>\n"\
     "<name>���</name><age>28</age><sc>����</sc><yz>Ư��</yz><memo>��Ҫ��������ʲô�¡�</memo><endl/>\n"\
     "<name>��ʩ</name><age>25</age><sc>����</sc><yz>Ư��</yz><memo>1���й�������һ����Ů��\n"\
     "2���������Ƿ�󻣻\n"\
     "3���Ϲ��Ƿ�������Ū���ˡ�</memo><endl/>\n"\
     "</data>\n");

  fclose(fp);  // �ر��ļ���
}

