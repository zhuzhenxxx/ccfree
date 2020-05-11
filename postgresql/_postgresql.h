/****************************************************************************************/
/*   ��������_postgresql.h���˳�����freecplus��ܵ�C/C++����PostgreSQL���ݿ�������ļ���*/
/*   ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525��                              */
/*                                                                                      */
/*   freecplus��Դ���Э���������£�                                                    */
/*     ��Ȩ���� (c) 2008-2020����ũ�е���C���Լ�������www.freecplus.net����             */
/*     �ش����κεõ����������������ĵ�������Ȩ������Ȩ����Ȩʹ�á����ơ��޸ġ�       */
/*   �ϲ������桢������ɢ��������Ȩ��/�������������ĸ����������豻��Ӧ��ͬ��        */
/*   Ȩ����ֻ�������������                                                           */
/*     ���������������и����ж�����������ϰ�Ȩ�����ͱ����������                     */
/*     ���Υ���������ڱ������ʹ���ϻ����������������Ƿ��漰��ͬ����������Ȩ��Ϊ��     */
/*   ���Ǳ���׷����Ȩ����                                                               */
/*   freecplus��Դ���Э�����Ľ�����                                                    */
/****************************************************************************************/

#ifndef _POSTGRESQL_H
#define _POSTGRESQL_H

// C/C++�ⳣ��ͷ�ļ�
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include <libpq-fe.h> // PostgreSQL���ݿ�ӿں�����ͷ�ļ� 

struct CDA_DEF       // ����PostgreSQL�ӿں���ִ�еĽ����
{
  int      rc;          // ����ֵ��0-�ɹ�������ʧ�ܡ�
  unsigned long rpc;    // �����insert��update��delete������Ӱ���¼�������������select������������������
  char     message[2048];  // ִ��SQL������ʧ�ܣ���Ŵ���������Ϣ��
};

// PostgreSQL���ݿ����ӳ��ࡣ
class connection
{
private:
  char m_dbtype[21];   // ���ݿ����࣬�̶�ȡֵΪ"postgresql"��

  void character(char *charset); // �����ַ�����Ҫ�����ݿ��һ�£��������Ļ�������롣

  int  begin(); // ��ʼ����

  int m_autocommitopt; // �Զ��ύ��־��0-�ر��Զ��ύ��1-�����Զ��ύ��
public:
  int m_state;         // �����ݿ������״̬��0-δ���ӣ�1-�����ӡ�

  CDA_DEF m_cda;       // ���ݿ�����Ľ�������һ��ִ��SQL���Ľ����

  char m_sql[10241];   // SQL�����ı�������ܳ���10240�ֽڡ�

  connection();        // ���캯����
 ~connection();        // ����������

  // ��¼���ݿ⡣
  // connstr�����ݿ�ĵ�¼��������ʽ��"host= user= password= dbname= port=",
  // ���磺"host=172.16.0.15 user=qxidc password=qxidcpwd dbname=qxidcdb port=5432"
  // username-��¼���û�����password-��¼�����룬dbname-ȱʡ���ݿ⣬port-mysql����Ķ˿ڡ�
  // charset�����ݿ���ַ�������"gbk"�����������ݿⱣ��һ�£�����������������������
  // autocommitopt���Ƿ������Զ��ύ��0-�����ã�1-���ã�ȱʡ�ǲ����á�
  // ����ֵ��0-�ɹ�������ʧ�ܣ�ʧ�ܵĴ�����m_cda.rc�У�ʧ�ܵ�������m_cda.message�С�
  int connecttodb(char *connstr,char *charset,unsigned int autocommitopt=0);

  // �ύ����
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  int commit();

  // �ع�����
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  int  rollback();

  // �Ͽ������ݿ�����ӡ�
  // ע�⣬�Ͽ������ݿ������ʱ��ȫ��δ�ύ�������Զ��ع���
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  int disconnect();

