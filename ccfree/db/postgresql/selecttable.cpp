/*
 *  ��������selecttable.cpp���˳�����ʾfreecplus��ܲ���PostgreSQL���ݿ⣨��ѯ���еļ�¼����
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "_postgresql.h"   // freecplus��ܲ���PostgreSQL��ͷ�ļ���

// �������ڳ�Ů��Ϣ�Ľṹ������е��ֶζ�Ӧ��
struct st_girls
{
  long id;        // ��Ů��ţ���long�������Ͷ�ӦOracle��С����number(10)��
  char name[31];  // ��Ů��������char[31]��ӦOracle��varchar2(30)��
  double weight;  // ��Ů���أ���double�������Ͷ�ӦOracle��С����number(8,2)��
  char btime[20]; // ����ʱ�䣬��char��ӦOracle��date����ʽ��'yyyy-mm-dd hh24:mi:ss'��
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

  int iminid,imaxid;  // ��ѯ������С������id��

  // ׼����ѯ���SQL��䡣
  stmt.prepare("\
    select id,name,weight,to_char(btime,'yyyy-mm-dd hh24:mi:ss') from girls where id>=:1 and id<=:2");
  // prepare��������Ҫ�жϷ���ֵ��
  // ΪSQL������������ĵ�ַ��bindin��������Ҫ�жϷ���ֵ��
  stmt.bindin(1,&iminid);
  stmt.bindin(2,&imaxid);
  // ΪSQL������������ĵ�ַ��bindout��������Ҫ�жϷ���ֵ��
  stmt.bindout(1,&stgirls.id);
  stmt.bindout(2, stgirls.name,30);
  stmt.bindout(3,&stgirls.weight);
  stmt.bindout(4, stgirls.btime,19);

  iminid=2;  // ָ������ѯ��¼����Сid��ֵ��
  imaxid=4;  // ָ������ѯ��¼�����id��ֵ��

  // ִ��SQL��䣬һ��Ҫ�жϷ���ֵ��0-�ɹ�������-ʧ�ܡ�
  // ʧ�ܴ�����stmt.m_cda.rc�У�ʧ��������stmt.m_cda.message�С�
  if (stmt.execute() != 0)
  {
    printf("stmt.execute() failed.\n%s\n%s\n",stmt.m_sql,stmt.m_cda.message); return -1;
  }

  // ������ִ�е��ǲ�ѯ��䣬ִ��stmt.execute()�󣬽��������ݿ�Ļ������в���һ���������
  while (1)
  {
    memset(&stgirls,0,sizeof(stgirls)); // �Ȱѽṹ�������ʼ����

    // �ӽ�����л�ȡһ����¼��һ��Ҫ�жϷ���ֵ��0-�ɹ���1403-�޼�¼������-ʧ�ܡ�
    // ��ʵ�ʿ����У�����0��1403��������������ٳ��֡�
    if (stmt.next() !=0) break;
    
    // �ѻ�ȡ���ļ�¼��ֵ��ӡ������
    printf("id=%ld,name=%s,weight=%.02f,btime=%s\n",stgirls.id,stgirls.name,stgirls.weight,stgirls.btime);
  }

  // ��ע�⣬stmt.m_cda.rpc�����ǳ���Ҫ����������SQL��ִ�к�Ӱ��ļ�¼����
  printf("���β�ѯ��girls��%ld����¼��\n",stmt.m_cda.rpc);
}

