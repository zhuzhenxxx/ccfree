/*
 *  ��������demo42.cpp���˳�����ʾ����freecplus��ܵ�CLogFile���¼�����������־��
 *  �������޸�demo40.cpp�������printf����Ϊд��־�ļ���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  CLogFile logfile;

  // ����־�ļ������"/tmp/log"�����ڣ��ʹ�����������Ҫȷ����ǰ�û��߱�����Ŀ¼��Ȩ�ޡ�
  if (logfile.Open("/tmp/log/demo42.log")==false)
  { printf("logfile.Open(/tmp/log/demo42.log) failed.\n"); return -1; }

  logfile.Write("demo42����ʼ���С�\n");

  CDir Dir;

  // ɨ��/tmp/dataĿ¼���ļ���ƥ��"surfdata_*.xml"���ļ���
  if (Dir.OpenDir("/tmp/data","surfdata_*.xml")==false)
  { logfile.Write("Dir.OpenDir(/tmp/data) failed.\n"); return -1; }

  CFile File;

  while (Dir.ReadDir()==true)
  {
    logfile.Write("�����ļ�%s...",Dir.m_FullFileName);

    if (File.Open(Dir.m_FullFileName,"r")==false)
    { logfile.WriteEx("failed.File.Open(%s) failed.\n",Dir.m_FullFileName); return -1; }

    // ������Բ����ȡ�����ļ������ݡ�����xml�ַ�����������д�����ݿ�Ĵ��롣
    // ��ȡ�ı�������Fgets��FFGETS��������ȡ������������Fread������
    // ����Ĵ����ҾͲ�д�ˡ�

    // �������ļ��е����ݺ󣬹ر��ļ�ָ�룬��ɾ���ļ���
    File.CloseAndRemove();

    logfile.WriteEx("ok\n");
  }

  logfile.Write("demo42�������н�����\n");
}

