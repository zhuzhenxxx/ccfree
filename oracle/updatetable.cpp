/*
 *  ��������updatetable.cpp���˳�����ʾfreecplus��ܲ���Oracle���ݿ⣨�޸ı��еļ�¼����
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

  char strbtime[20];  // ���ڴ�ų�Ů�ı���ʱ�䡣
  memset(strbtime,0,sizeof(strbtime));
  strcpy(strbtime,"2019-12-20 09:45:30");

  // ׼���������ݵ�SQL��䣬����Ҫ�жϷ���ֵ��
  stmt.prepare("\
    update girls set btime=to_date(:1,'yyyy-mm-dd hh24:mi:ss') where id>=2 and id<=4");
  // prepare��������Ҫ�жϷ���ֵ��
  // ΪSQL������������ĵ�ַ��bindin��������Ҫ�жϷ���ֵ��
  stmt.bindin(1,strbtime,19);
  // ��������ð���������ķ�������strbtime��ֱֵ��д��SQL�����Ҳ�ǿ��Եģ����£�
  /*
  stmt.prepare("\
    update girls set btime=to_date('%s','yyyy-mm-dd hh24:mi:ss') where id>=2 and id<=4",strbtime);
  */

  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����stmt.m_cda.rc�У�ʧ��������stmt.m_cda.message�С�
  if (stmt.execute() != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  // ��ע�⣬stmt.m_cda.rpc�����ǳ���Ҫ����������SQL��ִ�к�Ӱ��ļ�¼����
  printf("���θ�����girls��%ld����¼��\n",stmt.m_cda.rpc);

  // �ύ����
  conn.commit();
}

