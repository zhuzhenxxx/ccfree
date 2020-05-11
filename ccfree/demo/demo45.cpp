/*
 *  ��������demo45.cpp���˳�����ʾ����freecplus��ܵ�CIniFile����ز����ļ���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

// ���ڴ�ű��������в��������ݽṹ��
struct st_args
{
  char logpath[301];
  char connstr[101];
  char datapath[301];
  char serverip[51];
  int  port;
  bool online;
}stargs;

int main(int argc,char *argv[])
{
  // ���ִ�г���ʱ����Ĳ�������ȷ������������Ϣ��
  if (argc != 2) 
  { 
    printf("\nusing:/freecplus/demo/demo45 inifile\n"); 
    printf("samples:/freecplus/demo/demo45 /freecplus/ini/hssms.xml\n\n"); 
    return -1;
  }

  // ���ز����ļ���
  CIniFile IniFile;
  if (IniFile.LoadFile(argv[1])==false)
  {
    printf("IniFile.LoadFile(%s) failed.\n",argv[1]); return -1;
  } 

  // ��ȡ�����������stargs�ṹ�С�
  memset(&stargs,0,sizeof(struct st_args));
  IniFile.GetValue("logpath",stargs.logpath,300);
  IniFile.GetValue("connstr",stargs.connstr,100);
  IniFile.GetValue("datapath",stargs.datapath,300);
  IniFile.GetValue("serverip",stargs.serverip,50);
  IniFile.GetValue("port",&stargs.port);
  IniFile.GetValue("online",&stargs.online);
  
  printf("logpath=%s\n",stargs.logpath);
  printf("connstr=%s\n",stargs.connstr);
  printf("datapath=%s\n",stargs.datapath);
  printf("serverip=%s\n",stargs.serverip);
  printf("port=%d\n",stargs.port);
  printf("online=%d\n",stargs.online);

  // ���¿���д�����������Ĵ��롣
}

