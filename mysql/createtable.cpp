/*
 *  ��������createtable.cpp���˳�����ʾfreecplus��ܲ���MySQL���ݿ⣨��������
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "_mysql.h"   // freecplus��ܲ���MySQL��ͷ�ļ���

int main(int argc,char *argv[])
{
  connection conn; // ���ݿ�������

  // ��¼���ݿ⣬����ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����conn.m_cda.rc�У�ʧ��������conn.m_cda.message�С�
  if (conn.connecttodb("172.16.0.15,root,123qweASD!@#,mysql,3306","gbk") != 0)
  {
    printf("connect database failed.\n%s\n",conn.m_cda.message); return -1;
  }
  
  sqlstatement stmt(&conn); // ����SQL���Ķ���

  // ׼���������SQL��䡣
  // ��Ů��girls����Ů���id����Ů����name������weight������ʱ��btime����Ů˵��memo����ŮͼƬpic��
  stmt.prepare("\
    create table girls(id    bigint(10),\
                       name  varchar(30),\
                       weight   decimal(8,2),\
                       btime datetime,\
                       memo  longtext,\
                       pic   longblob,\
                       primary key (id))");
  // prepare��������Ҫ�жϷ���ֵ��

  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����stmt.m_cda.rc�У�ʧ��������stmt.m_cda.message�С�
  if (stmt.execute() != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  printf("create table girls ok.\n");
}

