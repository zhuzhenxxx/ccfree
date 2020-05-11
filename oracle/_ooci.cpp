// �����windowsƽ̨��Ҫ�������У�����ᱨ���´���
// _ooci.cpp(845) : fatal error C1010: unexpected end of file while looking for precompiled header. Did you forget to add '#include "stdafx.h"' to your source?
// #include "stdafx.h"

#include "_ooci.h"

/*
OCI_SUCCESS                0  // maps to SQL_SUCCESS of SAG CLI  ����ִ�гɹ�
OCI_SUCCESS_WITH_INFO      1  // maps to SQL_SUCCESS_WITH_INFO   ִ�гɹ������������Ϣ���أ�
                              // �����Ǿ�����Ϣ�����ǣ��ڲ��Ե�ʱ���һ���δ��
                              // ʶ��OCI_SUCCESS_WITH_INFO����ô����
OCI_RESERVED_FOR_INT_USE 200  // reserved 
OCI_NO_DATA              100  // maps to SQL_NO_DATA ����ִ����ɣ���û���������� 
OCI_ERROR                 -1  // maps to SQL_ERROR ����ִ�д��� 
OCI_INVALID_HANDLE        -2  // maps to SQL_INVALID_HANDLE ���ݸ������Ĳ���Ϊ��Ч�����
                              // �򴫻صľ����Ч 
OCI_NEED_DATA             99  // maps to SQL_NEED_DATA ��ҪӦ�ó����ṩ����ʱ�̵�����
OCI_STILL_EXECUTING    -3123  // OCI would block error ���񻷾������ڷ�����ģʽ��
                              // OCI������������ִ����

OCI_CONTINUE          -24200  // Continue with the body of the OCI function 
                              // ˵���ص�������ҪOCI��ָ��������Ĵ������ 
OCI_ROWCBK_DONE       -24201  // done with user row callback 
*/

int oci_init(LOGINENV *env)
{
  //��ʼ��Oracle ��������
  int  oci_ret;

  oci_ret = OCIEnvCreate(&env->envhp,OCI_DEFAULT,NULL,NULL,NULL,NULL,0,NULL);

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO ) 
  {
    oci_close(env); return -1;
  }

  return 0;
} 

int oci_close(LOGINENV *env)
{
  int oci_ret;

  // �ͷ�Oracle ��������
  oci_ret=OCIHandleFree(env->envhp,OCI_HTYPE_ENV);

  env->envhp = 0;

  return oci_ret;
}

int oci_context_create(LOGINENV *env,OCI_CXT *cxt )
{
  // �������ݿ����ӵ������Ķ������ӷ���������֤�������Ự

  if (env->envhp == 0) return -1;

  int oci_ret;
    
  oci_ret = OCIHandleAlloc(env->envhp,(dvoid**)&cxt->errhp,OCI_HTYPE_ERROR,(size_t) 0,NULL);

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO ) 
  {
    oci_context_close(cxt); return -1;
  }

  // ��¼
  oci_ret = OCILogon(env->envhp,cxt->errhp,&cxt->svchp,(OraText*)env->user,strlen(env->user),
                     (OraText*)env->pass,strlen(env->pass),(OraText*)env->tnsname,strlen(env->tnsname));

  if( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO )
  {
    oci_context_close(cxt); return -1;
  }

  cxt->envhp = env->envhp;

  return 0;    
}

int oci_context_close(OCI_CXT *cxt)
{
  // �ر����ݿ����ӵ�������

  int oci_ret;
    
  oci_ret = OCILogoff(cxt->svchp,cxt->errhp);

  oci_ret = OCIHandleFree(cxt->svchp,OCI_HTYPE_SVCCTX);

  oci_ret = OCIHandleFree(cxt->errhp, OCI_HTYPE_ERROR);

  cxt->svchp=0;

  cxt->errhp=0;

  return oci_ret;
}

