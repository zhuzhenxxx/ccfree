
#include "_mysql.h"

connection::connection()
{ 
  m_conn = NULL;

  m_state = 0; 

  memset(&m_env,0,sizeof(LOGINENV));

  memset(&m_cda,0,sizeof(m_cda));

  m_cda.rc=-1;
  strncpy(m_cda.message,"database not open.",128);

  // ���ݿ�����
  memset(m_dbtype,0,sizeof(m_dbtype));
  strcpy(m_dbtype,"mysql");
}

connection::~connection()
{
  disconnect();
}

// ��connstr�н���username,password,tnsname
// "120.77.115.3","szidc","SZmb1601","lxqx",3306
void connection::setdbopt(char *connstr)
{
  memset(&m_env,0,sizeof(LOGINENV));

  char *bpos,*epos;

  bpos=epos=0;

  // ip
  bpos=connstr;
  epos=strstr(bpos,",");
  if (epos > 0) 
  {
    strncpy(m_env.ip,bpos,epos-bpos); 
  }else return;

  // user
  bpos=epos+1;
  epos=0;
  epos=strstr(bpos,",");
  if (epos > 0) 
  {
    strncpy(m_env.user,bpos,epos-bpos); 
  }else return;

  // pass
  bpos=epos+1;
  epos=0;
  epos=strstr(bpos,",");
  if (epos > 0) 
  {
    strncpy(m_env.pass,bpos,epos-bpos); 
  }else return;

  // dbname
  bpos=epos+1;
  epos=0;
  epos=strstr(bpos,",");
  if (epos > 0) 
  {
    strncpy(m_env.dbname,bpos,epos-bpos); 
  }else return;

  // port
  m_env.port=atoi(epos+1);
}

int connection::connecttodb(char *connstr,char *charset,unsigned int autocommitopt)
{
  // ��������������ݿ⣬�Ͳ�������
  // ���ԣ�������������ݿ⣬������ʾ�ĵ���disconnect()�������������
  if (m_state == 1) return 0;

  // ��connstr�н���username,password,tnsname
  setdbopt(connstr);

  memset(&m_cda,0,sizeof(m_cda));

  if ( (m_conn = mysql_init(NULL)) == NULL )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"initialize mysql failed.\n",128); return -1;
  }

  if ( mysql_real_connect(m_conn,m_env.ip,m_env.user,m_env.pass,m_env.dbname,m_env.port, NULL, 0 ) == NULL )
  {
    m_cda.rc=mysql_errno(m_conn); strncpy(m_cda.message,mysql_error(m_conn),2000); mysql_close(m_conn); m_conn=NULL;  return -1;
  }

  // ��������ģʽ��0-�ر��Զ��ύ��1-�����Զ��ύ
  m_autocommitopt=autocommitopt;

  if ( mysql_autocommit(m_conn, m_autocommitopt ) != 0 )
  {
    m_cda.rc=mysql_errno(m_conn); strncpy(m_cda.message,mysql_error(m_conn),2000); mysql_close(m_conn); m_conn=NULL;  return -1;
  }

  // �����ַ���
  character(charset);

  m_state = 1;

  return 0;
}

// �����ַ�����Ҫ�����ݿ��һ�£��������Ļ��������
void connection::character(char *charset)
{
  mysql_set_character_set(m_conn,charset);

  return;
}

