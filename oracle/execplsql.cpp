/*
 *  ��������execplsql.cpp���˳�����ʾfreecplus��ܲ���Oracle���ݿ⣨ִ��PL/SQL���̣���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
 *  ˵˵�Ҹ��˵Ŀ������ҴӲ���Oracle���ݿ��д���PL/SQL���̣�Ҳ����ʹ�ô�������ԭ�����£�
 *  1����Oracle���ݿ��д���PL/SQL���̣�����ĵ��Ժ��鷳��
 *  2��ά���������鷳����Ϊά����ԱҪ��ʱ��ȥ�˽����ݿ��еĴ洢���̣�
 *  3������freecplus��ܲ���Oracle�Ѿ��Ƿǳ��򵥣�û��Ҫȥ���ڴ洢���̣�
 *  4��PL/SQL���̿���ֲ�Բ��ã��������mysql���������ݿ⣬�Ƚ��鷳��
 *  ���У�����C/C++�����к����ø��ӵ�PL/SQL���̣���Ϊ���ӵ�PL/SQL�����鷳��
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

  int id=100;

  // ׼����ѯ���PL/SQL��䣬��ɾ��girls���е�ȫ����¼���ٲ���һ����¼��
  stmt.prepare("\
    BEGIN\
      delete from girls;\
      insert into girls(id,name,weight,btime)\
                 values(:1,'��Ů����',55.65,to_date('2018-01-02 13:00:55','yyyy-mm-dd hh24:mi:ss'));\
    END;");
  // ע�⣬PL/SQL�е�ÿ��SQL��Ҫ�÷ֺŽ�����END֮����һ���ֺš�
  // prepare��������Ҫ�жϷ���ֵ��
  // ΪPL/SQL������������ĵ�ַ��bindin��������Ҫ�жϷ���ֵ��
  stmt.bindin(1,&id);
  
  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  if (stmt.execute() != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  printf("exec PL/SQL ok.\n");

  // �ύ����
  conn.commit();
}