int oci_stmt_create(OCI_CXT *cxt,OCI_HANDLE *handle )
{
  //�������
  int  oci_ret;
    
  oci_ret = OCIHandleAlloc( cxt->envhp, (dvoid**)&handle->smthp, OCI_HTYPE_STMT,(size_t)0, NULL);

  if( oci_ret == OCI_SUCCESS || oci_ret == OCI_SUCCESS_WITH_INFO )
  {
    handle->svchp  = cxt->svchp;
    handle->errhp  = cxt->errhp;
    handle->envhp = cxt->envhp;

    oci_ret = OCI_SUCCESS;
  }

  return oci_ret;
}

int oci_stmt_close(OCI_HANDLE *handle)
{
  // �ر����
  int oci_ret=0;

  oci_ret = OCIHandleFree(handle->smthp,OCI_HTYPE_STMT);

  return oci_ret;
}

connection::connection()
{ 
  m_state = 0; 

  memset(&m_cxt,0,sizeof(OCI_CXT));
  memset(&m_env,0,sizeof(LOGINENV));

  memset(&m_cda,0,sizeof(m_cda));

  m_cda.rc=-1;
  strncpy(m_cda.message,"database not open.",128);

  // ���ݿ�����
  memset(m_dbtype,0,sizeof(m_dbtype));
  strcpy(m_dbtype,"oracle");
}

connection::~connection()
{
  disconnect();
}

// ��connstr�н���username,password,tnsname
void connection::setdbopt(char *connstr)
{
  char strtemp[201];

  memset(strtemp,0,sizeof(strtemp));

  strncpy(strtemp,connstr,128);

  char *pos=0;

  // tnsname
  pos = strstr(strtemp,"@");
  if (pos > 0) 
  {
    strncpy(m_env.tnsname,pos+1,50); pos[0]=0;
  }

  // password
  pos = strstr(strtemp,"/");
  if (pos > 0) 
  {
    strncpy(m_env.pass,pos+1,30); pos[0]=0;
  }

  // username
  strncpy(m_env.user,strtemp,30); 
}


// �����ַ���������ͻ��˵��ַ��������ݿ�Ĳ�һ�£��ͻ�������롣
void connection::character(char *charset)
{
  // UNIXƽ̨�ǲ���setenv����
  setenv("NLS_LANG",charset,1);

  // windows�ǲ���putenv������
  /*
  char str[100];
  memset(str,0,sizeof(str));
  _snprintf(str,50,"NLS_LANG=%s",charset);
  putenv(str);
  */
}

int connection::connecttodb(char *connstr,char *charset,int autocommitopt)
{
  // ��������������ݿ⣬�Ͳ�������
  // ���ԣ�������������ݿ⣬������ʾ�ĵ���disconnect()�������������
  if (m_state == 1) return 0;

  // �����ַ���
  character(charset);

  // ���������ֶε������ʽ
  
  // UNIXƽ̨�ǲ���setenv����
  // setenv("NLS_DATE_FORMAT","yyyy-mm-dd hh24:mi:ss",1);
  
  // windows�ǲ���putenv������
  // putenv("NLS_DATE_FORMAT=yyyy-mm-dd hh24:mi:ss");
  
  
  // ��connstr�н���username,password,tnsname
  setdbopt(connstr);

  memset(&m_cda,0,sizeof(m_cda));

  // ��ʼ������
  int oci_ret = oci_init(&m_env);

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO )
  {
    oci_close(&m_env); m_cda.rc=-1; strncpy(m_cda.message,"initialize oracle call interface failed.\n",128); return -1;
  }

  // �����������¼���ݿ�
  oci_ret = oci_context_create(&m_env,&m_cxt);

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO )
  {
    oci_close(&m_env); m_cda.rc=1017; strncpy(m_cda.message,"ORA-01017: invalid username/password,logon denied.\n",128); return -1;
  }

  m_state = 1;

  m_autocommitopt=autocommitopt;

  return 0;
}

