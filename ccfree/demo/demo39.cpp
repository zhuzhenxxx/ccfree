/*
 *  ��������demo39.cpp���˳�����ʾfreecplus����в���CFile�����������ļ����÷���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  CFile File;

  char strLocalTime[21];   // ���ڴ��ϵͳ��ǰ��ʱ�䣬��ʽyyyymmddhh24miss��
  memset(strLocalTime,0,sizeof(strLocalTime));
  LocalTime(strLocalTime,"yyyymmddhh24miss");  // ��ȡϵͳ��ǰʱ�䡣
  
  // ���ɾ���·�����ļ�����Ŀ¼/tmp/data���ļ�����ǰ׺(surfdata_)+ʱ��+��׺(.xml)��
  char strFileName[301];
  SNPRINTF(strFileName,sizeof(strFileName),300,"/tmp/data/surfdata_%s.xml",strLocalTime);

  // ����OpenForRename�����ļ���ʵ�ʴ������ļ�������/tmp/data/surfdata_20200101123000.xml.tmp��
  if (File.OpenForRename(strFileName,"w")==false)
  {
    printf("File.OpenForRename(%s) failed.\n",strFileName); return -1;
  }

  // ������Բ������ļ�д�����ݵĴ��롣
  // д���ı�������Fprintf������д�������������Fwrite������

  // ���ļ���д�����г�Ů���ݡ�
  File.Fprintf("<data>\n"\
     "<name>���</name><age>28</age><sc>����</sc><yz>Ư��</yz><memo>��Ҫ��������ʲô�¡�</memo><endl/>\n"\
     "<name>��ʩ</name><age>25</age><sc>����</sc><yz>Ư��</yz><memo>1���й�������һ����Ů��\n"\
     "2���������Ƿ�󻣻\n"\
     "3���Ϲ��Ƿ�������Ū���ˡ�</memo><endl/>\n"\
     "</data>\n");

  sleep(30);   // ֹͣ30�룬��ls /tmp/data/*.tmp���Կ������ɵ���ʱ�ļ���

  // �ر��ļ�ָ�룬������ʱ�ļ�����Ϊ��ʽ���ļ�����
  // ע�⣬������File.Close()����ΪClose�����ǹر��ļ�ָ�룬��ɾ����ʱ�ļ���
  // CFile��������������õ���Close������
  File.CloseAndRename();
}