  // ִ��SQL��䡣
  // ���SQL��䲻��Ҫ�����������������ް󶨱������ǲ�ѯ��䣩������ֱ���ô˷���ִ�С�
  // ����˵��������һ���ɱ�������÷���printf������ͬ��
  // ����ֵ��0-�ɹ�������ʧ�ܣ�ʧ�ܵĴ�����m_cda.rc�У�ʧ�ܵ�������m_cda.message�У�
  // ����ɹ���ִ���˷ǲ�ѯ��䣬��m_cda.rpc�б����˱���ִ��SQLӰ���¼��������
  // ����Ա������execute�����ķ���ֵ��
  // ��connection�����ṩ��execute��������Ϊ�˷������Ա���ڸ÷����У�Ҳ����sqlstatement������ɹ��ܡ�
  int execute(const char *fmt,...);

  ////////////////////////////////////////////////////////////////////
  // ���³�Ա����������sqlstatement�࣬������ⲿ����Ҫ��������
  PGconn *m_conn;  // PostgreSQL���ݿ����Ӿ����
  ////////////////////////////////////////////////////////////////////
};

// ִ��SQL���ǰ�����������������������ֵ��256�Ǻܴ���ˣ����Ը���ʵ�����������
#define MAXPARAMS  256

// ��������������������ַ�����ָ���ַ�������󳤶ȣ��������ַ����Ľ�������
#define MAXFIELDLENGTH 2000   

// ����SQL����ࡣ
class sqlstatement
{
private:
  PGresult *m_res;  // �����ָ�롣
  connection *m_conn;  // ���ݿ����ӳ�ָ�롣
  int m_sqltype;       // SQL�������ͣ�0-��ѯ��䣻1-�ǲ�ѯ��䡣
  int m_autocommitopt; // �Զ��ύ��־��0-�رգ�1-������

  int   m_nParamsIn;
  char *m_paramValuesIn[MAXPARAMS];
  char  m_paramValuesInVal[MAXPARAMS][MAXFIELDLENGTH+1];
  char *m_paramValuesInPtr[MAXPARAMS];
  char  m_paramTypesIn[MAXPARAMS][15];
  int   m_paramLengthsIn[MAXPARAMS];

  int   m_nParamsOut;
  char  m_paramTypesOut[MAXPARAMS][15];
  char *m_paramValuesOut[MAXPARAMS];
  int   m_paramLengthsOut[MAXPARAMS];

  int  m_respos;
  int  m_restotal;

  void initial();      // ��ʼ����Ա������
public:
  int m_state;         // �����ݿ����ӳصİ�״̬��0-δ�󶨣�1-�Ѱ󶨡�

  char m_sql[10241];   // SQL�����ı�������ܳ���10240�ֽڡ�

  CDA_DEF m_cda;       // ִ��SQL���Ľ����

  sqlstatement();      // ���캯����
  sqlstatement(connection *conn);    // ���캯����ͬʱ�����ݿ����ӳء�
 ~sqlstatement();      // ����������

  // �����ݿ����ӳء�
  // conn�����ݿ����ӳ�connection����ĵ�ַ��
  // ����ֵ��0-�ɹ�������ʧ�ܣ�ֻҪconn��������Ч�ģ��������ݿ���α���Դ�㹻��connect�������᷵��ʧ�ܡ�
  // ����Աһ�㲻�ع���connect�����ķ���ֵ��
  // ע�⣬ÿ��sqlstatementֻ��Ҫ��һ�Σ��ڰ��µ�connectionǰ�������ȵ���disconnect������
  int connect(connection *conn);

  // ȡ�������ݿ����ӳصİ󶨡�
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  int disconnect();

  // ׼��SQL��䡣
  // ����˵��������һ���ɱ�������÷���printf������ͬ��
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  // ע�⣺���SQL���û�иı䣬ֻ��Ҫprepareһ�ξͿ����ˡ�
  int prepare(const char *fmt,...);