int connection::disconnect()
{
  memset(&m_cda,0,sizeof(m_cda));

  if (m_state == 0) 
  { 
    m_cda.rc=-1; strncpy(m_cda.message,"database not open.",128); return -1;
  }

  rollback();

  oci_context_close(&m_cxt);

  oci_close(&m_env);

  m_state = 0;    

  return 0;
}

int connection::rollback()
{ 
  memset(&m_cda,0,sizeof(m_cda));

  if (m_state == 0) 
  { 
    m_cda.rc=-1; strncpy(m_cda.message,"database not open.",128); return -1;
  }

  int oci_ret = OCITransRollback( m_cxt.svchp, m_cxt.errhp, OCI_DEFAULT ); 

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO )
  {
    err_report(); return m_cda.rc;
  }

  return 0;    
}

int connection::commit()
{ 
  memset(&m_cda,0,sizeof(m_cda));

  if (m_state == 0) 
  { 
    m_cda.rc=-1; strncpy(m_cda.message,"database not open.",128); return -1;
  }

  int oci_ret = OCITransCommit( m_cxt.svchp, m_cxt.errhp, OCI_DEFAULT );

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO )
  {
    err_report(); return m_cda.rc;
  }

  return 0;
}

int connection::execute(const char *fmt,...) 
{
  memset(m_sql,0,sizeof(m_sql));

  va_list ap;
  va_start(ap,fmt);
  vsnprintf(m_sql,10240,fmt,ap);
  va_end(ap);

  sqlstatement stmt(this);

  return stmt.execute(m_sql);
}

void connection::err_report()
{
  if (m_state == 0) 
  { 
    m_cda.rc=-1; strncpy(m_cda.message,"database not open.",128); return;
  }

  memset(&m_cda,0,sizeof(m_cda));

  m_cda.rc=-1;
  strncpy(m_cda.message,"call err_report failed.",128);

  if (m_cxt.errhp != NULL)
  {
    if (OCIErrorGet(m_cxt.errhp,1,NULL,&m_cda.rc,(OraText*)m_cda.message,sizeof(m_cda.message),OCI_HTYPE_ERROR) == OCI_NO_DATA)
    {
      // �����ȡ����������Ϣ���ͷ�����ȷ��
      memset(&m_cda,0,sizeof(m_cda)); return;
    }
  }
}

sqlstatement::sqlstatement()
{
  m_state=0; 

  memset(&m_handle,0,sizeof(m_handle));

  memset(&m_cda,0,sizeof(m_cda));

  memset(m_sql,0,sizeof(m_sql));

  m_cda.rc=-1;
  strncpy(m_cda.message,"sqlstatement not connect to connection.\n",128);

  m_lob=0;
}

sqlstatement::sqlstatement(connection *conn)
{
  sqlstatement();

  connect(conn);
}

sqlstatement::~sqlstatement()
{
  disconnect();
}

int sqlstatement::connect(connection *conn)
{
  // ע�⣬һ��sqlstatement�ڳ�����ֻ����һ��connection�������������connection
  // ���ԣ�ֻҪ�������Ѵ򿪣��Ͳ������ٴδ򿪣�ֱ�ӷ��سɹ�
  if ( m_state == 1 ) return 0;

  memset(&m_cda,0,sizeof(m_cda));

  m_conn=conn;

  // ������ݿ��������ָ��Ϊ�գ�ֱ�ӷ���ʧ��
  if (m_conn == 0) 
  {
    m_cda.rc=-1; strncpy(m_cda.message,"database not open.\n",128); return -1;
  }

  // ������ݿ�û�����Ӻã�ֱ�ӷ���ʧ��
  if (m_conn->m_state == 0) 
  {
    m_cda.rc=-1; strncpy(m_cda.message,"database not open.\n",128); return -1;
  }
    
  m_cda.rc = oci_stmt_create(&m_conn->m_cxt,&m_handle);

  if ( m_cda.rc != OCI_SUCCESS && m_cda.rc != OCI_SUCCESS_WITH_INFO )
  {
    err_report(); return m_cda.rc;
  }

  m_state = 1;  // ���ɹ���

  m_autocommitopt=m_conn->m_autocommitopt;

  m_cda.rc = OCI_SUCCESS; 

  return 0;
}

