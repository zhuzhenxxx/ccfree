/*
 *  ��������counttable.cpp���˳�����ʾfreecplus��ܲ���Oracle���ݿ⣨��ѯ���еļ�¼������
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "_ooci.h"   // freecplus��ܲ���Oracle��ͷ�ļ���

int main(int argc,char *argv[])
{
  connection conn; // ���ݿ�������
  
  // ��¼���ݿ⣬����ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����conn.m_cda.rc�У�ʧ��������conn.m_cda.message�С�
  if (conn.connecttodb("scott/tiger@snorcl11g_198","Simplified Chinese_China.ZHS16GBK")!=0)
  {
    printf("connect database failed.\n%s\n",conn.m_cda.message); return -1;
  }

  sqlstatement stmt(&conn); // ����SQL���Ķ���

  int icount=0;  // ���ڴ�Ų�ѯ����ļ�¼����

  // ׼����ѯ���SQL��䣬�Ѳ�ѯ����ֱ��д��SQL����У�û�в��ð���������ķ�����
  stmt.prepare("select count(*) from girls where id>=2 and id<=4");
  // prepare��������Ҫ�жϷ���ֵ��
  // ΪSQL������������ĵ�ַ��bindout��������Ҫ�жϷ���ֵ��
  stmt.bindout(1,&icount);

  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����stmt.m_cda.rc�У�ʧ��������stmt.m_cda.message�С�
  if (stmt.execute() != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  // ������ִ�е��ǲ�ѯ��䣬ִ��stmt.execute()�󣬽��������ݿ�Ļ������в���һ���������
  // ���ǣ��ڱ������У��������Զֻ��һ����¼������stmt.next()һ�ξ��У�����Ҫѭ����
  stmt.next();
  
  printf("girls���з��������ļ�¼����%d��\n",icount);
}

