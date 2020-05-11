/****************************************************************************************/
/*   ��������_ftp.h���˳�����freecplus��ܵ�ftp�ͻ��˹��ߵ���������ļ���               */
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

#ifndef __FTP_H
#define __FTP_H

#include "_freecplus.h"
#include "ftplib.h"

class Cftp
{
public:
  netbuf *m_ftpconn;   // ftp���Ӿ����
  unsigned int m_size; // �ļ��Ĵ�С����λ���ֽڡ�
  char m_mtime[21];    // �ļ����޸�ʱ�䣬��ʽ��yyyymmddhh24miss��

  // ����������Ա�������ڴ��login������¼ʧ�ܵ�ԭ��
  bool m_connectfailed;    // ����ʧ�ܡ�
  bool m_loginfailed;      // ��¼ʧ�ܣ��û��������벻��ȷ����û�е�¼Ȩ�ޡ�
  bool m_optionfailed;     // ���ô���ģʽʧ�ܡ�

  Cftp();  // ��Ĺ��캯����
 ~Cftp();  // �������������

  void initdata();   // ��ʼ��m_size��m_mtime��Ա������

  // ��¼ftp��������
  // host��ftp������ip��ַ�Ͷ˿ڣ��м���":"�ָ�����"192.168.1.1:21"��
  // username����¼ftp�������û�����
  // password����¼ftp�����������롣
  // imode������ģʽ��FTPLIB_PASSIVE�Ǳ���ģʽ��FTPLIB_PORT������ģʽ��ȱʡ�Ǳ���ģʽ��
  bool login(const char *host,const char *username,const char *password,const int imode=FTPLIB_PASSIVE);
  
  // ע����
  bool logout();

  // ��ȡftp���������ļ���ʱ�䡣
  // remotefilename������ȡ���ļ�����
  // ����ֵ��false-ʧ�ܣ�true-�ɹ�����ȡ�����ļ�ʱ������m_mtime��Ա�����С�
  bool mtime(const char *remotefilename);

  // ��ȡftp���������ļ��Ĵ�С��
  // remotefilename������ȡ���ļ�����
  // ����ֵ��false-ʧ�ܣ�true-�ɹ�����ȡ�����ļ���С�����m_size��Ա�����С�
  bool size(const char *remotefilename);

  // �ı�ftp�������ĵ�ǰ����Ŀ¼��
  // remotedir��ftp�������ϵ�Ŀ¼����
  // ����ֵ��true-�ɹ���false-ʧ�ܡ�
  bool chdir(const char *remotedir);

  // ��ftp�������ϴ���Ŀ¼��
  // remotedir��ftp�������ϴ�������Ŀ¼����
  // ����ֵ��true-�ɹ���false-ʧ�ܡ�
  bool mkdir(const char *remotedir);

  // ɾ��ftp�������ϵ�Ŀ¼��
  // remotedir��ftp�������ϴ�ɾ����Ŀ¼����
  // ����ֵ��true-�ɹ������Ȩ�޲��㡢Ŀ¼�����ڻ�Ŀ¼��Ϊ�ջ᷵��false��
  bool rmdir(const char *remotedir);

  // ����NLST�����г�ftp��������Ŀ¼���ļ�����
  // remotedir��ftp��������Ŀ¼����
  // listfilename�����ڱ���ӷ��������ص�Ŀ¼���ļ����б�
  // ����ֵ��true-�ɹ���false-ʧ�ܡ�
  // ע�⣺����г�����ftp��������ǰĿ¼��remotedir��"","*","."�����ԣ����ǣ����淶��ftp�����������в��
  bool nlist(const char *remotedir,const char *listfilename);

  // ��ftp�������ϻ�ȡ�ļ���
  // remotefilename������ȡftp�������ϵ��ļ�����
  // localfilename�����浽���ص��ļ�����
  // bCheckMTime���ļ�������ɺ��Ƿ�˶�Զ���ļ�����ǰ���ʱ�䣬��֤�ļ��������ԡ�
  // ����ֵ��true-�ɹ���false-ʧ�ܡ�
  // ע�⣺�ļ��ڴ���Ĺ����У�������ʱ�ļ������ķ���������localfilename���".tmp"���ڴ���
  // ��ɺ����ʽ��Ϊlocalfilename��
  bool get(const char *remotefilename,const char *localfilename,const bool bCheckMTime=true);

  // ��ftp�����������ļ���
  // localfilename�����ش����͵��ļ�����
  // remotefilename�����͵�ftp�������ϵ��ļ�����
  // bCheckSize���ļ�������ɺ��Ƿ�˶Ա����ļ���Զ���ļ��Ĵ�С����֤�ļ��������ԡ�
  // ����ֵ��true-�ɹ���false-ʧ�ܡ�
  // ע�⣺�ļ��ڴ���Ĺ����У�������ʱ�ļ������ķ���������remotefilename���".tmp"���ڴ���
  // ��ɺ����ʽ��Ϊremotefilename��
  bool put(const char *localfilename,const char *remotefilename,const bool bCheckSize=true);

  // ɾ��ftp�������ϵ��ļ���
  // remotefilename����ɾ����ftp�������ϵ��ļ�����
  // ����ֵ��true-�ɹ���false-ʧ�ܡ�
  bool ftpdelete(const char *remotefilename);

  // ������ftp�������ϵ��ļ���
  // srcremotefilename��ftp�������ϵ�ԭ�ļ�����
  // dstremotefilename��ftp�������ϵ�Ŀ���ļ�����
  // ����ֵ��true-�ɹ���false-ʧ�ܡ�
  bool ftprename(const char *srcremotefilename,const char *dstremotefilename);

  /* �����������������ⲻ�˾����ˣ����Բ����á� */
  // ����LIST�����г�ftp������Ŀ¼�е��ļ���
  // �����ͷ���ֵ��nlist������ͬ��
  bool dir(const char *remotedir,const char *listfilename);

  // ��ftp����������site���
  // command����������ݡ�
  // ����ֵ��true-�ɹ���false-ʧ�ܡ�
  bool site(const char *command);

  // ��ȡ������������Ϣ�����һ��(return a pointer to the last response received)��
  char *response();
};

#endif
