/*
 *  ��������demo48.cpp���˳�����ʾ����freecplus��ܵ�CTcpServer��ʵ��socketͨ�ŵķ���ˡ�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main(int argc,char *argv[])
{
  CTcpServer TcpServer;   // ��������˶���
  
  if (TcpServer.InitServer(5858)==false) // ��ʼ��TcpServer��ͨ�Ŷ˿ڡ�
  {
    printf("TcpServer.InitServer(5858) failed.\n"); return -1;
  }
  
  if (TcpServer.Accept()==false)   // �ȴ��ͻ������ӡ�
  {
    printf("TcpServer.Accept() failed.\n"); return -1;
  }

  printf("�ͻ���(%s)�����ӡ�\n",TcpServer.GetIP());

  char strbuffer[1024];  // ������ݵĻ�������

  while (true)
  {
    memset(strbuffer,0,sizeof(strbuffer));
    if (TcpServer.Read(strbuffer,300)==false) break; // ���տͻ��˷������������ġ�
    printf("���գ�%s\n",strbuffer);

    strcat(strbuffer,"ok");      // �ڿͻ��˵ı��ĺ����"ok"��
    printf("���ͣ�%s\n",strbuffer);
    if (TcpServer.Write(strbuffer)==false) break;     // ��ͻ��˻�Ӧ���ġ�
  }

  printf("�ͻ����ѶϿ���\n");    // ����ֱ���˳��������������ͷ���Դ��
}

