/*
 *  ��������deletetable.cpp���˳�����ʾfreecplus��ܲ���Oracle���ݿ⣨ɾ�����еļ�¼����
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

  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����stmt.m_cda.rc�У�ʧ��������stmt.m_cda.message�С�
  // �������Ҫ������������������stmt.execute()����ֱ��ִ��SQL��䣬����Ҫstmt.prepare()��
  if (stmt.execute("delete from girls where id>=2 and id<=4") != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  // ��ע�⣬stmt.m_cda.rpc�����ǳ���Ҫ����������SQL��ִ�к�Ӱ��ļ�¼����
  printf("���δ�girls����ɾ����%ld����¼��\n",stmt.m_cda.rpc); 

  // �ύ����
  conn.commit();
}