int sqlstatement::disconnect()
{
  if (m_state == 0) return 0;

  memset(&m_cda,0,sizeof(m_cda));

  freelob();

  m_cda.rc = oci_stmt_close(&m_handle);

  m_state=0;

  memset(&m_handle,0,sizeof(m_handle));

  memset(&m_cda,0,sizeof(m_cda));

  memset(m_sql,0,sizeof(m_sql));

  m_cda.rc=-1;
  strncpy(m_cda.message,"cursor not open.",128);

  return 0;
}

// ���ַ����е�Сд��ĸת���ɴ�д�����Բ�����ĸ���ַ���
// �������ֻ��prepare�������õ���
void OR__ToUpper(char *str)
{
  if (str == 0) return;

  if (strlen(str) == 0) return;

  int istrlen=strlen(str);

  for (int ii=0;ii<istrlen;ii++)
  {
    if ( (str[ii] >= 'a') && (str[ii] <= 'z') ) str[ii]=str[ii] - 32;
  }
}

// ɾ���ַ�����ߵĿո�
// �������ֻ��prepare�������õ���
void OR__DeleteLChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;

  char strTemp[strlen(str)+1];

  int iTemp=0;

  memset(strTemp,0,sizeof(strTemp));
  strcpy(strTemp,str);

  while ( strTemp[iTemp] == chr )  iTemp++;

  memset(str,0,strlen(str)+1);

  strcpy(str,strTemp+iTemp);

  return;
}

// ���µ�OCI�����У���SQL����д���ʱ��OCIStmtPrepare���ص���0������ʧ��
// ���ԣ�����Ա�ڳ�����һ�㲻�ش���prepare�Ľ��
int sqlstatement::prepare(const char *fmt,...)
{ 
  memset(&m_cda,0,sizeof(m_cda));

  if (m_state == 0) 
  {
    m_cda.rc=-1; strncpy(m_cda.message,"cursor not open.\n",128); return -1;
  }

  memset(m_sql,0,sizeof(m_sql));

  va_list ap;
  va_start(ap,fmt);
  vsnprintf(m_sql,10240,fmt,ap);
  va_end(ap);

  int oci_ret = OCIStmtPrepare(m_handle.smthp,m_handle.errhp,(OraText*)m_sql,strlen(m_sql),OCI_NTV_SYNTAX,OCI_DEFAULT);

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO )
  {
    err_report(); return m_cda.rc;
  }

  // �ж��Ƿ��ǲ�ѯ��䣬����ǣ���m_sqltype��Ϊ0�����������Ϊ1��
  m_sqltype=1;

  // �Ӵ�ִ�е�SQL����н�ȡ30���ַ����������"select"��ͷ������Ϊ�ǲ�ѯ��䡣
  char strtemp[31]; memset(strtemp,0,sizeof(strtemp)); strncpy(strtemp,m_sql,30);
  OR__ToUpper(strtemp); OR__DeleteLChar(strtemp,' ');
  if (strncmp(strtemp,"SELECT",6)==0)  m_sqltype=0; 

  m_cda.rc = OCI_SUCCESS; 

  return 0;
}

int sqlstatement::bindin(unsigned int position,int *value)
{
  return OCIBindByPos(m_handle.smthp, &m_handle.bindhp, m_handle.errhp, (ub4)position, value, sizeof(int),
                        SQLT_INT, NULL, NULL,NULL,0, NULL, OCI_DEFAULT);  
}

int sqlstatement::bindin(unsigned int position,long *value)
{
  return OCIBindByPos(m_handle.smthp, &m_handle.bindhp, m_handle.errhp, (ub4)position, value, sizeof(long),
                        SQLT_INT, NULL, NULL,NULL,0, NULL, OCI_DEFAULT);  
}