  // ����������ĵ�ַ��
  // position���ֶε�˳�򣬴�1��ʼ��������prepare�����е�SQL�����һһ��Ӧ��
  // value����������ĵ�ַ��������ַ������ڴ��СӦ���Ǳ��Ӧ���ֶγ��ȼ�1��
  // len�������������������������ַ�������lenָ��������󳤶ȣ�������ñ��Ӧ���ֶγ��ȡ�
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  // ע�⣺1�����SQL���û�иı䣬ֻ��Ҫbindinһ�ξͿ����ˣ�2��������������������ܳ���256����
  int bindin(unsigned int position,int    *value);
  int bindin(unsigned int position,long   *value);
  int bindin(unsigned int position,unsigned int  *value);
  int bindin(unsigned int position,unsigned long *value);
  int bindin(unsigned int position,float *value);
  int bindin(unsigned int position,double *value);
  int bindin(unsigned int position,char   *value,unsigned int len);

  // ����������ĵ�ַ��
  // position���ֶε�˳�򣬴�1��ʼ����SQL�Ľ����һһ��Ӧ��
  // value����������ĵ�ַ��������ַ������ڴ��СӦ���Ǳ��Ӧ���ֶγ��ȼ�1��
  // len�������������������������ַ�������lenָ��������󳤶ȣ�������ñ��Ӧ���ֶγ��ȡ�
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  // ע�⣺1�����SQL���û�иı䣬ֻ��Ҫbindoutһ�ξͿ����ˣ�2��������������������ܳ���256����
  int bindout(unsigned int position,int    *value);
  int bindout(unsigned int position,long   *value);
  int bindout(unsigned int position,unsigned int  *value);
  int bindout(unsigned int position,unsigned long *value);
  int bindout(unsigned int position,float *value);
  int bindout(unsigned int position,double *value);
  int bindout(unsigned int position,char   *value,unsigned int len);

  // ִ��SQL��䡣
  // ����ֵ��0-�ɹ�������ʧ�ܣ�ʧ�ܵĴ�����m_cda.rc�У�ʧ�ܵ�������m_cda.message�С�
  // ����ɹ���ִ���˷ǲ�ѯ��䣬��m_cda.rpc�б����˱���ִ��SQLӰ���¼��������
  // ����Ա������execute�����ķ���ֵ��
  int execute();

  // ִ��SQL��䡣
  // ���SQL��䲻��Ҫ�����������������ް󶨱������ǲ�ѯ��䣩������ֱ���ô˷���ִ�С�
  // ����˵��������һ���ɱ�������÷���printf������ͬ��
  // ����ֵ��0-�ɹ�������ʧ�ܣ�ʧ�ܵĴ�����m_cda.rc�У�ʧ�ܵ�������m_cda.message�У�
  // ����ɹ���ִ���˷ǲ�ѯ��䣬��m_cda.rpc�б����˱���ִ��SQLӰ���¼��������
  // ����Ա������execute�����ķ���ֵ��
  int execute(const char *fmt,...);

  // �ӽ�����л�ȡһ����¼��
  // ���ִ�е�SQL����ǲ�ѯ��䣬����execute�����󣬻����һ�����������������ݿ�Ļ������У���
  // next�����ӽ�����л�ȡһ����¼�����ֶε�ֵ�����Ѱ󶨵���������С�
  // ����ֵ��0-�ɹ���1403-��������޼�¼������-ʧ�ܣ�ʧ�ܵĴ�����m_cda.rc�У�ʧ�ܵ�������m_cda.message�С�
  // ����ʧ�ܵ�ԭ����Ҫ��������1�������ݿ�������ѶϿ���2��������������ڴ�̫С��
  // ÿִ��һ��next������m_cda.rpc��ֵ��1��
  // ����Ա������next�����ķ���ֵ��
  int next();
};

/*
create or replace function to_null(varchar) returns numeric as $$
begin
if (length($1)=0) then
  return null;
else
  return $1;
end if;
end
$$ LANGUAGE plpgsql;
*/

#endif

