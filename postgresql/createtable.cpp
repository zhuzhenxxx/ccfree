/*
 *  ��������createtable.cpp���˳�����ʾfreecplus��ܲ���PostgreSQL���ݿ⣨��������
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "_postgresql.h"   // freecplus��ܲ���PostgreSQL��ͷ�ļ���

int main(int argc,char *argv[])
{
  connection conn; // ���ݿ����ӳء�

  // ��¼���ݿ⣬����ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����conn.m_cda.rc�У�ʧ��������conn.m_cda.message�С�
  if (conn.connecttodb("host=172.16.0.15 user=postgres password=pwdidc dbname=postgres port=5432","gbk")!=0)
  {
    printf("connect database failed.\n%s\n",conn.m_cda.message); return -1;
  }  

  sqlstatement stmt(&conn); // ����SQL���Ķ���

  // ׼���������SQL��䡣
  // ��Ů��girls����Ů���id����Ů����name������weight������ʱ��btime����Ů˵��memo����ŮͼƬpic��
  stmt.prepare("\
    create table girls(id    int,\
                       name  varchar(30),\
                       weight   numeric(8,2),\
                       btime timestamp,\
                       memo  text,\
                       pic   bytea,\
                       primary key (id))");
  // prepare��������Ҫ�жϷ���ֵ��

  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����stmt.m_cda.rc�У�ʧ��������stmt.m_cda.message�С�
  if (stmt.execute() != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  // ע�⣬��postgresql���ݿ��У�������ҲҪ�ύ���񣬺�Oracle��MySQL���ݿⲻͬ��
  conn.commit();

  printf("create table girls ok.\n");
}