int sqlstatement::bindin(unsigned int position,unsigned int *value)
{
  return OCIBindByPos(m_handle.smthp, &m_handle.bindhp,m_handle.errhp,(ub4)position,value,sizeof(unsigned int),
                        SQLT_INT, NULL, NULL,NULL,0, NULL, OCI_DEFAULT);  
}

int sqlstatement::bindin(unsigned int position,unsigned long *value)
{
  return OCIBindByPos(m_handle.smthp,&m_handle.bindhp,m_handle.errhp,(ub4)position,value,sizeof(unsigned long),
                        SQLT_INT, NULL, NULL,NULL,0, NULL, OCI_DEFAULT);  
}

int sqlstatement::bindin(unsigned int position,char *value,unsigned int len)
{
  return OCIBindByPos(m_handle.smthp, &m_handle.bindhp, m_handle.errhp, (ub4)position, value, len+1,
                        SQLT_STR, NULL, NULL,NULL,0, NULL, OCI_DEFAULT);  
}

int sqlstatement::bindin(unsigned int position,float *value)
{
  return OCIBindByPos(m_handle.smthp, &m_handle.bindhp, m_handle.errhp, (ub4)position, value, sizeof(float),
                        SQLT_FLT, NULL, NULL,NULL,0, NULL, OCI_DEFAULT);
}

int sqlstatement::bindin(unsigned int position,double *value)
{
  return OCIBindByPos(m_handle.smthp, &m_handle.bindhp, m_handle.errhp, (ub4)position, value, sizeof(double),
                        SQLT_FLT, NULL, NULL,NULL,0, NULL, OCI_DEFAULT);
}

int sqlstatement::bindout(unsigned int position,int *value)
{
  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, position, value, sizeof(int), 
                          SQLT_INT, NULL, NULL, NULL, OCI_DEFAULT );
}

int sqlstatement::bindout(unsigned int position,long *value)
{
  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, position, value, sizeof(long), 
                          SQLT_INT, NULL, NULL, NULL, OCI_DEFAULT );
}

int sqlstatement::bindout(unsigned int position,unsigned int *value)
{
  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, position, value, sizeof(unsigned int), 
                          SQLT_INT, NULL, NULL, NULL, OCI_DEFAULT );
}
int sqlstatement::bindout(unsigned int position,unsigned long *value)
{
  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, position, value, sizeof(unsigned long), 
                          SQLT_INT, NULL, NULL, NULL, OCI_DEFAULT );
}

int sqlstatement::bindout(unsigned int position,float *value)
{
  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, position, value, sizeof(float), 
                          SQLT_FLT, NULL, NULL, NULL, OCI_DEFAULT );
}

int sqlstatement::bindout(unsigned int position,double *value)
{
  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, position, value, sizeof(double), 
                          SQLT_FLT, NULL, NULL, NULL, OCI_DEFAULT );
}

int sqlstatement::bindout(unsigned int position,char *value,unsigned int len)
{
  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, position, value, len+1, 
                          SQLT_STR, NULL, NULL, NULL, OCI_DEFAULT );
}

int sqlstatement::bindblob()
{
  alloclob();

  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, 1,(dvoid *) &m_lob,-1, 
                          SQLT_BLOB, NULL, NULL, NULL, OCI_DEFAULT );
}

int sqlstatement::bindclob()
{
  alloclob();

  return OCIDefineByPos(m_handle.smthp, &m_handle.defhp, m_handle.errhp, 1,(dvoid *) &m_lob,-1, 
                          SQLT_CLOB, NULL, NULL, NULL, OCI_DEFAULT );
}

