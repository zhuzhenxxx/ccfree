/*
 *  ��������demo52.cpp���˳�����ʾ����freecplus��ܵ�Cftp�������ļ���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_ftp.h"

int main(int argc,char *argv[])
{
  Cftp ftp;

  // ��¼Զ��FTP�����������Ϊ���Լ���������ip��ַ��
  if (ftp.login("172.16.0.15:21","freecplus","freecpluspwd",FTPLIB_PASSIVE) == false)
  {
    printf("ftp.login(172.16.0.15:21(freecplus/freecpluspwd)) failed.\n"); return -1;
  }

  // �ѷ������ϵ�/home/freecplus/tmp/demo51.cpp���ص����أ���Ϊ/tmp/test/demo51.cpp��
  // ������ص�/tmp/testĿ¼�����ڣ��ʹ�������
  if (ftp.get("/home/freecplus/tmp/demo51.cpp","/tmp/test/demo51.cpp")==false)
  { printf("ftp.get() failed.\n"); return -1; }

  printf("get /home/freecplus/tmp/demo51.cpp ok.\n");  

  // ɾ�������ϵ�/home/freecplus/tmp/demo51.cpp�ļ���
  if (ftp.ftpdelete("/home/freecplus/tmp/demo51.cpp")==false) 
  { printf("ftp.ftpdelete() failed.\n"); return -1; }

  printf("delete /home/freecplus/tmp/demo51.cpp ok.\n");  

  // ɾ���������ϵ�/home/freecplus/tmpĿ¼�����Ŀ¼�ǿգ�ɾ����ʧ�ܡ�
  if (ftp.rmdir("/home/freecplus/tmp")==false) { printf("ftp.rmdir() failed.\n"); return -1; }
}

