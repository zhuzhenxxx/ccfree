/*
 *  ��������demo47.cpp���˳�����ʾ����freecplus��ܵ�CTcpClient��ʵ��socketͨ�ŵĿͻ��ˡ�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main(int argc,char *argv[])
{
  CTcpClient TcpClient;   // �����ͻ��˵Ķ���
  
  if (TcpClient.ConnectToServer("172.16.0.15",5858)==false) // �����˷�����������
  {
    printf("TcpClient.ConnectToServer(\"172.16.0.15\",5858) failed.\n"); return -1;
  }

  char strbuffer[1024];    // ������ݵĻ�������

  for (int ii=0;ii<5;ii++)   // ����ѭ���������˽���5�ν�����
  {
    memset(strbuffer,0,sizeof(strbuffer));
    snprintf(strbuffer,50,"���ǵ�%d������Ů�������%03d��",ii+1,ii+1);
    printf("���ͣ�%s\n",strbuffer);
    if (TcpClient.Write(strbuffer)==false) break;    // �����˷��������ġ�

    memset(strbuffer,0,sizeof(strbuffer));
    if (TcpClient.Read(strbuffer,20)==false) break;  // ���շ���˵Ļ�Ӧ���ġ�
    printf("���գ�%s\n",strbuffer);

    sleep(1);
  }

  // ����ֱ���˳��������������ͷ���Դ��
}