int sqlstatement::execute() 
{
  memset(&m_cda,0,sizeof(m_cda));

  if (m_state == 0) 
  {
    m_cda.rc=-1; strncpy(m_cda.message,"cursor not open.\n",128); return -1;
  }

  ub4 mode=OCI_DEFAULT;

  if (m_sqltype==1 && m_autocommitopt==1) mode=OCI_COMMIT_ON_SUCCESS;

  int oci_ret = OCIStmtExecute(m_handle.svchp,m_handle.smthp,m_handle.errhp,m_sqltype,0,NULL,NULL,mode);

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO )
  {
    // �����˴�����ѯû�н��
    err_report(); return m_cda.rc;
  }

  // ������ǲ�ѯ��䣬�ͻ�ȡӰ���¼������
  if (m_sqltype == 1)
  {
    OCIAttrGet((CONST dvoid *)m_handle.smthp,OCI_HTYPE_STMT,(dvoid *)&m_cda.rpc, (ub4 *)0,
                OCI_ATTR_ROW_COUNT, m_handle.errhp);
    m_conn->m_cda.rpc=m_cda.rpc;
  }

  return 0;
}

int sqlstatement::execute(const char *fmt,...) 
{
  char strtmpsql[10241];
  memset(strtmpsql,0,sizeof(strtmpsql));

  va_list ap;
  va_start(ap,fmt);
  vsnprintf(strtmpsql,10240,fmt,ap);
  va_end(ap);

  if (prepare(strtmpsql) != 0) return m_cda.rc;

  return execute();
}

int sqlstatement::next() 
{ 
  // ע�⣬�ڸú����У�����������memset(&m_cda,0,sizeof(m_cda))����������m_cda.rpc������
  if (m_state == 0) 
  {
    m_cda.rc=-1; strncpy(m_cda.message,"cursor not open.\n",128); return -1;
  }

  // ������δִ�гɹ���ֱ�ӷ���ʧ�ܡ�
  if (m_cda.rc != 0) return m_cda.rc;

  // �ж��Ƿ��ǲ�ѯ��䣬������ǣ�ֱ�ӷ��ش���
  if (m_sqltype != 0)
  {
    m_cda.rc=-1; strncpy(m_cda.message,"no recordset found.\n",128); return -1;
  }

  int oci_ret = OCIStmtFetch(m_handle.smthp,m_handle.errhp,1,OCI_FETCH_NEXT,OCI_DEFAULT);

  if ( oci_ret != OCI_SUCCESS && oci_ret != OCI_SUCCESS_WITH_INFO )
  {
    err_report(); 

    // ֻ�е�m_cda.rc����1405��1406��ʱ�򣬲ŷ��ش���1405��1406�����
    // ���ң����ش����ʱ�򣬲�Ҫ�����m_cda.rpc
    if (m_cda.rc != 1405 && m_cda.rc != 1406) 
    {
      // ������ش��벻��0,1403,1405,1406���ͱ���next�����������쳣
      // ����ر����ݿ����ӣ��ó�������˳���
      if ( (m_cda.rc!=0) && (m_cda.rc!=1403) && (m_cda.rc!=1405) && (m_cda.rc!=1406) ) m_conn->disconnect();

      return m_cda.rc;
    }
  }

  // ��ȡ������ɹ�

  // ������ص���1405��1406���Ͱ���ǿ��Ϊ0
  if (m_cda.rc == 1405 || m_cda.rc == 1406) m_cda.rc=0;

  // ��ȡӰ���¼��������
  OCIAttrGet((CONST dvoid *)m_handle.smthp,OCI_HTYPE_STMT,(dvoid *)&m_cda.rpc, (ub4 *)0,
              OCI_ATTR_ROW_COUNT, m_handle.errhp);

  m_conn->m_cda.rpc=m_cda.rpc;

  return 0;
}