int connection::disconnect()
{
  memset(&m_cda,0,sizeof(m_cda));

  if (m_state == 0) 
  { 
    m_cda.rc=-1; strncpy(m_cda.message,"database not open.",128); return -1;
  }

  rollback();

  mysql_close(m_conn); 

  m_conn=NULL;

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

  if ( mysql_rollback(m_conn ) != 0 )
  {
    m_cda.rc=mysql_errno(m_conn); strncpy(m_cda.message,mysql_error(m_conn),2000); mysql_close(m_conn); m_conn=NULL;  return -1;
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

  if ( mysql_commit(m_conn ) != 0 )
  {
    m_cda.rc=mysql_errno(m_conn); strncpy(m_cda.message,mysql_error(m_conn),2000); mysql_close(m_conn); m_conn=NULL;  return -1;
  }

  return 0;
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

  m_cda.rc=mysql_errno(m_conn);

  strncpy(m_cda.message,mysql_error(m_conn),2000);

  return;
}

sqlstatement::sqlstatement()
{
  initial();
}

void sqlstatement::initial()
{
  m_state=0;

  m_handle=NULL;

  memset(&m_cda,0,sizeof(m_cda));

  memset(m_sql,0,sizeof(m_sql));

  m_cda.rc=-1;
  strncpy(m_cda.message,"sqlstatement not connect to connection.\n",128);
}

sqlstatement::sqlstatement(connection *conn)
{
  initial();

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

  if ( (m_handle=mysql_stmt_init(m_conn->m_conn)) == NULL)
  {
    err_report(); return m_cda.rc;
  }

  m_state = 1;  // ���ɹ���

  m_autocommitopt=m_conn->m_autocommitopt;

  return 0;
}

int sqlstatement::disconnect()
{
  if (m_state == 0) return 0;

  memset(&m_cda,0,sizeof(m_cda));

  mysql_stmt_close(m_handle);

  m_state=0;

  m_handle=NULL;

  memset(&m_cda,0,sizeof(m_cda));

  memset(m_sql,0,sizeof(m_sql));

  m_cda.rc=-1;
  strncpy(m_cda.message,"cursor not open.",128);

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

void sqlstatement::err_report()
{
  // ע�⣬�ڸú����У�����������memset(&m_cda,0,sizeof(m_cda))����������m_cda.rpc������
  if (m_state == 0)
  {
    m_cda.rc=-1; strncpy(m_cda.message,"cursor not open.\n",128); return;
  }
  
  memset(&m_conn->m_cda,0,sizeof(m_conn->m_cda));

  m_cda.rc=-1;
  strncpy(m_cda.message,"call err_report() failed.\n",128);

  m_cda.rc=mysql_stmt_errno(m_handle);

  snprintf(m_cda.message,2000,"%d,%s",m_cda.rc,mysql_stmt_error(m_handle));

  m_conn->err_report();

  return;
}

// ���ַ����е�Сд��ĸת���ɴ�д�����Բ�����ĸ���ַ���
// �������ֻ��prepare�������õ���
void MY__ToUpper(char *str)
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
void MY__DeleteLChar(char *str,const char chr)
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

// �ַ����滻����
// ���ַ���str�У���������ַ���str1�����滻Ϊ�ַ���str2��
// �������ֻ��prepare�������õ���
void MY__UpdateStr(char *str,const char *str1,const char *str2,bool bloop)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;
  if ( (str1 == 0) || (str2 == 0) ) return;

  // ���bloopΪtrue����str2�а�����str1�����ݣ�ֱ�ӷ��أ���Ϊ�������ѭ�������յ����ڴ������
  if ( (bloop==true) && (strstr(str2,str1)>0) ) return;

  // �����ܷ������Ŀռ䣬�����п��ܳ����ڴ���������������Ż���string��
  int ilen=strlen(str)*10;
  if (ilen<1000) ilen=1000;

  char strTemp[ilen];

  char *strStart=str;

  char *strPos=0;

  while (true)
  {
    if (bloop == true)
    {
      strPos=strstr(str,str1);
    }
    else
    {
      strPos=strstr(strStart,str1);
    }

    if (strPos == 0) break;

    memset(strTemp,0,sizeof(strTemp));
    strncpy(strTemp,str,strPos-str);
    strcat(strTemp,str2);
    strcat(strTemp,strPos+strlen(str1));
    strcpy(str,strTemp);

    strStart=strPos+strlen(str2);
  }
}

  
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

  int ilen=strlen(m_sql);

  // Ϊ�˺�oracle���ݣ���:1,:2,:3...���滻��?
  for (int ii=0;ii<ilen;ii++)
  {
    if ( (m_sql[ii]==':') && (isdigit(m_sql[ii+1])!=0) )
    {
      m_sql[ii]='?';
      m_sql[ii+1]=' ';
      if (isdigit(m_sql[ii+2])!=0) m_sql[ii+2]=' ';
      if (isdigit(m_sql[ii+3])!=0) m_sql[ii+3]=' ';
    }
  }

  // Ϊ�˺�oracle����
  // ��to_date���Ƴ�str_to_date��
  // ��to_char�滻��date_format��
  if (strstr(m_sql,"str_to_date")==0) MY__UpdateStr(m_sql,"to_date","str_to_date",false);
  MY__UpdateStr(m_sql,"to_char","date_format",false);
  MY__UpdateStr(m_sql,"yyyy-mm-dd hh24:mi:ss","%Y-%m-%d %h:%i:%s",false);
  MY__UpdateStr(m_sql,"yyyymmddhh24miss","%Y%m%d%h%i%s",false);
  // ��λ��������oracle��mysql�����ʱ���ʽ������������Ӵ��롣
  // һ��Ҫ�Ѹ�ʽһһ�г�����������"yyyy"�滻"%Y"����Ϊ��SQL���������ط�Ҳ���ܴ���"yyyy"��

  if (mysql_stmt_prepare(m_handle,m_sql,strlen(m_sql)) != 0)
  {
    err_report(); return m_cda.rc;
  }

  // �ж��Ƿ��ǲ�ѯ��䣬����ǣ���m_sqltype��Ϊ0�����������Ϊ1��
  m_sqltype=1;
  
  // �Ӵ�ִ�е�SQL����н�ȡ30���ַ����������"select"��ͷ������Ϊ�ǲ�ѯ��䡣
  char strtemp[31]; memset(strtemp,0,sizeof(strtemp)); strncpy(strtemp,m_sql,30);
  MY__ToUpper(strtemp); MY__DeleteLChar(strtemp,' ');
  if (strncmp(strtemp,"SELECT",6)==0)  m_sqltype=0;

  memset(params_in,0,sizeof(params_in));

  memset(params_out,0,sizeof(params_out));

  return 0;
}
  
