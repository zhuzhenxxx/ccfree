/*
 *  ��������demo51.cpp���˳�����ʾ����freecplus��ܵ�Cftp���ϴ��ļ���
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

  // ��ftp�������ϴ���/home/freecplus/tmp��ע�⣬���Ŀ¼�Ѵ��ڣ��᷵��ʧ�ܡ�
  if (ftp.mkdir("/home/freecplus/tmp")==false) { printf("ftp.mkdir() failed.\n"); return -1; }
  
  // ��ftp�������ϵĹ���Ŀ¼�л���/home/freecplus/tmp
  if (ftp.chdir("/home/freecplus/tmp")==false) { printf("ftp.chdir() failed.\n"); return -1; }

  // �ѱ��ص�demo51.cpp�ϴ���ftp�������ĵ�ǰ����Ŀ¼��
  ftp.put("demo51.cpp","demo51.cpp");

  // ���������chdir�л�����Ŀ¼�����´���Ҳ����ֱ���ϴ��ļ���
  // ftp.put("demo51.cpp","/home/freecplus/tmp/demo51.cpp");
  
  printf("put demo51.cpp ok.\n");  
}