void sqlstatement::err_report()
{
  // ע�⣬�ڸú����У�����������memset(&m_cda,0,sizeof(m_cda))����������m_cda.rpc������
  if (m_state == 0) 
  {
    m_cda.rc=-1; strncpy(m_cda.message,"cursor not open.\n",128); return;
  }

  m_cda.rc=-1;
  strncpy(m_cda.message,"call sqlstatement::err_report() failed.\n",128);

  if (m_handle.errhp != NULL)
  {
    if (OCIErrorGet(m_handle.errhp,1,NULL,&m_cda.rc,(OraText*)m_cda.message,sizeof(m_cda.message),OCI_HTYPE_ERROR) == OCI_NO_DATA)
    {
      // ���û�л�ȡ���κδ�����Ϣ���ͷ�����ȷ��
      // ���������memset���m_cda����Ϊ���û���κδ���m_cda.rpc��next�л����¸�ֵ
      m_cda.rc=0; memset(m_cda.message,0,sizeof(m_cda.message)); return;
    }
  }

  m_conn->err_report();
}

int sqlstatement::alloclob()
{
  if (m_lob!=0) return 0;

  return OCIDescriptorAlloc((dvoid *)m_handle.envhp,(dvoid **)&m_lob,(ub4)OCI_DTYPE_LOB,(size_t)0,(dvoid **)0);
}

void sqlstatement::freelob()
{
  if (m_lob!=0) OCIDescriptorFree((dvoid *)m_lob, (ub4)OCI_DTYPE_LOB);

  m_lob=0;
}


ub4 file_length(FILE *fp)
{
  fseek(fp, 0, SEEK_END);
  return (ub4) (ftell(fp));
}

int  sqlstatement::filetolob(char *filename)
{
  FILE *fp=0;

  if ( (fp = fopen(filename,"rb")) == 0) 
  {
    m_cda.rc=-1; strncpy(m_cda.message,"fopen failed",128); return -1;
  }
  
  int iret = filetolob(fp);

  fclose(fp);

  return iret;
}

/* ����CLOB��BLOB����ʱ���������Ĵ�С��һ�㲻��Ҫ�޸ġ� */
#define LOBMAXBUFLEN  10240

int sqlstatement::filetolob(FILE *fp)
{
  ub4   offset = 1;
  ub4   loblen = 0;
  ub1   bufp[LOBMAXBUFLEN+1];
  ub4   amtp;
  ub1   piece;
  sword retval;
  ub4   nbytes;
  ub4   remainder;

  ub4  filelen = file_length(fp);

  if (filelen == 0) return 0;

  amtp = filelen;

  remainder = filelen;

  (void) OCILobGetLength(m_handle.svchp, m_handle.errhp, m_lob, &loblen);

  (void) fseek(fp, 0, 0);

  if (filelen > LOBMAXBUFLEN)
  {
    nbytes = LOBMAXBUFLEN;
  }
  else
  {
    nbytes = filelen;
  }

  memset(bufp,0,sizeof(bufp));

  if (fread((void *)bufp, (size_t)nbytes, 1, fp) != 1)
  {
    m_cda.rc=-1; strncpy(m_cda.message,"fread failed",128); return -1;
  }

  remainder -= nbytes;

  if (remainder == 0)       
  {
    // exactly one piece in the file
    // Only one piece, no need for stream write
    if ( (retval = OCILobWrite(m_handle.svchp, m_handle.errhp, m_lob, &amtp, offset, (dvoid *) bufp,
                            (ub4) nbytes, OCI_ONE_PIECE, (dvoid *)0,
                            (sb4 (*)(dvoid *, dvoid *, ub4 *, ub1 *)) 0,
                            (ub2) 0, (ub1) SQLCS_IMPLICIT)) != OCI_SUCCESS)
    {
      err_report(); return m_cda.rc;
    }
  }
  else
  {
    // more than one piece
    if (OCILobWrite(m_handle.svchp, m_handle.errhp, m_lob, &amtp, offset, (dvoid *) bufp,
                    (ub4) LOBMAXBUFLEN, OCI_FIRST_PIECE, (dvoid *)0,
                    (sb4 (*)(dvoid *, dvoid *, ub4 *, ub1 *)) 0,
                    (ub2) 0, (ub1) SQLCS_IMPLICIT) != OCI_NEED_DATA)
    {
      err_report(); return m_cda.rc;
    }

    piece = OCI_NEXT_PIECE;

    do
    {
      if (remainder > LOBMAXBUFLEN)
      {
        nbytes = LOBMAXBUFLEN;
      }
      else
      {
        nbytes = remainder; piece = OCI_LAST_PIECE;
      }

       memset(bufp,0,sizeof(bufp));

      if (fread((void *)bufp, (size_t)nbytes, 1, fp) != 1)
      {
        m_cda.rc=-1; strncpy(m_cda.message,"fread failed",128); return -1;
      }

      retval = OCILobWrite(m_handle.svchp, m_handle.errhp, m_lob, &amtp, offset, (dvoid *) bufp,
                          (ub4) nbytes, piece, (dvoid *)0,
                          (sb4 (*)(dvoid *, dvoid *, ub4 *, ub1 *)) 0,
                          (ub2) 0, (ub1) SQLCS_IMPLICIT);
      remainder -= nbytes;

    } while (retval == OCI_NEED_DATA && !feof(fp));
  }

  if (retval != OCI_SUCCESS)
  {
    err_report(); return m_cda.rc;
  }

  (void) OCILobGetLength(m_handle.svchp, m_handle.errhp, m_lob, &loblen);

  return 0;
}