int sqlstatement::bindin(unsigned int position,int *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->param_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_in[position-1].buffer_type = MYSQL_TYPE_LONG;
  params_in[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindin(unsigned int position,long *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->param_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_in[position-1].buffer_type = MYSQL_TYPE_LONGLONG;
  params_in[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindin(unsigned int position,unsigned int *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->param_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_in[position-1].buffer_type = MYSQL_TYPE_LONG;
  params_in[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindin(unsigned int position,unsigned long *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->param_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_in[position-1].buffer_type = MYSQL_TYPE_LONGLONG;
  params_in[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindin(unsigned int position,char *value,unsigned int len)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->param_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_in[position-1].buffer_type = MYSQL_TYPE_VAR_STRING;
  params_in[position-1].buffer = value;
  params_in[position-1].buffer_length = len;

  return 0;
}

int sqlstatement::bindin(unsigned int position,float *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->param_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_in[position-1].buffer_type = MYSQL_TYPE_FLOAT;
  params_in[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindin(unsigned int position,double *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->param_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_in[position-1].buffer_type = MYSQL_TYPE_DOUBLE;
  params_in[position-1].buffer = value;

  return 0;
}

///////////////////
int sqlstatement::bindout(unsigned int position,int *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->field_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_out[position-1].buffer_type = MYSQL_TYPE_LONG;
  params_out[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindout(unsigned int position,long *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->field_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_out[position-1].buffer_type = MYSQL_TYPE_LONGLONG;
  params_out[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindout(unsigned int position,unsigned int *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->field_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_out[position-1].buffer_type = MYSQL_TYPE_LONG;
  params_out[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindout(unsigned int position,unsigned long *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->field_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_out[position-1].buffer_type = MYSQL_TYPE_LONGLONG;
  params_out[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindout(unsigned int position,char *value,unsigned int len)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->field_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_out[position-1].buffer_type = MYSQL_TYPE_VAR_STRING;
  params_out[position-1].buffer = value;
  params_out[position-1].buffer_length = len;

  return 0;
}

int sqlstatement::bindout(unsigned int position,float *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->field_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_out[position-1].buffer_type = MYSQL_TYPE_FLOAT;
  params_out[position-1].buffer = value;

  return 0;
}

int sqlstatement::bindout(unsigned int position,double *value)
{
  if ( (position<1) || (position>=MAXPARAMS) || (position>m_handle->field_count) )
  {
    m_cda.rc=-1; strncpy(m_cda.message,"array bound.",128);
  }

  params_out[position-1].buffer_type = MYSQL_TYPE_DOUBLE;
  params_out[position-1].buffer = value;

  return 0;
}

int sqlstatement::execute()
{
  memset(&m_cda,0,sizeof(m_cda));

  if (m_state == 0)
  {
    m_cda.rc=-1; strncpy(m_cda.message,"cursor not open.\n",128); return -1;
  }

  if ( (m_handle->param_count>0) && (m_handle->bind_param_done == 0))
  {
    if (mysql_stmt_bind_param(m_handle,params_in) != 0)
    {
      err_report(); return m_cda.rc;
    }
  }


  if ( (m_handle->field_count>0) && (m_handle->bind_result_done == 0) )
  {
    if (mysql_stmt_bind_result(m_handle,params_out) != 0)
    {
      err_report(); return m_cda.rc;
    }
  }

  if (mysql_stmt_execute(m_handle) != 0)
  {
    err_report(); return m_cda.rc;
  }
  
  // ������ǲ�ѯ��䣬�ͻ�ȡӰ���¼������
  if (m_sqltype == 1) 
  { 
    m_cda.rpc=m_handle->affected_rows;
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
  
  int ret=mysql_stmt_fetch(m_handle);

  if (ret==0) 
  { 
    m_cda.rpc++; return 0; 
  }
 
  if (ret==1) 
  {
    err_report(); return m_cda.rc;
  }

  if (ret==MYSQL_NO_DATA) return MYSQL_NO_DATA;

  if (ret==MYSQL_DATA_TRUNCATED) 
  {
    m_cda.rpc++; return 0;
  }
  
  return 0;
}
