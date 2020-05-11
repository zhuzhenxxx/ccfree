/*
 *  ��������inserttable.cpp���˳�����ʾfreecplus��ܲ���PostgreSQL���ݿ⣨����в���5����¼����
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "_postgresql.h"   // freecplus��ܲ���PostgreSQL��ͷ�ļ���

// �������ڳ�Ů��Ϣ�Ľṹ������е��ֶζ�Ӧ��
struct st_girls
{
  long id;        // ��Ů��ţ���long�������Ͷ�ӦOracle��С����number(10)��
  char name[11];  // ��Ů��������char[31]��ӦOracle��varchar2(30)��
  double weight;  // ��Ů���أ���double�������Ͷ�ӦOracle��С����number(8,2)��
  char btime[20]; // ����ʱ�䣬��char��ӦOracle��date����ʽ��'yyyy-mm-dd hh24:mi:ssi'��
} stgirls;

int main(int argc,char *argv[])
{
  connection conn; // ���ݿ�������

  // ��¼���ݿ⣬����ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����conn.m_cda.rc�У�ʧ��������conn.m_cda.message�С�
  if (conn.connecttodb("host=172.16.0.15 user=postgres password=pwdidc dbname=postgres port=5432","gbk")!=0)
  {
    printf("connect database failed.\n%s\n",conn.m_cda.message); return -1;
  }
  
  sqlstatement stmt(&conn); // ����SQL���Ķ���

  // ׼��������SQL��䡣
  stmt.prepare("\
    insert into girls(id,name,weight,btime) \
                values(:1,:2,:3,to_date(:4,'yyyy-mm-dd hh24:mi:ss'))");
  // prepare��������Ҫ�жϷ���ֵ��
  // ΪSQL������������ĵ�ַ��bindin��������Ҫ�жϷ���ֵ��
  stmt.bindin(1,&stgirls.id);
  stmt.bindin(2, stgirls.name,10);
  stmt.bindin(3,&stgirls.weight);
  stmt.bindin(4, stgirls.btime,19);

  // ģ�ⳬŮ���ݣ�����в���5��������Ϣ��
  for (int ii=1;ii<=5;ii++)
  {
    memset(&stgirls,0,sizeof(stgirls)); // �ṹ�������ʼ����

    // Ϊ�ṹ������ĳ�Ա��ֵ��
    stgirls.id=ii;                                 // ��Ů��š�
    sprintf(stgirls.name,"��Ů%02d",ii);           // ��Ů������
    stgirls.weight=ii*2.11;                        // ��Ů���ء�
    strcpy(stgirls.btime,"2018-03-01 12:25:31");   // ����ʱ�䡣

    // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
    // ʧ�ܴ�����stmt.m_cda.rc�У�ʧ��������stmt.m_cda.message�С�
    if (stmt.execute() != 0)
    {
      printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
    }

    printf("�ɹ�������%ld����¼��\n",stmt.m_cda.rpc); // stmt.m_cda.rpc�Ǳ���ִ��SQLӰ��ļ�¼����
  }

  printf("insert table girls ok.\n");

  conn.commit(); // �ύ���ݿ�����
}