// ��LOB�ֶ��е�����д���ļ�
int  sqlstatement::lobtofile(char *filename)
{
  FILE *fp=0;

  if ( (fp = fopen(filename,"wb")) == 0)
  {
    if ( (fp = fopen(filename,"wb")) == 0)
    {
      m_cda.rc=-1; strncpy(m_cda.message,"fopen failed",128); return -1;
    }
  }

  fseek(fp, 0, 0);

  int iret = lobtofile(fp);

  fclose(fp);

  // ����ļ������ɵĹ����з����˴��󣬾�ɾ�����ļ�����Ϊ����һ�����������ļ�
  if (iret != 0) remove(filename); 

  return iret;
}

int sqlstatement::lobtofile(FILE *fp)
{
  ub4   offset = 1;
  ub4   loblen = 0;
  ub1   bufp[LOBMAXBUFLEN+1];
  ub4   amtp = 0;
  sword retval;

  OCILobGetLength(m_handle.svchp, m_handle.errhp, m_lob, &loblen);

  if (loblen == 0) return 0;

  amtp = loblen;

  memset(bufp,0,sizeof(bufp));

  retval = OCILobRead(m_handle.svchp, m_handle.errhp, m_lob, &amtp, offset, (dvoid *) bufp,
                     (loblen < LOBMAXBUFLEN ? loblen : LOBMAXBUFLEN), (dvoid *)0,
                     (sb4 (*)(dvoid *, const dvoid *, ub4, ub1)) 0,
                     (ub2) 0, (ub1) SQLCS_IMPLICIT);

  switch (retval)
  {
    case OCI_SUCCESS:             /* only one piece */
      fwrite((void *)bufp, (size_t)amtp, 1, fp);
      break;

    case OCI_NEED_DATA:           /* there are 2 or more pieces */
      fwrite((void *)bufp, amtp, 1, fp); 

      while (1)
      {
        amtp = 0;
        memset(bufp,0,sizeof(bufp));

        retval = OCILobRead(m_handle.svchp, m_handle.errhp, m_lob, &amtp, offset, (dvoid *) bufp,
                           (ub4) LOBMAXBUFLEN, (dvoid *)0,
                           (sb4 (*)(dvoid *, const dvoid *, ub4, ub1)) 0,
                           (ub2) 0, (ub1) SQLCS_IMPLICIT);

        fwrite((void *)bufp, (size_t)amtp, 1, fp);

        if (retval != OCI_NEED_DATA) break;
      } 

      break;

    case OCI_ERROR:
      err_report(); 

      return m_cda.rc;
  }

  return 0;
}

