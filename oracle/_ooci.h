/**************************************************************************************/
/*   ��������_ooci.h���˳�����freecplus��ܵ�C/C++����Oracle���ݿ�������ļ���        */
/*   ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525��                            */
/*                                                                                    */
/*   freecplus��Դ���Э���������£�                                                  */
/*     ��Ȩ���� (c) 2008-2020����ũ�е���C���Լ�������www.freecplus.net����           */
/*     �ش����κεõ����������������ĵ�������Ȩ������Ȩ����Ȩʹ�á����ơ��޸ġ�     */
/*   �ϲ������桢������ɢ��������Ȩ��/�������������ĸ����������豻��Ӧ��ͬ��      */
/*   Ȩ����ֻ�������������                                                         */
/*     ���������������и����ж�����������ϰ�Ȩ�����ͱ����������                   */
/*     ���Υ���������ڱ������ʹ���ϻ����������������Ƿ��漰��ͬ����������Ȩ��Ϊ��   */
/*   ���Ǳ���׷����Ȩ����                                                             */
/*   freecplus��Դ���Э�����Ľ�����                                                  */
/**************************************************************************************/

#ifndef __OOCI_H
#define __OOCI_H

// C/C++�ⳣ��ͷ�ļ�
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <oci.h>     // OCI��ͷ�ļ���

struct LOGINENV      // OCI��¼������
{
  char user[32];     // ���ݿ���û�����
  char pass[32];     // ���ݿ�����롣
  char tnsname[51];  // ���ݿ��tnsname����ORACLE_HOME/network/admin/tnsnames.ora�����á�

  OCIEnv *envhp;     // ���������ľ����
};

struct OCI_CXT       // OCI�����ľ����
{
  OCISvcCtx  *svchp;
  OCIError   *errhp;
  OCIEnv     *envhp; // ���������ľ����
};

struct OCI_HANDLE    // OCI��SQL�����
{
  OCISvcCtx  *svchp; // �����������ĵľ������context�����
  OCIStmt    *smthp;

  OCIBind    *bindhp;
  OCIDefine  *defhp;

  OCIError   *errhp; // ����������context�����

  OCIEnv     *envhp; // ���������ľ����
};

struct CDA_DEF       // OCI�ӿں���ִ�еĽ����
{
  int      rc;          // ����ֵ��0-�ɹ�������ʧ�ܡ�
  unsigned long rpc;    // �����insert��update��delete������Ӱ���¼�������������select������������������
  char     message[2048];  // ִ��SQL������ʧ�ܣ���Ŵ���������Ϣ��
};

int oci_init(LOGINENV *env);
int oci_close(LOGINENV *env); 
int oci_context_create(LOGINENV *env,OCI_CXT *cxt);
int oci_context_close(OCI_CXT *cxt);

int oci_stmt_create(OCI_CXT *cxt,OCI_HANDLE *handle);
int oci_stmt_close(OCI_HANDLE *handle);

// Oracle���ݿ����ӳ��ࡣ
class connection
{
private:
  LOGINENV m_env;    // ���������������

  char m_dbtype[21]; // ���ݿ����࣬�̶�ȡֵΪ"oracle"��

  // �����ַ���������ͻ��˵��ַ��������ݿ�Ĳ�һ�£��ͻ�������롣
  void character(char *charset);

  // ��connstr�н���username��password��tnsname��
  void setdbopt(char *connstr);
public:
  int m_state;       // �����ݿ������״̬��0-δ���ӣ�1-�����ӡ�

  CDA_DEF m_cda;       // ���ݿ�����Ľ�������һ��ִ��SQL���Ľ����

  char m_sql[10241];   // SQL�����ı�������ܳ���10240�ֽڡ�

  connection();    // ���캯����
 ~connection();    // ����������

  // ��¼���ݿ⡣
  // connstr�����ݿ�ĵ�¼��������ʽ��username/password@tnsname��username-�û�����password-��¼��
  // �룬tnsname-���ݿ�ķ���������$ORACLE_HOME/network/admin/tnsnames.ora�ļ������á�
  // charset�����ݿ���ַ��������������ݿⱣ��һ�£�����������������������
  // autocommitopt���Ƿ������Զ��ύ��0-�����ã�1-���ã�ȱʡ�ǲ����á�
  // ����ֵ��0-�ɹ�������ʧ�ܣ�ʧ�ܵĴ�����m_cda.rc�У�ʧ�ܵ�������m_cda.message�С�
  int connecttodb(char *connstr,char *charset,int autocommitopt=0);

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
  // ���³�Ա�����ͺ���������sqlstatement�࣬������ⲿ����Ҫ��������
  int m_autocommitopt; // �Զ��ύ��־��0-�رգ�1-������
  OCI_CXT m_cxt;       // �����������ġ�
  void err_report();   // ��ȡ������Ϣ��
  ////////////////////////////////////////////////////////////////////
};

// ����SQL����ࡣ
class sqlstatement
{
  OCI_HANDLE m_handle; // SQL�����
  connection *m_conn;  // ���ݿ����ӳ�ָ�롣
  int m_sqltype;       // SQL�������ͣ�0-��ѯ��䣻1-�ǲ�ѯ��䡣
  int m_autocommitopt; // �Զ��ύ��־��0-�رգ�1-������
  void err_report();   // ���󱨸档

  OCILobLocator *m_lob;     // ָ��LOB�ֶε�ָ�롣
  int  alloclob();          // ��ʼ��lobָ�롣
  int  filetolob(FILE *fp); // ���ļ������ݵ��뵽clob��blob�ֶ��С�
  int  lobtofile(FILE *fp); // ��clob��blob�ֶ��е������ݵ��ļ��С�
  void freelob();           // �ͷ�lobָ�롣
public:
  int m_state;         // �����ݿ����ӳصİ�״̬��0-δ�󶨣�1-�Ѱ󶨡�

  char m_sql[10241];   // SQL�����ı�������ܳ���10240�ֽڡ�

  CDA_DEF m_cda;       // ִ��SQL���Ľ����

  sqlstatement();      // ���캯����
  sqlstatement(connection *conn);    // ���캯����ͬʱ�����ݿ����ӳء�

 ~sqlstatement();

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
  // ע�⣺���SQL���û�иı䣬ֻ��Ҫbindinһ�ξͿ����ˡ�
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
  // ע�⣺���SQL���û�иı䣬ֻ��Ҫbindoutһ�ξͿ����ˡ�
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

  // ��clob�ֶΡ�
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  int bindblob();

  // ��blob�ֶΡ�
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  int bindclob();

  // ���ļ������ݵ��뵽clob��blob�ֶ��С�
  // filename����������ļ�����������þ���·����
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  int filetolob(char *filename);

  // ��clob��blob�ֶ��е������ݵ��ļ��С�
  // filename���������ݴ�ŵ��ļ�����������þ���·����
  // ����ֵ��0-�ɹ�������ʧ�ܣ�����Աһ�㲻�ع��ķ���ֵ��
  int lobtofile(char *filename);
};

#endif 

